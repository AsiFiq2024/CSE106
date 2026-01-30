#include "queue.h"
#include <iostream>
using namespace std;
// Constructor implementation
ArrayQueue::ArrayQueue(int initial_capacity)
{
    // TODO: Initialize data members (data, capacity, front_idx, rear_idx)
    // TODO: Allocate memory for the array with the specified initial capacity
    capacity = initial_capacity;
    data = new int[capacity];
    front_idx = 0;
    rear_idx = 0;
}

// Destructor implementation
ArrayQueue::~ArrayQueue()
{
    // TODO: Free the dynamically allocated memory for the array
    delete[] data;
}

// Enqueue implementation (add an item to the rear of the queue)
void ArrayQueue::enqueue(int item)
{
    // TODO: Check if the array is full
    // TODO: If full, resize the array to double its current capacity
    if (size() == capacity - 1)
        resize(capacity * 2);

    // TODO: Add the new element to the rear of the queue
    data[rear_idx] = item;
    rear_idx = (rear_idx + 1) % capacity;
}

// Dequeue implementation (remove an item from the front of the queue)
int ArrayQueue::dequeue()
{
    // TODO: Check if the queue is empty, display error message if it is
    if (empty())
    {
        cout << "Queue is empty" << endl;
        return -1;
    }

    int dequeue_element = data[front_idx];

    // TODO: Update front index
    front_idx = (front_idx + 1) % capacity;

    // TODO: If the array is less than 25% full, resize it to half its current capacity (but not less than 2)
    if (size() * 4 < capacity && capacity >= 4)
        resize(capacity / 2);

    // TODO: Return the dequeued element
    return dequeue_element;
}

// Clear implementation
void ArrayQueue::clear()
{
    // TODO: Reset the queue to be empty (reset capacity, front_idx, rear_idx, data)
    delete[] data;
    capacity = 2;
    data = new int[capacity];
    front_idx = 0;
    rear_idx = 0;
}

// Size implementation
int ArrayQueue::size() const
{
    // TODO: Return the number of elements currently in the queue
    return (rear_idx - front_idx + capacity) % capacity;
}

// Front implementation
int ArrayQueue::front() const
{
    // TODO: Check if the queue is empty, display error message if it is
    if (empty())
    {
        cout << "Queue is empty" << endl;
        return -1;
    }
    // TODO: Return the element at the front of the queue without removing it
    return data[front_idx];
}

// Back implementation (get the element at the back of the queue)
int ArrayQueue::back() const
{
    // TODO: Check if the queue is empty, display error message if it is
    if (empty())
    {
        cout << "Queue is empty" << endl;
        return -1;
    }
    // TODO: Return the element at the back of the queue without removing it
    return data[(rear_idx - 1 + capacity) % capacity];
}

// Empty implementation
bool ArrayQueue::empty() const
{
    // TODO: Return whether the queue is empty
    return size() == 0;
}

// Print implementation
string ArrayQueue::toString() const
{
    // TODO: Convert queue to a string representation in the format: <elem1, elem2, ..., elemN|
    string queue_seq;
    queue_seq += "<";
    for (int i = 0; i < size(); i++)
    {
        queue_seq += to_string(data[(front_idx + i) % capacity]);
        if (i != size() - 1)
            queue_seq += ", ";
    }
    queue_seq += "|";
    return queue_seq;
}

// Resize implementation
void ArrayQueue::resize(int new_capacity)
{
    int prev_size = size();
    // TODO: Create a new array with the new capacity
    int *new_data = new int[new_capacity];
    // TODO: Copy elements from the old array to the new array
    for (int i = 0; i < size(); i++)
    {
        new_data[i] = data[(front_idx + i) % capacity];
    }
    // TODO: Delete the old array
    delete[] data;
    // TODO: Update the data pointer and capacity
    data = new_data;
    // TODO: Update front and rear indices
    capacity = new_capacity;
    front_idx = 0;
    rear_idx = prev_size;
}

int ArrayQueue::getCapacity() const
{
    // TODO: Return the current capacity of the queue
    return capacity;
}