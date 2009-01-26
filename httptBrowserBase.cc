
// ***************************************************************************
// 
// HttpTools Project
//
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

#include "httptBrowserBase.h"

httptBrowserBase::httptBrowserBase()
{
	httptNodeBase::httptNodeBase();
	m_bDisplayMessage = true;
	m_bDisplayResponseContent = true;
    eventTimer = NULL;
}

httptBrowserBase::~httptBrowserBase()
{
    cancelAndDelete(eventTimer);
}

void httptBrowserBase::initialize()
{
	ll = par("logLevel");

	EV_DEBUG << "Initializing HTTP browser component\n";

	cXMLElement *rootelement = par("config").xmlValue();
	if ( rootelement==NULL ) error("Configuration file is not defined");

	cXMLAttributeMap attributes;
	cXMLElement *element;
	rdObjectFactory rdFactory;
	// Activity period length -- the waking period
	element = rootelement->getFirstChildWithTag("activityPeriod");
	if ( element==NULL ) error("Activity period parameter undefined in XML configuration");
	attributes = element->getAttributes();
	rdActivityLength = rdFactory.create(attributes);
	if ( rdActivityLength==NULL) error("Activity period random object could not be created");
	// Inter-session interval
	element = rootelement->getFirstChildWithTag("interSessionInterval");
	if ( element==NULL ) error("Inter-request interval parameter undefined in XML configuration");
	attributes = element->getAttributes();
	rdInterSessionInterval = rdFactory.create(attributes);
	if ( rdInterSessionInterval==NULL) error("Inter-session interval random object could not be created");
	// Inter-request interval
	element = rootelement->getFirstChildWithTag("InterRequestInterval");
	if ( element==NULL ) error("Inter-request interval parameter undefined in XML configuration");
	attributes = element->getAttributes();
	rdInterRequestInterval = rdFactory.create(attributes);
	if ( rdInterRequestInterval==NULL) error("Inter-request interval random object could not be created");
	// request size
	element = rootelement->getFirstChildWithTag("requestSize");
	if ( element==NULL ) error("Inter-request interval parameter undefined in XML configuration");
	attributes = element->getAttributes();
	rdRequestSize = rdFactory.create(attributes); 
	if ( rdRequestSize==NULL) error("Request size random object could not be created");
	// Requests in session 
	element = rootelement->getFirstChildWithTag("reqInSession");
	if ( element==NULL ) error("requests in session parameter undefined in XML configuration");
	attributes = element->getAttributes();
	rdReqInSession = rdFactory.create(attributes); 
	if ( rdReqInSession==NULL) error("Requests in session random object could not be created");
	// Processing delay
	element = rootelement->getFirstChildWithTag("processingDelay"); // TODO: CHECK USE OF DELAY IN SOCKET APPLICATIONS
	if ( element==NULL ) error("processing delay parameter undefined in XML configuration");
	attributes = element->getAttributes();
	rdProcessingDelay = rdFactory.create(attributes);
	if ( rdProcessingDelay==NULL) error("Processing delay random object could not be created");

	controller = dynamic_cast<httptController*>(parentModule()->parentModule()->submodule("controller"));
	if ( controller == NULL )
		error("Controller module not found");

	httpProtocol = par("httpProtocol");

	logFileName = (const char*)par("logFile");
	enableLogging = logFileName!="";
	outputFormat = lf_short;

	// Initialize counters
   	msgsRcvd = 0;
    msgsSent = 0;
    bytesRcvd = 0;
    bytesSent = 0;
	htmlRequested = 0;
	htmlReceived = 0;
	htmlErrorsReceived = 0;
	imgResourcesRequested = 0;
	imgResourcesReceived = 0;
	textResourcesRequested = 0;
	textResourcesReceived = 0;
	messagesInCurrentSession = 0;
	connectionsCount = 0;
	sessionCount = 0;

	reqInCurSession = 0;
	reqNoInCurSession = 0;

	eventTimer = new cMessage("eventTimer");

	string scriptFile = (const char*)par("scriptFile");
	scriptedMode = ( scriptFile.size() != 0 );
	if ( scriptedMode )
	{
		readScriptedEvents(scriptFile.c_str());
	}
	else
	{
		double activationTime = par("activationTime"); // This is the activation delay. Optional // TODO: Is this necessary??
		if ( ENABLE_ACTIVITY_PERIOD )
			activationTime += (86400.0 - rdActivityLength->get())/2; // Activate after half the sleep period
		EV_INFO << "Initial activation time is " << activationTime << endl;
		eventTimer->setKind(MSGKIND_ACTIVITY_START);
		scheduleAt(simTime()+(simtime_t)activationTime, eventTimer);
	}
}

