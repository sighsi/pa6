#include "funcs.h"
#include "textbox.h"
#include "strings.h"
/* void fill_button_arr(Button button_arr[]) //
{
    Button btn0(70.0*0, sf::Vector2f(150.0f,70.0f), sf::Color::Cyan);
  Button btn1(70.0*1, sf::Vector2f(150.0f,70.0f), sf::Color::Cyan);
  Button btn2(70.0*2, sf::Vector2f(150.0f,70.0f), sf::Color::Cyan);
  Button btn3(70.0*3, sf::Vector2f(150.0f,70.0f), sf::Color::Cyan);
  Button btn4(70.0*4, sf::Vector2f(150.0f,70.0f), sf::Color::Cyan);
  Button btn5(70.0*5, sf::Vector2f(150.0f,70.0f), sf::Color::Cyan);
  Button btn6(70.0*6, sf::Vector2f(150.0f,70.0f), sf::Color::Cyan);

  Button a;
} */
void narg();
void nag();
void reset_indicators (Button button_arr[], int cur_select)
{
    for (int i = 0; i < 7; i++) //update this so it doesn't depend on magic num connor. -connor 12/8/20
    {
        if(i == cur_select)
        {
            continue;
        }
        button_arr[i].set_indicator(false); // 

    }


}


void run_program()
{
  
  sf::RenderWindow Window(sf::VideoMode(800, 600), "Covid-tracker");
  
  sf::Texture background;
  background.loadFromFile("blk.png");
  
  sf::Texture btn;
  btn.loadFromFile("botton.png");

  sf::Texture grn;
  //grn.loadFromFile("green.png");
  

  sf::RectangleShape back_g(sf::Vector2f(800.0f,600.0f));
  back_g.setTexture(&background);

  /* std::vector<std::unique_ptr<Button> > button_vec;
  for(int i = 0; i < 7; i++)
  {
    button_vec.push_back ( new Button(70.0*i, sf::Vector2f(150.0f,70.0f), sf::Color::Cyan) );
  } */

  //Button *btn;
   
  sf::Font ocra;
  ocra.loadFromFile("OCRAEXT.TTF");
  //(sf::Vector2f location, sf::Vector2f size, sf::Font &font)
  Textbox state_input(sf::Vector2f(550.0f, 30.0f), sf::Vector2f(200.0f,35.0f), ocra);
  //state_i
  state_input.set_text_size(25);
  state_input.set_box_color(sf::Color(170,170,170,220));
  sf::Text state_label;
  state_label.setFont(ocra);
  state_label.setString("State:");
  state_label.setCharacterSize(20);
  state_label.setPosition(sf::Vector2f(475.0f,33.0f));
  state_label.setFillColor(sf::Color::Red);


  Textbox date_input (sf::Vector2f(150.0f, 550.0f), sf::Vector2f(200.0f,35.0f), ocra);
  date_input.set_box_color(sf::Color(170,170,170,220));

  sf::Text date_label;
  
  date_label.setFont(ocra);
  date_label.setString("Date:");
  date_label.setCharacterSize(20);
  date_label.setPosition(sf::Vector2f(75.0f,550.0f));
  date_label.setFillColor(sf::Color::Red);



   // Textbox(sf::Vector2f position, int char_size, std::string to_write, sf::Font &font, sf::Color)
  Textbox help_str(sf::Vector2f(205.0f ,95.0f), 15, help, ocra, sf::Color::White);

  //float ypos, sf::Vector2f size, sf::Color color, std::string label, sf::Font & font
  Button btn0(70.0*0, sf::Vector2f(150.0f,70.0f), sf::Color::Cyan, "btn0", ocra);
  Button btn1(70.0*1, sf::Vector2f(150.0f,70.0f), sf::Color::Cyan,"btn1", ocra );
  Button btn2(70.0*2, sf::Vector2f(150.0f,70.0f), sf::Color::Cyan, "btn2", ocra);
  Button btn3(70.0*3, sf::Vector2f(150.0f,70.0f), sf::Color::Cyan, "btn3", ocra);
  Button btn4(70.0*4, sf::Vector2f(150.0f,70.0f), sf::Color::Cyan, "btn4", ocra);
  Button btn5(70.0*5, sf::Vector2f(150.0f,70.0f), sf::Color::Cyan, "btn5", ocra);
  Button btn6(70.0*6, sf::Vector2f(150.0f,70.0f), sf::Color::Cyan, "help", ocra);

  Button butt_arr[7];
  butt_arr[0] = btn0;
  butt_arr[1] = btn1;
  butt_arr[2] = btn2;
  butt_arr[3] = btn3;
  butt_arr[4] = btn4;
  butt_arr[5] = btn5;
  butt_arr[6] = btn6;
  //Button btn1(70.0*7, sf::Vector2f(150.0f,70.0f), sf::Color::Cyan);




  sf::RectangleShape text_sq(sf::Vector2f(550.0f, 450.0f)); //changed to 450 12/10-connor
  text_sq.setFillColor(sf::Color(47,79,79,200));
  text_sq.setPosition(200,90);
  text_sq.setOutlineColor(sf::Color(35, 67,67,220));
  text_sq.setOutlineThickness(2.5f);


  
  Window.setSize(sf::Vector2u(800,600)); 

  int index = 0;
  int cur_btn = -1;

  Window.setKeyRepeatEnabled(false);
  
  while(Window.isOpen())
  {
      for(int i = 0; i < 7; i++)
    {
      butt_arr[i].draw_to_screen(Window);

    }
    state_input.draw_to_screen(Window);
    Window.draw(state_label);
    date_input.draw_to_screen(Window);
    Window.draw(date_label);
    Window.draw(text_sq);

    
      sf::Event Event;
      while(Window.pollEvent(Event))
      {

        switch(Event.type)
        {
            case sf::Event::Closed:
                Window.close();
                break;
            case sf::Event::MouseMoved:
              {
                for (int i =0; i < NUMBTNS; i++)
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
            case sf::Event::TextEntered:
            {
              if(state_input.get_selected())
              {
              write_to_screen(Event,state_input, state_input_str );
              }
              else if (date_input.get_selected())
              {
                write_to_screen(Event, date_input, date_input_str);
              }
               
              break;  
              
            }
            case sf::Event::MouseButtonPressed:
            {

          sf::Vector2i cur_pos= sf::Mouse::getPosition(Window);
          if(cur_pos.x < 150 && cur_pos.y <= 70)
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
          else if (cur_pos.x > 550.0f && cur_pos.x < 750.0f && cur_pos.y > 30.0f && cur_pos.y < 65.0f )
          {
            state_input.set_selected(true);
            //tate_input.set_text("selected state");

          }
          else if (cur_pos.x > 150.0f && cur_pos.x < 350.0f && cur_pos.y > 550.0f && cur_pos.y < 585.0f)
          {
            date_input.set_selected(true);
            state_input.set_selected(false);
          }
          else
          {
            state_input.set_selected(false);
            date_input.set_selected(false);
          }
            }
                
        }
      
        /* if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {

           
        } */
      }
    switch(cur_btn)
    {
        case -1:
        break;
        case 0:
        break;
        case 1:
        break;
        case 2:
        break;
        case 3:
        break;
        case 4:
        break;
        case 5:
      //  std::cout << "case 5";
        break;
        case 6:
        //std::cout << "case 6";
        help_str.draw_to_screen(Window);
        break;


    }


      
      //square_0.getPosition///
      /* for(auto it = rect_vec->begin(); it != rect_vec->end(); it++)
      {
        Window.draw(*it);
      } */
      
    // for(auto it = button_vec->begin(); it != button_vec->end(); it++)





     /* for(auto x : button_vec)
     {
       int i = 0;
       //*it.draw_to_screen(Window);
       x->draw_to_screen(Window);
     } */


    
      /* Window.draw(back_g);
      Window.draw(text_sq);
      Window.draw(square_0);
      Window.draw(circle_0);
      Window.draw(square_1);
      Window.draw(square_2); */
      
      Window.display();

   
  }




}


void write_to_screen(sf::Event &Event, Textbox &tbox, std::string &out)//doesn't actually write to screen, more updates what will be
{
  std::string input;
  std::string str;
    if(Event.text.unicode != 13 && Event.text.unicode != 8) //carriage return. and backspace respectively.
    {
      str += Event.text.unicode;
      tbox.append(str);
    }
    else if( Event.text.unicode == 13)
    {
      input = tbox.get_string();
      out = input;
      std::cout << "entered: " << input ;
    }
    else
    {
      tbox.del_char();
     // std::cout << "\nleft del char\n";
      
    }
  input = tbox.get_string();
      //return input;

}