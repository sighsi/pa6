
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

std::string API_BASE = "https://api.covidtracking.com";
std::string API_CURRENT_US_VALUES = "/v1/us/current.csv"; // Button 1
std::string API_DAILY_VALUES = "/v1/us/daily.csv";        // button 2
std::string API_DATE_PART1 = "/v1/us/";                   // enter "20200501" to get may first
std::string API_DATE_PART2 = ".csv";
std::string API_STATE_VALUES = "/v1/states/info.csv"; // state values
std::string API_SPEC_STATE_PT1 = "/v1/states/{state}/info.csv"; ///v1/status.csv
int NUMBTNS = 7;

//******************************** API CODE *****************************************//
int main(int argc, char *argv[])
{
    apiCall(API_CURRENT_US_VALUES);
    std::unordered_map<double, nationalHistory> *data = new std::unordered_map<double, nationalHistory>(); // hash table <key is date in format
    readFiles("data/national-history.csv", data);

    sf::RenderWindow Window(sf::VideoMode(800, 600), "Covid-tracker");

    sf::Texture background;
    background.loadFromFile("blk.png");

    sf::Texture btn;
    btn.loadFromFile("botton.png");

    sf::Texture grn;
    sf::RectangleShape back_g(sf::Vector2f(800.0f, 600.0f));
    back_g.setTexture(&background);


    sf::Font ocra;
    ocra.loadFromFile("OCRAEXT.TTF");

    std::vector<Button> button_vec;
    Button btn0(70.0 * 0, sf::Vector2f(150.0f, 70.0f), sf::Color::Cyan, "Current US Info", ocra); // URL: 
    Button btn1(70.0 * 1, sf::Vector2f(150.0f, 70.0f), sf::Color::Cyan, "Cases By Day", ocra);
    Button btn2(70.0 * 2, sf::Vector2f(150.0f, 70.0f), sf::Color::Cyan, "API Status", ocra);
    Button btn3(70.0 * 3, sf::Vector2f(150.0f, 70.0f), sf::Color::Cyan, "btn3", ocra);
    Button btn4(70.0 * 4, sf::Vector2f(150.0f, 70.0f), sf::Color::Cyan, "btn4", ocra);
    Button btn5(70.0 * 5, sf::Vector2f(150.0f, 70.0f), sf::Color::Cyan, "btn5", ocra);
    Button btn6(70.0 * 6, sf::Vector2f(150.0f, 70.0f), sf::Color::Cyan, "btn6", ocra);

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
    text_sq.setPosition(200, 50);
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
    int cur_btn = 0;

    Window.setKeyRepeatEnabled(false);
    while (Window.isOpen())
    {
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

        for (int i = 0; i < 7; i++)
        {
            butt_arr[i].draw_to_screen(Window);
        }

        Window.display();
    }

    return 0;
}
