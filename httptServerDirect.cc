
// ***************************************************************************
// 
// HttpTools Project
//
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

#include "httptServerDirect.h"

Define_Module(httptServerDirect);

void httptServerDirect::initialize()
{
	httptServerBase::initialize();

	// Set the linkspeed
	linkSpeed = par("linkSpeed");
	if ( linkSpeed == 0 ) linkSpeed = 1024*1024; // Default is 1 MBit/s
}

void httptServerDirect::finish()
{
	httptServerBase::finish();
}

void httptServerDirect::handleMessage(cMessage *msg)
{
	EV_DEBUG << "Handling received message " << msg->name() << endl;
    if (msg->isSelfMessage())
    {
		// Self messages are not used at the present
    }
	else
	{
		httptNodeBase *senderModule = dynamic_cast<httptNodeBase*>(msg->senderModule());
		if ( senderModule == NULL )
		{
			EV_ERROR << "Unspecified sender module in received message " << msg->name() << endl;
			delete msg;
		}

		EV_DEBUG << "Sender is " << senderModule->fullName() 
				 << " in host " << senderModule->parentModule()->fullName() << endl;
		cMessage* reply = handleReceivedMessage(msg);
		// Echo back to the requester
		if ( reply!=NULL )
			sendDirectToModule(senderModule,reply,0.0,rdReplyDelay);
		delete msg;
	}
	httptServerBase::handleMessage(msg);
}


