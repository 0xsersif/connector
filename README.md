# tor_connect


SOCKS Proxy Connection Setup
This project demonstrates connecting to a SOCKS proxy using C programming.
Problem Encountered
Initially encountered connect: Connection refused error when trying to connect to SOCKS proxy at 127.0.0.1:9050.
Root Cause
The error occurred because no SOCKS proxy service was running on the system. Port 9050 is the default port for Tor's SOCKS proxy.
Solution Steps
1. Install Tor
bashsudo apt install tor
2. Start Tor Service
bashsudo systemctl start tor
3. Verify Tor is Running
bashss -tlnp | grep 9050
This should show Tor listening on port 9050.
What Was Learned

Connection refused errors typically indicate no service is listening on the target port
Port 9050 is Tor's default SOCKS proxy port
Tor installation provides a local SOCKS proxy for testing and secure connections
Proper error handling helps identify network connectivity issues

Usage
Once Tor is running, the C program can successfully connect to the SOCKS proxy and display "connected to proxy".
Next Steps

Implement full SOCKS protocol communication
Add error handling for different connection scenarios
Consider proxy authentication if needed




