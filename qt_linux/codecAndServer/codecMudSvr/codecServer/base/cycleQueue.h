#ifndef CYCLEQUEUE_H
#define CYCLEQUEUE_H

#include <iostream>
using namespace std;

template <class T>

class cycleQueue
{
public:
    cycleQueue(unsigned int size);
    ~cycleQueue();
    bool isEmpty();
    bool isFull();
    void push(T ele);
    void pushR(T && ele);
    T pop();
private:
    unsigned int m_size;
    int m_front;
    int m_rear;
    T*  m_data;
};

#endif // CYCLEQUEUE_H
