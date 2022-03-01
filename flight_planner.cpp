//
// Created by Sofia  Murillo on 11/1/21.
//

#include "flight_planner.h"

// This method essentially "creates" the flight from the flight date (not the request file)
// It basically sets up the stack and adjacency list. Lots of fun.
void flight_planner::create_flight(string origin_city, string destination_city, int time, int cost, string airline, bool repeat){
    // Take the origin and set the origin city as the city passed in
    origin o;
    o.set_city(origin_city);

    // Do the same as above but for the destination and also set the cost, time, and airline
    // Only doing this for destinations since it wouldn't make sense to set these variables for each origin city
    destination d;
    d.set_city(destination_city);
    d.set_cost(cost);
    d.set_time(time);
    d.set_airline(airline);

    // A flag to check whether the origin passed in actually exists (to decide whether or not it needs to be pushed to the list)
    bool hasOrigin = false;

    adjacencyList.set_curr_head();

    // Iterate through the adjacency list
    while(adjacencyList.get_curr() != nullptr){
        // Check whether the iterator contains the origin passed in
        if(adjacencyList.get_curr_val().get_city() == o.get_city()){

            // Set hasOrigin to true
            hasOrigin = true;

            // Create a flag to check whether you should add the destination to the origin being checked in the adjacency list
            bool dontAdd = false;

            // Iterate through the destinations list
            while(adjacencyList.get_curr_val().getDestinations().get_curr()){
                // If the destination is already in the destinations list, set dontAdd to true
                if(adjacencyList.get_curr_val().getDestinations().get_curr_val().get_city() == d.get_city() && adjacencyList.get_curr_val().getDestinations().get_curr_val().get_airline() == d.get_airline()){
                    dontAdd = true;
                }

                adjacencyList.get_curr_val().getDestinations().advance_curr();
            }

            // If dontAdd is STILL false, add the destination to the destinations list
            if (!dontAdd){
                adjacencyList.get_curr_val().add_destination(d);
            }

        }
        adjacencyList.advance_curr();
    }


    // If the origin city doesn't "exist" in the adj. list, push it
    if(!hasOrigin){
        o.add_destination(d);
        adjacencyList.push_back(o);
    }

    // Create the flight for the destination city (since a flight can go both ways)
    if (repeat) {
        create_flight(destination_city, origin_city, time, cost, airline, false);
    }
}

// This is the iterative backtracking function.. don't worry, I'm dreading writing the comments for this just as much as you are dreading
// to read/scroll past them
void flight_planner::iterative_backtracking(string o, string d, bool t, bool c) {
    string temp_path_text = "";
    int cost = 0;
    int time = 0;


    // Set the iterator to head
    adjacencyList.set_curr_head();

    // Iterate through adjacency list until you reach a city that isn't in the list (and while it isn't nullptr)
    while (adjacencyList.get_curr() != nullptr && adjacencyList.get_curr()->data.get_city() != o) {
        adjacencyList.advance_curr();
    }

    // Take the origin city that you reach
    origin* orig = &adjacencyList.get_curr()->data;

    // Create a LinkedList of connection flights made up of the city's destinations
    DSLinkedList<destination>* connections = &orig->getDestinations();

    // Create a destination object with the origin city
    destination dest(orig->get_city(), "", 0, 0);

    // Push the destination city to the stack
    stack.push(dest);
    while(!stack.isEmpty()){
        adjacencyList.set_curr_head();

        // Basically, do the same as above where you iterate through the adjacency list to find a city, but this time, you check to see if it's in the stack
        while (adjacencyList.get_curr() != nullptr && adjacencyList.get_curr()->data.get_city() != stack.peek().get_city()) {
            adjacencyList.advance_curr();
        }


        orig = &adjacencyList.get_curr()->data;
        connections = &orig->getDestinations();

        // If it is at the top of the stack, you pop and go to the output functions
        if(stack.peek().get_city() == d){
            temp_path_text = store_path();
            cost = get_total_cost();
            time = get_total_time();
            stack.pop();
            if(t){
                send_to_time_output(o, d, temp_path_text, cost, time);
            }
            else{
                send_to_cost_output(o, d, temp_path_text, cost, time);
            }
        }

        // If it isn't at the top of the stack, you check whether the connections is null, if it isn't...
        else{
            if (connections->get_curr() == nullptr) {
                stack.pop();
                connections->set_curr_head();
            }
            else{
                // Check if that location was already visited, if it was, move the iterator and check the other connections
                if (is_visited(connections->get_curr_val().get_city())) {
                    connections->advance_curr();
                }

                // If it wasn't visited already, push the connection to the stack and move the iterator
                else {
                    stack.push(connections->get_curr_val());
                    connections->advance_curr();
                }
            }
        }
    }

}


