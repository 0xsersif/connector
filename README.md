# SOCKS4 Proxy Connector

A complete C implementation of a SOCKS4 proxy client that connects through Tor's SOCKS proxy.

## Features

- **SOCKS4 Protocol Implementation**: Full SOCKS4 client with proper request/response handling
- **Tor Integration**: Connects to Tor's SOCKS proxy (127.0.0.1:9050)
- **Error Handling**: Comprehensive error handling for network and protocol issues
- **Response Parsing**: Interprets all SOCKS4 response codes (90, 91, 92, 93)

## Project Structure

```
connector/
├── connector.c      # Main implementation
├── connector.h      # Headers and SOCKS4 protocol structures
├── Makefile        # Build configuration
└── README.md       # This file
```

## SOCKS4 Protocol

The implementation follows the SOCKS4 protocol specification:

### Request Format
```
+----+----+----+----+----+----+----+----+----+----+....+----+
| VN | CD | DSTPORT |      DSTIP        | USERID       |NULL|
+----+----+----+----+----+----+----+----+----+----+....+----+
   1    1      2              4           variable       1
```

### Response Format
```
+----+----+----+----+----+----+----+----+
| VN | CD | DSTPORT |      DSTIP        |
+----+----+----+----+----+----+----+----+
   1    1      2              4
```

## Setup and Installation

### 1. Install Tor (macOS)
```bash
brew install tor
```

### 2. Install Tor (Linux)
```bash
sudo apt install tor
```

### 3. Start Tor Service
```bash
# macOS
brew services start tor

# Linux
sudo systemctl start tor
```

### 4. Verify Tor is Running
```bash
lsof -i :9050
```
This should show Tor listening on port 9050.

## Building

```bash
make clean && make
```

## Usage

```bash
./connector <destination_host> <destination_port>
```

### Examples

```bash
# Connect to Google's HTTP server through Tor
./connector google.com 80

# Connect to a web server
./connector example.com 443
```

### Expected Output

**Success (with Tor running):**
```
Connected to SOCKS proxy at 127.0.0.1:9050
Sent SOCKS4 request for google.com:80
SOCKS4 connection successful! Ready to relay traffic.
```

**Error (Tor not running):**
```
connect: Connection refused
```

## Response Codes

- **90**: Request granted (success)
- **91**: Request rejected or failed
- **92**: Request rejected - cannot connect to identd on client
- **93**: Request rejected - client and identd report different user-ids

## Troubleshooting

### Connection Refused
- **Cause**: Tor is not running
- **Solution**: Start Tor service as shown above

### Invalid Response
- **Cause**: Non-SOCKS4 server or protocol mismatch
- **Solution**: Verify you're connecting to a SOCKS4 proxy

## Implementation Details

- **Memory Management**: Proper allocation/deallocation of request structures
- **Network Byte Order**: Correct handling of port and IP address byte ordering
- **Error Handling**: Comprehensive error checking for all network operations
- **Protocol Compliance**: Full SOCKS4 specification implementation

## Next Steps

- [ ] Add SOCKS5 support
- [ ] Implement proxy authentication
- [ ] Add connection timeout handling
- [ ] Support for SOCKS4A (domain name resolution through proxy)




