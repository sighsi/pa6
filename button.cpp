#include "button.h"

Button::Button(float ypos, sf::Vector2f size, sf::Texture &texture, sf::Color color) // do not use this one yet not fully done.
{
    rect.setPosition(sf::Vector2f(0.0, ypos));
    rect.setSize(size);
    rect.setTexture(&texture);
    rect.setFillColor(color);
    indicator.setPosition(sf::Vector2f(size.x * double(3 / 4), ypos + size.y / 2)); //might need to fiddle with this connor. - connor 12/7

    if (!butt_texture.loadFromFile("images/botton.png"))
    {
        std::cout << "\nError indicator texture failed to load.\n";
    }
    indicator.setTexture(&butt_texture);
}


Button::Button(float ypos, sf::Vector2f size, sf::Color color, std::string label, sf::Font &font) //loads botton with default texture.
{

    rect.setPosition(sf::Vector2f(0.0, ypos));
    rect.setSize(size);

    this->label.setString(label);
    this->label.setPosition(sf::Vector2f(5.0, ypos + size.y * .01));
    this->label.setFillColor(sf::Color::White);
    this->label.setFont(font);
    this -> label.setCharacterSize(18);

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
    indicator.setRadius(15.0f);
    indicator.setTexture(&butt_texture);
    indicator.setFillColor(sf::Color::Red);
}


void Button::draw_to_screen(sf::RenderWindow &window)
{
    window.draw(rect);
    window.draw(indicator);
    window.draw(label);
}


sf::Vector2f Button::get_pos() const
{
    return rect.getSize();
}

sf::Vector2f Button::get_size() const
{
    return rect.getSize();
}

bool Button::hover(sf::Window &window) // needs to be edited if you are going to use with buttons not on left of screen. -connor 12/8
{
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    if (mouse_pos.x < rect.getSize().x && mouse_pos.y < (rect.getSize().y + rect.getPosition().y) && mouse_pos.y > (rect.getPosition().y))
    {
        return true;
    }
    return false;
}

void Button::set_indicator(bool selected)
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

void Button::set_font(sf::Font &font)
{
    label.setFont(font);
}

void Button::set_indicator(sf::Color color)
{
    indicator.setFillColor(color);
}

void Button::set_size(sf::Vector2f new_size)
{
    rect.setSize(new_size);
}

void Button::set_color(sf::Color color)
{
    rect.setFillColor(color);
}