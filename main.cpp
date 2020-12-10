
// c++ libs
#include <iostream>
#include <string>
#include <fstream> // to read from the files
#include <string>  //
#include <sstream>
#include <unordered_map> // Hash map
#include <memory>

//external libraries:
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
//custom libs
#include "functions.h"
#include "button.h"

//REST
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
using namespace utility;              // Common utilities like string conversions
using namespace web;                  // Common features like URIs.
using namespace web::http;            // Common HTTP functionality
using namespace web::http::client;    // HTTP client features
using namespace concurrency::streams; // Asynchronous streams

std::string API_BASE =              "https://api.covidtracking.com";
std::string API_CURRENT_US_VALUES = "/v1/us/current.csv"; // Button 1
std::string API_DAILY_VALUES =      "/v1/us/daily.csv";        // THIS IS THE ONLY ONE WE NEED
std::string API_DATE_PART1 =        "/v1/us/";                   // enter "20200501" to get may first
std::string API_FILE_EXTENSION =    ".csv";
std::string API_STATE_VALUES =      "/v1/states/daily.csv";           // state values


std::string DATA_FILE_PATH =        "data/";
std::string TODAYS_DATE;
int NUMBTNS = 7;
/**
 * MEETING NOTES:
 *  BTN0: SHOWS TODAYS DATA
 *  BTN1: GET DATA FROM A DATE TEXTBOX
 *  BTN2: SHOW WASHINGTON DATA
 *  BTN3: GRAB STATE STRING FROM TEXTBOX AND DISPLAY STATE DATA
*   BTN4: CHAT BOX
 *  BTN5: COLORADO DATA
 *  BTN6: HELP -> FEATURES/ OF THE PROGRAM AND ALSO SHOWS API STATUS
 * 
 * TODO:
 *      silas:  1) create a state data structure
 *          2)  
 *  Connor
 * 
 *  Daniel:
 * 
 * 
 */ 

//*************************************************************************************\\
//**************************** button class     *************************************\\
//*************************************************************************************\\
//*************************************************************************************\\
//*************************************************************************************\\

class Button
{

private:
    sf::RectangleShape rect;
    sf::CircleShape indicator;
    sf::Texture butt_texture;
    sf::Texture rect_texture;
    sf::Text label;

public:
    Button() {}

    Button(float ypos, sf::Vector2f size, sf::Texture &texture, sf::Color color) // do not use this one yet not fully done.
    {
        rect.setPosition(sf::Vector2f(0.0, ypos));
        rect.setSize(size);
        rect.setTexture(&texture);
        rect.setFillColor(color);
        indicator.setPosition(sf::Vector2f(size.x * double(3 / 4), ypos + size.y / 2)); //might need to fiddle with this connor. - connor 12/7

        if (!butt_texture.loadFromFile("images/botton.png"))
            ;
        {
            std::cout << "\nError indicator texture failed to load.\n";
        }
        indicator.setTexture(&butt_texture);
    }

    Button(float ypos, sf::Vector2f size, sf::Color color, std::string label, sf::Font &font) //loads botton with default texture.
    {

        rect.setPosition(sf::Vector2f(0.0, ypos));
        rect.setSize(size);

        this->label.setString(label);
        this->label.setPosition(sf::Vector2f(15.0, ypos + size.y * .33));
        this->label.setFillColor(sf::Color::White);
        this->label.setFont(font);

        if (!butt_texture.loadFromFile("images/texture.png"))
        {
            std::cout << "\nError! indicator texture failed to load.\n";
        }
        if (!rect_texture.loadFromFile("images/botton.png"))
        {
            std::cout << "\nError botton texture failed to load.\n";
        }

        rect.setTexture(&rect_texture);
        rect.setFillColor(color);
        indicator.setPosition(sf::Vector2f(size.x * 3 / 4, ypos + size.y * .33)); //might need to fiddle with this connor. - connor 12/7
        std::cout << "yo";
        indicator.setRadius(15.0f);
        indicator.setTexture(&butt_texture);
        indicator.setFillColor(sf::Color::Red);
    }

