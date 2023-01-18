#include "Poco/Net/DNS.h"
#include <iostream>
using Poco::Net::DNS;
using Poco::Net::IPAddress;
using Poco::Net::HostEntry;
int main(int argc, char** argv)
{
    const HostEntry& entry = DNS::hostByName("www.appinf.com");

    std::cout << "Canonical Name: " << entry.name() << std::endl;
    
    const HostEntry::AliasList& aliases = entry.aliases();
    
    
    for (auto it = aliases.begin(); it != aliases.end(); ++it)
        std::cout << "Alias: " << *it << std::endl;
    
    const HostEntry::AddressList& addrs = entry.addresses();
    
    for (auto it = addrs.begin(); it != addrs.end(); ++it)
        std::cout << "Address: " << it->toString() << std::endl;
    
    return 0;
}