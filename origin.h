//
// Created by Sofia  Murillo on 10/29/21.
//

#ifndef INC_21F_FLIGHT_PLANNER_ORIGIN_H
#define INC_21F_FLIGHT_PLANNER_ORIGIN_H

#include "DSLinkedList.h"
#include "destination.h"
#include <string>

using namespace std;

class origin {
private:
    // Linkedlist of destinations
    DSLinkedList<destination> destinationCities;
    string city;

public:
    // Setter and getters for city
    void set_city(string);
    string get_city();

    // Functions to add to and get linked list
    void add_destination(destination);
    DSLinkedList<destination>& getDestinations();
};


#endif //INC_21F_FLIGHT_PLANNER_ORIGIN_H
