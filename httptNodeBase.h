
// ***************************************************************************
// 
// HttpTools Project
//// This file is a part of the HttpTools project. The project was created at
// Reykjavik University, the Laboratory for Dependable Secure Systems (LDSS).
// Its purpose is to create a set of OMNeT++ components to simulate browsing
// behaviour in a high-fidelity manner along with a highly configurable 
// Web server component.
//
// Maintainer: Kristjan V. Jonsson (LDSS) kristjanvj04@ru.is
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
 

#ifndef __httptNodeBase_H_
#define __httptNodeBase_H_

#include <omnetpp.h>
#include <INETDefs.h>
#include <string>
#include <map>
#include <queue>
#include <iostream>
#include <fstream>
#include "httptController.h"
#include "httptMessages_m.h"
#include "httptRandom.h"
#include "httptUtils.h"
#include "httptLogdefs.h"

#define HTTPT_REQUEST_MESSAGE  10000
#define HTTPT_RESPONSE_MESSAGE 10001

using namespace std;

enum LOG_FORMAT {lf_short,lf_long};

typedef deque<cMessage*> MESSAGE_QUEUE_TYPE;

class httptNodeBase : public cSimpleModule
{
	protected:
		/** Log level 2: Debug, 1: Info; 0: None */
		int ll; 
		
		string wwwName;
		int port;

		/** The linkspeed in bits per second. Only needed for direct message passing transmission delay calculations. */
		unsigned long linkSpeed;

		/** The http protocol. http/1.0: 10 ; http/1.1: 11 */
		int httpProtocol; 				 	

		string logFileName;
		bool enableLogging;
		LOG_FORMAT outputFormat;
		bool m_bDisplayMessage;
		bool m_bDisplayResponseContent;

		long msgsSent;
		long msgsRcvd;
		long bytesSent;
		long bytesRcvd;

	public:
		httptNodeBase();

		const char* getWWW();

	protected:
		void sendDirectToModule( httptNodeBase *receiver, MESSAGE_QUEUE_TYPE *queue, simtime_t baseDelay=0.0, rdObject *rd=NULL );
		double sendDirectToModule( httptNodeBase *receiver, cMessage *message, simtime_t constdelay=0.0, rdObject *rd=NULL );

		void logRequest( const httptRequestMessage* httpRequest );
		void logResponse( const httptReplyMessage* httpResponse );
		void logEntry( string line );

		string formatHttpRequestShort( const httptRequestMessage* httpRequest );
		string formatHttpResponseShort( const httptReplyMessage* httpResponse );
		string formatHttpRequestLong( const httptRequestMessage* httpRequest );
		string formatHttpResponseLong( const httptReplyMessage* httpResponse );

		/** Calculate the transmission delay for the message msg */
		double transmissionDelay( cMessage *msg );

		/** A factory function for generating a random distribution object from xml specification parameters */
//		rdObject* createDistrObject( cXMLAttributeMap attributes );
};

#endif /* __httptNodeBase_H_ */