// The following two functions are LONG, but they basically do the exact same thing. The only key difference is their logic (one is an output
// that's generated based off time and the other one is for the cost.
void flight_planner :: send_to_time_output(string o, string d, string final_path_text, int cost, int time){
    int first_temp_min_cost;            // The logic might seem convulted if you don't read the comments, so please read these if you're confused
    int first_temp_min_time;            // Basically, I created some temp values to store the flight path, cost, and time (to be used later)
    string first_temp_path_text;

    int second_temp_min_cost;
    int second_temp_min_time;
    string second_temp_path_text;

    string org = o;                     // Then I stored the origin and destination cities in their own strings
    string dest = d;

    // Make sure that entries aren't repeated (so duplicate itineraries aren't created)
    if (final_path_text == first_final_path_text || final_path_text == second_final_path_text || final_path_text == third_final_path_text)
        return;

    if(time <= third_min_time){         // Check whether the time is equal to or less than the third best time
        if(time < second_min_time){     // If it is, check whether it's less than the second best
            if(time < first_min_time){  // Less than first best
                first_temp_path_text = first_final_path_text;   // Set the temp values equal to the first and second ones
                first_temp_min_cost = first_min_cost;
                first_temp_min_time = first_min_time;

                second_temp_path_text = second_final_path_text;
                second_temp_min_cost = second_min_cost;
                second_temp_min_time = second_min_time;

                first_min_time = time;
                first_min_cost = cost;
                first_final_path_text = final_path_text;

                second_final_path_text = first_temp_path_text;      // Set values accordingly
                second_min_cost = first_temp_min_cost;
                second_min_time = first_temp_min_time;

                third_final_path_text = second_temp_path_text;
                third_min_cost = second_temp_min_cost;
                third_min_time = second_temp_min_time;

                set_first_best();        // Call the set functions for the values changed so the top 3 itineraries are created
                set_second_best();
                set_third_best();
            }
            else if(time == first_min_time){ // Follow similar logic as above but for the case where time is equal to first_min_time
                if(cost < first_min_cost){ // If this is the case, you will need to compare the costs
                    first_temp_path_text = first_final_path_text;
                    first_temp_min_cost = first_min_cost;
                    first_temp_min_time = first_min_time;

                    second_temp_path_text = second_final_path_text;
                    second_temp_min_cost = second_min_cost;
                    second_temp_min_time = second_min_time;


                    first_min_time = time;  // Set the values accordingly
                    first_min_cost = cost;
                    first_final_path_text = final_path_text;

                    second_final_path_text = first_temp_path_text;
                    second_min_cost = first_temp_min_cost;
                    second_min_time = first_temp_min_time;

                    third_final_path_text = second_temp_path_text;
                    third_min_cost = second_temp_min_cost;
                    third_min_time = second_temp_min_time;

                    set_first_best();   // Call set functions accordingly
                    set_second_best();
                    set_third_best();
                }
                else{ // Case where the cost is not less than the min cost
                    second_temp_path_text = second_final_path_text;
                    second_temp_min_cost = second_min_cost;
                    second_temp_min_time = second_min_time;


                    second_min_time = time;
                    second_min_cost = cost;
                    second_final_path_text = final_path_text;

                    third_final_path_text = second_temp_path_text;
                    third_min_cost = second_temp_min_cost;
                    third_min_time = second_temp_min_time;

                    set_second_best(); // Call set functions accordingly
                    set_third_best();
                }
            }
            else{ // Case where time is JUST less than second_min_time and it doesn't meet some other weird condition
                second_temp_path_text = second_final_path_text;
                second_temp_min_cost = second_min_cost;
                second_temp_min_time = second_min_time;


                second_min_time = time;
                second_min_cost = cost;
                second_final_path_text = final_path_text;

                third_final_path_text = second_temp_path_text;
                third_min_cost = second_temp_min_cost;
                third_min_time = second_temp_min_time;

                set_second_best();
                set_third_best();
            }
        }
        else if(time == second_min_time){ // Case where time is the same as second_min_time
            if(cost < second_min_cost){ // Compare cost with second_min cost (same logic as above)
                second_temp_path_text = second_final_path_text;
                second_temp_min_cost = second_min_cost;
                second_temp_min_time = second_min_time;


                second_min_time = time;
                second_min_cost = cost;
                second_final_path_text = final_path_text;

                third_final_path_text = second_temp_path_text;
                third_min_cost = second_temp_min_cost;
                third_min_time = second_temp_min_time;

                set_second_best();
                set_third_best();
            }
            else{ // Else, just set this case to the third one since it's more efficient than the third but not as efficient as the other option
                third_min_time = time;
                third_min_cost = cost;
                third_final_path_text = final_path_text;

                set_third_best();
            }
        }
        else{ // Set the third option to the values
            third_min_time = time;
            third_min_cost = cost;
            third_final_path_text = final_path_text;

            set_third_best();
        }
    }

    // Else, do nothing because it won't be printed to the itinerary otherwise
}

