#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template<class T>
class LinkedList {
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T>& obj);

    ~LinkedList();

    int getSize() const;
    bool isEmpty() const;
    bool contains(Node<T>* node) const;

    Node<T>* getFirstNode() const;
    Node<T>* getLastNode() const;
    Node<T>* getNode(const T& data) const;
    Node<T>* getNodeAtIndex(int index) const;

    void insertAtTheFront(const T& data);
    void insertAtTheEnd(const T& data);
    void insertAfterNode(const T& data, Node<T>* node);
    void insertAsEveryKthNode(const T& data, int k);

    void removeNode(Node<T>* node);
    void removeNode(const T& data);
    void removeAllNodes();
    void removeEveryKthNode(int k);

    void swap(Node<T>* node1, Node<T>* node2);
    void shuffle(int seed);

    void print(bool reverse = false) const;

    LinkedList<T>& operator=(const LinkedList<T>& rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T>* head;

    int size;
};

template<class T>
LinkedList<T>::LinkedList() {
    /* TODO */
    head = NULL;
    size = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& obj) {
    /* TODO */

    if (obj.head == NULL) {
        head = NULL;


    }
    else if (obj.size == 1) {
        head = new Node<T>(obj.head->data);
        head->next = head;
        head->prev = head;
    }
    else {
        head = new Node<T>(obj.head->data);
        Node<T>* p1 = head;
        Node<T>* p2 = obj.head->next;
        while (p2 != obj.head) {
            p1->next = new Node<T>(p2->data);
            p1->next->prev = p1;
            p1 = p1->next;
            p2 = p2->next;
        }
        head->prev = p1;
        p1->next = head;

    }
    size = obj.size;
    
}

template<class T>
LinkedList<T>::~LinkedList() {
    /* TODO */
    if (this->head == NULL) {
        delete head;

    }
    else {
        if (head == head->next) {
            delete head;

        }

        else {
            int i;
            Node<T>* temp = head;

            for (i = 0; i < size; i++) {

                head = head->next;

                delete temp;

                temp = head;
            }
        }




    }
    size = 0;

}

template<class T>
int LinkedList<T>::getSize() const {
    /* TODO */
    return size;
}

template<class T>
bool LinkedList<T>::isEmpty() const {
    /* TODO */
    if (size == 0) {
        return true;
    }
    else {
        return false;
    }
}

template<class T>
bool LinkedList<T>::contains(Node<T>* node) const {
    /* TODO */
    Node<T>* current = head;

    for (int i = 0; i < size; i++) {
        if (current == node) {
            return true;
        }
        else {
            current = current->next;
        }
    }

    return false;
}

template<class T>
Node<T>* LinkedList<T>::getFirstNode() const {
    /* TODO */
    return head;
}

template<class T>
Node<T>* LinkedList<T>::getLastNode() const {
    /* TODO */

    if (head == NULL) {
        return NULL;
    }
    else {
        return head->prev;
    }
}

template<class T>
Node<T>* LinkedList<T>::getNode(const T& data) const {
    /* TODO */
    if (head == NULL) {
        return NULL;
    }
    else {
        Node<T>* current = head->next;
        if (head->data == data) {
            return head;
        }
        else {
            while (current != head) {
                if (current->data == data) {
                    return current;
                }
                else {
                    current = current->next;
                }
            }


        }
        return NULL;
    }
}

template<class T>
Node<T>* LinkedList<T>::getNodeAtIndex(int index) const {
    /* TODO */
    Node<T>* current = head;
    if (index > size - 1 || index < 0) {
        return NULL;
    }
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}

template<class T>
void LinkedList<T>::insertAtTheFront(const T& data) {
    /* TODO */
    Node<T>* p = new Node<T>(data);
    if (head == NULL) {
        head = p;
        head->next = head;
        head->prev = head;
    }
    else {
        p->next = head;
        p->prev = head->prev;
        head->prev = p;
        p->prev->next = p;
        head = p;
    }

    size += 1;

}

template<class T>
void LinkedList<T>::insertAtTheEnd(const T& data) {
    /* TODO */
    Node<T>* p = new Node<T>(data);
    if (head == NULL) {
        head = p;
        head->next = head;
        head->prev = head;
    }
    else {
        p->next = head;
        p->prev = head->prev;
        head->prev = p;
        p->prev->next = p;

    }
    size += 1;

}

template<class T>
void LinkedList<T>::insertAfterNode(const T& data, Node<T>* node) {
    /* TODO */
    bool x = true;
    if (head == NULL) {

    }
    else if (head == node) {
        Node<T>* p = new Node<T>(data);
        p->next = head->next;
        p->next->prev = p;
        head->next = p;
        p->prev = head;
        size += 1;
    }
    else {
        Node<T>* current = head->next;
        while (current != node) {

            if (current == head) {
                x = false;
                break;
            }
            current = current->next;
        }
        if (x) {
            Node<T>* p = new Node<T>(data);
            p->next = current->next;
            current->next = p;
            p->next->prev = p;
            p->prev = current;
            size += 1;
        }
    }

}

template<class T>
void LinkedList<T>::insertAsEveryKthNode(const T& data, int k) {
    /* TODO */
    bool x = true;
    int i = 0, a, b = 0;
    if (k <= 1) {

    }
    else {
        Node<T>* current = head;
        while (i < size) {
            a = 2;

            while (a < k) {
                current = current->next;
                i++;
                a++;
                if (current == head) {
                    x = false;
                    break;
                }

            }

            if (x) {
                Node<T>* p = new Node<T>(data);
                p->next = current->next;
                p->prev = current;
                current->next = p;
                p->next->prev = p;
                current = current->next->next;
                i += 2;
                size += 1;
            }
            else {
                break;
            }
            if (current == head) {
                x = false;
                break;
            }
        }
    }
}

