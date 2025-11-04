//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

int buildEncodingTree(int nextFree) {
    MinHeap heap;

    // push leaf nodes index into heap
    for (int i = 0; i < nextFree; ++i) {
        heap.push(i, weightArr);
    }

    // combine until node remains
    while (heap.size > 1) {
        int left = heap.pop(weightArr);
        int right = heap.pop(weightArr);

        // create parent
        leftArr[nextFree] = left;
        rightArr[nextFree] = right;
        weightArr[nextFree] = weightArr[left] + weightArr[right];
        //node marker
        charArr[nextFree] = '*'; 

        // push new parent node
        heap.push(nextFree, weightArr);
        nextFree++;
    }

    // make last node the root
    int root = heap.pop(weightArr);
    cout << "built encoding tree \n";
    return root;
}


void generateCodes(int root, string codes[]) {
    //if no root node
    if (root == -1) 
    return;

    stack<pair<int, string>> st;
    st.push({root, ""});
    // while not empty stack
    while (!st.empty()) {
        auto [node, code] = st.top();
        st.pop();

        int left = leftArr[node];
        int right = rightArr[node];

        // if leaf node
        if (left == -1 && right == -1) {
            char ch = charArr[node];
            if (ch >= 'a' && ch <= 'z') {
                codes[ch - 'a'] = code;
            }
        } 
        else {
            //push right first so left node done first
            if (right != -1) st.push({right, code + "1"});
            if (left != -1) st.push({left, code + "0"});
        }
    }

    cout << "Generated binary codes successfully.\n";
}



// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}