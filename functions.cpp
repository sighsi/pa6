#include "functions.h"

     

/**
 * this handles the GUI and statemachine aspect of the code. 
 * The parameters it takes are the two hashmaps that hold the covid data
 * accessible by state or by date.
 * 
 */ 

void run_program(std::unordered_map<std::string, apiDataClass> *& dateData, std::unordered_map<std::string, stateData> *& state) {
    sf::Font ocra;
    ocra.loadFromFile("images/OCRAEXT.TTF");
    std::string state_input_str= "Enter state";
    std::string date_input_str= "Enter date";
    std::string help = "Click the button enter the state.\nMoreAdvanced help soon.";
    Textbox output_str(sf::Vector2f(205.0f, 93.0f), 25, "", ocra, sf::Color::White);
    
    sf::RenderWindow Window(sf::VideoMode(800, 600), "Covid-tracker");

    sf::Texture background;
    background.loadFromFile("images/blk.png");

    sf::Texture btn;
    btn.loadFromFile("images/botton.png");

    sf::Texture grn;
    //grn.loadFromFile("green.png");

    sf::RectangleShape back_g(sf::Vector2f(800.0f, 600.0f));
    back_g.setTexture(&background);



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

    Textbox date_input (sf::Vector2f(150.0f, 550.0f), sf::Vector2f(200.0f,35.0f), ocra);
    date_input.set_box_color(sf::Color(170,170,170,220));

    sf::Text date_label;
    
    date_label.setFont(ocra);
    date_label.setString("Date:");
    date_label.setCharacterSize(20);
    date_label.setPosition(sf::Vector2f(75.0f,550.0f));
    date_label.setFillColor(sf::Color::Red);


    Textbox help_str(sf::Vector2f(0, 0), 15, help, ocra, sf::Color::White);

    //float ypos, sf::Vector2f size, sf::Color color, std::string label, sf::Font & font
    Button btn0(70.0 * 0, sf::Vector2f(150.0f, 70.0f), sf::Color::Cyan, "Current Data", ocra);
    Button btn1(70.0 * 1, sf::Vector2f(150.0f, 70.0f), sf::Color::Cyan, "Data By Date", ocra);
    Button btn2(70.0 * 2, sf::Vector2f(150.0f, 70.0f), sf::Color::Cyan, "WA Data", ocra);
    Button btn3(70.0 * 3, sf::Vector2f(150.0f, 70.0f), sf::Color::Cyan, "State Data", ocra);
    Button btn4(70.0 * 4, sf::Vector2f(150.0f, 70.0f), sf::Color::Cyan, "Chat", ocra);
    Button btn5(70.0 * 5, sf::Vector2f(150.0f, 70.0f), sf::Color::Cyan, "help", ocra);
    Button btn6(70.0 * 6, sf::Vector2f(150.0f, 70.0f), sf::Color::Cyan, "", ocra);

    Button butt_arr[7];
    butt_arr[0] = btn0;
    butt_arr[1] = btn1;
    butt_arr[2] = btn2;
    butt_arr[3] = btn3;
    butt_arr[4] = btn4;
    butt_arr[5] = btn5;
    butt_arr[6] = btn6;

    sf::RectangleShape text_sq(sf::Vector2f(550.0f, 450.0f)); //changed to 450 12/10-connor
    text_sq.setFillColor(sf::Color(47,79,79,200));
    text_sq.setPosition(200,90);
    text_sq.setOutlineColor(sf::Color(35, 67,67,220));
    text_sq.setOutlineThickness(2.5f);

    Window.setSize(sf::Vector2u(800, 600));

    int index = 0;
    int cur_btn = -1;

    Window.setKeyRepeatEnabled(false);

    while (Window.isOpen()) {
        for (int i = 0; i < 7; i++) {
            butt_arr[i].draw_to_screen(Window);
        }
        state_input.draw_to_screen(Window);
        Window.draw(state_label);
        date_input.draw_to_screen(Window);
        Window.draw(date_label);
        Window.draw(text_sq);
        sf::Event Event;
        while (Window.pollEvent(Event)) {
            switch (Event.type) {
                case sf::Event::Closed:
                    Window.close();
                    break;
                case sf::Event::MouseMoved: {
                    for (int i = 0; i < NUMBTNS; i++) {
                        if (butt_arr[i].hover(Window)) {
                            butt_arr[i].set_color(sf::Color::Green);
                        } else {
                            
                            butt_arr[i].set_color(sf::Color::Cyan);
                            
                        }
                    }
                    break;
                }
                case sf::Event::TextEntered: {
                    if (state_input.get_selected()) {
                        write_to_screen(Event, state_input, state_input_str);
                        
                    }
                    else if (date_input.get_selected()) {
                        write_to_screen(Event, date_input, date_input_str);
                    }

                    break;
                }
                case sf::Event::MouseButtonPressed: {
                    sf::Vector2i cur_pos = sf::Mouse::getPosition(Window);
                    if (cur_pos.x < 150 && cur_pos.y <= 70) {
                        butt_arr[0].set_indicator(true);
                        cur_btn = 0;
                        reset_indicators(butt_arr, 0);
                    } else if (cur_pos.x < 150 && cur_pos.y <= 140) {
                        butt_arr[1].set_indicator(true);
                        cur_btn = 1;
                        reset_indicators(butt_arr, 1);
                    } else if (cur_pos.x < 150 && cur_pos.y <= 210) {
                        butt_arr[2].set_indicator(true);
                        cur_btn = 2;
                        reset_indicators(butt_arr, 2);
                    } else if (cur_pos.x < 150 && cur_pos.y <= 280) {
                        butt_arr[3].set_indicator(true);
                        cur_btn = 3;
                        reset_indicators(butt_arr, 3);
                    } else if (cur_pos.x < 150 && cur_pos.y <= 350) {
                        butt_arr[4].set_indicator(true);
                        cur_btn = 4;
                        reset_indicators(butt_arr, 4);
                    } else if (cur_pos.x < 150 && cur_pos.y <= 420) {
                        butt_arr[5].set_indicator(true);
                        cur_btn = 5;
                        reset_indicators(butt_arr, 5);
                    } else if (cur_pos.x < 150 && cur_pos.y <= 490) {
                        butt_arr[6].set_indicator(true);
                        cur_btn = 6;
                        reset_indicators(butt_arr, 6);
                    } else if (cur_pos.x > 550.0f && cur_pos.x < 750.0f && cur_pos.y > 30.0f && cur_pos.y < 65.0f) {
                        state_input.set_selected(true);
                        //tate_input.set_text("selected state");
                    } else if (cur_pos.x > 150.0f && cur_pos.x < 350.0f && cur_pos.y > 550.0f && cur_pos.y < 585.0f)                {
                        date_input.set_selected(true);
                    } else {
                        state_input.set_selected(false);
                        date_input.set_selected(false);
                    }
                }
            }
            switch (cur_btn) {
            case -1:
                break;
            case 0: { 
                printDateData(dateData, Window, output_str);

                break;
            }
            case 1:
                printDateData(dateData, Window, output_str, date_input.get_string());

                break;
            case 2:
                printStateData(state, Window, output_str);

                break;
            case 3:
                printStateData(state, Window, output_str, state_input.get_string());

                break;
            case 4:
   
                break;
            case 5:

                break;
            case 6:
                help_str.draw_to_screen(Window);
                break;
        }
        Window.display();
    }
}
}

