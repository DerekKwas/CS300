//============================================================================
// Name        : Project2.cpp
// Author      : Derek KWasniewski
// Version     : 1.0
// Description : Software for ABC University (ABCU) to organize course 
//                   information so advisors can help students.
//============================================================================

#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Course {
    string courseNum; // unique identifier
    string title;
    vector<string> prereqs;
};

// Internal structure for tree node
struct Node {
    Course course;
    Node *left;
    Node *right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Course aCourse) :
            Node() {
        course = aCourse;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;
    void inOrder(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Course course);
    void Remove(string courseNum);
    Course Search(string courseNum);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // Root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // Recurse from root deleting every node
    delete root->left;
    delete root->right;
}

void BinarySearchTree::Insert(Course course) {
    Node* newNode = new Node;
    newNode->course = course;

    // if root equarl to null ptr
    if (root == nullptr) {
        // root is equal to new node course
        root = newNode;
        newNode->left = nullptr;
        newNode->right = nullptr;
    }
    else {
        // Create new node equal to root node
        Node* currNode = root;

        // Continue looping through tree until a proper spot has been found for the new node
        while (currNode != nullptr) {
            // LEFT branch
            if (newNode->course.courseNum < currNode->course.courseNum) {
                // IF no left node set it to the new node
                if (currNode->left == nullptr) {
                    currNode->left = newNode;
                    currNode = nullptr;
                }
                // Set currNode to the new left node
                else {
                    currNode = currNode->left;
                }
            }
            // RIGHT branch
            else {
                // IF no right node set it to the new node
                if (currNode->right == nullptr) {
                    currNode->right = newNode;
                    currNode = nullptr;
                }
                // Set currNode to the new right node
                else {
                    currNode = currNode->right;
                }
            }
            // Once a spot has been found for the new node, set its left & right nodes to nullptr as the newNode is a leaf node
            newNode->left = nullptr;
            newNode->right = nullptr;
        }
    }
}

void BinarySearchTree::InOrder() {
    this->inOrder(root);
}

/**
 * Search for a bid
 */
Course BinarySearchTree::Search(string courseNum) {
    // set current node equal to root
    Node* currNode = root;

    // keep looping downwards until bottom reached or matching courseNum found
    while (currNode != nullptr) {
        // if match found, return current course
        if (currNode->course.courseNum == courseNum) {
            return currNode->course;
        }
        // if courseNum is smaller than current node then traverse left
        else if (courseNum < currNode->course.courseNum) {
            currNode = currNode->left;
        }
        // else larger so traverse right
        else {
            currNode = currNode->right;
        }
    }
    // Course not found, return empty course
    Course course;
    return course;
}

void BinarySearchTree::inOrder(Node* node) {
    //if node is not equal to null ptr
    if (node == nullptr) {
        return;
    }

    //InOrder left
    inOrder(node->left);
    //output courseNum, title
    cout << node->course.courseNum << ": " << node->course.title << endl;
    //InOder right
    inOrder(node->right);
}

void loadCourses(string filePath, BinarySearchTree* bst) {
    // Create file stream object
    fstream fs;

    // Added file extenstion to filename
    filePath.append(".txt");

    // Open file with filePath
    fs.open(filePath, fstream::in);

    // If file doesn't exist, return
    if (!fs.is_open()) {
        cout << "ERROR: No file with that name in main directory!" << endl;
        return;
    }
    
    // POSSIBLE PROBLEM: Microsoft Text file encoding can cause a problem if it is UTF-8 BOM
    // FIX: Save text file as the same file but change the encoding to the normal UTF-8
    string line;
    while (getline(fs, line)) {
        
    }
    return;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param  course containing the course info
 */
void displayCourse(Course course) {
    // FIXME: Output course data for prerequisites
    cout << course.courseNum << ": " << course.title << endl;
    return;
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // FIXME: Create function to load file

    // Declare variable to hold user choice for key and choice for file path
    string searchNum;
    string filePath;

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all courses
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course course;

    int choice = 0;
    while (choice != 9) {
        cout << "Welcome To The Course Planner:" << endl;
        cout << "  1. Load Data Structure" << endl;
        cout << "  2. Print Course List" << endl;
        cout << "  3. Print Course" << endl;
        cout << "  9. Exit" << endl;
        cout << "What would you like to do? ";
        cin >> choice;

        switch (choice) {

            case 1:

                // Initialize a timer variable before loading bids
                ticks = clock();

                cout << "Enter file name (without .txt): ";
                cin >> filePath;
                loadCourses(filePath, bst);

                // Calculate elapsed time and display result
                ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                cout << "time: " << ticks << " clock ticks" << endl;
                cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
                break;

            case 2:
                bst->InOrder();
                break;

            case 3:
                ticks = clock();

                cout << "Please enter the ID of the course: ";
                cin >> searchNum;

                course = bst->Search(searchNum);

                ticks = clock() - ticks; // current clock ticks minus starting clock ticks

                if (!course.courseNum.empty()) {
                    displayCourse(course);
                }
                else {
                    cout << "Course number " << searchNum << " not found." << endl;
                }

                cout << "time: " << ticks << " clock ticks" << endl;
                cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

                break;
        }
    }
    cout << "Good bye." << endl;
    return 0;
}
