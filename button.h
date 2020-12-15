#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>



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

    Button(float ypos, sf::Vector2f size, sf::Texture &texture, sf::Color color);

    Button(float ypos, sf::Vector2f size, sf::Color color, std::string label, sf::Font &font) ;

    void draw_to_screen(sf::RenderWindow &window);

    sf::Vector2f get_pos() const;

    sf::Vector2f get_size() const;

    bool hover(sf::Window &window) ;

    void set_indicator(bool selected);

    void set_font(sf::Font &font);

    void set_indicator(sf::Color color);

    void set_size(sf::Vector2f new_size);

    void set_color(sf::Color color);
};



#endif