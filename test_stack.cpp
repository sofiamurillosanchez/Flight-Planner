//
// Created by Sofia  Murillo on 10/23/21.
//

#include "catch.hpp"
#include "DSStack.h"
#include <string>

using namespace std;
TEST_CASE("DSStack", "[DSStack]"){
    DSStack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);

    DSStack<string> stringStack;
    stringStack.push("a");
    stringStack.push("b");
    stringStack.push("c");
    stringStack.push("d");


    SECTION("pop function"){
        stack.pop();
        REQUIRE(stack.peek() == 3);
        stack.pop();
        REQUIRE(stack.peek() == 2);
        stack.push(5);
        stack.push(6);
        stack.pop();
        REQUIRE(stack.peek() == 5);

        stringStack.pop();
        REQUIRE(stringStack.peek() == "c");

        stringStack.push("I would put the letter d but I will just put in a whole sentence instead");
        REQUIRE(stringStack.peek() == "I would put the letter d but I will just put in a whole sentence instead");

        stringStack.pop();
        stringStack.pop();
        REQUIRE(stringStack.peek() == "b");

        REQUIRE(stringStack.isEmpty() == false);
        while(!stack.isEmpty()){
            stack.pop();
        }
        REQUIRE(stack.isEmpty());
    }
    SECTION("push function"){
        stack.push(6);
        stack.push(7);
        REQUIRE(stack.peek() == 7);
        stack.pop();
        REQUIRE(stack.peek() == 6);
        stack.push(1);
        REQUIRE(stack.peek() == 1);

        // TODO: Colin read this!!
        stringStack.push("what's up Colin");
        REQUIRE(stringStack.peek() == "what's up Colin");
        stringStack.push("lol text me hokay when you see this");
        REQUIRE(stringStack.peek() == "lol text me hokay when you see this");
    }
    SECTION("isEmpty function"){
        DSStack<int> temp;
        REQUIRE(temp.isEmpty() == true);
        REQUIRE(stack.isEmpty() == false);
        temp.push(1);
        REQUIRE(temp.isEmpty() == false);
        temp.pop();
        REQUIRE(temp.isEmpty() == true);

        REQUIRE(stringStack.isEmpty() == false);
        while(!stack.isEmpty()){
            stack.pop();
        }
        REQUIRE(stack.isEmpty());
    }
    SECTION("peek function"){
       REQUIRE(stack.peek() == 4);
       stack.push(5);
       REQUIRE(stack.peek() == 5);
       stack.pop();
       REQUIRE(stack.peek() == 4);
       stack.pop();
       REQUIRE(stack.peek() == 3);

       REQUIRE(stringStack.peek() == "d");
       stringStack.pop();
       REQUIRE(stringStack.peek() == "c");
    }
}