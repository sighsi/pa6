#ifndef CLIENT
#define CLIENT

#include <SFML/Network.hpp> 
#include <thread> 
#include <vector> 
#include <iostream>
#include <map> 

using namespace std; 

class Client
{
    public: 

    Client(const string& ID)
    {
        this->ID = ID; 
    }

    ~Client()
    {
        
    }

    // connect - IP Address and Port

    // send - Packets / Packet Handling

    // recieve - Message Packet 

    private: 

    string ID; 

    sf::TcpSocket socket; 
    sf::Packet packet; 
}; 

#endif