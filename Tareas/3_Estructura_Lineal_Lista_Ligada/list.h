#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <sstream>

template <class T>
class Link {
public:
    T value;
    Link<T>* next;
    Link(T val) : value(val), next(nullptr) {}
};

template <class T>
class List {
private:
    Link<T>* head;

public:

    void insertion(T val);
    int search(T val);
    void update(int index, T val);
    void deleteAt(int index);
    std::string toString();
    List() : head(nullptr) {}     

};

template <class T>
void List<T>::insertion(T val)  {
    Link<T>* new_val = new Link<T>(val); // Create a new value with the given value

    if (head == nullptr) {
        head = new_val;
    } else {
        Link<T>* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new_val;
    }
}

template <class T>
int List<T>::search(T val) {
    Link<T> *current = head;
    int index = 0;
    while (current) {
        if (current->value == val) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

template <class T>
void List<T>::update(int index, T val) {
    Link<T> *current = head;
    int current_index = 0;
    while (current) {
        if (current_index == index) {
            current->value = val;
            return;
        }
        current = current->next;
        current_index++;
    }
}

template <class T>
void List<T>::deleteAt(int index) {
    if (index == 0) {
        Link<T> *temp = head;
        head = head->next;
        delete temp;
    } else {
        Link<T> *current = head;
        int current_index = 0;
        while (current) {
            if (current_index == index - 1) {
                Link<T> *temp = current->next;
                current->next = temp->next;
                delete temp;
                return;
            }
            current = current->next;
            current_index++;
        }
    }
}

template <class T>
std::string List<T>::toString() {
    std::stringstream aux;
    Link<T>* ptr = head;
    aux << "[";
    while (ptr != nullptr) {
        aux << ptr->value;
        if (ptr->next != nullptr) {
            aux << ", ";
        }
        ptr = ptr->next;
    }
    aux << "]";
    return aux.str();
}

#endif