// The exact same logic as above, except the cost is comapared rather than the time
// For cases where they are equal, the time is checked for rather than the cost
void flight_planner :: send_to_cost_output(string o, string d, string final_path_text, int cost, int time){
    int first_temp_min_cost; // Everything is the same structurally (and logically), I will just keep commenting that
    int first_temp_min_time;
    string first_temp_path_text;

    int second_temp_min_cost;
    int second_temp_min_time;
    string second_temp_path_text;
    string org = o;
    string dest = d;

    time = tTime;
    cost = tCost;

    // Make sure that entries aren't repeated (so duplicate itineraries aren't created)
    if (final_path_text == first_final_path_text || final_path_text == second_final_path_text || final_path_text == third_final_path_text)
        return;

    if(cost <= third_min_cost){ // Same logic as above, but cost and time are inverted accordingly
        if(cost < second_min_cost){
            if(cost < first_min_cost){
                first_temp_path_text = first_final_path_text;
                first_temp_min_cost = first_min_cost;
                first_temp_min_time = first_min_time;

                second_temp_path_text = second_final_path_text;
                second_temp_min_cost = second_min_cost;
                second_temp_min_time = second_min_time;

                first_min_time = time;
                first_min_cost = cost;
                first_final_path_text = final_path_text;

                second_final_path_text = first_temp_path_text;
                second_min_cost = first_temp_min_cost;
                second_min_time = first_temp_min_time;

                third_final_path_text = second_temp_path_text;
                third_min_cost = second_temp_min_cost;
                third_min_time = second_temp_min_time;

                set_first_best(); // Call set functions
                set_second_best();
                set_third_best();
            }
            else if(cost == first_min_cost){ // Same as above
                if(time < first_min_time){
                    first_temp_path_text = first_final_path_text;
                    first_temp_min_cost = first_min_cost;
                    first_temp_min_time = first_min_time;

                    second_temp_path_text = second_final_path_text;
                    second_temp_min_cost = second_min_cost;
                    second_temp_min_time = second_min_time;

                    first_min_time = time;
                    first_min_cost = cost;
                    first_final_path_text = final_path_text;

                    second_final_path_text = first_temp_path_text;
                    second_min_cost = first_temp_min_cost;
                    second_min_time = first_temp_min_time;

                    third_final_path_text = second_temp_path_text;
                    third_min_cost = second_temp_min_cost;
                    third_min_time = second_temp_min_time;

                    set_first_best();
                    set_second_best();
                    set_third_best();

                }
                else{ // Same as above
                    second_temp_path_text = second_final_path_text;
                    second_temp_min_cost = second_min_cost;
                    second_temp_min_time = second_min_time;

                    second_min_time = time;
                    second_min_cost = cost;
                    second_final_path_text = final_path_text;

                    third_final_path_text = second_temp_path_text;
                    third_min_cost = second_temp_min_cost;
                    third_min_time = second_temp_min_time;

                    set_second_best();
                    set_third_best();
                }
            }
            else{ // Same as above
                second_temp_path_text = second_final_path_text;
                second_temp_min_cost = second_min_cost;
                second_temp_min_time = second_min_time;

                second_min_time = time;
                second_min_cost = cost;
                second_final_path_text = final_path_text;

                third_final_path_text = second_temp_path_text;
                third_min_cost = second_temp_min_cost;
                third_min_time = second_temp_min_time;

                set_second_best();
                set_third_best();
            }
        }
        else if(cost == second_min_cost){ // Same as above
            if(time < second_min_time){ // Same as above
                second_temp_path_text = second_final_path_text;
                second_temp_min_cost = second_min_cost;
                second_temp_min_time = second_min_time;


                second_min_time = time;
                second_min_cost = cost;
                second_final_path_text = final_path_text;

                third_final_path_text = second_temp_path_text;
                third_min_cost = second_temp_min_cost;
                third_min_time = second_temp_min_time;

                set_second_best();
                set_third_best();
            }
            else{ // Same as above
                third_min_time = time;
                third_min_cost = cost;
                third_final_path_text = final_path_text;

                set_third_best();
            }
        }
        else { // Same as above
            third_min_time = time;
            third_min_cost = cost;
            third_final_path_text = final_path_text;

            set_third_best();
        }
    }

    // Else, do nothing because it won't be printed to the itinerary
}


