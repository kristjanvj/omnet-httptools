
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

#include "httptNodeBase.h"

httptNodeBase::httptNodeBase()
{
	m_bDisplayMessage=false;
	m_bDisplayResponseContent=false;
}

const char* httptNodeBase::getWWW()
{
	Enter_Method_Silent();
	return wwwName.c_str();
}

void httptNodeBase::sendDirectToModule( httptNodeBase *receiver, MESSAGE_QUEUE_TYPE *queue, simtime_t baseDelay, rdObject *rd )
{
	while( queue->size() > 0 )
	{
		cMessage *sendmsg = queue->back();
		queue->pop_back();
		if ( sendmsg == NULL )
		{
			EV_ERROR << "No message to send to " << receiver->parentModule()->name() << endl;
			continue;
		}
		sendDirectToModule( receiver, sendmsg, baseDelay, rd );
	}
}

double httptNodeBase::sendDirectToModule( httptNodeBase *receiver, cMessage *message, simtime_t constdelay, rdObject *rd )
{
	if ( message==NULL ) return -1.0;
	simtime_t delay=constdelay+transmissionDelay(message);
	if ( rd!=NULL ) delay+=rd->get();
	EV_DEBUG << "Sending " << message->name() << " direct to " << receiver->parentModule()->name() << " with a delay of " << delay << " s\n";
	sendDirect(message,delay,receiver,"tcpIn");
	msgsSent++;
	bytesSent+=message->byteLength();
	return delay;
}

void httptNodeBase::logRequest( const httptRequestMessage* httpRequest )
{	
	if (!enableLogging) return;
	if ( outputFormat == lf_short )
		logEntry(formatHttpRequestShort(httpRequest));
	else
		logEntry(formatHttpRequestLong(httpRequest));
	if ( m_bDisplayMessage )
		EV_INFO << "Request:\n" << formatHttpRequestLong(httpRequest);
}

void httptNodeBase::logResponse( const httptReplyMessage* httpResponse )
{
	if (!enableLogging) return;
	if ( outputFormat == lf_short )
		logEntry(formatHttpResponseShort(httpResponse));
	else
		logEntry(formatHttpResponseLong(httpResponse));
	if ( m_bDisplayMessage )
		EV_INFO << "Response:\n" << formatHttpResponseLong(httpResponse);
}

void httptNodeBase::logEntry( string line )
{
	if (!enableLogging) return;
	if (logFileName.size() == 0) return;

	ofstream outfile;
	time_t curtime;
	time(&curtime);

	outfile.open(logFileName.c_str(),ios::app); 
	outfile << curtime << ";" << simTime() << ";" << fullPath();
	if( outputFormat == lf_short )
		outfile << ";";
	else
		outfile << endl;
 	outfile << line << endl;
	outfile.close();
}

string httptNodeBase::formatHttpRequestShort( const httptRequestMessage* httpRequest )
{	
	ostringstream str;

	str << "REQ;" << httpRequest->targetUrl() << ";"  << httpRequest->originatorUrl() << ";";
	str << httpRequest->protocol() << httpRequest->keepAlive() << ";" << httpRequest->serial() << ";";
//	str << httpRequest->messageType() << ";" << httpRequest->requestSubType() 
	str << httpRequest->requestString() << ";" << httpRequest->badRequest();
	
	return str.str();
}

string httptNodeBase::formatHttpResponseShort( const httptReplyMessage* httpResponse )
{
	ostringstream str;

	str << "RESP;" << httpResponse->targetUrl() << ";"  << httpResponse->originatorUrl() << ";";
	str << httpResponse->protocol() << httpResponse->keepAlive() << ";" << httpResponse->serial() << ";";
	str << httpResponse->result() << ";" << ";" << httpResponse->contentType();

	return str.str();
}

string httptNodeBase::formatHttpRequestLong( const httptRequestMessage* httpRequest )
{	
	ostringstream str;

	str << "REQUEST: " << httpRequest->name() << " -- " << httpRequest->byteLength() << " bytes\n";
	str << "Target URL:" << httpRequest->targetUrl() << "  Originator URL:" << httpRequest->originatorUrl() << endl;

	str << "PROTOCOL:"; 
	switch( httpRequest->protocol() )
	{
		case 10: str << "HTTP/1.0"; break;
		case 11: str << "HTTP/1.1"; break;
		default: str << "UNKNOWN"; break;
	}
	str << "  ";

	str << "KEEP-ALIVE:" << httpRequest->keepAlive() << "  ";
	str << "BAD-REQ:" << httpRequest->badRequest() << "  ";
	str << "SERIAL:" << httpRequest->serial() << "  " << endl;

	str << "REQUEST:" << httpRequest->requestString() << endl;
/*	str << "REQUEST-TYPE:";
	switch( httpRequest->messageType() )
	{
		case 0: str << "GET"; break;
		case 1: str << "PUT"; break;
		default: str << "UNKNOWN"; break;
	}
	str << "  ";  */

/*	str << "SUB-TYPE:";
	switch( httpRequest->requestSubType() )
	{
		case 0: str << "HTML DOC"; break;
		case 1: str << "Text/HTML RES"; break;
		case 2: str << "IMAGE RES"; break;
		default: str << "UNKNOWN"; break;
	} 
	str << "  "; */
	
	return str.str();
}

string httptNodeBase::formatHttpResponseLong( const httptReplyMessage* httpResponse )
{
	ostringstream str;

	str << "RESPONSE: " << httpResponse->name() << " -- " << httpResponse->byteLength() << " bytes\n";

	str << "Target URL:" << httpResponse->targetUrl() << "  Originator URL:" << httpResponse->originatorUrl() << endl;

	str << "PROTOCOL:"; 
	switch( httpResponse->protocol() )
	{
		case 10: str << "HTTP/1.0"; break;
		case 11: str << "HTTP/1.1"; break;
		default: str << "UNKNOWN"; break;
	}
	str << "  ";

	str << "RESULT:" << httpResponse->result() << "  ";
	str << "KEEP-ALIVE:" << httpResponse->keepAlive() << "  ";
	str << "SERIAL:" << httpResponse->serial() << "  " << endl;

	str << "CONTENT-TYPE:";
	switch( httpResponse->contentType() )
	{
		case rt_html_page: str << "HTML DOC"; break;
		case rt_text: str << "Text/HTML RES"; break;
		case rt_image: str << "IMG RES"; break;
		default: str << "UNKNOWN"; break;
	} 
	str << endl;

	if ( m_bDisplayResponseContent )
	{
		str << "CONTENT:" << endl;	
		str << httpResponse->payload() << endl;
	}

	return str.str();
}

double httptNodeBase::transmissionDelay( cMessage *msg )
{
	if ( linkSpeed==0 ) return 0.0; // No delay if linkspeed unspecified
	return msg->byteLength()/((double)linkSpeed/8);
}






