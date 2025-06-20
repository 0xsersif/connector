#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>



#define PROXY	"127.0.0.1"
#define PROXYPORT   9050
#define reqsize sizeof(struct proxyr_request)
#define ressize sizeof(struct prorxy_response)



typedef unsigned char int8;
typedef  unsigned short int int16;
typedef unsigned int int32;



/* 

		+----+----+----+----+----+----+----+----+----+----+....+----+
		| VN | CD | DSTPORT |      DSTIP        | USERID       |NULL|
		+----+----+----+----+----+----+----+----+----+----+....+----+
    	   1    1      2              4           variable       1

*/

struct proxy_request 
{
    int8 vn ;
    int8 cd ;
    int16 dstport ;
    int32 dstip ;
    unsigned char userid[8];
};
typedef struct proxy_request Req ;


/* 

        +----+----+----+----+----+----+----+----+
		| VN | CD | DSTPORT |      DSTIP        |
		+----+----+----+----+----+----+----+----+
           1    1      2              4

VN is the version of the reply code and should be 0. CD is the result
code with one of the following values:

	90: request granted
	91: request rejected or failed
	92: request rejected becasue SOCKS server cannot connect to
	    identd on the client
	93: request rejected because the client program and identd
	    report different user-ids

The remaining fields are ignored _ .

The SOCKS server closes its connection immediately after notifying
the client of a failed or rejected request. For a successful request,
the SOCKS server gets ready to relay traffic on both directions. This
enables the client to do I/O on its connection as if it were directly
connected to the application server.
  */




struct proxy_response
{
    int8 vn ;
    int8 cd ;
    int16 _;
    int32 __;
};
typedef struct proxy_response Res;

Req *request(const char*, const int); 

int main(int, char**);
