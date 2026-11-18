#pragma once
#include "Node.h"
#include "doubleLinkedList.h"

template <typename T>
class Queue
{
    doubleLinkedList<T> list;
public:
    void Enqueue(T& item) 
    { 
        list.insertEnd(item); 
    }
    bool Dequeue(T& out) 
    { 
        return list.removeFirst(out); 
    }
    bool Front(T& out){ 
        return list.GetAt(0, out); 
    }
    int  Count(){ 
        return list.Count(); 
    }
    bool IsEmpty(){ 
        return list.isEmpty(); 
    }
};