
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

//
// httptServerEvilA
//
// Demonstrates subclassing the server to create a custom site. This site is an attacker -- a puppetmaster --
// which serves HTML pages containing attack code. In this case, we are simulating JavaScript attack code which prompts
// the unsuspecting browser to request a number of images from a wictim site. Delays are specified to simulate hiding
// the attack from the browser user by use of JavaScript timeouts or similar mechanisms.
// The generateBody virtual function is redefined to create a page containing the attack code.
//
// This module definition has two additional parameters to the standard httptServerDirect definition:
// * minBadRequests specifies the lower bound on bad requests caused to be sent to the wictim by the browser.
// * maxBadRequests specifies the upper bound on bad requests caused to be sent to the wictim by the browser.
//
// @version 0.9 
// @author  Kristjan V. Jonsson
//
simple httptServerEvilA
	parameters:
		www: string,				// The WWW name of the server
		port: numeric const,		// The listening port number
		httpProtocol: numeric,		// The http protocol: 10 for http/1.0, 11 for http/1.1. Not used at the present time.
		logLevel: numeric,			// The log level: 2: Debug, 1: Info; 0: Errors and warnings only
		logFile: string,			// Name of server log file. Events are appended, allowing sharing of file for multiple servers.
		siteDefinition: string,		// The site script file. Blank to disable.
		config: xml,				// The XML configuration file for random sites
		activationTime: numeric,	// The initial activation delay. Zero to disable.
		linkSpeed: numeric,			// Used to model transmission delays.
		minBadRequests: numeric,	// The lower bound of bad requests.
		maxBadRequests: numeric;	// The upper bound of bad requests
	gates:
		in: tcpIn;
		out: tcpOut;
endsimple

