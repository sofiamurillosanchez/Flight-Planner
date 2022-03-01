/*Sofia Murillo Sanchez  CS2341   11/5/2021
 * This program essentially takes two input files, one with flight data, and another with requested information related
 * to those flights. From there, this program produces and output file with flight plans listing the top 3 most efficient
 * itineraries.
 * */



#include "catch.hpp"
#include "DSLinkedList.h"
#include <string>

TEST_CASE("DSLinkedList", "[DSLinkedList]"){
    DSLinkedList<int> p;
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;

    SECTION("push_front function"){
        p.push_front(a);
        REQUIRE(p.get_head()->data == a);
        p.push_front(b);
        REQUIRE(p.get_head()->data == b);
        p.push_front(c);
        REQUIRE(p.get_head()->data == c);
    }
    SECTION("push_back function"){
        p.push_back(a);
        REQUIRE(p.get_tail()->data == a);
        p.push_back(b);
        REQUIRE(p.get_tail()->data == b);
        p.push_back(c);
        REQUIRE(p.get_tail()->data == c);
    }
    SECTION("delete_last function"){
        p.push_back(a);
        p.push_back(b);
        p.push_back(c);
        p.delete_last();
        REQUIRE(p.get_tail()->data == b);
        p.delete_last();
        REQUIRE(p.get_tail()->data == a);
    }

    SECTION("iteration functions"){
        p.push_back(a);
        p.push_back(b);
        p.push_back(c);
        p.push_back(d);
        p.push_back(e);
        int cnt = 5;
        int track = 1;

        p.set_curr_head();
        REQUIRE(p.get_curr_val() == a);
        while(p.has_next()){
            p.advance_curr();
            track++;
        }
        REQUIRE(cnt == track);
        REQUIRE(p.get_curr_val() == e);

        p.delete_last();

        cnt = 4;
        track = 1;

        while(p.has_next()){
            p.advance_curr();
            track++;
        }
        REQUIRE(track == 1);

        p.set_curr_head();
        while(p.has_next()){
            p.advance_curr();
            track++;
        }
        REQUIRE(track == cnt);

    }
}