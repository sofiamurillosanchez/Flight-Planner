//
// Created by Sofia  Murillo on 10/19/21.
//

#include "manager.h"

// Use argv and call the functions to run the flight data and flight request files
void manager::run_files(char** argv){
    read_flight_file(argv);
    read_request_file(argv);
}

// Read flight data file
void manager::read_flight_file(char** argv){
    ifstream file(argv[1]); // Create ifstream object

    int numEntries = 0;
    int trackEntries = 0;
    string origin = "";
    string destination = "";
    int time = 0;
    int cost = 0;
    string airline = "";

    if(!file.is_open()){
        throw std::runtime_error("Looks like the file isn't opening! :'(");
    }

    // Read in the file
    file >> numEntries;
    while(trackEntries < numEntries){ // Referenced this line: https://stackoverflow.com/questions/22290891/reading-in-file-with-delimiter/22291012
        file >> origin;
        file >> destination;
        file >> cost;
        file >> time;
        file >> airline;

        flight.create_flight(origin, destination, time, cost, airline); // Create flights with the information read in

        trackEntries++; // Track the number of entries
    }

    file.close();
}

// Read the flight request file
void manager::read_request_file(char ** argv) {
    ifstream file(argv[2]); // Create ifstream object

    int numRequested = 0;
    int trackEntries = 0;
    string origin = "";
    string destination = "";
    string request = "";
    bool time = false;
    bool cost = false;

    ofstream out(argv[3]); // Create ofstream object (to product output later on)

    string itinerary1;
    string itinerary2;
    string itinerary3;
    string flight_plan;

    if(!file.is_open()){ // Referenced previous code from PA02
        throw std::runtime_error("Looks like the file isn't opening! :'(");
    }

    // Read in all the information accordingly (this is why number of entries were tracked)
    file >> numRequested;
    while(trackEntries < numRequested){
        file >> origin;
        file >> destination;
        file >> request;

        // Depending on the request, specific functions from flight_planner are called
        if(request == "c" || request == "C"){
            cost = true;
            flight.iterative_backtracking(origin, destination, time, cost);
            itinerary1 = flight.get_first_best();

            // Check how many itinraries need to be printed by checking their time and cost values
            // (if they are INT_MAX, they haven't changed)
            if(flight.get_second_cost() == INT_MAX && flight.get_second_time() == INT_MAX){
                itinerary2 = "";
                if(flight.get_third_cost() == INT_MAX && flight.get_third_time() == INT_MAX){
                    itinerary3 = "";
                }
            }
            else{
                itinerary2 = flight.get_second_best();
                itinerary3 = flight.get_third_best();
            }

            // Get the flight plan string (first line for each flight plan)
            flight_plan = flight.get_flight_plan(origin, destination, "Cost");

            // Call output file and produce the output!
            output_file(out, trackEntries, flight_plan, itinerary1, itinerary2, itinerary3);
        }

        // Same logic as above, but a different function is called to get the flight plans according to time
        else if(request == "t" || request == "T"){
            time = true;
            flight.iterative_backtracking(origin, destination, time, cost);
            itinerary1 = flight.get_first_best();
            if(flight.get_second_cost() == INT_MAX && flight.get_second_time() == INT_MAX){
                itinerary2 = "";
                if(flight.get_third_cost() == INT_MAX && flight.get_third_time() == INT_MAX){
                    itinerary3 = "";
                }
            }
            else{
                itinerary2 = flight.get_second_best();
                itinerary3 = flight.get_third_best();
            }

            flight_plan = flight.get_flight_plan(origin, destination, "Time");
            output_file(out, trackEntries, flight_plan, itinerary1, itinerary2, itinerary3);
        }

        // If the request isn't C or T, then an error is thrown
        else{
            throw std::runtime_error("Your request is invalid. Please enter a valid request :)");
        }

        time = false;
        cost = false;

        // Reset the values to make sure entries aren't overwritten
        flight.reset_vals();
        trackEntries++;
    }

    // Close the files :)
    out.close();
    file.close();
}

// Write to the output file
void manager::output_file(ofstream& file, int entry, string flight_plan, string itinerary1, string itinerary2, string itinerary3){
    file << "Flight " << entry+1 << ": " << flight_plan << endl;
    if(itinerary1 == ""){
        file << "\tNo itineraries found :(" << endl;
        return;
    }
    file << itinerary1 << endl;
    file << itinerary2 << endl;
    file << itinerary3 << endl;
 }
