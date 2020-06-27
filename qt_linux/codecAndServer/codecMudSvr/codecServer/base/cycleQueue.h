#ifndef CYCLEQUEUE_H
#define CYCLEQUEUE_H
#include <iostream>
#include <memory>
using namespace std;

template <class T>
class cycleQueue
{
private:
    unsigned int m_size;
    int m_front;
    int m_rear;
    T*  m_data;
public:
    cycleQueue(unsigned size);
    ~cycleQueue();
    bool isEmpty();
    bool isFull();
    void push(T ele);
    T pop();
};


template <class T>
cycleQueue<T>::cycleQueue(unsigned size)
    :m_size(size),
    m_front(0),
    m_rear(0)
{
    m_data = new T[size];
}

template <class T>
cycleQueue<T>::~cycleQueue()
{
    delete [] m_data;
}

template <class T>
bool  cycleQueue<T>::isEmpty()
{
    return m_front == m_rear;
}

template <class T>
bool cycleQueue<T>::isFull()
{
    return m_front == (m_rear + 1)%m_size;
}

template <class T>
void cycleQueue<T>::push(T ele)
{
    if(isFull())
    {
        throw bad_exception();
    }
    m_data[m_rear] = ele;
    m_rear = (m_rear + 1)%m_size;
}

template <class T>
T cycleQueue<T>::pop()
{
    if(isEmpty())
    {
        throw bad_exception();
    }
    T tmp = m_data[m_front];
    m_front = (m_front + 1)%m_size;
    return tmp;
}

#endif // CYCLEQUEUE_H
