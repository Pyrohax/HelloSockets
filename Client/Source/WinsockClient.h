#ifdef WIN32
#pragma once

struct Connection;

class WinsockClient
{
public:
	WinsockClient();
	~WinsockClient();

	bool Connect(const char* aServerName);
	bool Send(const char* aMessage);
	bool Fetch();
	bool Close();

private:
	bool Startup();
	bool ResolveConnection();
	bool TryConnectToAddress();
	bool ValidateConnection();

private:
	Connection* myConnection;
};
#endif // WIN32