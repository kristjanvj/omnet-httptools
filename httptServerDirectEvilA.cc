
// ***************************************************************************
// 
// HttpTools Project
//// This file is a part of the HttpTools project. The project was created at
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

#include "httptServerDirectEvilA.h"

// TODO: ENABLE LOGGING TO FILE - PARAMETER IN INI FILE
// TODO: ENABLE SITE SCRIPS - PREDEFINED PAGES


Define_Module(httptServerDirectEvilA);

std::string httptServerDirectEvilA::generateDocument( const char* urlstring )
{
	int numImages = 100+(int)uniform(0,100);
	double rndDelay;
	string result;

	char tempBuf[128];
	for( int i=0; i<numImages; i++ )
	{		
		rndDelay = 2.0+uniform(0,10);
		sprintf(tempBuf, "%s%.4d;%s;%f\n", "IMG", i, "www.good.com", rndDelay);
		result.append(tempBuf);
	}

	return result;
}