template<class T>
void LinkedList<T>::removeNode(Node<T>* node) {
    /* TODO */
    Node<T>* current = head;
    for (int i = 0; i < size; i++) {

        if (head == node && size == 1) {
            delete head;
            size = 0;
            break;
        }
        else if (head == node && size != 1) {
            Node<T>* temp = head;
            head->next->prev = head->prev;
            head->prev->next = head->next;
            head = head->next;
            delete temp;
            size -= 1;
            break;
        }
        else {
            if (current == node) {
                current->next->prev = current->prev;
                current->prev->next = current->next;
                delete current;
                size -= 1;
                break;
            }
            else {
                current = current->next;
            }
        }
    }
}

template<class T>
void LinkedList<T>::removeNode(const T& data) {
    /* TODO */
    Node<T>* current = head;
    for (int i = 0; i < size; i++) {

        if (head->data == data && size == 1) {
            delete head;
            size = 0;
            head = NULL;
            break;

        }
        else if (head->data == data && size != 1) {
            Node<T>* temp = head;
            head->next->prev = head->prev;
            head->prev->next = head->next;
            head = head->next;
            current = current->next;
            delete temp;
            size -= 1;
            i--;

        }
        else {
            if (current->data == data) {
                current->next->prev = current->prev;
                current->prev->next = current->next;
                Node<T>* temp = current;
                current = current->next;
                delete temp;
                size -= 1;
                i--;
            }
            else {
                current = current->next;
            }
        }
    }
}

template<class T>
void LinkedList<T>::removeAllNodes() {
    /* TODO */
    for (int i = 0; i < size; i++) {
        Node<T>* temp = head;
        head->next->prev = head->prev;
        head->prev->next = head->next;
        head = head->next;
        delete temp;
        size--;
        i--;

    }
    head = NULL;
}

template<class T>
void LinkedList<T>::removeEveryKthNode(int k) {
    /* TODO */
    Node<T>* current = head;
    Node<T>* temp;
    bool x = true;
    if (k < 2) {

    }
    else {
        for (int i = 0; i < size; i++) {
            for (int b = 1; b < k; b++) {
                current = current->next;
                if (current == head) {
                    x = false;
                    break;
                }
            }
            if (x) {
                temp = current;
                current->prev->next = current->next;
                current->next->prev = current->prev;
                current = current->next;
                delete temp;
                size--;
            }


        }
    }
}

template<class T>
void LinkedList<T>::swap(Node<T>* node1, Node<T>* node2) {
    /* TODO */

    if (contains(node2) && contains(node1))
    {
        if (node1 != node2) {
            Node<T>* n;
            Node<T>* p;

            if (node1 == head) {
                head = node2;
            }
            else if (node2 == head) {
                head = node1;
            }
            if ((node1->next == node2) && size == 2)
            {

            }
            else if (node2->next == node1)
            {
                node1->next->prev = node2;
                node2->prev->next = node1;
                node1->prev = node2->prev;
                node2->next = node1->next;
                node1->next = node2;
                node2->prev = node1;
            }
            else if (node1->next == node2)
            {
                node2->next->prev = node1;
                node1->prev->next = node2;
                node1->next = node2->next;
                node2->prev = node1->prev;
                node2->next = node1;
                node1->prev = node2;
            }
            else
            {
                n = node1->next;
                p = node1->prev;
                node2->prev->next = node1;
                node2->next->prev = node1;
                node1->prev->next = node2;
                node1->next->prev = node2;
                node1->next = node2->next;
                node1->prev = node2->prev;
                node2->next = n;
                node2->prev = p;
            }
        }

    }
}
template<class T>
void LinkedList<T>::shuffle(int seed) {
    /* TODO */
    int index;

    for (int i = 0; i < size; i++) {
        index = (i * i + seed) % size;
        swap(getNodeAtIndex(i), getNodeAtIndex(index));
    }

}

template<class T>
void LinkedList<T>::print(bool reverse) const {
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    if (reverse) {
        // traverse in reverse order (last node to first node).

        Node<T>* node = this->getLastNode();

        do {
            std::cout << *node << std::endl;
            node = node->prev;
        } while (node != this->getLastNode());
    }
    else {
        // traverse in normal order (first node to last node).

        Node<T>* node = this->getFirstNode();

        do {
            std::cout << *node << std::endl;
            node = node->next;
        } while (node != this->getFirstNode());
    }
}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
    /* TODO */

    if (this != &rhs) {
        removeAllNodes();
        if (rhs.head == NULL) {
            head = NULL;


        }
        else if (rhs.size == 1) {
            this->head = new Node<T>(rhs.head->data);
            this->head->next = head;
            this->head->prev = head;
        }
        else {
            this->head = new Node<T>(rhs.head->data);
            Node<T>* p1 = this->head;
            Node<T>* p2 = rhs.head->next;
            while (p2 != rhs.head) {
                p1->next = new Node<T>(p2->data);
                p1->next->prev = p1;
                p1 = p1->next;
                p2 = p2->next;
            }
            this->head->prev = p1;
            p1->next = this->head;

        }
        this->size = rhs.size;
    }

    return *this;

}

#endif //LINKEDLIST_H