void httptBrowserBase::finish()
{    
	EV_SUMMARY << "Sessions: " << sessionCount << endl;
	EV_SUMMARY << "Sent " << bytesSent << " bytes in " << msgsSent << " messages\n";  
	EV_SUMMARY << "Received " << bytesRcvd << " bytes in " << msgsRcvd << " messages\n";
	EV_SUMMARY << "HTML requested " << htmlRequested << "\n";
	EV_SUMMARY << "HTML received " << htmlReceived << "\n";
	EV_SUMMARY << "HTML errors received " << htmlErrorsReceived << "\n";
	EV_SUMMARY << "Image resources requested " << imgResourcesRequested << "\n";
	EV_SUMMARY << "Image resources received " << imgResourcesReceived << "\n";
	EV_SUMMARY << "Text resources requested " << textResourcesRequested << "\n";
	EV_SUMMARY << "Text resources received " << textResourcesReceived << "\n";

	recordScalar("session.count", sessionCount);
	recordScalar("messages.sent", msgsSent);
	recordScalar("messages.rcvd", msgsRcvd);
	recordScalar("bytes.sent", bytesSent);
	recordScalar("bytes.rcvd", bytesRcvd);
	recordScalar("html.requested", htmlRequested);
	recordScalar("html.received", htmlReceived);
	recordScalar("html.errors", htmlErrorsReceived);
	recordScalar("html.image.requested", imgResourcesRequested);
	recordScalar("html.image.received", imgResourcesReceived);
	recordScalar("html.text.requested", textResourcesRequested);
	recordScalar("html.text.received", textResourcesReceived);
}

void httptBrowserBase::handleSelfMessages(cMessage *msg)
{
	string serverUrl;
    switch (msg->kind())
    {
		case MSGKIND_ACTIVITY_START:
			eventTimer->setKind(MSGKIND_START_SESSION);
			messagesInCurrentSession = 0;
			reqNoInCurSession = 0;
			activityPeriodLength = rdActivityLength->get(); // Get the length of the activity period
			acitivityPeriodEnd = simTime()+activityPeriodLength; // The end of the activity period
			EV_INFO << "Activity period starts @ T=" << simTime() << ". Activity period is " << activityPeriodLength/3600 << " hours." << endl;
			scheduleAt(simTime() + (simtime_t)rdInterSessionInterval->get()/2, eventTimer);
			break;
		case MSGKIND_START_SESSION:
			sessionCount++;
			messagesInCurrentSession = 0;
			reqInCurSession = 0;
			reqNoInCurSession = (int)rdReqInSession->get();
			EV_INFO << "Starting session # " << sessionCount << " @ T=" << simTime() << ". Requests in session are " << reqNoInCurSession << "\n";
			sendRequestToRandomServer();
			scheduleNextBrowseEvent();						
			break;
		case MSGKIND_NEXT_MESSAGE:
			EV_INFO << "Next message in session # " << sessionCount << " @ T=" << simTime() << ". "
 					<< "Current request is " << reqInCurSession << "/" << reqNoInCurSession << "\n";
			sendRequestToRandomServer();
			scheduleNextBrowseEvent();
			break;
		case MSGKIND_SCRIPT_EVENT:
			EV_INFO << "Scripted event @ T=" << simTime() << "\n";
			sessionCount++;
			messagesInCurrentSession = 0;
			// Get the browse event
			if ( browseEvents.size() == 0 ) error("No event entry in queue");
			BROWSE_EVENT_ENTRY be = browseEvents.back();
			browseEvents.pop_back();				
			sendRequestToServer(be);
			// Schedule the next event
			if ( browseEvents.size() != 0 )
			{
				be = browseEvents.back();
				EV_DEBUG << "Scheduling next event @ " << be.time << "\n";
				eventTimer->setKind(MSGKIND_SCRIPT_EVENT);
				scheduleAt(be.time, eventTimer);
			}
			else
			{
				EV_DEBUG << "No more browsing events\n";
			}
			break;
	}
}