// This function checks whether a city was already visited by iterating through the stack and
// looking for a match
bool flight_planner::is_visited(string city) {
    bool visited = false;
    DSStack<destination> temp_stack;

    while(!stack.isEmpty()) {
        if (city == stack.peek().get_city()) {
            visited = true;     // If there is a match, visited is changed to true
        }
        temp_stack.push(stack.peek());
        stack.pop();
    }

    // The temp stack is popped and pushed back into the original stack. fun times.
    while(!temp_stack.isEmpty()){
        stack.push(temp_stack.peek());
        temp_stack.pop();
    }

    // return whether it was visited or not
    return visited;
}


// This function is quite literally the bain of my existence. The path storage isn't what's giving me issues, it's the
// attempt to calculate the time and cost while storing the path. Everything in terms of calculations goes downhill here.
string flight_planner::store_path() {
    // Declare all the needed variables for this function
    DSStack<destination> temp_stack;
    int totalCost = 0;
    int totalTime = 0;
    int cost;
    int time;
    string airline = "";

    // Create a stringstream variable (the true MVP of this function)
    stringstream s("");

    int cntFlights = 0;

    // Push the stack into a temp stack to get it into the right "order".
    while(!stack.isEmpty()){
        temp_stack.push(stack.peek());
        stack.pop();
        cntFlights++;
    }


    cntFlights -= 2;    // This basically represents the number of layovers
    totalCost += 23*cntFlights; // Multiply the number of layovers by 23 and add that to the total cost
    totalTime += 43*cntFlights; // Multiply the number of layovers by 43 and add that to the total time

    while(!temp_stack.isEmpty()){
        string city = temp_stack.peek().get_city();
        cost = temp_stack.peek().get_cost();
        time = temp_stack.peek().get_time();

        // Set the airline string to the top of the temp stack
        airline = temp_stack.peek().get_airline();

        stack.push(temp_stack.peek());
        temp_stack.pop();

        // Increment totalCost to reflect the cost of each flight and totalTime with the time of each flight
        totalCost += cost;
        totalTime += time;

        if (temp_stack.isEmpty())
            continue;

        // Check for the case where there is an airline change
        if(airline != temp_stack.peek().get_airline() && airline != ""){
            totalTime += 27;
        }

        // Send the information to string stream which will then be used to create each specific itinerary
        s << city << " -> ";
        s << temp_stack.peek().get_city() << " (" << temp_stack.peek().get_airline() << ")\n\t";
    }

    // Set the totalCost and totalTime (to be used for itinerary creation)
    set_total_cost(totalCost);
    set_total_time(totalTime);

    return s.str();
}

