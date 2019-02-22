#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

/* @Author Student Name: Muhammed Furkan KAMER 
Student ID : 150160013 
Date: 13.12.2018 */ 




/*
Struct for implementing stack and queue with singly linked list
*/
struct Node {
    Node* next;
    unsigned long long int x;
};
/*
Struct of queue and member functions

*/
struct queueAnt {
    Node* first;
    Node* last;
    void create();
    void close();
    void enqueue(unsigned long long int);
    bool isempty();
    unsigned long long int dequeue();
    void print();
};

/*
Checks if queue is empty
*/
bool queueAnt::isempty()
{

    return first == NULL;
}
/*
closes queue after the work done

*/
void queueAnt::close()
{
    Node* iter;
    while (first) {
        iter = first;
        first = first->next;
        delete iter;
    }
}

/*
Struct of stack and member functions

*/
struct stackAnt {
    Node* head;
    void create();
    void close();
    void push(unsigned long long int);
    unsigned long long int pop();
    bool isempty();
};
/*
member function for creating queue

*/
void queueAnt::create()
{
    first = NULL;
    last = NULL;
}
/*
member function for adding data to queue

*/
void queueAnt::enqueue(unsigned long long int nd)
{
    Node* freshnode = new Node;
    freshnode->x = nd;
    freshnode->next = NULL;
    if (isempty()) {
        last = freshnode;
        first = last;
    } else {
        last->next = freshnode;
        last = freshnode;
    }
}
/*
member function for printing queue

*/
void queueAnt::print()
{
    Node* iter;
    iter = first;
    while (iter != NULL) {

        std::cout << iter->x << " ";
        iter = iter->next;
    }
    std::cout << "\n";
    delete iter;
}

/*
struct for queues and stack and member functions

*/

struct Ants {
    queueAnt ants;
    queueAnt holeDepths;
    stackAnt hole;
    void ReadFile(char*);
    void ShowContents(bool);
    void CrossRoad();
};

/*
function for reading file and store the variables in queue
@param file is the name of input file
function first calls create function to create ants and holeDepths queues
function reads first line and adds sequence to ants queue 
after that reads second line and adds values to holeDepths queue
*/
void Ants::ReadFile(char* file)
{
    std::ifstream input(file);
    if(!input)
    {
    	return;
	}
    ants.create();
    holeDepths.create();
    int count = 0;
    for (std::string line; getline(input, line);) {
        if (count == 0) {
            std::istringstream line2(line);
            unsigned long long int antnumber;
            line2 >> antnumber;

            for (unsigned long long int i = 1; i <= antnumber; i++) {
                ants.enqueue(i);
            }

        } else {
            std::istringstream line2(line);
            unsigned long long int depth;
            while (line2 >> depth) {

                holeDepths.enqueue(depth);
            }
        }
        count++;
    }
}

/*
member function for getting first in data of queue 

*/
unsigned long long int queueAnt::dequeue()
{
    Node* top_node;
    unsigned long long int temp;
    top_node = first;
    first = first->next;
    temp = top_node->x;
    delete top_node;
    return temp;
}
/*
function for creating an empty stack

*/

void stackAnt::create()
{
    head = NULL;
}

/*
function that closes stack after the work done

*/

void stackAnt::close()
{
    Node* iter;
    while (head) {
        iter = head;
        head = head->next;
        delete iter;
    }
}
/*
function for adding on the top of stack
@param nd is the newly got data from call
*/
void stackAnt::push(unsigned long long int nd)
{
    Node* freshnode = new Node;
    freshnode->x = nd;
    freshnode->next = head;
    head = freshnode;
}
/*
function for getting data from top of the stack

*/
unsigned long long int stackAnt::pop()
{
    Node* top_node;
    unsigned long long int temp;
    top_node = head;
    head = head->next;
    temp = top_node->x;
    delete top_node;
    return temp;
}

/*
function that checks stack if it is empty

*/

bool stackAnt::isempty()
{
    return head == NULL;
}

/*
shows ant sequence after the work is done
@param t is the truth value
*/

void Ants::ShowContents(bool t)
{
    if (t == 1) {

        ants.print();
    } else {

        holeDepths.print();
    }
}
/*
function for making all ants to croos the road
first takes from first in data from ant queue and adds it top ant stack from top
after remaining ants passes road and function calls pop function and pops values
from stack and adds the values again to queue
*/
void Ants::CrossRoad()
{
    hole.create();
    while (holeDepths.first != NULL) {
        unsigned long long int depth = holeDepths.dequeue();
        for (unsigned long long int i = 0; i < depth; i++) {
            hole.push(ants.dequeue());
        }
        while (hole.head != NULL) {
            ants.enqueue(hole.pop());
        }
    }
}

int main(int argc, char** argv)
{
    Ants a;
    a.ReadFile(argv[1]); //store the number of ants and depths of holes
    std::cout << "The initial Ant sequence is: ";
    a.ShowContents(1); //list ant sequence (initially: 1, 2, ..., N)
    std::cout << "The depth of holes are: ";
    a.ShowContents(0); //list depth of holes
    a.CrossRoad();
    std::cout << "The final Ant sequence is: ";
    a.ShowContents(1);
    a.ants.close();
    a.hole.close();
    a.hole.close();
    return 0;
}
