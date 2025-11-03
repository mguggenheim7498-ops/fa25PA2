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
        // remove and return smallest index
        // Replace root with last element, then call downheap()
        if (size == 0) return -1; // heap is empty
        
        int root = data[0];
        data[0] = data[size - 1];
        size--;
        
        if (size > 0) {
            downheap(0, weightArr);
        }
        
        return root;
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
        // swap parent downward while larger than any child
        while (true) {
            int leftChild = 2 * pos + 1;
            int rightChild = 2 * pos + 2;
            int smallest = pos;
            
            // find the smallest in parent/children
            if (leftChild < size && weightArr[data[leftChild]] < weightArr[data[smallest]]) {
                smallest = leftChild;
            }
            if (rightChild < size && weightArr[data[rightChild]] < weightArr[data[smallest]]) {
                smallest = rightChild;
            }
            
            // if parent is already smallest breka
            if (smallest == pos) {
                break;
            }
            
            // swaps parent with smallest child
            int temp = data[pos];
            data[pos] = data[smallest];
            data[smallest] = temp;
            
            // move down to the swapped position
            pos = smallest;
        }
    }
};

#endif