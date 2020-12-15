
#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <SFML/Graphics.hpp>

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
    
    Textbox(sf::Vector2f position, int char_size, std::string to_write, sf::Font &font, sf::Color color) ;

    Textbox(sf::Vector2f location, sf::Vector2f size, sf::Font &font);

    Textbox(sf::Vector2f location, sf::Texture &texture, sf::Vector2f size, sf::Font &font);

    void append(std::string new_char);

    void del_char();

    void draw_to_screen(sf::RenderWindow &window);

    bool get_selected() const;

    std::string get_string() const;

    void set_box_pos(sf::Vector2f pos);

    void set_box_color(sf::Color color);

    void set_selected(bool selec);

    void set_text(std::string str);

    void set_text_size(int char_size);

    void set_writable(bool write);



};

#endif