/**
 * based on the button pressed both printData's will populate the console on the screen
 * with data from the hashmap.
 * 
 * 
 */ 
void printDateData(std::unordered_map<std::string, apiDataClass> *& data, sf::RenderWindow &window ,Textbox &tb ,std::string date = TODAYS_DATE) {
    if (date == "") date = TODAYS_DATE;
    auto todayData = data->find(date);
    date.insert(4, "/");
    date.insert(7, "/");

    std::string str = "The date: " + date +  "\nNumber of cases is " +  todayData -> second.positive + "\nThe death toll: " + todayData -> second.death;
    str+= "\nIncrease from day prior: " + todayData -> second.death + "\nNumber of cases is: " + todayData -> second.positive;
    str+= "\nNumber of recovered cases: " + todayData -> second.recovered ;
    tb.set_text(str);
    tb.draw_to_screen(window);
}

void printStateData(std::unordered_map<std::string, stateData> *& state, sf::RenderWindow &window ,Textbox &tb , std::string statestr = "WA")  {
    if (statestr == "") statestr = "WA";
    auto StateNode = state->find(statestr);
    std::string date = StateNode -> second.date ;
    date.insert(4, "/");
    date.insert(7, "/");
    std::string str = "Showing data for " + statestr + "\nThe date: " + date +  "\nNumber of cases is " +  StateNode -> second.positive + "\nThe death toll: " + StateNode -> second.death;
    str+= "\nIncrease from day prior: " + StateNode -> second.death + "\nNumber of cases is: " + StateNode -> second.positive;
    str+= "\nNumber of recovered cases: " + StateNode -> second.recovered ;
    tb.set_text(str);
    tb.draw_to_screen(window);
}

/**
 * Reads files located in the subdirectory "data" and populates the hash tree passed
 * 
 */ 

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



