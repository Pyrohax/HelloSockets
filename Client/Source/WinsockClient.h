#ifdef WIN32
#pragma once

struct Connection;

class WinsockClient
{
public:
	WinsockClient();
	~WinsockClient();

	void ConnectToServer(const char* aServerName);

	bool Startup();
	bool ResolveConnection();
	bool Poll();
	bool Send(const char* aMessage);
	bool Close();
	void Fetch();
	bool Fail();
	void Clean();

private:
	Connection* myConnection;
};
#endif // WIN32