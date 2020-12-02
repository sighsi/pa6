#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H


// DATA CLASS:
class nationalHistory { // titled this way bc that's the name of the csv file I downloaded from their website

public:
    nationalHistory(){}
// I'm just going to make all the params publics bc fuck this many setters and getters. I think I can technically make this a struct to do this correctly
    
    int month;
    int day;
    int year;

    double monthDay; // i.e 1.22 is the 1/22/2020
    
    int date;
    int death;
    int deathIncrease;
    int inIcuCumulative;
    int inIcuCurrently;
    int hospitalizedIncrease;
    int hospitalizedCurrently;
    int hospitalizedCumulative;
    int negative;
    int negativeIncrease;
    int onVentilatorCumulative;
    int onVentilatorCurrently;
    int positive;
    int positiveIncrease;
    int recovered;
    int states;
    int totalTestResults;
    int totalTestResultsIncrease;

};


#endif