/**
 * Reads files located in the subdirectory "data" and populates the hash tree passed
 * 
 */ 
void readStateFiles(std::string fileName, std::unordered_map<std::string, stateData> *& data)
{
    std::fstream f;
    f.open( fileName);
    if (!f.is_open()) std::cout << "Error reading destinations" << std::endl;

    std::string line;

    std::string date;
    std::string state;
    std::string positive;
    std::string probableCases;
    std::string negative;
    std::string pending;
    std::string totalTestResultsSource;
    std::string totalTestResults;
    std::string hospitalizedCurrently;
    std::string hospitalizedCumulative;
    std::string inIcuCurrently;
    std::string inIcuCumulative;
    std::string onVentilatorCurrently;
    std::string onVentilatorCumulative;
    std::string recovered;
    std::string dataQualityGrade;
    std::string lastUpdateEt;
    std::string dateModified;
    std::string checkTimeEt;
    std::string death;
    std::string hospitalized;
    std::string dateChecked;
    std::string totalTestsViral;
    std::string positiveTestsViral;
    std::string negativeTestsViral;
    std::string positiveCasesViral;
    std::string deathConfirmed;
    std::string deathProbable;
    std::string totalTestEncountersViral;
    std::string totalTestsPeopleViral;
    std::string totalTestsAntibody;
    std::string positiveTestsAntibody;
    std::string negativeTestsAntibody;
    std::string totalTestsPeopleAntibody;
    std::string positiveTestsPeopleAntibody;
    std::string negativeTestsPeopleAntibody;
    std::string totalTestsPeopleAntigen;
    std::string positiveTestsPeopleAntigen;
    std::string totalTestsAntigen;
    std::string fips;
    std::string negativeIncrease;
    std::string total;
    std::string totalTestResultsIncrease;
    std::string posNeg;
    std::string deathIncrease;
    std::string hospitalizedIncrease;
    std::string hash;
    std::string commercialScore;
    std::string negativeRegularScore;
    std::string negativeScore;
    std::string positiveScore;
    std::string score;
    std::string grade;
 
    getline(f, line, '\n'); // throws away all the labels
    while (getline(f, line, '\n')) {
        stateData nH;
        std::istringstream tokenStream(line);
        tokenStream.fill(); 
        
        getline(tokenStream, date, ',');
        getline(tokenStream, state, ',');
        getline(tokenStream, positive, ',');
        getline(tokenStream, probableCases, ',');
        getline(tokenStream, negative, ',');
        getline(tokenStream, pending, ',');
        getline(tokenStream, totalTestResultsSource, ',');
        getline(tokenStream, totalTestResults, ',');
        getline(tokenStream, hospitalizedCurrently, ',');
        getline(tokenStream, hospitalizedCumulative, ',');
        getline(tokenStream, inIcuCurrently, ',');
        getline(tokenStream, inIcuCumulative, ',');
        getline(tokenStream, onVentilatorCurrently, ',');
        getline(tokenStream, onVentilatorCumulative, ',');
        getline(tokenStream, recovered, ',');
        getline(tokenStream, dataQualityGrade, ',');
        getline(tokenStream, lastUpdateEt, ',');
        getline(tokenStream, dateModified, ',');
        getline(tokenStream, checkTimeEt, ',');
        getline(tokenStream, death, ',');
        getline(tokenStream, hospitalized, ',');
        getline(tokenStream, dateChecked, ',');
        getline(tokenStream, totalTestsViral, ',');
        getline(tokenStream, positiveTestsViral, ',');
        getline(tokenStream, negativeTestsViral, ',');
        getline(tokenStream, positiveCasesViral, ',');
        getline(tokenStream, deathConfirmed, ',');
        getline(tokenStream, deathProbable, ',');
        getline(tokenStream, totalTestEncountersViral, ',');
        getline(tokenStream, totalTestsPeopleViral, ',');
        getline(tokenStream, totalTestsAntibody, ',');
        getline(tokenStream, positiveTestsAntibody, ',');
        getline(tokenStream, negativeTestsAntibody, ',');
        getline(tokenStream, totalTestsPeopleAntibody, ',');
        getline(tokenStream, positiveTestsPeopleAntibody, ',');
        getline(tokenStream, negativeTestsPeopleAntibody, ',');
        getline(tokenStream, totalTestsPeopleAntigen, ',');
        getline(tokenStream, positiveTestsPeopleAntigen, ',');
        getline(tokenStream, totalTestsAntigen, ',');
        getline(tokenStream, fips, ',');
        getline(tokenStream, negativeIncrease, ',');
        getline(tokenStream, total, ',');
        getline(tokenStream, totalTestResultsIncrease, ',');
        getline(tokenStream, posNeg, ',');
        getline(tokenStream, deathIncrease, ',');
        getline(tokenStream, hospitalizedIncrease, ',');
        getline(tokenStream, hash, ',');
        getline(tokenStream, commercialScore, ',');
        getline(tokenStream, negativeRegularScore, ',');
        getline(tokenStream, negativeScore, ',');
        getline(tokenStream, positiveScore, ',');
        getline(tokenStream, score, ',');
        getline(tokenStream, grade, ',');        
        nH.date = date;
        nH.state = state;
        nH.positive = positive;
        nH.probableCases = probableCases;
        nH.negative = negative;
        nH.pending = pending;
        nH.totalTestResultsSource = totalTestResultsSource;
        nH.totalTestResults = totalTestResults;
        nH.hospitalizedCurrently = hospitalizedCurrently;
        nH.hospitalizedCumulative = hospitalizedCumulative;
        nH.inIcuCurrently = inIcuCurrently;
        nH.inIcuCumulative = inIcuCumulative;
        nH.onVentilatorCurrently = onVentilatorCurrently;
        nH.onVentilatorCumulative = onVentilatorCumulative;
        nH.recovered = recovered;
        nH.dataQualityGrade = dataQualityGrade;
        nH.lastUpdateEt = lastUpdateEt;
        nH.dateModified = dateModified;
        nH.checkTimeEt = checkTimeEt;
        nH.death = death;
        nH.hospitalized = hospitalized;
        nH.dateChecked = dateChecked;
        nH.totalTestsViral = totalTestsViral;
        nH.positiveTestsViral = positiveTestsViral;
        nH.negativeTestsViral = negativeTestsViral;
        nH.positiveCasesViral = positiveCasesViral;
        nH.deathConfirmed = deathConfirmed;
        nH.deathProbable = deathProbable;
        nH.totalTestEncountersViral = totalTestEncountersViral;
        nH.totalTestsPeopleViral = totalTestsPeopleViral;
        nH.totalTestsAntibody = totalTestsAntibody;
        nH.positiveTestsAntibody = positiveTestsAntibody;
        nH.negativeTestsAntibody = negativeTestsAntibody;
        nH.totalTestsPeopleAntibody = totalTestsPeopleAntibody;
        nH.positiveTestsPeopleAntibody = positiveTestsPeopleAntibody;
        nH.negativeTestsPeopleAntibody = negativeTestsPeopleAntibody;
        nH.totalTestsPeopleAntigen = totalTestsPeopleAntigen;
        nH.positiveTestsPeopleAntigen = positiveTestsPeopleAntigen;
        nH.totalTestsAntigen = totalTestsAntigen;
        nH.fips = fips;
        nH.negativeIncrease = negativeIncrease;
        nH.total = total;
        nH.totalTestResultsIncrease = totalTestResultsIncrease;
        nH.posNeg = posNeg;
        nH.deathIncrease = deathIncrease;
        nH.hospitalizedIncrease = hospitalizedIncrease;
        nH.hash = hash;
        nH.commercialScore = commercialScore;
        nH.negativeRegularScore = negativeRegularScore;
        nH.negativeScore = negativeScore;
        nH.positiveScore = positiveScore;
        nH.score = score;
        nH.grade = grade;

        data -> emplace(state, nH);
    }
    f.close();
}


/**
 * This code is repurposed tutorial code from the rest SDK blog. 
 * I had attempted to write it based on the documentation alone and 
 * didn't have any luck and thus ended up finding an example which closely mirrored
 * the use we needed. The code is pretty different from the type of c++ we've learned in 
 * class considering it uses lamda's and .then calls and so I hope it's not a huge deal.
 * 
 * Blog can be found here:
 *      https://github.com/microsoft/cpprestsdk/wiki/Getting-Started-Tutorial
 * 
 */ 
void apiCall(std::string apiExtension) {
    std::string fileName = apiExtension;
    fileName.erase(std::remove(fileName.begin(), fileName.end(), '/'), fileName.end());
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
    try
    {
        requestTask.wait();
    }
    catch (const std::exception &e)
    {
        printf("Error exception:%s\n", e.what());
    }

}


// unhighlights button when the cursor leaves the button
void reset_indicators(Button button_arr[], int cur_select)
{
    for (int i = 0; i < 7; i++) 
    {
        if (i == cur_select)
        {
            continue;
        }
        button_arr[i].set_indicator(false); //
    }
}


// writes string to the screen
void write_to_screen(sf::Event &Event, Textbox &tbox, std::string &out) {
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
    }
  input = tbox.get_string();
}