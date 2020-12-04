
// c++ libs
#include <iostream>
#include <fstream>  // to read from the files
#include <string>   //
#include <sstream>
#include <unordered_map> // Hash map

//custom libs
#include "dataStructures.h"



//******************************** API CODE *****************************************//
int main(int argc, char* argv[])
{
    //apiCall();
    std::unordered_map<double, nationalHistory> *data = new std::unordered_map<double, nationalHistory>(); // hash table <key is date in format
    readFiles("data/national-history.csv", data);
    // here is where graphics can get implemented, I have called the api and gotten data and put in the data map
    // the data is a key value data structure where the key is the month.date as a decimal so march 3rd is 3.03
    // and the value is our nationalHistory data type defined in dataStrucutres


    return 0;
}
