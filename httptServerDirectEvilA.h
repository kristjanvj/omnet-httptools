
// ***************************************************************************
// 
// HttpTools Project
//
// Reykjavik University, the Laboratory for Dependable Secure Systems (LDSS).
// Its purpose is to create a set of OMNeT++ components to simulate browsing
// behaviour in a high-fidelity manner along with a highly configurable 
// Web server component.
//
// Maintainer: Kristjan V. Jonsson LDSS kristjanvj04@ru.is
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
 * @brief httptServerDirectEvilA module 
 *
 * This object models a malicious web site which serves documents with img-src resources
 * on a 3rd party site. The number of resources which is requested by the receiving 
 * browser contributes to a DDoS attack.
 *
 * @see httptServerDirect
 *
 * @version 1.0 
 * @author  Kristjan V. Jonsson
 */
class INET_API httptServerDirectEvilA : public httptServerDirect
{
	protected:
		virtual string generateDocument( const char* urlstring );
};

#endif /* httptServerDirectEvilA */

