#ifndef NETWORKREQ_H
#define NETWORKREQ_H

#pragma once

#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <string>

class NetworkReq
{
public:
	NetworkReq();
	~NetworkReq();
	void setReqDocument(std::string doc);
	void setReqHost(std::string host);
	void executeRequest();
	void getResponse();
private:
	sf::Http mHttpObject;
	std::string mReqHost;
	std::string mReqDocument;
	sf::Http::Response mResponse;
	sf::Http::Response::Status mStatus;
	sf::Http::Request mReqObject;
	sf::Http::Request::Method mReqMethod;
};

#endif


