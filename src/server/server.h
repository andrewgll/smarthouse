#ifndef SMARTHOUSE_SERVER_H_
#define SMARTHOUSE_SERVER_H_

#include <Poco/Util/ServerApplication.h>

class Server: public Poco::Util::ServerApplication
{
private:
	int main(const std::vector<std::string>& args) override;
	int test();
};

#endif
