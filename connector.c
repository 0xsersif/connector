#include "connector.h"

Req *request(const char *dstip, const int dstport)
{
  Req *req;

  req = malloc(reqsize);
  if (!req) {
    perror("malloc");
    return NULL;
  }

  req->vn = 4;        // SOCKS version 4
  req->cd = 1;        // Connect command
  req->dstport = htons(dstport);  // Convert to network byte order
  req->dstip = inet_addr(dstip);  // Convert IP string to binary
  
  // Initialize userid to empty (null-terminated)
  memset(req->userid, 0, sizeof(req->userid));
  
  return req;
};
int main (int argc, char *argv[])
{
    char *host;
    int port, s;
    struct sockaddr_in sock;
    Req *req;
    Res response;
    ssize_t bytes_sent, bytes_received;

    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
        return -1;
    }

    host = argv[1];
    port = atoi(argv[2]);

    // Create socket
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0)
    {
        perror("socket");
        return -1;
    }

    // Setup proxy connection
    sock.sin_family = AF_INET;
    sock.sin_port = htons(PROXYPORT);
    sock.sin_addr.s_addr = inet_addr(PROXY);
 
    if (connect(s, (struct sockaddr *)&sock, sizeof(sock)) < 0)
    {
        perror("connect");
        close(s);
        return -1;
    }
    printf("Connected to SOCKS proxy at %s:%d\n", PROXY, PROXYPORT);

    // Create SOCKS4 request
    req = request(host, port);
    if (!req) {
        close(s);
        return -1;
    }

    // Send SOCKS4 request
    bytes_sent = send(s, req, reqsize, 0);
    if (bytes_sent < 0) {
        perror("send");
        free(req);
        close(s);
        return -1;
    }
    printf("Sent SOCKS4 request for %s:%d\n", host, port);

    // Receive SOCKS4 response
    bytes_received = recv(s, &response, ressize, 0);
    if (bytes_received < 0) {
        perror("recv");
        free(req);
        close(s);
        return -1;
    }

    // Parse response
    if (response.vn != 0) {
        printf("Invalid SOCKS response version: %d\n", response.vn);
        free(req);
        close(s);
        return -1;
    }

    switch (response.cd) {
        case 90:
            printf("SOCKS4 connection successful! Ready to relay traffic.\n");
            break;
        case 91:
            printf("SOCKS4 request rejected or failed\n");
            break;
        case 92:
            printf("SOCKS4 request rejected: cannot connect to identd on client\n");
            break;
        case 93:
            printf("SOCKS4 request rejected: client and identd report different user-ids\n");
            break;
        default:
            printf("Unknown SOCKS4 response code: %d\n", response.cd);
            break;
    }

    free(req);
    close(s);
    return (response.cd == 90) ? 0 : -1;
}