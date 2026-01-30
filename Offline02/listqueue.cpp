#include "queue.h"
#include <iostream>
using namespace std;

// Constructor implementation
ListQueue::ListQueue()
{
    // TODO: Initialize front_node and rear_node
    front_node = rear_node = nullptr;

    // TODO: Initialize current_size to 0
    current_size = 0;
}

// Destructor implementation
ListQueue::~ListQueue()
{
    // TODO: Deallocate all nodes in the linked list
    // TODO: Consider using the clear() method
    clear();
}

// Enqueue implementation (add an item at the rear of the queue)
void ListQueue::enqueue(int item)
{
    // TODO: Create a new node with the given item
    Node *newNode = new Node(item);

    // TODO: Link the new node to the rear
    if (empty())
    {
        front_node = rear_node = newNode;
    }
    else
    {
        rear_node->next = newNode;

        // TODO: Update the rear_node
        rear_node = rear_node->next;
    }

    // TODO: Increment the current size
    current_size++;
}

// Dequeue implementation (remove an item from the front of the queue)
int ListQueue::dequeue()
{
    // TODO: Check if the queue is empty, display error message if it is
    if (empty())
    {
        cout << "Queue is empty." << endl;
        return -1;
    }

    // TODO: Store the data from the front node
    int dequeued_val = front_node->data;
    Node *old_front = front_node;

    // TODO: Update the front pointer to the next node
    front_node = front_node->next;

    // TODO: Update the rear pointer if the queue becomes empty
    if (front_node == nullptr)
    {
        rear_node = nullptr;
    }

    // TODO: Delete the old front node
    delete old_front;

    // TODO: Decrement current_size
    current_size--;

    // TODO: Return the stored data
    return dequeued_val;
}

// Clear implementation (delete all elements)
void ListQueue::clear()
{
    // TODO: Traverse the linked list and delete each node
    // TODO: Reset front and rear pointer
    // TODO: Reset current_size to 0
    while (front_node != nullptr)
    {
        Node *temp = front_node;
        front_node = front_node->next;
        delete temp;
    }
    rear_node = nullptr;
    current_size = 0;
}

// Size implementation (return the current number of elements)
int ListQueue::size() const
{
    // TODO: Return the current size (current_size)
    return current_size;
}

// Front implementation (get the element at the front of the queue)
int ListQueue::front() const
{
    // TODO: Check if the queue is empty, display error message if it is
    if (empty())
    {
        cout << "Queue is empty." << endl;
        return -1;
    }

    // TODO: Return the data from the front node without removing it
    return front_node->data;
}

// Back implementation (get the element at the back of the queue)
int ListQueue::back() const
{
    // TODO: Check if the queue is empty, display error message if it is
    if (empty())
    {
        cout << "Queue is empty." << endl;
        return -1;
    }

    // TODO: Return the data from the back node without removing it
    return rear_node->data;
}

// Empty implementation (check if the queue is empty)
bool ListQueue::empty() const
{
    // TODO: Return whether front is nullptr
    return current_size == 0;
}

// Print implementation (print elements from front to rear)
string ListQueue::toString() const
{
    // TODO: Convert queue to a string representation in the format: <elem1, elem2, ..., elemN|
    string queue_seq;
    queue_seq += "<";

    // TODO: Traverse the linked list from front
    Node *temp = front_node;
    while (temp != nullptr)
    {
        queue_seq += to_string(temp->data);
        if (temp->next != nullptr)
            queue_seq += ", ";
        temp = temp->next;
    }
    queue_seq += "|";

    return queue_seq;
}
