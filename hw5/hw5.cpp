#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

/* @Author Student Name: Muhammed Furkan Kamer 
Student ID : 150160013 
Date: 24.12.2018
*/

/*Struct for tree nodes
*/

struct Node {
    Node* left;
    Node* right;
    int x;
};

struct stack { //Struct for path stack
    int* array;
    int size;
    int top;
    void create(stack*, int);
    int flag;
    int flag2;
};

void stack::create(stack* s, int size1) //stack create function to create empty stack
{
    s->array = NULL;
    s->size = size1;
    s->top = 0;
    s->flag = 0;
    s->flag2 = 0;
}

void close(stack* s) // stack close function
{
    delete s;
}

bool isempty(stack* s1) //function to check if the stack is empty
{
    return s1->top == 0;
}

int pop(stack* s) //function to pop a value from top of the stack
{
    if (s->array == NULL) {
        return -1;
    } else {
        if (s->top <= s->size / 4) {
            int* array2 = new int[2 * s->size];
            for (int i = 0; i < s->top; i++) {
                array2[i] = s->array[i];
            }

            delete s->array;
            s->array = array2;
            s->size /= 2;
        }
        return s->array[--s->top];
    }
}

void push(stack* s, int a) //function to push a value to top of the stack

{
    if (s->array == NULL) {
        s->array = new int[s->size];
    }
    if (s->top >= s->size) {
        int* array2 = new int[2 * s->size];
        for (int i = 0; i < s->size; i++) {
            array2[i] = s->array[i];
        }

        delete s->array;
        s->array = array2;
        s->size *= 2;
    }

    s->array[s->top++] = a;
}

void print(stack* s) //function to print stack
{

    for (int i = 0; i < s->top; i++) {
        std::cout << s->array[i] << " ";
    }
    std::cout << "\n";
}

void findpaths(Node* root, int array[], int y, int sum, stack* s1, stack* s2, int summ, Node* root2) //function to find paths
{
    if (root == NULL) // to check if tree is empty
        return;
    array[y++] = root->x; // adds tree value on node to array for path check
    summ = 0;
    int flag1 = 0; //values for checking if the a path already found in the subtree
    int flag2 = 0;
    if (isempty(s1)) {
        flag1 = 1;
    }
    if (isempty(s2)) {
        flag2 = 1;
    }
    if (root->left == NULL && root->right == NULL) { //it checks if the node is a leaf

        for (int i = 0; i < y; i++) {

            if (summ != sum && array[1] == root2->left->x && flag1 == 1) { // for pushing first found path from left subtree
                summ += array[i];
                push(s1, array[i]);
            } else if (summ != sum && array[1] == root2->right->x && flag2 == 1) { // for pushing first found path from right subtree
                summ += array[i];
                push(s2, array[i]);
            }
        }

        if (summ == sum) {
            if (array[1] == root2->left->x && s1->flag != 1) { // it checks if a Path Found on left subtree
                std::cout << "Path Found: ";
                print(s1);
                s1->flag = 1;
            } else if (array[1] == root2->right->x && s2->flag != 1) { //it checks if a path found on right subtree
                if (s1->flag == 0) { //it checks if a path not found in left subtree
                    std::cout << "No Path Found \n";
                    s2->flag2 = 1;
                }
                std::cout << "Path Found: ";
                print(s2);
                s2->flag = 1;
            }

        } else {
            while (!isempty(s1)) { //it empties stack for left subtree path
                pop(s1);
            }
            while (!isempty(s2)) { // it empties stack for right subtree path
                pop(s2);
            }
        }

    }

    else {
        if (root->left)
            findpaths(root->left, array, y, sum, s1, s2, summ, root2); //recursive call for traverse from root to leaf
        if (root->right)
            findpaths(root->right, array, y, sum, s1, s2, summ, root2); //recursive call for traverse from root to leaf
    }
}

Node* TreeBuild(int array[],
    int m, int k) //function to build a tree
{

    if (m >= k) {
    return NULL;
}
        Node* temp = new Node;
        temp->x = array[m];
        temp->left = temp->right = NULL;
        Node*root= temp;
        root->left = TreeBuild(array, 2 * m + 1, k); //recursive calls for tree building
        root->right = TreeBuild(array, 2 * m + 2, k);
    
    return root;
}


int leftmost(Node *root)
{
	Node*temp;
	temp=root;
	while(temp->left != NULL)
	{
	     temp=temp->left;
	}
	return temp->x;
	
}







void read_fromfile(char* file) //function for reading values from file, stores them in an array
{
    std::ifstream input(file);
    if (!input) {
        return;
    }
    int count = 0;
    int i = 0;
    int size = 2;
    int value;
    int* array = new int[size];
    stack* s1 = new stack;
    stack* s2 = new stack;
    struct stack creat;
    creat.create(s1, 2);
    creat.create(s2, 2);
    for (std::string line; getline(input, line);) { // loop for reading file and store values
        if (count == 0) {
            std::istringstream line2(line);
            int treenumber;
            while (line2 >> treenumber) {
                if (i >= size) {
                    size *= 2;
                    int* array2 = new int[size];
                    for (int t = 0; t < size; t++) {
                        array2[t] = array[t]; // array to store values
                    }
                    delete array;
                    array = array2;
                }
                array[i] = treenumber;
                i++;
            }
        } else {
            std::istringstream line2(line);

            line2 >> value; //value for sum of path
        }
        count++;
    }
    int* array3 = new int[i];
    for (int t = 0; t < i; t++) {

        array3[t] = array[t];
    }

    delete array;
    array = array3;
    if (i == 1 || array[0] == value) { // it checks from the beginning if root is equals to required value
        if (array[0] == value) {
            std::cout << "Path Found: " << array[0] << "\n";
            std::cout << "Path Found: " << array[0] << "\n";

        } else {
            std::cout << "No Path Found \n";
            std::cout << "No Path Found \n";
        }
    } else {

        Node* root = NULL;

        root = TreeBuild(array, 0, i);
        findpaths(root, array, 0, value, s1, s2, 0, root);

        if (s1->flag == 0 && s2->flag2 == 0) { // it checks if a path not found
            std::cout << "No Path Found \n";
        }

        if (s2->flag == 0) {
            std::cout << "No Path Found \n"; // it checks if a path not found
        }
        std::cout<<leftmost(root);
    }
    
    close(s1); //closes stack for left subtree
    close(s2); //closes stack for right subtree
    delete array; // empties dynamic array
}





int main(int argc, char** argv)
{
    read_fromfile(argv[1]);
    
    return 0;
}
