
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
    "DirectHost",
    "httptController";

//
// Simple DDoS scenario
//
// Demonstration scenario for a simple DDoS attack simulation. It consists of
// two bad servers, a victim site and a single browser.
//
module httptSimpleDirectDDoS
    submodules:
        controller: httptController;
            display: "p=62,60;i=block/cogwheel";
        thegood: DirectHost;
            display: "p=369,300;i=device/server_l";
        thebad: DirectHost;
            display: "p=181,108;i=device/server_l";
        theugly: DirectHost;
            display: "p=356,108;i=device/server_l";
        client: DirectHost;
            display: "p=254,204;i=device/laptop_l";
    connections nocheck:


    display: "b=474,374";
endmodule

network httptSimpleDirectDDoS : httptSimpleDirectDDoS
endnetwork

