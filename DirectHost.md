# DirectHost #

This component is a very minimal container for [HTTPBrowser](HTTPBrowser.md) and [HTTPServer](HTTPServer.md) components. This excerpt from the NED file explains in the simplest possible terms:

```
module DirectHost
    parameters:
        numTcpApps: numeric const,		// The number of tcpApps in the array
        tcpAppType: string;			// The type of contained tcpApps
    submodules:
        tcpApp: tcpAppType[numTcpApps] like TCPApp;
            display: "p=163,67;i=block/app";
    connections nocheck:
endmodule
```

Use this module if direct message passing is desired. Simply plug in the server or browser module as a _tcpApp_ in the initialization file.