
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
 
#ifndef __httptServerSock_H_
#define __httptServerSock_H_

#include "TCPSocket.h"
#include "TCPSocketMap.h"
#include "httptServerBase.h"

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
class INET_API httptServer : public httptServerBase, public TCPSocket::CallbackInterface
{
	protected:
		TCPSocket listensocket;
		TCPSocketMap sockCollection;
		unsigned long numBroken;
		unsigned long socketsOpened;

	/** @name cSimpleModule redefinitions */
	//@{
	protected: 
		virtual void initialize();
		virtual void finish();

		/** Handle incoming messages */
		virtual void handleMessage(cMessage *msg);
	//@}

	/** @name TCPSocket::CallbackInterface callback methods */
	//@{
	protected:
		/** Does nothing but update statistics/status. Redefine to perform or schedule first sending. */
		virtual void socketEstablished(int connId, void *yourPtr);

		/**
		 * Does nothing but update statistics/status. Redefine to perform or schedule next sending.
		 * Beware: this funcion deletes the incoming message, which might not be what you want.
		 */
		virtual void socketDataArrived(int connId, void *yourPtr, cMessage *msg, bool urgent);

		/** Since remote TCP closed, invokes close(). Redefine if you want to do something else. */
		virtual void socketPeerClosed(int connId, void *yourPtr);

		/** Does nothing but update statistics/status. Redefine if you want to do something else, such as opening a new connection. */
		virtual void socketClosed(int connId, void *yourPtr);

		/** Does nothing but update statistics/status. Redefine if you want to try reconnecting after a delay. */
		virtual void socketFailure(int connId, void *yourPtr, int code);

		/** Redefine to handle incoming TCPStatusInfo. */
		virtual void socketStatusArrived(int connId, void *yourPtr, TCPStatusInfo *status) {delete status;}
	//@}

//	protected:
//		virtual void sendToClient( httptNodeBase *receiver, cMessage *message );
};

#endif


