#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

// c++ libs
#include <iostream>
#include <string>
#include <fstream> // to read from the files
#include <string>  //
#include <sstream>
#include <unordered_map> // Hash map
#include <memory>

//CUSTOM LIBRARIES
#include "button.h"
#include "Textbox.h"
#include "test.h"

//external libraries:
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams


std::string API_DAILY_VALUES =      "/v1/us/daily.csv";        // THIS IS THE ONLY ONE WE NEED
std::string API_STATE_VALUES =      "/v1/states/current.csv";           // state values
std::string DATA_FILE_PATH =        "data/"; 
std::string TODAYS_DATE;
int NUMBTNS = 7;

class apiDataClass { 
    public:
    apiDataClass(){};
    std::string date, 
                states,
                positive,
                negative,
                pending,
                hospitalizedCurrently,
                hospitalizedCumulative,
                inIcuCurrently,
                inIcuCumulative,
                onVentilatorCurrently,
                onVentilatorCumulative,
                recovered,
                dateChecked, // strring?
                death,
                hospitalized,
                totalTestResults,
                lastModified, // string --> depreciated
                total,
                posNeg,
                deathIncrease,
                hospitalizedIncrease,
                negativeIncrease,
                positiveIncrease,
                totalTestResultsIncrease,
                hash;


};

class stateData {
public:
    stateData(){};
    std::string date,
                state,
                positive,
                probableCases,
                negative,
                pending,
                totalTestResultsSource,
                totalTestResults,
                hospitalizedCurrently,
                hospitalizedCumulative,
                inIcuCurrently,
                inIcuCumulative,
                onVentilatorCurrently,
                onVentilatorCumulative,
                recovered,
                dataQualityGrade,
                lastUpdateEt,
                dateModified,
                checkTimeEt,
                death,
                hospitalized,
                dateChecked,
                totalTestsViral,
                positiveTestsViral,
                negativeTestsViral,
                positiveCasesViral,
                deathConfirmed,
                deathProbable,
                totalTestEncountersViral,
                totalTestsPeopleViral,
                totalTestsAntibody,
                positiveTestsAntibody,
                negativeTestsAntibody,
                totalTestsPeopleAntibody,
                positiveTestsPeopleAntibody,
                negativeTestsPeopleAntibody,
                totalTestsPeopleAntigen,
                positiveTestsPeopleAntigen,
                totalTestsAntigen,positiveTestsAntigen,
                fips,positiveIncrease,
                negativeIncrease,
                total,
                totalTestResultsIncrease,
                posNeg,
                deathIncrease,
                hospitalizedIncrease,
                hash,
                commercialScore,
                negativeRegularScore,
                negativeScore,
                positiveScore,
                score,
                grade;

};

void apiCall(std::string apiExtension) ;
void reset_indicators(Button button_arr[], int cur_select);
void run_program(std::unordered_map<std::string, apiDataClass> *& , std::unordered_map<std::string, stateData> *&);
void readFiles(std::string fileName, std::unordered_map<std::string, apiDataClass> *& data);
void readStateFiles(std::string fileName, std::unordered_map<std::string, stateData> *& data);
void printDateData(std::unordered_map<std::string, apiDataClass> *& data, sf::RenderWindow &window ,Textbox &tb ,std::string date);
void printStateData(std::unordered_map<std::string, stateData> *& state, sf::RenderWindow &window ,Textbox &tb , std::string statestr); 


#endif