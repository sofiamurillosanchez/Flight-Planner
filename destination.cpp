//
// Created by Sofia  Murillo on 10/29/21.
//

#include "destination.h"

// Basic constructor, just set defaults to arbitrary values
destination::destination() {
    city = "";
    airline = "";
    cost = 0;
    time = 0;
}

// Constructor with parameters
destination::destination(string c, string a, int money, int t) {
    city = c;
    airline =  a;
    cost = money;
    time = t;
}

// Getters and setters!
void destination::set_city(string c) { // City G&S
    city = c;
}

string destination::get_city() const {
    return city;
}

// Cost G&S
void destination::set_cost(int c) {
    cost = c;
}

int destination::get_cost() {
    return cost;
}

// Time G&S
void destination::set_time(int t) {
    time = t;
}

int destination::get_time() {
    return time;
}


// Airline G&S
void destination::set_airline(string a) {
    airline = a;
}

string destination::get_airline() {
    return airline;
}