#ifndef HEAP_H
#define HEAP_H

#include <functional>
#include <memory>
#include <stdexcept>
#include <utility>

using namespace std;

template <typename T, typename Compare = less<T>>
class Heap
{
private:
    unique_ptr<T[]> arr;
    int size;
    int capacity;
    Compare comp;

    void heapifyUp(int i)
    {
        while (i > 0)
        {
            int parent = (i - 1) / 2;
            if (comp(arr[parent], arr[i]))
            {
                swap(arr[i], arr[parent]);
                i = parent;
            }
            else
            {
                break;
            }
        }
    }

    void heapifyDown(int i)
    {
        while (true)
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int largest = i;

            if (left < size && comp(arr[largest], arr[left]))
            {
                largest = left;
            }
            if (right < size && comp(arr[largest], arr[right]))
            {
                largest = right;
            }
            if (largest == i)
            {
                break;
            }
            swap(arr[i], arr[largest]);
            i = largest;
        }
    }

    void resize()
    {
        capacity *= 2;
        unique_ptr<T[]> temp(new T[capacity]);
        for (int i = 0; i < size; i++)
        {
            temp[i] = std::move(arr[i]);
        }
        arr = std::move(temp);
    }

public:
    Heap(int cap = 10, Compare c = Compare())
        : size(0), capacity(cap < 1 ? 1 : cap), comp(c)
    {
        arr.reset(new T[capacity]);
    }

    void insert(T item)
    {
        if (size == capacity)
        {
            resize();
        }
        arr[size] = std::move(item);
        heapifyUp(size);
        size++;
    }

    T extractMax()
    {
        if (size == 0)
        {
            throw out_of_range("extractMax() called on an empty heap");
        }
        T top = std::move(arr[0]);
        size--;
        if (size > 0)
        {
            arr[0] = std::move(arr[size]);
            heapifyDown(0);
        }
        return top;
    }

    bool isEmpty() const
    {
        return size == 0;
    }

    int getSize() const
    {
        return size;
    }
};

#endif
