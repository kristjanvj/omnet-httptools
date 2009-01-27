
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

#include "httptServer.h"

Define_Module(httptServer);

void httptServer::initialize()
{
	httptServerBase::initialize();

//    const char *address = par("address"); // Not needed
    int port = par("port");
//    delay = par("replyDelay");
//    maxMsgDelay = 0;

    TCPSocket listensocket;
    listensocket.setOutputGate(gate("tcpOut"));
    listensocket.bind(port);
	listensocket.setCallbackObject(this);
    listensocket.listen();

	numBroken=0;
	socketsOpened=0;

	WATCH(numBroken);
	WATCH(socketsOpened);
}

void httptServer::finish()
{
	httptServerBase::finish();

	EV_SUMMARY << "Sockets opened: " << socketsOpened << endl;
	EV_SUMMARY << "Broken connections: " << numBroken << endl;

	recordScalar("sock.opened", socketsOpened);
	recordScalar("sock.broken", numBroken);

	// Clean up sockets and datastructures
	sockCollection.deleteSockets();
}

void httptServer::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
	{
//		handleSelfMessages(msg);
	}
	else
	{
		EV_DEBUG << "Handle inbound message " << msg->name() << " of kind " << msg->kind() << endl;
		TCPSocket *socket = sockCollection.findSocketFor(msg);
		if (!socket)
		{
			EV_DEBUG << "No socket found for the message. Create a new one" << endl;
			// new connection -- create new socket object and server process
			socket = new TCPSocket(msg);
			socket->setOutputGate(gate("tcpOut"));
			socket->setCallbackObject(this,socket);
			sockCollection.addSocket(socket);
		}
		EV_DEBUG << "Process the message " << msg->name() << endl;
		socket->processMessage(msg);
/*		if ( msg->kind()==HTTPT_REQUEST_MESSAGE )
		{
			cMessage *reply = handleReceivedMessage(msg);
			socket->send(reply);
		}
		else
		{
			EV_ERROR << "Unexpected message " << msg->name() << ", kind " << msg->kind() << endl;
			delete msg;			
		}  */
		// TODO: CHECK DELETE FOR MSG
	}
}

void httptServer::socketEstablished(int connId, void *yourPtr)
{
    EV_INFO << "connected socket with id=" << connId << endl;
	socketsOpened++;
}

// TODO: REMOVE??
void httptServer::socketDataArrived(int connId, void *yourPtr, cMessage *msg, bool urgent)
{
	if ( yourPtr==NULL )
	{
		EV_ERROR << "Socket establish failure. Null pointer" << endl;
		return;
	}
	TCPSocket *socket = (TCPSocket*)yourPtr;

	// Should be a httptReplyMessage
	EV_DEBUG << "Socket data arrived on connection " << connId << ". Message=" << msg->name() << ", kind=" << msg->kind() << endl;
/*	if ( msg->kind()==HTTPT_REQUEST_MESSAGE )  // TODO: CHECK VALIDATION
	{ */
		cMessage *reply = handleReceivedMessage(msg);
		if ( reply!=NULL )
		{
			socket->send(reply);
			msgsSent++;
			bytesSent+=msg->byteLength();
		}
		delete msg;
		// TODO: Check if server should close connection here
/*	}
	else
	{
		delete msg;
		EV_ERROR << "Invalid message " << msg->name() << " received on socket with id " << connId << ". kind=" << msg->kind() << endl; 
	}  */
}

void httptServer::socketPeerClosed(int connId, void *yourPtr)
{
	if ( yourPtr==NULL )
	{
		EV_ERROR << "Socket establish failure. Null pointer" << endl;
		return;
	}
	TCPSocket *socket = (TCPSocket*)yourPtr;
	
    // close the connection (if not already closed)
    if (socket->state()==TCPSocket::PEER_CLOSED)
    {
        EV_INFO << "remote TCP closed, closing here as well. Connection id is " << connId << endl;
        socket->close();
		// TODO: Cleanup etc?
    }
}

void httptServer::socketClosed(int connId, void *yourPtr)
{
    EV_INFO << "connection closed. Connection id " << connId << endl;

	if ( yourPtr==NULL )
	{
		EV_ERROR << "Socket establish failure. Null pointer" << endl;
		return;
	}
	TCPSocket *socket = (TCPSocket*)yourPtr;
	sockCollection.removeSocket(socket);
	delete socket;
}

void httptServer::socketFailure(int connId, void *yourPtr, int code)
{
    EV_WARNING << "connection broken. Conneciton id " << connId << endl;
    numBroken++;

    EV_INFO << "connection closed. Connection id " << connId << endl;

	if ( yourPtr==NULL )
	{
		EV_ERROR << "Socket establish failure. Null pointer" << endl;
		return;
	}
	TCPSocket *socket = (TCPSocket*)yourPtr;

	if (code==TCP_I_CONNECTION_RESET)
		EV_WARNING << "Connection reset!\\n";
	else if (code==TCP_I_CONNECTION_REFUSED)
		EV_WARNING << "Connection refused!\\n";
//	else if (code==TCP_I_TIMEOUT)
//		EV_WARNING << "Connection timed out!\\n";

	sockCollection.removeSocket(socket); // TODO: CHECK
	delete socket;
}

/*
void httptServer::sendToClient( httptNodeBase *receiver, cMessage *message )
{

}
*/




