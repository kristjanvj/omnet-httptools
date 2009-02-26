
// ----------------------------------------------------------------------------
//
// HttpTools Project
//
// This file is a part of the HttpTools project. The project was created at
// Reykjavik University, the Laboratory for Dependable Secure Systems (LDSS).
// Its purpose is to create a set of OMNeT++ components to simulate browsing
// behaviour in a high-fidelity manner along with a highly configurable
// Web server component.
//
// Maintainer: Kristjan V. Jonsson (LDSS) kristjanvj@gmail.com
// Project home page: code.google.com/p/omnet-httptools
//
// ----------------------------------------------------------------------------
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License version 3
// as published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
// ----------------------------------------------------------------------------

import
    "Router",
    "StandardHost",
    "FlatNetworkConfigurator",
    "NAMTrace",
    "ChannelInstaller",
    "httptController";

channel ethernetline
    delay 0.1us;
    datarate 100*1000000;
endchannel

//
// Simple DDoS scenario
//
// Demonstration scenario for a simple DDoS attack simulation. It consists of
// two bad servers, a victim site and a single browser. Sockets version.
//
module httptSimpleDDoS
    submodules:
        channelInstaller: ChannelInstaller;
            parameters:
                channelClass = "ThruputMeteringChannel",
                channelAttrs = "format=u";
            display: "p=98,50;i=block/cogwheel_s";
        configurator: FlatNetworkConfigurator;
            parameters:
                moduleTypes = "Router StandardHost",
                nonIPModuleTypes = "",
                networkAddress = "145.236.0.0",
                netmask = "255.255.0.0";
            display: "p=50,64;i=block/cogwheel";
        controller: httptController;
            display: "p=46,140;i=block/cogwheel";
        router: Router;
            display: "p=277,204;i=abstract/router_l";
        thegood: StandardHost;
            display: "p=416,316;i=device/server_l";
        thebad: StandardHost;
            display: "p=157,84;i=device/server_l";
        theugly: StandardHost;
            display: "p=412,76;i=device/server_l";
        client: StandardHost;
            display: "p=150,308;i=device/laptop_l";
    connections:
        thegood.out++ --> ethernetline --> router.in++;
        thegood.in++ <-- ethernetline <-- router.out++;
        thebad.out++ --> ethernetline --> router.in++;
        thebad.in++ <-- ethernetline <-- router.out++;
        theugly.out++ --> ethernetline --> router.in++;
        theugly.in++ <-- ethernetline <-- router.out++;
        client.out++ --> ethernetline --> router.in++;
        client.in++ <-- ethernetline <-- router.out++;

    display: "b=474,374";
endmodule

network httptSimpleDDoS : httptSimpleDDoS
endnetwork