    void draw_to_screen(sf::RenderWindow &window)
    {
        window.draw(rect);
        window.draw(indicator);
        window.draw(label);
    }

    sf::Vector2f get_pos() const
    {
        return rect.getSize();
    }

    sf::Vector2f get_size() const
    {
        return rect.getSize();
    }

    bool hover(sf::Window &window) // needs to be edited if you are going to use with buttons not on left of screen. -connor 12/8
    {
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        if (mouse_pos.x < rect.getSize().x && mouse_pos.y < (rect.getSize().y + rect.getPosition().y) && mouse_pos.y > (rect.getPosition().y))
        {
            return true;
        }
        return false;
    }

    void set_indicator(bool selected)
    {
        if (selected)
        {
            indicator.setFillColor(sf::Color::Green);
        }
        else
        {
            indicator.setFillColor(sf::Color::Red);
        }
    }

    void set_font(sf::Font &font)
    {
        label.setFont(font);
    }

    void set_indicator(sf::Color color)
    {
        indicator.setFillColor(color);
    }

    void set_size(sf::Vector2f new_size)
    {
        rect.setSize(new_size);
    }

    void set_color(sf::Color color)
    {
        rect.setFillColor(color);
    }
};
//*************************************************************************************\\
//**************************** test box class     *************************************\\
//*************************************************************************************\\
//*************************************************************************************\\
//*************************************************************************************\\

class Textbox
{
private:
    sf::RectangleShape box;
    sf::Text box_text;
    sf::Texture box_texture;
    bool selected = false;
    bool writable = false;
    bool text_full = false;

public:
    Textbox() {}

    Textbox(sf::Vector2f position, int char_size, std::string to_write, sf::Font &font, sf::Color color)
    {

        std::cout << "In text constructor";
        this->box_text.setString(to_write);
        this->box_text.setFont(font);
        this->box_text.setPosition(sf::Vector2f(position));
        this->box_text.setFillColor(color);
        this->box_text.setCharacterSize(char_size);
    }

    Textbox(sf::Vector2f location, sf::Vector2f size, sf::Font &font)
    {

        box.setPosition(location);
        // box.setTexture(&texture);
        box.setSize(size);
        box.setOutlineColor(sf::Color(150, 150, 150, 220));
        // box.setOutlineColor(sf::Color::Green);
        box.setOutlineThickness(2.5f);

        box_text.setFont(font);
    }

    Textbox(sf::Vector2f location, sf::Texture &texture, sf::Vector2f size, sf::Font &font)
    {
        box.setPosition(location);
        box.setTexture(&texture);
        box.setSize(size);
        //box.setOutlineColor(sf::Color(150,150,150,220));

        box_text.setFont(font);
    }

    void draw_to_screen(sf::RenderWindow &window)
    {
        window.draw(box);
        window.draw(box_text);
    }

    void set_box_pos(sf::Vector2f pos)
    {
        this->box.setPosition(pos);
    }

    void set_box_color(sf::Color color)
    {
        this->box.setFillColor(color);
    }

    void set_text(std::string str)
    {
        this->box_text.setString(str);
    }

    void set_text_size(int char_size)
    {
        this->box_text.setCharacterSize(char_size);
    }
};

class apiDataClass { // titled this way bc that's the name of the csv file I downloaded from their website

    public:
        apiDataClass(){}

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
                totalTestResultsIncrease;
    std::string hash;


};



void apiCall(std::string);
void reset_indicators(Button button_arr[], int cur_select);
void run_program(std::unordered_map<std::string, apiDataClass> *& data);
void readFiles(std::string fileName, std::unordered_map<std::string, apiDataClass> *& data);

void printDateData(std::unordered_map<std::string, apiDataClass> *& data, std::string date);
// void button1Function(std::unordered_map<std::string, apiDataClass> *& data), std::string date;
void button2Function(std::unordered_map<std::string, apiDataClass> *& data);
void button3Function(std::unordered_map<std::string, apiDataClass> *& data);
void button4Function(std::unordered_map<std::string, apiDataClass> *& data);
void button5Function(std::unordered_map<std::string, apiDataClass> *& data);

