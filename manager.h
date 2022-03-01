//
// Created by Sofia  Murillo on 10/19/21.
//

#ifndef INC_21F_FLIGHT_PLANNER_MANAGER_H
#define INC_21F_FLIGHT_PLANNER_MANAGER_H


#include "flight_planner.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class manager {
private:
    flight_planner flight;
public:
    // Call file reading functions
    void run_files(char**);

    // File reading functions (call flight planner, etc)
    void read_flight_file(char**);
    void read_request_file(char**);

    // Output function
    void output_file(ofstream&, int, string, string, string, string);
};


#endif //INC_21F_FLIGHT_PLANNER_MANAGER_H
