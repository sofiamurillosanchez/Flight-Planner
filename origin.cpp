//
// Created by Sofia  Murillo on 10/29/21.
//

#include "origin.h"
#include <string>

using namespace std;    

// Just setters and getters for the city!
void origin::set_city(string c) {
    city = c;
}

string origin::get_city() {
    return city;
}

// Add a destination to the destination LinkedList
void origin::add_destination(destination d) {
    destinationCities.push_back(d);
}

// Getter for the destination linked list
DSLinkedList<destination>& origin::getDestinations() {
    return destinationCities;
}