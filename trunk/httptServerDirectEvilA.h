
// ***************************************************************************
// 
// HttpTools Project
//// This file is a part of the HttpTools project. The project was created at
// Reykjavik University, the Laboratory for Dependable Secure Systems (LDSS).
// Its purpose is to create a set of OMNeT++ components to simulate browsing
// behaviour in a high-fidelity manner along with a highly configurable 
// Web server component.
//
// Maintainer: Kristjan V. Jonsson (LDSS) kristjanvj@gmail.com
// Project home page: code.google.com/p/omnet-httptools
//
// ***************************************************************************
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
// ***************************************************************************

#ifndef __httptServerDirectEvilA_H_
#define __httptServerDirectEvilA_H_

#include <string>
#include "httptServerDirect.h"

using namespace std;

/**
 * @brief An evil attacker server demonstration - type A
 *
 * Demonstrates subclassing the server to create a custom site. This site is an attacker -- a puppetmaster --
 * which serves HTML pages containing attack code. In this case, we are simulating JavaScript attack code which prompts
 * the unsuspecting browser to issue a number of requests for non-existing resources to the victim site.
 * The generateBody virtual function is redefined to create a page containing the attack code.
 *
 * @see httptServerDirect
 *
 * @version 0.9
 * @author  Kristjan V. Jonsson
 */
class INET_API httptServerDirectEvilA : public httptServerDirect
{
	private:
		int badLow;
		int badHigh;
	protected:
		virtual void initialize();
		virtual string generateBody();
};

#endif /* httptServerDirectEvilA */


