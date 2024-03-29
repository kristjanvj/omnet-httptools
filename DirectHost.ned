
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

import inet.applications.tcpapp.TCPApp;


//
// DirectHost
//
// Simple host for the HttpTools project. The module is derived from the INET
// StandardHost module. All network infrastructure modules were removed; 
// the node is a simple container for tcpApps. Suitable apps are the httptBrowserDirect
// and httptServerDirect modules from HttpTools.
// See the INET documentation for StandardHost and the provided examples on how
// to assign tcpApps to the module.
//
// @see httptServerDirect
// @see httptBrowserDirect
//
// @author Kristjan V. Jonsson (kristjanvj@gmail.com)
// @version 1.0
//
module DirectHost
{
    parameters:
        double numTcpApps = default(0);		// The number of tcpApps in the array
        string tcpAppType = default("");				// The type of contained tcpApps
    submodules:
        tcpApp[numTcpApps]: <tcpAppType> like TCPApp {
            parameters:
                @display("p=163,67;i=block/app");
        }
    connections allowunconnected:
}


