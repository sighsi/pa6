#include <iostream>
#include "Server.h"

int main()
{
	/*unsigned short port;
	std::cout<<"What port? ";
	std::cin>>port;
	std::cout<<"\n";
	

	Server server(port);
	server.run();
	std::cin.get();*/

	std::cout<<"Local host:"<<sf::IpAddress::LocalHost<<"\n"
		<<"Local: "<<sf::IpAddress::getLocalAddress()<<"\n"
		<<"Public: "<<sf::IpAddress::getPublicAddress()<<"\n";
	std::cin.get();
}
