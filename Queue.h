#pragma once
#include "Node.h"
#include "doubleLinkedList.h"

template <typename T>
class Queue
{
    doubleLinkedList<T> list;
public:
    void Enqueue(const T& item) 
    { 
        list.insertEnd(item); 
    }
    bool Dequeue(T& out) 
    { 
        return list.removeFirst(out); 
    }
    bool Front(T& out) const { 
        return list.GetAt(0, out); 
    }
    int  Count() const{ 
        return list.Count(); 
    }
    bool IsEmpty() const{ 
        return list.isEmpty(); 
    }
};