void httptBrowserBase::handleDataMessage( cMessage *msg )
{
	httptReplyMessage *appmsg = check_and_cast<httptReplyMessage*>(msg);
	if (appmsg==NULL) error("Message (%s)%s is not a valid reply message", msg->className(), msg->name());

	logResponse(appmsg);

	messagesInCurrentSession++;
	bytesRcvd += msg->byteLength();
	msgsRcvd++;
		
	int serial = appmsg->serial();
	int resultCode = appmsg->result();

	string senderWWW = appmsg->originatorUrl();

	if ( appmsg->result()!=200 || (CONTENT_TYPE_ENUM)appmsg->contentType()==rt_unknown )
	{
		EV_INFO << "Receiving message " << appmsg->name() << " with result code " << appmsg->result() << endl;
		htmlErrorsReceived++;
		return;
	}
	else
	{
		switch( (CONTENT_TYPE_ENUM)appmsg->contentType() )
		{
			case rt_html_page:
				EV_INFO << "HTML Document received: " << appmsg->name() << "'. Size is " << msg->byteLength() << " bytes and serial " << serial << endl;
				htmlReceived++;
				break;
			case rt_text: 
				EV_INFO << "Text resource received: " << appmsg->name() << "'. Size is " << msg->byteLength() << " bytes and serial " << serial << endl;
				textResourcesReceived++;
				break;
			case rt_image:
				EV_INFO << "Image resource received: " << appmsg->name() << "'. Size is " << msg->byteLength() << " bytes and serial " << serial << endl;
				imgResourcesReceived++;
				break;
		}
		EV_DEBUG << "Receive time is " << simTime() << endl;

		// Parse the html page body 
		if ( (CONTENT_TYPE_ENUM)appmsg->contentType() == rt_html_page && strlen(appmsg->payload()) != 0)
		{
			EV_DEBUG << "Processing HTML document body:\n";
			cStringTokenizer lineTokenizer( (const char*)appmsg->payload(), "\n" );
			std::vector<string> lines = lineTokenizer.asVector();
			int serial=0;
			string providerName = "";
			string resourceName = "";
			double delay=0.0;
			bool bad=false;
			int refSize=0;
			MESSAGE_QUEUE_TYPE queue;
			std::map<string,MESSAGE_QUEUE_TYPE> requestQueues;
			for( vector<string>::iterator iter = lines.begin(); iter != lines.end(); iter++)
			{
				string resourceLine = *iter;
				cStringTokenizer fieldTokenizer( resourceLine.c_str(), ";" );
				std::vector<string> fields = fieldTokenizer.asVector();
				if ( fields.size()<1 )
				{
					EV_ERROR << "Invalid resource reference in received message: " << resourceLine << endl;
					continue;
				}
				// Get the resource name -- this is mandatory for all references
				resourceName = fields[0];

				providerName = senderWWW;
				if ( fields.size()>1 )
					providerName = fields[1];

				delay=0.0;
				if ( fields.size()>2 )
					delay = safeatof(fields[2].c_str());

				bad=false;
				if ( fields.size()>3 )
					bad = safeatobool(fields[3].c_str());
			
				refSize = 0;
				if ( fields.size()>4 )
					refSize = safeatoi(fields[4].c_str());

				EV_DEBUG << "Requesting resource " << resourceName << endl;

				// Generate a request message and push on queue for the intended recipient
				cMessage *reqmsg = generateResourceRequest(senderWWW,resourceName,serial++,bad,refSize);
				requestQueues[providerName].push_front(reqmsg);
			}
			// Iterate through the list of queues (one for each recipient encountered) and submit each queue.
			// A single socket will thus be opened for each recipient for a rough HTTP/1.1 emulation.
			std::map<string,MESSAGE_QUEUE_TYPE>::iterator i=requestQueues.begin();
			for( ; i!=requestQueues.end(); i++ )
				sendRequestsToServer((*i).first,(*i).second);
		} 
	}

    delete msg;
}  

cMessage* httptBrowserBase::generatePageRequest(string www, string pageName, bool bad, int size)
{
	EV_DEBUG << "Generating page request for URL " << www << ", page " << pageName << endl;
	
	long requestLength = (long)rdRequestSize->get();

	if (pageName.size()==0) pageName="/";
	else if (pageName[0]!='/') pageName.insert(0,"/");

	char szReq[1024];
	sprintf(szReq,"GET %s HTTP/1.1", pageName.c_str()); // TODO: Validate size
	httptRequestMessage *msg = new httptRequestMessage(szReq);
	msg->setTargetUrl(www.c_str());
	msg->setProtocol(httpProtocol);
	msg->setRequestString(szReq); 
	msg->setSerial(0);
	msg->setByteLength(requestLength+size);   	// Add extra request size if specified
	msg->setKeepAlive(httpProtocol==11);
	msg->setBadRequest(bad); 					// Simulates willingly requesting a non-existing resource.
	msg->setKind(HTTPT_REQUEST_MESSAGE);

	logRequest(msg);
	htmlRequested++;

	return msg;
}

cMessage* httptBrowserBase::generateRandomPageRequest(string www, bool bad, int size)
{
	EV_DEBUG << "Generating random page request, URL: " << www << endl;
	return generatePageRequest(www,"random_page.html",bad,size);
}

