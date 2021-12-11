# OMNeT++ HttpTools

**NOTE: This project is now merged into INET and available at the github repository. https://github.com/inet-framework/inet/tree/master/src/applications/httptools.**

**NOTE: This project is archived. It is for historical reference and not actively maintained. Feel free to contact me but I cannot guarantee any level of support.
Also note that this was written for a fairly old version of OMNet++, althoug upgraded to the 4.0 version a while back. There are no plans to continue support at this time.**

**This documentation can also be found at the original home of the project at https://code.google.com/archive/p/omnet-httptools/**

The purpose of HttpTools project was to create a set of components for HTTP traffic simulation in the OMNeT++ discrete event simulator. 
It was written as part of the author's Ph.D. dissertation work and actively used in a number of research projects and papers.
The HttpTools project itself is described in

Jonsson, K., HttpTools: A Toolkit for Simulation of Web Hosts in OMNeT++. In proceedings of the 2nd OMNeT++ workshop, Rome, Italy, 2009. 

## The components

The toolkit consists of three components which plug into the INET framework:

* HTTPBrowser simulates a single Web browser.
* HTTPServer simulates a single Web server.
* HTTPController manages the scenario.

A single controller object must be created at the scenario level in each simulation which uses the HttpTools components. Any number of nodes with browser or server components can be created (within the limits of memory constraints, processing power and general sanity!). Nodes can be interconnected using OMNeT++ communications links and the INET TCP/IP networking stack implementation or use direct message passing to eliminate the network effects altoghether.

Simulated HTTP messages are utilized by the browser and server components.

Two hosts can be used for the browser and server components:

* StandardHost from the INET framework should be used if a full network simulation using the TCP/IP stack is desired.
* DirectHost is a part of HttpTools and should be used for hosts which use direct message passing.
API reference and NED documentation for the model is coming soon. ASAP

## Get the source

Fist of all, get the [INET framework](http://www.omnetpp.org/doc/INET/neddoc/index.html) and build it. Run some examples to see if everything works.
Next, clone this repository and build.
You will need to run ./makemake and mke again for the INET framework to build and integrate the httptools components.
