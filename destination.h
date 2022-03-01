//
// Created by Sofia  Murillo on 10/29/21.
//

#ifndef INC_21F_FLIGHT_PLANNER_DESTINATION_H
#define INC_21F_FLIGHT_PLANNER_DESTINATION_H

#include <iostream>
#include "DSLinkedList.h"
#include <string>

using namespace std;

class destination {
private:
    // Information related to each "destination" (it wouldnt make sense for an origin to have this info)
    string city;
    int cost;
    int time;
    string airline;
public:

    // Constructors
    destination();
    destination(string, string, int, int);

    // Getters and setters
    void set_city(string);
    string get_city() const;
    void set_cost(int);
    int get_cost();
    void set_time(int);
    int get_time();
    void set_airline(string);
    string get_airline();
};


#endif //INC_21F_FLIGHT_PLANNER_DESTINATION_H
