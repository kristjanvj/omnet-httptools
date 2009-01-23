
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
 
#ifndef __httptServerBase_H_
#define __httptServerBase_H_

#include <string>
#include <vector>
#include "httptNodeBase.h"

#define MSGKIND_START_SESSION 0
#define MSGKIND_NEXT_MESSAGE  1
#define MSGKIND_SCRIPT_EVENT  2

#define LL_NONE 0 
#define LL_INFO 1
#define LL_DEBUG 2

using namespace std;

struct SITE_DEF_STRUCT
{
	long size;
	string body;
};

/**
 * @brief httptServerDirect module 
 *
 * This module implements a flexible Web server. It is part of the HttpTools project
 * and should be used in conjunction with a number of clients running the httptBrowserDirect.
 *
 * @see httptBrowserDirect
 *
 * @version 1.0 
 * @author  Kristjan V. Jonsson
 */
class INET_API httptServerBase : public httptNodeBase
{
  	protected:
		simtime_t maxMsgDelay;

		bool scriptedMode;
		map<string,SITE_DEF_STRUCT> htmlPages;
		map<string,unsigned int> resources;

		long htmlDocsServed;
		long imgResourcesServed;
		long textResourcesServed;
		long badRequests;

		simtime_t scheduleHTTP(cMessage *msg, simtime_t delay=0);
		void sendHTTP(cMessage *msg);

		rdObject *rdReplyDelay;
		rdObject *rdHtmlPageSize;
		rdObject *rdTextResourceSize;
		rdObject *rdImageResourceSize;
		rdObject *rdNumResources;
		rdObject *rdTextImageResourceRatio;
		rdObject *rdErrorMsgSize;

		simtime_t activationTime;

	protected: 
		virtual void initialize();
		virtual void handleMessage(cMessage *msg);
		virtual void finish();

	protected:
		httptReplyMessage* generateDocument( httptRequestMessage *request, const char* resource, int size=0 );
		httptReplyMessage* generateResourceMessage( httptRequestMessage *request, string resource, CONTENT_TYPE_ENUM category );
		httptReplyMessage* handleGetRequest( httptRequestMessage *request, string resource );
		httptReplyMessage* generateErrorReply( httptRequestMessage *request, int code );
		virtual string generateRandomBody();

	protected:
		cMessage* handleReceivedMessage( cMessage *msg );
		void registerWithController();
		void readSiteDefinition(string file);
		string readHtmlBodyFile( string file );

//	protected:
//		virtual void httptServerBase::sendToClient( httptNodeBase *receiver, cMessage *message );
};

#endif


