//
// Created by Sofia  Murillo on 10/19/21.
//

#ifndef INC_21F_FLIGHT_PLANNER_DSSTACK_H
#define INC_21F_FLIGHT_PLANNER_DSSTACK_H

#include "DSLinkedList.h"

template <typename T>
class DSStack {
private:
    DSLinkedList<T> stack;

public:
    void push(T);   // Required functions
    void pop();     // The basic idea from this entire class is FIFO
    bool isEmpty();
    T peek();
};

// Pop a value off the stack, it would essentially just delete the last value in a linkedlist because FIFO
template <typename T>
void DSStack<T>::pop() {
    stack.delete_last();
}

// Push a value into the stack, it would push a value to the back of a linkedlist because FIFO
template <typename T>
void DSStack<T>::push(T val){
    stack.push_back(val);
}

// Check if head is nullptr to see if it's empty (it would have some other value if it isn't)
template <typename T>
bool DSStack<T>::isEmpty() {
    return stack.get_head() == nullptr;
}

// Return the top value off the stack which is basically the tail (again.. FIFO)
template <typename T>
T DSStack<T>::peek() {
    return stack.get_tail()->data;
}

#endif //INC_21F_FLIGHT_PLANNER_DSSTACK_H
