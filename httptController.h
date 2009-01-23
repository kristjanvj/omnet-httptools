
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


#ifndef __httptController_H_
#define __httptController_H_

#include <string>
#include <list>
#include <vector>
#include <omnetpp.h>
#include <fstream>
#include "httptLogdefs.h"
#include "httptUtils.h"
#include "httptRandom.h"
#include "httptEventMessages_m.h"

using namespace std;

#define INSERT_END 0
#define INSERT_RANDOM -1
#define INSERT_MIDDLE -2

enum ServerStatus {ss_normal, ss_flashcrowd, ss_special};

struct WEB_SERVER_ENTRY
{
	string name;
	string host;
	int port;
	cModule *module;
	simtime_t activationTime;
	simtime_t statusSetTime;
	ServerStatus serverStatus;
	double pvalue;
	double pamortize;
	unsigned long accessCount;
};

#define STATUS_UPDATE_MSG 0

/**
 * @brief httptController module 
 *
 *
 *
 * @see httptBrowser
 * @see httptServer
 *
 * @version 1.0 
 * @author  Kristjan V. Jonsson 
 */
class httptController : public cSimpleModule
{
	protected:
		int ll;
		map<string,WEB_SERVER_ENTRY*> webSiteList;
		vector<WEB_SERVER_ENTRY*> pickList;
		list<WEB_SERVER_ENTRY*> specialList;
		double pspecial;

		unsigned long totalLookups;

		rdObject *rdServerSelection;

	protected:
		virtual void initialize(int stage);
		virtual void finish();
		virtual void handleMessage(cMessage *msg);
		int numInitStages() const {return 2;}

	public:
		void registerWWWserver( const char* objectName, const char* wwwName, int port, int rank=INSERT_RANDOM, simtime_t activationTime=0.0 );
		cModule* getServerModule( const char* wwwName );
		cModule* getAnyServerModule();
		int getServerInfo( const char* wwwName, char* module, int &port );
		int getAnyServerInfo( char* wwwName, char* module, int &port );

	protected:
		cModule* getTcpApp(string node);

		void setSpecialStatus( const char* www, ServerStatus status, double p, double amortize );
		void cancelSpecialStatus( const char* www );
		WEB_SERVER_ENTRY* selectFromSpecialList();

		string listRegisteredServers();
		string listSpecials();
		string listPickOrder();

		void parseOptionsFile(string file, string section);

	private:
		WEB_SERVER_ENTRY* __getRandomServerInfo();
};

#endif /* httptController */


