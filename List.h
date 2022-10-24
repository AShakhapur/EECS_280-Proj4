#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL

using namespace std;

template <typename T>
class List {
    //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

    List() {
        first = nullptr;
        last = nullptr;
        list_size = 0;
    }

    List(const List& other) {

        first = nullptr;
        last = nullptr;
        list_size = 0;
        copy_all(other);
    }

    List& operator=(const List& rhs) {
        if (this != &rhs) {
            clear();
            copy_all(rhs);
        }
        return *this;
    }

    ~List() {
        clear();
    }
    //EFFECTS:  returns true if the list is empty
    bool empty() const {
        //assert(false);
        //return list_size == 0; 
        return first == nullptr;
    }

    //EFFECTS: returns the number of elements in this List
    //HINT:    Traversing a list is really slow.  Instead, keep track of the size
    //         with a private member variable.  That's how std::list does it.
    int size() const {
        return list_size;
        //assert(false);
    }

    //REQUIRES: list is not empty
    //EFFECTS: Returns the first element in the list by reference
    T& front() {
        assert(!empty());
        return first->datum;
    }

    //REQUIRES: list is not empty
    //EFFECTS: Returns the last element in the list by reference
    T& back() {
        assert(!empty());
        return last->datum;
    }

    //EFFECTS:  inserts datum into the front of the list
    void push_front(const T& datum) {
        Node* new_node = new Node{ nullptr, nullptr, datum };

        if (empty()) {
            first = last = new_node;
        }
        else {
            first->prev = new_node;
            new_node->next = first;
            first = new_node;
        }
        list_size++;
    }

    //EFFECTS:  inserts datum into the back of the list
    void push_back(const T& datum) {

        Node* new_node = new Node{ nullptr, nullptr, datum };

        if (empty()) {
            first = last = new_node;
        }
        else {
            last->next = new_node;
            new_node->prev = last;
            last = new_node;
        }
        list_size++;
    }

    //REQUIRES: list is not empty
    //MODIFIES: may invalidate list iterators
    //EFFECTS:  removes the item at the front of the list

    void pop_front() {
        assert(!empty());
        Node* old_first = first;  // temporary keeps track of old first

        if (list_size == 1) {
            first = nullptr;
            last = nullptr;
        }
        else {
            first = first->next;
            first->prev = nullptr;
        }
        delete old_first;
        list_size--;

    }
    //REQUIRES: list is not empty
    //MODIFIES: may invalidate list iterators
    //EFFECTS:  removes the item at the back of the list
    void pop_back() {
        assert(!empty());

        Node* old_last = last;  // temporary keeps track of old last

        // If there’s only 1 node in the list, this method should remove 
        // this node and set head and last to nullptr
        if (size() == 1) {
            first = nullptr;
            last = nullptr;
        }
        else {
            last->prev->next = nullptr;
            last = last->prev;
        }
        delete old_last;
        list_size--;
    }

    //MODIFIES: may invalidate list iterators
    //EFFECTS:  removes all items from the list
    void clear() {
        while (!empty()) {
            pop_front();
        }
        //assert(false);
    }

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Lists

private:
    //a private type
    struct Node {
        Node* next;
        Node* prev;
        T datum;
    };

    //REQUIRES: list is empty
    //EFFECTS:  copies all nodes from other to this
    void copy_all(const List<T>& other) {
        for (Node* node_ptr = other.first; node_ptr != nullptr;
            node_ptr = node_ptr->next) {
            push_back(node_ptr->datum);
        }
        //assert(false);
    }

    Node* first;   // points to first Node in list, or nullptr if list is empty
    Node* last;    // points to last Node in list, or nullptr if list is empty
    size_t list_size = 0;

public:
    ////////////////////////////////////////
    class Iterator {
        //OVERVIEW: Iterator interface to List

        // You should add in a default constructor, destructor, copy constructor,
        // and overloaded assignment operator, if appropriate. If these operations
        // will work correctly without defining these, you can omit them. A user
        // of the class must be able to create, copy, assign, and destroy Iterators.

        // Your iterator should implement the following public operators: *,
        // ++ (prefix), default constructor, == and !=.

    public:

        Iterator() : node_ptr(nullptr) {}
        // construct an Iterator at a specific position
        Iterator(Node* p) {
            node_ptr = p;
        }
        //
        ~Iterator() {}
        //
        // This operator will be used to test your code. Do not modify it.
        // Requires that the current element is dereferenceable.
        Iterator& operator--() {
            assert(node_ptr);
            node_ptr = node_ptr->prev;
            return *this;
        }

        Iterator& operator++() {
            assert(node_ptr);
            node_ptr = node_ptr->next;
            return *this;
        }

        bool operator==(Iterator rhs) const {
            return node_ptr == rhs.node_ptr;
        }

        bool operator!=(Iterator rhs) const {
            return node_ptr != rhs.node_ptr;
        }

        T& operator*() const {
            assert(node_ptr != nullptr);
            return node_ptr->datum;
        }

    private:
        Node* node_ptr; //current Iterator position is a List node
        // add any additional necessary member variables here

        // add any friend declarations here
        friend class List;

    };//List::Iterator
    ////////////////////////////////////////

    // return an Iterator pointing to the first element
    Iterator begin() const {
        return Iterator(first);
    }

    // return an Iterator pointing to "past the end"
    Iterator end() const {
        return Iterator();
    }

    //REQUIRES: i is a valid, dereferenceable iterator associated with this list
    //MODIFIES: may invalidate other list iterators
    //EFFECTS: Removes a single element from the list container
    void erase(Iterator i) {
        assert(i.node_ptr);

        Node* cur_node = i.node_ptr;

        if (cur_node == first) {
            pop_front();
        }
        else if (cur_node == last) {
            pop_back();
        }
        else {
            cur_node->prev->next = cur_node->next;
            cur_node->next->prev = cur_node->prev;
            delete cur_node;
            list_size--;
        }

    }

    //REQUIRES: i is a valid iterator associated with this list
    //EFFECTS: inserts datum before the element at the specified position.
    void insert(Iterator i, const T& datum) {
        Node* cur_node = i.node_ptr;


        if (cur_node == first) {
            push_front(datum);
        }
        else {
            Node* new_node = new Node{ nullptr, nullptr, datum };

            new_node->prev = cur_node->prev;
            new_node->next = cur_node;

            cur_node->prev->next = new_node;
            cur_node->prev = new_node;
            list_size++;
        }
    }
};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.

#endif // Do not remove this. Write all your code above this line.