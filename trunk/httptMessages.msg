
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

// ----------------------------------------------------------------------------
//
// @file httptMessages.msg
//
// Protocol message definitions for the HttpTools components.
//
// @version 0.9 
// @author  Kristjan V. Jonsson
//
// ----------------------------------------------------------------------------

//
// Base class for HTTP messages
//
// @author Kristjan V. Jonsson
// @version 0.9
//
message httptBaseMessage
{
	properties:
		omitGetVerb = true;
	fields:
		string targetUrl; 				// The target URL - request set for browsers, echoed by servers.
		string originatorUrl="";		// The originator URL. Only applicable for servers.
		int protocol = 11; 				// 10 for http/1.0, 11 for http/1.1.
		bool keepAlive = true;
		int serial = 0;
		string payload="";
};

//
// Message class for HTTP requests
//
// @author Kristjan V. Jonsson
// @version 0.9
//
message httptRequestMessage extends httptBaseMessage
{
	properties:
		omitGetVerb = true;			// Dont append get to generated getter methods.
	fields:
		string requestString="";	// The request string. Emulates HTTP request format
		bool badRequest = false;	// Set to true to simulate a bad request. Server answers w. 404.
};

//
// Message class for HTTP replies
//
// @author Kristjan V. Jonsson
// @version 0.9
//
message httptReplyMessage extends httptBaseMessage
{
	properties:
		omitGetVerb = true;
	fields:
		int result=0; 				// e.g. 200 for OK
		int contentType=0;
};