// This function is super basic, it just resets the values of the private instance variables to make sure previous itineraries
// don't interfere with future ones
void flight_planner::reset_vals(){
    first_final_path_text = "";
    second_final_path_text = "";
    third_final_path_text = "";
    third_min_cost = INT_MAX;
    third_min_time = INT_MAX;
    second_min_cost = INT_MAX;
    second_min_time = INT_MAX;
    first_min_cost = INT_MAX;
    first_min_time = INT_MAX;
    itinerary3 = "";
    itinerary2 = "";
    itinerary1 = "";
    tTime = 0;
    tCost = 0;
}


// You've just reached the getter and setter zone of my code. Keep scrolling at your own discretion...
void flight_planner::set_total_cost(int c) { // Total cost getter & setter
    tCost = c;
}

int flight_planner::get_total_cost(){
    return tCost;
}

// Total time getter and setter
void flight_planner::set_total_time(int t) {
    tTime = t;
}

int flight_planner::get_total_time() {
    return tTime;
}


// Second-best time and cost getters
int flight_planner::get_second_cost(){
    return second_min_cost;
}

int flight_planner::get_second_time() {
    return second_min_time;
}

// Third-best time and cost getters
int flight_planner::get_third_cost(){
    return third_min_cost;
}

int flight_planner::get_third_time() {
    return third_min_time;
}


// Setters and getters for first-best itinerary
void flight_planner::set_first_best() {
    stringstream s("");
    s << "  Itinerary 1: \n";
    s << "\t" << first_final_path_text;
    s <<  "Totals for Itinerary 1: Time: " <<  first_min_time << " Cost: " << first_min_cost << ".00\n";
    itinerary1 = s.str();
}

string flight_planner::get_first_best() {
    return itinerary1;
}

// Setters and getters for second-best itinerary
void flight_planner::set_second_best() {
    stringstream s("");
    s << "  Itinerary 2: \n";
    s << "\t" << second_final_path_text;
    s <<  "Totals for Itinerary 2: Time: " <<  second_min_time << " Cost: " << second_min_cost << ".00\n";
    itinerary2 = s.str();
}
string flight_planner::get_second_best() {
    return itinerary2;
}


// Setters and getters for third-best itinerary
void flight_planner::set_third_best() {
    stringstream s("");
    s << "  Itinerary 3: \n";
    s << "\t" << third_final_path_text;
    s <<  "Totals for Itinerary 3: Time: " <<  third_min_time << " Cost: " << third_min_cost << ".00\n";
    itinerary3 = s.str();
}

string flight_planner::get_third_best() {
    return itinerary3;
}

// Getter for the flight plan (which is basically just the first line of each flight plan in output)
string flight_planner::get_flight_plan(string origin, string destination, string request) {
    string flight_plan = origin + ", " + destination + " (" + request + ")";
    return flight_plan;
}

