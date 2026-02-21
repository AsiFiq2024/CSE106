#ifndef MINHEAP_H
#define MINHEAP_H

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <climits>

#define MAX_CAPACITY 1000 // Defines the maximum capacity of the heap

class MinHeap
{
private:
    int heap[MAX_CAPACITY]; // Array to store heap elements
    int size;               // Current number of elements in the heap

    /**
     * Sifts up the node at index i to maintain heap property.
     */
    void siftUp(int i)
    {
        /**Write your code here**/
        while (i > 0 && heap[i] < heap[(i - 1) / 2])
        {
            int temp = heap[i];
            heap[i] = heap[(i - 1) / 2];
            heap[(i - 1) / 2] = temp;
            i = (i - 1) / 2;
        }
    }

    /**
     * Sifts down the node at index i to maintain heap property.
     */
    void siftDown(int i)
    {
        /**Write your code here**/
        while (true)
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int f = 0;

            if (i >= size)
                break;
            else if (left >= size && right >= size)
                break;

            if (left < size && right < size)
            {
                if (heap[left] > heap[right])
                {
                    if (heap[i] > heap[right])
                    {
                        int temp = heap[i];
                        heap[i] = heap[right];
                        heap[right] = temp;
                        i = right;
                        f = 1;
                    }
                }
                else
                {
                    if (heap[i] > heap[left])
                    {
                        int temp = heap[i];
                        heap[i] = heap[left];
                        heap[left] = temp;
                        i = left;
                        f = 1;
                    }
                }
            }
            else if (left < size)
            {
                if (heap[i] > heap[left])
                {
                    int temp = heap[i];
                    heap[i] = heap[left];
                    heap[left] = temp;
                    i = left;
                    f = 1;
                }
            }
            else if (right < size)
            {
                if (heap[i] > heap[right])
                {
                    int temp = heap[i];
                    heap[i] = heap[right];
                    heap[right] = temp;
                    i = right;
                    f = 1;
                }
            }
            if (!f)
                break;
        }
    }

public:
    // Constructor initializes an empty heap
    MinHeap() : size(0) {}

    /**
     * Inserts a new element x into the heap.
     */
    void insert(int x)
    {
        /**Write your code here**/
        if (size == MAX_CAPACITY)
            return;

        int idx = size;
        size++;
        heap[idx] = x;

        siftUp(idx);
    }

    /**
     * Returns the minimum element without removing it.
     */
    int findMin()
    {
        /**Write your code here**/
        if (size == 0)
        {
            return -1;
        }

        return heap[0];
    }

    /**
     * Removes and returns the minimum element from the heap.
     */
    int extractMin()
    {

        /**Write your code here**/
        if (size == 0)
        {
            return -1;
        }

        int min = heap[0];
        heap[0] = heap[size - 1];
        size--;
        siftDown(0);

        return min;
    }

    /**
     * Returns the number of elements in the heap.
     */
    int getSize()
    {
        /**Write your code here**/
        return size;
    }

    /**
     * Checks if the heap is empty.
     * Returns true if empty, false otherwise.
     */
    bool isEmpty()
    {
        /**Write your code here**/
        return size == 0;
    }

    /**
     * Decreases the value of the element at index i to newValue.
     */
    void decreaseKey(int i, int newValue)
    {
        /**Write your code here**/
        if (i >= size)
            return;

        heap[i] = newValue;
        siftUp(i);
    }

    /**
     * Deletes the element at index i.
     */
    void deleteKey(int i)
    {
        /**Write your code here**/
        if (i >= size)
            return;

        decreaseKey(i, findMin());
        extractMin();
    }

    /**
     * Prints the heap's content to the output file.
     * Format: "elem1 elem2 elem3 ..." (space-separated)
     */
    void printHeap(std::ofstream &outfile)
    {
        /**Write your code here**/
        if (isEmpty())
        {
            outfile << "No elements" << std::endl;
            return;
        }

        for (int i = 0; i < size; i++)
        {
            outfile << heap[i] << " ";
        }
        outfile << std::endl;
    }

    /**
     * Checks whether the Min Heap property is preserved.
     * Returns true if valid, false otherwise.
     */
    bool isValidMinHeap()
    {
        /**Write your code here**/
        for (int i = 0; i < size; i++)
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (right < size)
            {
                if (heap[i] > heap[left] || heap[i] > heap[right])
                {
                    return false;
                }
            }
            else if (left < size)
            {
                if (heap[i] > heap[left])
                {
                    return false;
                }
            }
        }
        return true;
    }

    /**
     * Builds a heap from an unsorted array using bottom-up heapify.
     */
    void heapify(int arr[], int n)
    {
        /**Write your code here**/
        for (int i = 0; i < n; i++)
        {
            heap[i] = arr[i];
        }
        size = n;

        for (int i = (size - 2) / 2; i >= 0; i--)
        {
            siftDown(i);
        }
    }

    /**
     * Returns all elements in sorted (ascending) order.
     * The original heap should remain UNCHANGED after this operation.
     */
    void heapSort(std::ofstream &outfile)
    {
        /**Write your code here**/
        int prev_size = size;
        int arr[prev_size];
        for (int i = 0; i < prev_size; i++)
        {
            arr[i] = heap[i];
        }

        for (int i = 0; i < prev_size; i++)
        {
            outfile << extractMin() << " ";
        }

        outfile << std::endl;

        for (int i = 0; i < prev_size; i++)
        {
            heap[i] = arr[i];
        }
        size = prev_size;
    }

    /**
     * Replaces the minimum element with a new value x in a single operation.
     * Returns the old minimum value.
     */
    int replaceMin(int x)
    {
        /**Write your code here**/
        if (isEmpty())
        {
            return -1;
        }

        int old_min = findMin();
        heap[0] = x;
        siftDown(0);

        return old_min;
    }
};

#endif // MINHEAP_H
