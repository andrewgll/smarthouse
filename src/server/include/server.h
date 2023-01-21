#include <Poco/Util/ServerApplication.h>
#ifndef SMARTHOUSE_SERVER_H_
#define SMARTHOUSE_SERVER_H_


class Server: public Poco::Util::ServerApplication
{
private:
	int main(const std::vector<std::string>& args) override;
};

#endif
