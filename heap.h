//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        // insert index at end of heap, restore order using upheap()
        data[size] = idx;
        size++;

        upheap(size - 1, weightArr);
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        return -1; // placeholder
    }

    void upheap(int pos, int weightArr[]) {
        // swap the child upward if smaller than parent 
        while (pos > 0) {
            int parent;
            parent = (pos - 1) / 2;

            if (weightArr[data[pos]] < weightArr[data[parent]]) {
            int temp = data[pos];
            data[pos] = data[parent];
            data[parent] = temp;

            // moving up to the parent 
            pos = parent;
        } 
        else {
            break;
                }
            }
        }


    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child

    }
};

#endif