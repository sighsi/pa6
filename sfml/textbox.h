#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Graphics.hpp>
#include <iostream>

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

    Textbox(){}

    Textbox(sf::Vector2f position, int char_size, std::string to_write, sf::Font &font, sf::Color color) 
    {
        
        std::cout << "In text constructor";
        this->box_text.setString(to_write);
        this->box_text.setFont(font);
        this->box_text.setPosition(sf::Vector2f(205.0f ,95.0f));
        this->box_text.setFillColor(color);
        this->box_text.setCharacterSize(char_size);
        
    }

    Textbox(sf::Vector2f location, sf::Vector2f size, sf::Font &font)
    {
        
        box.setPosition(location);
       // box.setTexture(&texture);
        box.setSize(size);
        box.setOutlineColor(sf::Color(150,150,150,220));
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


#endif