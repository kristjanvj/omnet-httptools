
//
// ldssWWWnetwork
//
// Scenario definition for our WWW test.
//
// Reykjavik University
// LDSS - Laboratory for Dependable Secure Systems
// Kristján V. Jónsson
// November 2008
//
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
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


import
    "DirectHost",
    "httptController";


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

