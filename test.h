#ifndef TESTCLASS_H
#define TESTCLASS_H

#include "button.h"
#include "textbox.h"

#include "functions.h"
#include <iostream>
#include <map>

using namespace std;

class TestClass
{

public:

    TestClass(){}
    bool test_Textures()
    {
        sf::Texture test;

        if (!test.loadFromFile("botton.png"))
        {
            cout << "Exit failure" << endl;
            return false;
        }
        else if (!test.loadFromFile("blk.png"))
        {
            cout << "Exit failure" << endl;
            return false;
        }
        else if (!test.loadFromFile("backgroudn.png"))
        {
            cout << "Exit failure" << endl;
            return false;
        }

        return true;
    }

    void test_TextInput(int charTyped)
    {
        sf::Event input;
        charTyped = input.text.unicode;

        if (charTyped > 128)
        {
            cout << "outside bounds of keyboard input";
            cout<< "character typed: " << static_cast<char>(input.text.unicode) << endl; 
            // Maybe Give Delete Opportunity (I do not have a textbox with delete)
        }
    }

    bool test_KeyHeld(sf::Keyboard::Key key)
    {
        bool CurrentState[sf::Keyboard::KeyCount]; 
        return CurrentState[key];
    }

    bool test_APICALL(){
        std::cout << "calling the API to return with date info" << std::endl;
        apiCall("/v1/us/daily.csv");
        std::cout << "return type is void but if worked correctly there should be a file named /v1/us/daily.csv generated in data" << std::endl;
        std::fstream f;
        f.open( "data/v1usdaily.csv");
        if (!f.is_open()) {
            std::cout << "Error reading destinations, API call failed because file doesn't exist" << std::endl;
            return false;
        }
        else std::cout << "API call worked and generated a data csv file" << std::endl;

        return true;
    }

    void test_readDateFiles(){

        std::unordered_map<std::string, apiDataClass> *dateData = new std::unordered_map<std::string, apiDataClass>(); // hash table <key is date in format
    
        readFiles("data/v1usdaily.csv", dateData);

        for (auto i : *dateData){
            std::cout << "The key read from data file: "  << i.first << std::endl;
        }
        
    }

    void test_runGrpahics(){
        
    }

};

#endif