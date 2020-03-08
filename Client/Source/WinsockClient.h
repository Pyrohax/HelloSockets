#ifdef WIN32
#pragma once

struct Connection;

class WinsockClient
{
public:
	WinsockClient();
	~WinsockClient();

	bool Connect(const char* aServerName);
	bool Update();
	bool Send(const char* aMessage);
	size_t Receive(char* buffer, size_t size);
	bool Close();

private:
	bool Startup();
	bool ResolveConnection();
	bool TryConnectToAddress();
	bool ValidateConnection();

private:
	Connection* myConnection;
	bool myShouldClose;
};
#endif // WIN32