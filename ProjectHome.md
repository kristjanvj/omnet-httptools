# OMNeT++ HttpTools #

**NOTE: This project is now merged into INET and available at the github repository. https://github.com/inet-framework/inet/tree/master/src/applications/httptools.**

The purpose of this project is to create a set of components for HTTP traffic simulation in the [OMNeT++](http://www.omnetpp.org) discrete event simulator.

The project is currently in the initial stages. Full source is now available via subversion. The code is still not fully tested and will be extensively revised in the next few weeks.

HttpTools was developed and tested on a Linux platform (fedora 8). It should work on all Linux platforms and will be tested on Windows in the coming months.

HttpTools is described in
> Jonsson, K., _HttpTools: A Toolkit for Simulation of Web Hosts in OMNeT++_. In proceedings of the 2nd OMNeT++ workshop, Rome, Italy, 2009.
A pdf of the paper is available in downloads.

**NEWS** Finally managed to find some time to work on this project. The code is now ported to OMNeT++ 4.0. You can get the updated source from the subversion repository. The old code is available as a tar in downloads. Examples for the new version will be available soon.

## The components ##

The toolkit consists of three components which plug into the INET framework:

  * **[HTTPBrowser](HTTPBrowser.md)** simulates a single Web browser.

  * **[HTTPServer](HTTPServer.md)** simulates a single Web server.

  * **[HTTPController](HTTPController.md)** manages the scenario.

A single controller object must be created at the scenario level in each simulation which uses the HttpTools components. Any number of nodes with browser or server components can be created (within the limits of memory constraints, processing power and general sanity!). Nodes can be interconnected using OMNeT++ communications links and the INET TCP/IP networking stack implementation or use direct message passing to eliminate the network effects altoghether.

Simulated [HTTP messages](HTTPMessage.md) are utilized by the browser and server components.

Two hosts can be used for the browser and server components:

  * **StandardHost** from the INET framework should be used if a full network simulation using the TCP/IP stack is desired.
  * **DirectHost** is a part of HttpTools and should be used for hosts which use direct message passing.


API reference and NED documentation for the model is coming soon. **ASAP**


## Get the source ##

Fist of all, get the [INET framework](http://www.omnetpp.org/doc/INET/neddoc/index.html) and build it. Run some examples to see if everything works.

Next, get the HttpTools. Enter the following from within your INET directory to retrieve the current source from the subversion repository:

```
svn checkout http://omnet-httptools.googlecode.com/svn/trunk/ httptools
```

You will need to run ./makemake and make again for the INET framework to build and integrate the httptools components.

See [Build and install](buildAndInstall.md) for further instructions.