cMessage* httptBrowserBase::generateResourceRequest(string www, string resource, int serial, bool bad, int size)
{
	EV_DEBUG << "Generating resource request for URL " << www << ", resource: " << resource << endl;
	
	long requestLength = (long)rdRequestSize->get()+size;

	if (resource.size()==0) 
	{
		EV_ERROR << "Unable to request resource -- empty resource string" << endl;
		return NULL;
	}
	else if (resource[0]!='/') 
		resource.insert(0,"/");

	string ext = trimLeft(resource,".");
	CONTENT_TYPE_ENUM rc = getResourceCategory(ext);
	if ( rc==rt_image ) imgResourcesRequested++;
	else if ( rc==rt_text ) textResourcesRequested++;

	char szReq[1024];
	sprintf(szReq,"GET %s HTTP/1.1",resource.c_str());  // TODO: VALIDATE SIZE!

	httptRequestMessage *msg = new httptRequestMessage(szReq);
	msg->setTargetUrl(www.c_str());	
	msg->setProtocol(httpProtocol);
	msg->setRequestString(szReq); 
	msg->setSerial(serial);
	msg->setByteLength(requestLength);   	// Add extra request size if specified
	msg->setKeepAlive(httpProtocol==11);
	msg->setBadRequest(bad); 					// Simulates willingly requesting a non-existing resource.
	msg->setKind(HTTPT_REQUEST_MESSAGE);

	logRequest(msg);

	return msg;
}		

void httptBrowserBase::scheduleNextBrowseEvent()
{
	if( eventTimer->isScheduled() )
		cancelEvent(eventTimer);
	double nextEventTime;
	if ( ++reqInCurSession >= reqNoInCurSession )	
	{
		// The requests in the current round are done. Lets check what to do next.
		if ( !ENABLE_ACTIVITY_PERIOD || simTime() < acitivityPeriodEnd )
		{
			// Scheduling next session start within an activity period.	
			nextEventTime = simTime()+ (simtime_t)rdInterSessionInterval->get();
			EV_INFO << "Scheduling a new session start @ T=" << nextEventTime << endl;
			messagesInCurrentSession = 0;
			eventTimer->setKind(MSGKIND_START_SESSION);
			scheduleAt(nextEventTime, eventTimer);
		}
		else
		{
			// Schedule the next activity period start. This corresponds to to a working day or home time, ie. time 
			// when the user is near his workstation and periodically browsing the web. Inactivity periods then
			// correspond to sleep time or time away from the office
			simtime_t activationTime = simTime() + (simtime_t)(86400.0 - rdActivityLength->get()); // Sleep for a while
			EV_INFO << "Terminating current activity @ T=" << simTime() << ". Next activation time is " << activationTime << endl;
			eventTimer->setKind(MSGKIND_ACTIVITY_START);
			scheduleAt(activationTime, eventTimer);
		}
	}
	else
	{
		// Schedule another browse event in a while.
		nextEventTime = simTime() + (simtime_t)rdInterRequestInterval->get();
		EV_INFO << "Scheduling a browse event @ T=" << nextEventTime 
				<< ". Request " << reqInCurSession << " of " << reqNoInCurSession << endl;
		eventTimer->setKind(MSGKIND_NEXT_MESSAGE);
		scheduleAt(nextEventTime, eventTimer);
	}						
}

void httptBrowserBase::readScriptedEvents( const char* filename )
{
	EV_DEBUG << "Reading scripted events from " << filename << "\n";

	ifstream scriptfilestream;
	scriptfilestream.open(filename);
	if(!scriptfilestream.is_open())
		error("Could not open script file %s",filename);

	string line;
	string timepart;
	string wwwpart;
	int pos;	
	simtime_t t;
	while(!std::getline(scriptfilestream, line).eof())
	{
		line = trim(line);
		if ( line.find("#") == 0 ) 
			continue;

		pos = line.find(";");
		if ( pos == -1 ) continue;
		timepart = line.substr(0,pos);
		wwwpart = line.substr(pos+1,line.size()-pos-1);

		try
		{
			t = (simtime_t)atof(timepart.c_str());
		}
		catch(...)
		{
			continue;
		}

		vector<string> path = parseResourceName(wwwpart);

		BROWSE_EVENT_ENTRY be;
		be.time = t;
		be.wwwhost = extractServerName(wwwpart.c_str());
		be.resourceName = extractResourceName(wwwpart.c_str());
		be.serverModule = dynamic_cast<httptNodeBase*>(controller->getServerModule(wwwpart.c_str()));
		if ( be.serverModule==NULL ) error("Unable to locate server %s in the scenario", wwwpart.c_str());

		EV_DEBUG << "Creating scripted browse event @ T=" << t << ", " << be.wwwhost << " / " << be.resourceName << endl;
		browseEvents.push_front(be);
	}
	scriptfilestream.close();

	if ( browseEvents.size() != 0 )
	{ 
		BROWSE_EVENT_ENTRY be = browseEvents.back();
		eventTimer->setKind(MSGKIND_SCRIPT_EVENT);
		scheduleAt(be.time, eventTimer);
	}
}