//******************************** MAIN MAIN MAIN *****************************************//
//******************************** MAIN MAIN MAIN *****************************************//
//******************************** MAIN MAIN MAIN *****************************************//
//******************************** MAIN MAIN MAIN *****************************************//
//******************************** MAIN MAIN MAIN *****************************************//
//******************************** MAIN MAIN MAIN *****************************************//

int main(int argc, char *argv[])
{
    apiCall(API_DAILY_VALUES);
    // apiCall(API_STATE_VALUES);
    std::unordered_map<std::string, apiDataClass> *data = new std::unordered_map<std::string, apiDataClass>(); // hash table <key is date in format
    readFiles("data/v1usdaily.csv", data); ///v1/states/daily.csv" ///v1/us/daily.csv

    run_program(data);
    return 0;
}

//*************************************************************************************\\
//*************************************************************************************\\
//**************************** API CALL           *************************************\\
//*************************************************************************************\\
//*************************************************************************************\\
//*************************************************************************************\\

void apiCall(std::string apiExtension)
{
    std::string fileName = apiExtension;
    fileName.erase(std::remove(fileName.begin(), fileName.end(), '/'), fileName.end());
    // std::size_t found = fileName.find('/');
    // while (found != std::string::npos){
    //     fileName = fileName.substr(found +1);
    //     std::cout << "the substring: " << fileName << std::endl;
    //     found = fileName.find("/");
    // }
    std::cout << "the substring: " << fileName << std::endl;
    fileName = DATA_FILE_PATH + fileName;
    auto fileStream = std::make_shared<ostream>();
    // Open stream to output file.
    pplx::task<void> requestTask = fstream::open_ostream(U(fileName))
                                        .then([=](ostream outFile) {
                                            *fileStream = outFile;

                                            // Create http_client to send the request.
                                            http_client client(U("https://api.covidtracking.com")); //https://api.covidtracking.com    /v1/us/current.csv

                                            // Build request URI and start the request.
                                            uri_builder builder(U(apiExtension));
                                            // builder.append_query(U("q"), U("cpprestsdk github"));
                                            return client.request(methods::GET, builder.to_string());
                                            })

                                       // Handle response headers arriving.
                                       .then([=](http_response response) {
                                           printf("Received response status code:%u\n", response.status_code());
                                           // Write response body into the file.
                                           return response.body().read_to_end(fileStream->streambuf());
                                       })

                                       // Close the file stream.
                                       .then([=](size_t) {
                                           return fileStream->close();
                                       });

    // Wait for all the outstanding I/O to complete and handle any exceptions
    try
    {
        requestTask.wait();
    }
    catch (const std::exception &e)
    {
        printf("Error exception:%s\n", e.what());
    }

    //return *statusCode;
}

//*************************************************************************************\\
//*************************************************************************************\\
//**************************** FUNCTIONS           ************************************\\
//*************************************************************************************\\
//*************************************************************************************\\
//*************************************************************************************\\

void reset_indicators(Button button_arr[], int cur_select)
{
    for (int i = 0; i < 7; i++) //update this so it doesn't depend on magic num connor. -connor 12/8/20
    {
        if (i == cur_select)
        {
            continue;
        }
        button_arr[i].set_indicator(false); //
    }
}



void printDateData(std::unordered_map<std::string, apiDataClass> *& data, std::string date = TODAYS_DATE) 
{
    auto todayData = data->find(date);
    date.insert(4, "/");
    date.insert(7, "/");
    std::cout << "The date: " << date  << std::endl;
    std::cout << "Number of cases is " << todayData -> second.positive << std::endl;
    std::cout << "The death toll: " << todayData -> second.death << std::endl;
    std::cout << "Amount increase from the day before: " << todayData -> second.death << std::endl;
    std::cout << "Number of cases is: " << todayData -> second.positive << std::endl;
    std::cout << "Number of recovered cases: " << todayData -> second.recovered << std::endl;

}

void button2Function(std::unordered_map<std::string, apiDataClass> *& data) 
{
std::cout << "case 2" << std::endl;
}
void button3Function(std::unordered_map<std::string, apiDataClass> *& data) 
{std::cout << "case 3" << std::endl;

}
void button4Function(std::unordered_map<std::string, apiDataClass> *& data) 
{
std::cout << "case 4" << std::endl;
}
void button5Function(std::unordered_map<std::string, apiDataClass> *& data) 
{
std::cout << "case 5" << std::endl;
}





