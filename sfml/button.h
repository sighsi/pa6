#ifndef BUTTON
#define BUTTON

#include <SFML/Graphics.hpp>
#include <iostream>
#define NUMBTNS 7
class Button
{

private:
sf::RectangleShape rect;
sf::CircleShape indicator; 
sf::Texture butt_texture; 
sf::Texture rect_texture;
sf::Text label;

public:

Button(){}

Button (float ypos, sf::Vector2f size, sf::Texture &texture, sf::Color color) // do not use this one yet not fully done.
{
    rect.setPosition(sf::Vector2f(0.0, ypos));
    rect.setSize(size);
    rect.setTexture(&texture);
    rect.setFillColor(color);
    indicator.setPosition(sf::Vector2f(size.x*double(3/4), ypos + size.y / 2)); //might need to fiddle with this connor. - connor 12/7
    
    if(!butt_texture.loadFromFile("botton.png"));
    {
        std::cout << "\nError indicator texture failed to load.\n";
    }
    indicator.setTexture(&butt_texture);


}

Button (float ypos, sf::Vector2f size, sf::Color color, std::string label, sf::Font & font)//loads botton with default texture.
{

    

    rect.setPosition(sf::Vector2f(0.0, ypos));
    rect.setSize(size);

    this->label.setString(label);
    this->label.setPosition(sf::Vector2f(15.0, ypos + size.y * .33 ));
    this->label.setFillColor(sf::Color::White);
    this->label.setFont(font);

    if(!butt_texture.loadFromFile("texture.png"))
    {
        std::cout << "\nError! indicator texture failed to load.\n";
    }
    if(!rect_texture.loadFromFile("botton.png"))
    {
        std::cout << "\nError botton texture failed to load.\n";
    }


    rect.setTexture(&rect_texture);
    rect.setFillColor(color);
    indicator.setPosition(sf::Vector2f(size.x * 3/4, ypos + size.y * .33)); //might need to fiddle with this connor. - connor 12/7
    std::cout  << "yo";
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
    if(mouse_pos.x < rect.getSize().x && mouse_pos.y < (rect.getSize().y + rect.getPosition().y) && mouse_pos.y > (rect.getPosition().y))
    {
        return true;
    }
    return false;
}

void set_color(sf::Color color)
{
    rect.setFillColor(color);
}

void set_font(sf::Font & font)
{
    label.setFont(font);
}

void set_indicator(bool selected)
{
    if(selected)
    {
        indicator.setFillColor(sf::Color::Green);
    }
    else
    {
        indicator.setFillColor(sf::Color::Red);
    }
    
}


void set_indicator(sf::Color color)
{
    indicator.setFillColor(color);
}




void set_size(sf::Vector2f new_size)
{
    rect.setSize(new_size);
}



};

#endif