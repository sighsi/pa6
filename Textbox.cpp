#include "Textbox.h"


    
    Textbox::Textbox(sf::Vector2f position, int char_size, std::string to_write, sf::Font &font, sf::Color color) 
    {
        
       // std::cout << "In text constructor!";
        this->box_text.setString(to_write);
        this->box_text.setFont(font);
        this->box_text.setPosition(position);
        this->box_text.setFillColor(color);
        this->box_text.setCharacterSize(char_size);
        
    }

    Textbox::Textbox(sf::Vector2f location, sf::Vector2f size, sf::Font &font)
    {
        
        box.setPosition(location);
       // box.setTexture(&texture);
        box.setSize(size);
        box.setOutlineColor(sf::Color(150,150,150,220));
       // box.setOutlineColor(sf::Color::Green);
        box.setOutlineThickness(2.5f);
        writable = true;
        box_text.setFont(font);
        box_text.setPosition(location);
    }

    Textbox::Textbox(sf::Vector2f location, sf::Texture &texture, sf::Vector2f size, sf::Font &font)
    {
        box.setPosition(location);
        box.setTexture(&texture);
        box.setSize(size);
        //box.setOutlineColor(sf::Color(150,150,150,220));
        
        box_text.setFont(font);

        
    }

    void Textbox::append(std::string new_char)
    {
        std::string str;
        str = box_text.getString();
        str+=new_char;
        box_text.setString(str);

    }

    void Textbox::del_char()
    {

        //std::cout <<"in Del char";
        if( box_text.getString().getSize() > 0)// something to del
        {
           // std::cout << "\nin if\n";
            std::string oldstr, newstr;
            oldstr = box_text.getString();
            int size = oldstr.length();
            //box_text.setString(""); //erase
            for(int i = 0; i < size -1; i++)
            {
                newstr+= oldstr[i];
            } 
            
            box_text.setString(newstr);
        }
    }

    void Textbox::draw_to_screen(sf::RenderWindow &window)
    {
        window.draw(box);
        window.draw(box_text);
        
    }

    bool Textbox::get_selected() const
    {
        return this->selected;
    }

    std::string Textbox::get_string() const
    {
        return this->box_text.getString();
    }
    void Textbox::set_box_pos(sf::Vector2f pos)
    {
        this->box.setPosition(pos);
    }

    void Textbox::set_box_color(sf::Color color)
    {
        this->box.setFillColor(color);
    }

    void Textbox::set_selected(bool selec)
    {
        this->selected = selec;
    }

    void Textbox::set_text(std::string str)
    {
        this->box_text.setString(str);
    }

    void Textbox::set_text_size(int char_size)
    {
        this->box_text.setCharacterSize(char_size);
    }

    void Textbox::set_writable(bool write)
    {
        this->writable = write;
    }

