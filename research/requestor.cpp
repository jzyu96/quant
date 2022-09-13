/* This is the requestor program; the purpose of this file is to gather financial data
 * on a given ticker from a website of our choice. This data will be passed onto another
 * program whose duty will be to parse the data. Data will be gathered by this program via
 * a GET request through HTTP or HTTPS. 
 */

#include <iostream>
#include <string>
#include <Poco/URI.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPMessage.h>

using namespace std;
using namespace Poco;
using namespace Poco::Net;

void request(string ticker) {
	// Create URI
	URI uri("http://httpbin.org");

	// Create a session
	HTTPClientSession session(uri.getHost(), uri.getPort());

	// Set connection to keepalive
	session.setKeepAlive(true);

	// Choose the http request method
	HTTPRequest request(HTTPRequest::HTTP_GET, "/", HTTPMessage::HTTP_1_1);

	// Add headers
	
	// Send the request
	session.sendRequest(request);

	// Receive response
	HTTPResponse response;
	istream &page = session.receiveResponse(response);

	// Print the status code
	cout << response.getStatus() << endl;

	// Lets compile and start wireshark

}




