// REST
// #include <cpprest/http_client.h>
// #include <cpprest/filestream.h>

// c++ libs
#include <iostream>
#include <fstream>  // to read from the files
#include <string>   //
#include <sstream>
#include <unordered_map> // Hash map

//custom libs
#include <dataStructures.h>

// using namespace utility;                    // Common utilities like string conversions
// using namespace web;                        // Common features like URIs.
// using namespace web::http;                  // Common HTTP functionality
// using namespace web::http::client;          // HTTP client features
// using namespace concurrency::streams;       // Asynchronous streams





void readFiles(std::string fileName, std::unordered_map<double, nationalHistory> *&);
int main (){
    std::unordered_map<double, nationalHistory> *data = new std::unordered_map<double, nationalHistory>(); // hash table <key is date in format

    readFiles("national-history.csv", data);


    return 0;
}












void readFiles(std::string fileName, std::unordered_map<double, nationalHistory> *& data){
    std::fstream f;
    f.open(fileName);
    if (!f.is_open()) std::cout << "Error reading destinations" << std::endl;

    std::string line;

    std::string date;
    std::string death;
    std::string deathIncrease;
    std::string inIcuCumulative;
    std::string inIcuCurrently;
    std::string hospitalizedIncrease;
    std::string hospitalizedCurrently;
    std::string hospitalizedCumulative;
    std::string negative;
    std::string negativeIncrease;
    std::string onVentilatorCumulative;
    std::string onVentilatorCurrently;
    std::string positive;
    std::string positiveIncrease;
    std::string recovered;
    std::string states;
    std::string totalTestResults;
    std::string totalTestResultsIncrease;

    getline(f, line, '\n'); // throws away all the labels
    while (getline(f, line, '\n')){
        std::istringstream tokenStream(line);
        tokenStream.fill(); 
        getline(tokenStream, date,',');
        getline(tokenStream, death,',');
        getline(tokenStream, deathIncrease,',');
        getline(tokenStream, inIcuCumulative,',');
        getline(tokenStream, inIcuCurrently,',');
        getline(tokenStream, hospitalizedIncrease,',');
        getline(tokenStream, hospitalizedCurrently,',');
        getline(tokenStream, hospitalizedCumulative,',');
        getline(tokenStream, negative,',');
        getline(tokenStream, negativeIncrease,',');
        getline(tokenStream, onVentilatorCumulative,',');
        getline(tokenStream, onVentilatorCurrently,',');
        getline(tokenStream, positive,',');
        getline(tokenStream, positiveIncrease,',');
        getline(tokenStream, recovered,',');
        getline(tokenStream, states,',');
        getline(tokenStream, totalTestResults,',');
        getline(tokenStream, totalTestResultsIncrease,'\r');
        nationalHistory nH;
//getting date        // nH.date = std::stoi( date);//"2020-12-01"
        date = date.substr(1,10);
        nH.year = std::stoi (date.substr(0,4));
        nH.month = std::stoi (date.substr(5,7));
        nH.day = std::stoi (date.substr(9,10));

        nH.death = (death.compare("") == 0) ? : std::stoi( death);
        nH.deathIncrease = (deathIncrease.compare("") == 0) ? : std::stoi( deathIncrease);
        nH.inIcuCumulative = (inIcuCumulative.compare("") == 0) ? : std::stoi( inIcuCumulative);
        nH.inIcuCurrently = (inIcuCurrently.compare("") == 0) ? : std::stoi( inIcuCurrently);
        nH.hospitalizedIncrease = (hospitalizedIncrease.compare("") == 0) ? : std::stoi( hospitalizedIncrease);
        nH.hospitalizedCurrently = (hospitalizedCurrently.compare("") == 0) ? : std::stoi( hospitalizedCurrently);
        nH.hospitalizedCumulative = (hospitalizedCumulative.compare("") == 0) ? : std::stoi( hospitalizedCumulative);
        nH.negative = (negative.compare("") == 0) ? : std::stoi( negative);
        nH.negativeIncrease = (negativeIncrease.compare("") == 0) ? : std::stoi( negativeIncrease);
        nH.onVentilatorCumulative = (onVentilatorCumulative.compare("") == 0) ? : std::stoi( onVentilatorCumulative);
        nH.onVentilatorCurrently = (onVentilatorCurrently.compare("") == 0) ? : std::stoi( onVentilatorCurrently);
        nH.positive = (positive.compare("") == 0) ? : std::stoi( positive);
        nH.positiveIncrease = (positiveIncrease.compare("") == 0) ? : std::stoi( positiveIncrease);
        nH.recovered = (recovered.compare("") == 0) ? : std::stoi( recovered);
        nH.states = (states.compare("") == 0) ? : std::stoi( states);
        nH.totalTestResults = (totalTestResults.compare("") == 0) ? : std::stoi( totalTestResults);
        nH.totalTestResultsIncrease = (totalTestResultsIncrease.compare("") == 0) ? : std::stoi( totalTestResultsIncrease);
        // double decimal = (nH.day < 10) ? ((double)nH.day /100) : ((double)nH.day /100);
        double monthYear = (double)nH.month + ((double)nH.day /100);
        data -> emplace(monthYear, nH);


        // CancerData t = {token1, stof(token2)};
        // AVLNode<CancerData> *node = new AVLNode<CancerData>(t); 
        // avl-> insert(node);
    }
    f.close();
}




//******************************** API CODE *****************************************//
/*
int main(int argc, char* argv[])
{
    auto fileStream = std::make_shared<ostream>();

    // Open stream to output file.
    pplx::task<void> requestTask = fstream::open_ostream(U("results.html")).then([=](ostream outFile)
    {
        *fileStream = outFile;

        // Create http_client to send the request.
        http_client client(U("http://www.bing.com/"));

        // Build request URI and start the request.
        uri_builder builder(U("/search"));
        builder.append_query(U("q"), U("cpprestsdk github"));
        return client.request(methods::GET, builder.to_string());
    })

    // Handle response headers arriving.
    .then([=](http_response response)
    {
        printf("Received response status code:%u\n", response.status_code());

        // Write response body into the file.
        return response.body().read_to_end(fileStream->streambuf());
    })

    // Close the file stream.
    .then([=](size_t)
    {
        return fileStream->close();
    });

    // Wait for all the outstanding I/O to complete and handle any exceptions
    try{
        requestTask.wait();
    }
    catch (const std::exception &e)
    {
        printf("Error exception:%s\n", e.what());
    }
    return 0;
}
*/