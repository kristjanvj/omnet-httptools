
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
// httptBrowserDirect
//
// This component is the direct message passing version of the browser simulation 
// component. It is derived from httptBrowserBase. Use this component with the
// DirectHost container module.
//
// Direct message passing is used for transmission, thus bypassing the normal links and
// interfaces. A linkSpeed parameter is hence needed to model transmission delays.
//
// @see DirectHost
// @see httptBrowserBase
// @see httptBrowser
//
// @version 0.9 
// @author  Kristjan V. Jonsson
//
simple httptBrowserDirect
	parameters:
		config: xml,				// The XML configuration file for the browser
		logLevel: numeric,			// The log level: 2: Debug, 1: Info; 0: Errors and warnings only
		httpProtocol: numeric,		// The http protocol: 10 for http/1.0, 11 for http/1.1. Not used at the present time.
		logFile: string,			// Name of a browser log file. Browse events are appended, allowing sharing of file for multiple browsers.
		scriptFile: string,			// The browsing script file. Blank to disable.
		activationTime: numeric,	// The initial activation delay. Zero to disable.
		linkSpeed: numeric;			// Used to model transmission delays
	gates:
		in: tcpIn;
		out: tcpOut;
endsimple

