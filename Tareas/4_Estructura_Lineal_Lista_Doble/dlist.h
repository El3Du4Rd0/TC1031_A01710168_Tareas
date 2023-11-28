#ifndef DLIST_H
#define DLIST_H

#include <string>
#include <sstream>

template <class T> class DList;

template <class T>
class DLink {
private:
	DLink(T);
	DLink(T, DLink<T>*, DLink<T>*);

	T value;
	DLink<T> *previous;
	DLink<T> *next;

	friend class DList<T>; 
};

template <class T>
DLink<T>::DLink(T val) : value(val), previous(nullptr), next(nullptr) {} 

template <class T>
DLink<T>::DLink(T val, DLink *prev, DLink* nxt) : value(val), previous(prev), next(nxt) {} 

template <class T>
class DList {
	private:
        DLink<T> *head;
	    DLink<T> *tail; 
	    int size; 

    public:
		DList(); 
	    DList(const DList<T>&); 
        ~DList() { clear(); }
        bool empty() const { return (head == 0); }; 
        void clear();
		
		void insertion(T);
        T search(T);
    	void update(int, T); 
    	void deleteAt(int); 

		std::string toStringForward() const;
        std::string toStringBackward() const;
};

template <class T>
DList<T>::DList() : head(nullptr), tail(nullptr) {}

template <class T>
DList<T>::DList(const DList<T> &source) : head(nullptr), tail(nullptr) {
	DLink<T> *p, *q; 

	if (source.empty()) {
		size = 0;
		head = 0;
		tail = 0;
	} 
	else {
		p = source.head;
		head = new DLink<T>(p->value);
		q = head;

		p = p->next;
		while(p != 0) {
			q->next = new DLink<T>(p->value, q, 0);
			p = p->next;
			q = q->next;
		}
		size = source.size;
	}
}

template <class T>
void DList<T>::clear() {
	DLink<T> *p, *q;

	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0; tail = 0; size = 0;
}

template <class T>
void DList<T>::insertion(T val) {

	DLink<T> *newLink = new DLink<T>(val);

	if (empty()) {
		head = newLink;
		tail = newLink;
	} 
	else {
		tail->next = newLink;
		newLink->previous = tail;
		tail = newLink;
	}
	size++;
}

template <class T>
T DList<T>::search(T val) {
	DLink<T> *current = head;
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
void DList<T>::update(int index, T val) {
    DLink<T> *current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    current->value = val;
}

template <class T>
void DList<T>::deleteAt(int index) {
    int pos;
    DLink<T> *p;
    if (index == 0) {
        p = head;

        if (head == tail) {
            head = nullptr;
            tail = nullptr;
        } 
		else {
            head = p->next;
            p->next->previous = nullptr;
        }
        delete p;
        size--;
        return;
    }
    p = head; 
    pos = 0; 
    while (pos != index) {
        p = p->next;
        pos++;
    }

    p->previous->next = p->next;
    if (p->next != nullptr) {
        p->next->previous = p->previous;
    }
    size--;
    delete p;
}

template <class T>
std::string DList<T>::toStringForward() const {
	std::stringstream aux;
	DLink<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string DList<T>::toStringBackward() const {
	std::stringstream aux;
	DLink<T> *p;

	p = tail;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->previous != 0) {
			aux << ", ";
		}
		p = p->previous;
	}
	aux << "]";
	return aux.str();
}

#endif