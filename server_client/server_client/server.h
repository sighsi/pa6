#ifndef SERVER
#define SERVER

#include <SFML/Network.hpp> 
#include <thread> 
#include <vector> 
#include <map> 
#include <iostream> 

using namespace std; 

#include "client.h"
class Server
{
    public: 

    Server(unsigned short port) : listener_port(port)
    { 
        // Chat server is started
        Listener.listen(2000); // port
        Listener.listen(listener_port); // accepts the port if it is found 
    }

    ~Server()
    {

    }


    private: 

    // Listens to a Specific Port
    sf::TcpListener Listener; 
    unsigned short listener_port; 

    sf::TcpSocket socket; 
    sf::Packet packet; 

    typedef map<unsigned short, sf::IpAddress> ClientID; 
    ClientID client; 

    // Packet handling functions for the Server:

    void packetHandling()
    {

    }
}; 

#endif