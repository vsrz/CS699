#include "NetworkReq.h"


NetworkReq::NetworkReq()
{
	mReqMethod = sf::Http::Request::Method::Get;
}


NetworkReq::~NetworkReq()
{	
}

void NetworkReq::setReqDocument(std::string doc)
{
	mReqDocument = doc;
}

void NetworkReq::setReqHost(std::string host)
{
	mReqHost = host;
}

void NetworkReq::executeRequest()
{
	mHttpObject.setHost(mReqHost);
	mReqObject.setUri(mReqDocument);
	mReqObject.setMethod(mReqMethod);
	mResponse = mHttpObject.sendRequest(mReqObject);

	mStatus = mResponse.getStatus();
}

std::string NetworkReq::getResponse()
{
	return std::string();
}