void run_program(std::unordered_map<std::string, apiDataClass> *& data) {

    sf::RenderWindow Window(sf::VideoMode(800, 600), "Covid-tracker");

    sf::Texture background;
    background.loadFromFile("images/blk.png");

    sf::Texture btn;
    btn.loadFromFile("images/botton.png");

    sf::Texture grn;
    //grn.loadFromFile("green.png");

    sf::RectangleShape back_g(sf::Vector2f(800.0f, 600.0f));
    back_g.setTexture(&background);

    sf::Font ocra;
    ocra.loadFromFile("images/OCRAEXT.TTF");

    //(sf::Vector2f location, sf::Vector2f size, sf::Font &font)
    Textbox state_input(sf::Vector2f(550.0f, 30.0f), sf::Vector2f(200.0f, 35.0f), ocra);
    //state_i
    state_input.set_text_size(25);
    state_input.set_box_color(sf::Color(170, 170, 170, 220));
    sf::Text state_label;
    state_label.setFont(ocra);
    state_label.setString("State:");
    state_label.setCharacterSize(20);
    state_label.setPosition(sf::Vector2f(475.0f, 33.0f));
    state_label.setFillColor(sf::Color::Red);
    // Textbox(sf::Vector2f position, int char_size, std::string to_write, sf::Font &font, sf::Color)
    //                            x  y
    Textbox help_str(sf::Vector2f(0, 0), 15, "help", ocra, sf::Color::White);

    //float ypos, sf::Vector2f size, sf::Color color, std::string label, sf::Font & font
    Button btn0(70.0 * 0, sf::Vector2f(150.0f, 70.0f), sf::Color::Cyan, "Current Data", ocra);
    Button btn1(70.0 * 1, sf::Vector2f(150.0f, 70.0f), sf::Color::Cyan, "btn1", ocra);
    Button btn2(70.0 * 2, sf::Vector2f(150.0f, 70.0f), sf::Color::Cyan, "btn2", ocra);
    Button btn3(70.0 * 3, sf::Vector2f(150.0f, 70.0f), sf::Color::Cyan, "btn3", ocra);
    Button btn4(70.0 * 4, sf::Vector2f(150.0f, 70.0f), sf::Color::Cyan, "btn4", ocra);
    Button btn5(70.0 * 5, sf::Vector2f(150.0f, 70.0f), sf::Color::Cyan, "btn5", ocra);
    Button btn6(70.0 * 6, sf::Vector2f(150.0f, 70.0f), sf::Color::Cyan, "help", ocra);

    Button butt_arr[7];
    butt_arr[0] = btn0;
    butt_arr[1] = btn1;
    butt_arr[2] = btn2;
    butt_arr[3] = btn3;
    butt_arr[4] = btn4;
    butt_arr[5] = btn5;
    butt_arr[6] = btn6;

    sf::Vector2u size(400, 400);
    std::string message = "Hi my name is connor.";
    std::string display = "";
    sf::RectangleShape square_0(sf::Vector2f(150.0f, 70.0f));
    sf::CircleShape circle_0;
    circle_0.setRadius(20.0f);
    sf::RectangleShape square_1(sf::Vector2f(150.0f, 70.0f));
    sf::RectangleShape square_2(sf::Vector2f(150.0f, 70.0f));
    sf::RectangleShape square_3(sf::Vector2f(150.0f, 70.0f));
    sf::RectangleShape square_4(sf::Vector2f(150.0f, 70.0f));
    sf::RectangleShape square_5(sf::Vector2f(150.0f, 70.0f));
    sf::RectangleShape text_sq(sf::Vector2f(550.0f, 470.0f));
    text_sq.setFillColor(sf::Color(47, 79, 79, 200));
    text_sq.setPosition(200, 90);
    text_sq.setOutlineColor(sf::Color(35, 67, 67, 220));
    text_sq.setOutlineThickness(2.5f);
    sf::CircleShape circle_1(20.0f);
    sf::CircleShape circle_2(20.0f);
    sf::CircleShape circle_3(20.0f);
    sf::CircleShape circle_4(20.0f);
    sf::CircleShape circle_5(20.0f);

    square_1.setPosition(sf::Vector2f(0, 70.0f));
    square_1.setFillColor(sf::Color::Green);
    square_1.setOutlineColor(sf::Color::Black);
    // square_1.setOutlineThickness(-2.0);
    square_2.setPosition(0, 140.0);
    square_1.setTexture(&btn);
    // circle_0.setFillColor(sf::Color::Green);
    circle_0.setTexture(&grn);
    circle_0.setPosition(sf::Vector2f(125.0F, 17.5f));
    square_0.setFillColor(sf::Color::Cyan);
    square_0.setTexture(&btn);
    std::cout << size.x << " " << size.y << std::endl;

    square_2.setFillColor(sf::Color::Cyan);
    square_2.setTexture(&btn);
    Window.setSize(sf::Vector2u(800, 600));

    int index = 0;
    int cur_btn = -1;

    Window.setKeyRepeatEnabled(false);

    while (Window.isOpen())
    {
        for (int i = 0; i < 7; i++)
        {
            butt_arr[i].draw_to_screen(Window);
        }
        state_input.draw_to_screen(Window);
        Window.draw(state_label);
        Window.draw(text_sq);

        sf::Event Event;
        while (Window.pollEvent(Event))
        {

            switch (Event.type)
            {
            case sf::Event::Closed:
                Window.close();
                break;
            case sf::Event::MouseMoved:
            {
                for (int i = 0; i < NUMBTNS; i++)
                {
                    if (butt_arr[i].hover(Window))
                    {
                        butt_arr[i].set_color(sf::Color::Green);
                    }
                    else
                    {
                        {
                            butt_arr[i].set_color(sf::Color::Cyan);
                        }
                    }
                }
            }

            //std::cout << "Mouse within bounds" << std::endl;
            break;
            case sf::Event::MouseLeft:
                std::cout << "Mouse not within bounds" << std::endl;
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {

                sf::Vector2i cur_pos = sf::Mouse::getPosition(Window);
                if (cur_pos.x < 150 && cur_pos.y <= 70)
                {
                    butt_arr[0].set_indicator(true);
                    cur_btn = 0;
                    reset_indicators(butt_arr, 0);
                }
                else if (cur_pos.x < 150 && cur_pos.y <= 140)
                {
                    butt_arr[1].set_indicator(true);
                    cur_btn = 1;
                    reset_indicators(butt_arr, 1);
                }
                else if (cur_pos.x < 150 && cur_pos.y <= 210)
                {
                    butt_arr[2].set_indicator(true);
                    cur_btn = 2;
                    reset_indicators(butt_arr, 2);
                }
                else if (cur_pos.x < 150 && cur_pos.y <= 280)
                {
                    butt_arr[3].set_indicator(true);
                    cur_btn = 3;
                    reset_indicators(butt_arr, 3);
                }
                else if (cur_pos.x < 150 && cur_pos.y <= 350)
                {
                    butt_arr[4].set_indicator(true);
                    cur_btn = 4;
                    reset_indicators(butt_arr, 4);
                }
                else if (cur_pos.x < 150 && cur_pos.y <= 420)
                {
                    butt_arr[5].set_indicator(true);
                    cur_btn = 5;
                    reset_indicators(butt_arr, 5);
                }
                else if (cur_pos.x < 150 && cur_pos.y <= 490)
                {
                    butt_arr[6].set_indicator(true);
                    cur_btn = 6;
                    reset_indicators(butt_arr, 6);
                }
            }
        }
        switch (cur_btn){
            case -1:
                break;
            case 0:
                std::cout <<"button 0 pressed" << std::endl;
                printDateData(data);
                cur_btn = -1;
                break;
            case 1:
                printDateData(data, "20200805"); // just an example string
                cur_btn = -1;
                break;
            case 2:
                button2Function(data);
                cur_btn = -1;
                break;
            case 3:
                button3Function(data);
                cur_btn = -1;
                break;
            case 4:
                button4Function(data);
                cur_btn = -1;
                break;
            case 5:

                cur_btn = -1;
                std::cout << "case 5";
                break;
            case 6:
                //std::cout << "case 6";
                help_str.draw_to_screen(Window);
                break;
        }

        Window.display();
    }
}



void readFiles(std::string fileName, std::unordered_map<std::string, apiDataClass> *& data)
{
    std::fstream f;
    f.open( fileName);
    if (!f.is_open()) std::cout << "Error reading destinations" << std::endl;

    std::string line;

    std::string date; 
    std::string states;
    std::string positive;
    std::string negative;
    std::string pending;
    std::string hospitalizedCurrently;
    std::string hospitalizedCumulative;
    std::string inIcuCurrently;
    std::string inIcuCumulative;
    std::string onVentilatorCurrently;
    std::string onVentilatorCumulative;
    std::string recovered;
    std::string dateChecked; // strring?
    std::string death;
    std::string hospitalized;
    std::string totalTestResults;
    std::string lastModified; // string --> depreciated
    std::string total;
    std::string posNeg;
    std::string deathIncrease;
    std::string hospitalizedIncrease;
    std::string negativeIncrease;
    std::string positiveIncrease;
    std::string totalTestResultsIncrease;
    std::string hash;
    bool firstIteration = true;
    getline(f, line, '\n'); // throws away all the labels
    while (getline(f, line, '\n')) {
        apiDataClass nH;
        std::istringstream tokenStream(line);
        tokenStream.fill(); 
        getline(tokenStream, date,',');
        getline(tokenStream, states, ',');
        getline(tokenStream, positive, ',');
        getline(tokenStream, negative, ',');
        getline(tokenStream, pending, ',');
        getline(tokenStream, hospitalizedCurrently, ',');
        getline(tokenStream, hospitalizedCumulative, ',');
        getline(tokenStream, inIcuCurrently, ',');
        getline(tokenStream, inIcuCumulative, ',');
        getline(tokenStream, onVentilatorCurrently, ',');
        getline(tokenStream, onVentilatorCumulative, ',');
        getline(tokenStream, recovered, ',');
        getline(tokenStream, dateChecked, ',');
        getline(tokenStream, death, ',');
        getline(tokenStream, hospitalized, ',');
        getline(tokenStream, totalTestResults, ',');
        getline(tokenStream, lastModified, ',');
        getline(tokenStream, total, ',');
        getline(tokenStream, posNeg, ',');
        getline(tokenStream, deathIncrease, ',');
        getline(tokenStream, hospitalizedIncrease, ',');
        getline(tokenStream, negativeIncrease, ',');
        getline(tokenStream, positiveIncrease, ',');
        getline(tokenStream, totalTestResultsIncrease, ',');
        getline(tokenStream, hash, '\r');

        if (firstIteration) {
            TODAYS_DATE = date; 
            firstIteration = false;
        }

        nH.date = date;
        nH.states = states;
        nH.positive = positive;
        nH.negative = negative;
        nH.pending = pending;
        nH.hospitalizedCurrently = hospitalizedCurrently;
        nH.hospitalizedCumulative = hospitalizedCumulative;
        nH.inIcuCurrently = inIcuCurrently;
        nH.inIcuCumulative = inIcuCumulative;
        nH.onVentilatorCurrently = onVentilatorCurrently;
        nH.onVentilatorCumulative = onVentilatorCumulative;
        nH.recovered = recovered;
        nH.dateChecked = dateChecked;
        nH.death = death;
        nH.hospitalized = hospitalized;
        nH.totalTestResults = totalTestResults;
        nH.lastModified = lastModified;
        nH.total = total;
        nH.posNeg = posNeg;
        nH.deathIncrease = deathIncrease;
        nH.hospitalizedIncrease = hospitalizedIncrease;
        nH.negativeIncrease = negativeIncrease;
        nH.positiveIncrease = positiveIncrease;
        nH.totalTestResultsIncrease = totalTestResultsIncrease;
        nH.hash = hash;
        data -> emplace(date, nH);
    }
    f.close();
}