cmake_minimum_required(VERSION 3.15)
project(21f_flight_planner)

set(CMAKE_CXX_STANDARD 14)

configure_file(data/sample01-flight-data.txt data/sample01-flight-data.txt COPYONLY)
configure_file(data/sample01-req-flights.txt data/sample01-req-flights.txt COPYONLY)
configure_file(data/sample02-flight-data.txt data/sample02-flight-data.txt COPYONLY)
configure_file(data/sample02-req-flights.txt data/sample02-req-flights.txt COPYONLY)


add_executable(21f_flight_planner main.cpp catch_setup.cpp sample_tests.cpp DSStack.h DSLinkedList.h manager.cpp manager.h test_list.cpp test_stack.cpp origin.cpp origin.h destination.cpp destination.h flight_planner.cpp flight_planner.h)
