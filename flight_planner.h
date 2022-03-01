//
// Created by Sofia  Murillo on 11/1/21.
//

#ifndef INC_21F_FLIGHT_PLANNER_FLIGHT_PLANNER_H
#define INC_21F_FLIGHT_PLANNER_FLIGHT_PLANNER_H

#include <iostream>
#include <string>
#include <sstream>
#include "DSStack.h"
#include "DSLinkedList.h"
#include "destination.h"
#include "origin.h"
#include <climits>

using namespace std;

class flight_planner {
private:
    // Declare the stack and adjacencyList
    DSLinkedList<origin> adjacencyList;
    DSStack<destination> stack;

    string first_final_path_text = "";
    int first_min_cost = INT_MAX; // Set min cost and time to some arbitrarily large number (so the standard is pretty low for starting min)
    int first_min_time = INT_MAX;

    string second_final_path_text = "";
    int second_min_cost = INT_MAX;
    int second_min_time = INT_MAX;

    string third_final_path_text = "";
    int third_min_cost = INT_MAX;
    int third_min_time = INT_MAX;

    // Total Cost and Total Time variables. I know the names are weird, but I used totalCost and totalTime
    // way too many times to bother refactoring
    int tCost;
    int tTime;

    // itinerary strings (which will later be sent to the output file)
    string itinerary1 = "";
    string itinerary2 = "";
    string itinerary3 = "";


public:
    // This function basically takes the information read in from the flight data and "creates" the different flights
    void create_flight(string, string, int, int, string, bool repeat = true);

    // This function performs the iterative backtracking (if the name wasn't a dead giveaway)
    // The other functions below it are also related to the iterative backtracking
    void iterative_backtracking(string, string, bool, bool);
    bool is_visited(string);
    string store_path();

    // The following functions are setters and getters used for cost and time calculation purposes
    void set_total_cost(int);
    int get_total_cost();
    void set_total_time(int);
    int get_total_time();


    // The following functions send the information (like final flight paths) to the output after
    // being processed to see what the top 3 itineraries are
    void send_to_time_output(string, string, string, int, int);
    void send_to_cost_output(string, string, string, int, int);


    // The following is the mess of setter and getter functions incurred from directly comparing
    // the top three entries (if you want to skip this part of the cpp file, you can)
    void set_first_best();
    string get_first_best();

    void set_second_best();
    string get_second_best();

    void set_third_best();
    string get_third_best();

    int get_second_cost();
    int get_second_time();

    int get_third_cost();
    int get_third_time();

    // This function basically creates that first line of each flight plan which is then sent to the output file
    string get_flight_plan(string, string, string);

    // This function resets the values to make sure that previous entries aren't still contained in the variables
    void reset_vals();
};

#endif //INC_21F_FLIGHT_PLANNER_FLIGHT_PLANNER_H
