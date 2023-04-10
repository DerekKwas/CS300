//============================================================================
// Name        : Project2.cpp
// Author      : Derek KWasniewski
// Version     : 1.0
// Description : Software for ABC University (ABCU) to organize course 
//                   information so advisors can help students.
//============================================================================

#include <iostream>
#include <time.h>

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
    Node* removeNode(Node* node, string courseNum);

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

void BinarySearchTree::InOrder() {
    this->inOrder(root);
}

/**
 * Insert a course
 */
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

/**
 * Remove a course
 */
void BinarySearchTree::Remove(string courseNum) {
    // remove node root courseNum
    this->removeNode(root, courseNum);
}

Node* BinarySearchTree::removeNode(Node* node, string courseNum) {
     // if this node is null then return (avoid crashing)
    if (node == nullptr) {
        return node;
    }

    // Recurse down left subtree
    if (courseNum < node->course.courseNum) {
        node->left = removeNode(node->left, courseNum);
    }
    // Recurse down right subtree
    else if (courseNum > node->course.courseNum) {
        node->right = removeNode(node->right, courseNum);
    }
    // ELSE correct node found
    else {
        // no children so this is a leaf node
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        }
        // one child to the left
        else if (node->left != nullptr && node->right == nullptr) {
            Node* temp = node;
            node = node->left;
            delete temp;
        }
        // one child to the right
        else if (node->right != nullptr && node->left == nullptr) {
            Node* temp = node;
            node = node->right;
            delete temp;
        }
        // two children
        else {
            Node* temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            node->course = temp->course;
            node->right = removeNode(node->right, temp->course.courseNum);
        }
    }
    return node;
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
    //output courseNum, title, prerequisites
    // FIXME: Output course data for prerequisites
    cout << node->course.courseNum << ": " << node->course.title << endl;
    //InOder right
    inOrder(node->right);
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

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all courses
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course course;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Courses" << endl;
        cout << "  2. Display All Courses" << endl;
        cout << "  3. Find Course" << endl;
        cout << "  4. Remove Course" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            
            // Initialize a timer variable before loading bids
            ticks = clock();

            // FIXME: Complete the method call to load the courses

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

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}
