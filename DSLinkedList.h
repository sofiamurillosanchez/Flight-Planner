//
// Created by Sofia  Murillo on 10/19/21.
//

#ifndef INC_21F_FLIGHT_PLANNER_DSLINKEDLIST_H
#define INC_21F_FLIGHT_PLANNER_DSLINKEDLIST_H

#include <iostream>


// The Node class! :)
template <typename T>
class Node {

public:
    Node() {    // Basic constructor, just initialize next and prev
        next = nullptr;
        prev = nullptr;
    };
    Node(T& val){   // Constructor with parameter, just set the data of the node to val
        data = val;
        next = nullptr;
        prev = nullptr;
    };
    Node<T>* getNext(); // Get the next node
    Node<T>* getPrev(); // Get the previous node
    T data; // The actual value of the node
    Node<T>* next;  // Next node
    Node<T>* prev;  // Previous node
};


// Same comments as above, just return next
template <typename T>
Node<T>* Node<T> :: getNext(){
    return next;
}

// Return prev
template <typename T>
Node<T>* Node<T> :: getPrev(){
    return prev;
}

// DSLinkedList!
template <typename T>
class DSLinkedList {
private:
    Node<T>* head = nullptr,* tail = nullptr,* curr = nullptr;

public:
    // Default Constructor, Copy Constructor, Destructor
    DSLinkedList();
    DSLinkedList(const T&);
    DSLinkedList(const DSLinkedList<T>&);
    ~DSLinkedList();

    // Iteration functions!
    void set_curr_head();
    void advance_curr();
    T& get_curr_val();
    bool has_next();

    // Getters for head tail and curr
    Node<T>* get_head();
    Node<T>* get_tail();
    Node<T>* get_curr();

    // Push_back, front, and delete functions
    void push_front(T&); // Referenced https://www.cplusplus.com/reference/list/list/push_front/
    void push_back(T&);
    void delete_last();

    // Final part of rule of 3!
    DSLinkedList& operator=(const DSLinkedList<T>&);

};

// Nothing needs to be set in here since head, tail, and curr are already set to nullptr
template <typename T>
DSLinkedList<T> ::DSLinkedList() {}

// Copy Constructors
template <typename T>
DSLinkedList<T>::DSLinkedList(const T& val){
    this->head = val;   // Set head to val and prev and tail values to nullptr (easy money!)
    this->head->prev = nullptr;
    this->tail = nullptr;
}

template <typename T>
DSLinkedList<T>::DSLinkedList(const DSLinkedList<T> & list) { // Referenced: https://www.homeworklib.com/qaa/756922/c-linkedlist-i-need-the-code-for-copy-constructor
    if(list.head == nullptr){   // Check whether the list head is nullptr
        this->head = nullptr;
        return;
    }

    this->head = list.head; // Set head of instance list to parameter list
    this->head->data = list.head->data;
    set_curr_head();
    Node<T>* current = list.head;

    while(current != nullptr){  // Set all values in the list to the instance variable list
        this->curr = current;
        this->curr->data = current->data;
        current = current->next;
    }
    this->curr->next = nullptr;
}

// Destructor
template <typename T>
DSLinkedList<T> ::~DSLinkedList() {
    Node<T>* temp;

    if(head != nullptr) {   // Make sure head isn't nullptr
        while (head != nullptr) {   // Delete all values after head using a temp node
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    head = nullptr; // Set head, tail, and curr to nullptr
    tail = nullptr;
    curr = nullptr;
}

// set curr to its next node
template <typename T>
void DSLinkedList<T>::advance_curr() {
    curr = curr->next;
}

// set curr to head
template <typename T>
void DSLinkedList<T>::set_curr_head() {
    curr = head;
}

// get curr's value (just return curr->data)
template <typename T>
T& DSLinkedList<T>::get_curr_val() {
    return curr->data;
}

// get curr itself
template <typename T>
Node<T>* DSLinkedList<T>::get_curr() {
    return curr;
}

// get head
template <typename T>
Node<T>* DSLinkedList<T>::get_head() {
    return head;
}

// get tail
template <typename T>
Node<T>* DSLinkedList<T>::get_tail() {
    return tail;
}

// check whether there is a nect value bu seeing whether curr is nullptr, if it is, then there isn't a next value
// if it isn't then return whether curr's next value is nullptr
template <typename T>
bool DSLinkedList<T>::has_next() {
    if(curr == nullptr){
        return false;
    }
    else{
        return curr->next != nullptr;
    }
}

// Push a value to the front of a linkedlist
template <typename T>
void DSLinkedList<T>::push_front(T &val) { // Referenced: https://www.softwaretestinghelp.com/doubly-linked-list-2/
    Node<T>* temp = new Node<T>(val); // Create a new node with val
    temp->prev = nullptr;
    temp->next = head;

    if(head != nullptr){ // Check whether head is null
        head->prev = temp;
    }
    else {
        tail = temp;
        curr = temp;
    }

    head = temp; // Set head as temp
}

// Push_back function of LinkedList
template<typename T>
void DSLinkedList<T> ::push_back(T& val){ // Referenced: https://www.softwaretestinghelp.com/doubly-linked-list-2/
    Node<T>* temp = new Node<T>(val);
    set_curr_head();

    if(head == nullptr){    // If head is nullptr, just set head, tail, and curr to the temp value
        head = temp;
        tail = temp;
        curr = temp;
        return;
    }
    tail->next = temp;  // If not, then just set tail's next value to temp and tail's previous value to tail, and temp's to nullptr
    temp->prev = tail;  // tl; dr, just make temp the tail after the current tail (so it is no longer the tail)
    temp->next = nullptr;
    tail = temp;

}

// Delete the last node in the linked list
template<typename T>
void DSLinkedList<T>::delete_last() {
    if(head != nullptr){    // Make sure head isn't nullptr, or else this will not go the way you want it to
        if(head->next == nullptr){  // Check whether the next value of head is nullptr
            head = nullptr;
        }

        else{
            Node<T>* temp = head;   // Set the current value to head
            while(temp->next->next != nullptr){ // Check whether the next node's next node is nullptr
                temp = temp->next;
            }

            temp->next = nullptr;   // Set temp->next to nullptr (essentially "deleting" the last node
            tail = temp; // Set tail = to temp
        }
    }
}

// The assignment operator!
template<typename T>
DSLinkedList<T>& DSLinkedList<T>::operator=(const DSLinkedList<T>& list) { // Referenced: https://www.homeworklib.com/qaa/756922/c-linkedlist-i-need-the-code-for-copy-constructor
    if(this == &list){     // Follow similar logic to the copy constructor!
        return *this;
    }

    if(list.head == nullptr){   // Check whether the head is nullptr
        head = nullptr;
        tail = nullptr;
        curr = nullptr;
        return *this;
    }
    Node<T>* current = list.head;

    while(current != nullptr){  // Push back the values from the list to the instance variable list
        push_back(current->data);
        current = current->next;
    }

    return *this;       // Return the instance variable list
}


#endif //INC_21F_FLIGHT_PLANNER_DSLINKEDLIST_H
