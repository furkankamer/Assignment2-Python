#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

/*Author
 * 
 * Student Name: Muhammed Furkan KAMER
 * Student ID: 150160013
 * Date: 03.12.2018 */

/*
struct which implements stack
array takes card values
size determines array size
top is stacks top value
*/
struct stack {
    int* array;
    int size;
    int top;
    void create(stack*, int);
};
/*
@param s is a pointer in type of stack struct
@param size1 is size value of array which keeps card values
function is used for initialization of stack
*/
void stack::create(stack* s, int size1)
{
    s->array = NULL;
    s->size = size1;
    s->top = 0;
}
/*
@param s is a pointer in type of stack struct
function act pop function of stack which takes value from top of the stack
*/
int pop(stack* s)
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
/*
@param s is a pointer in type of stack struct
@param a is value which will be pushed by function to stack s
function act push function of stack which add value to top of the stack
*/
void push(stack* s, int a)

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
/*
@param s is a pointer in type of stack struct
function prints card value of stack from bottom to top
*/
void print(stack* s)
{
    std::cout << "[";
    for (int i = 0; i < s->top; i++) {
        std::cout << s->array[i] << " ";
    }
    std::cout << "]\n";
}
/*
@param s1 is a pointer in type of stack struct which popped value from s2 to pushed  
@param s2 is a pointer in type of stack struct which a value will be pushed from
@param s3 is a pointer in type of stack struct which thrown away cards will be pushed
function is uses if statements for the exchange cards or thrown away 
*/
void exchange(stack* s1, stack* s2, stack* b)
{

    int taken;
    int topmost;

    taken = pop(s1);
    topmost = pop(s2);
    if (taken > topmost) {
        push(s2, topmost);
        push(s2, taken);

    }

    else {
        push(s2, topmost);
        push(b, taken);
    }
}

/*
function checks whether player who gives card to other is have enough card and
according to result calls exchange function to perform it
@param s1 is stack of the player who will gives
@param s2 is stack of the player who will takes
@param b is bin stack
@param amountt is card value on the top of the deck

*/


void check(stack* s1, stack* s2, stack* b, int amountt)
{
    if (abs(amountt) > s1->top) {
        int topp = s1->top;
        for (int i = 0; i < topp; i++) {
            exchange(s1, s2, b);
        }
    }

    else {
        for (int i = 0; i < abs(amountt); i++) {
            exchange(s1, s2, b);
        }
    }
}

int main(int argc, char* argv[])
{

    (void)argc;
    std::ifstream input(argv[1]);
    if (!input) {

        return -1;
    }

    stack* gamer1 = new stack;
    stack* gamer2 = new stack;
    stack* deck = new stack;
    stack* bin = new stack;
    struct stack creat;
    int count = 1;
    int deck_count = 0;
    int gamer1_count = 0;
    int gamer2_count = 0;

    for (std::string line; getline(input, line);) {

        if (count == 1) {
            std::istringstream some_stream(line);
            int size1, size2;
            some_stream >> size1 >> size2;
            creat.create(gamer1, size2);
            creat.create(gamer2, size2);
            creat.create(deck, size1);

        } else {

            std::istringstream some_stream(line);
            int value;
            some_stream >> value;
            if (deck_count != deck->size) {
                if (value != 0) {

                    push(deck, value);
                    deck_count++;
                }
            }

            else {

                if (gamer1_count != gamer1->size) {
                    push(gamer1, value);
                    gamer1_count++;
                }

                else {
                    if (gamer2_count != gamer2->size) {
                        push(gamer2, value);
                        gamer2_count++;
                    }
                }
            }
        }

        count++;
    }

    creat.create(bin, 1);
    int order = 0;
    int amount;
    /*
    Loop changes order between first player and second player, and with respect to
    card which is popped from deck, it checks several condition and calls exchange function
    and fills parameters with appropriate stacks
    
    */
    while (deck->top > 0 && gamer1->top>0 && gamer2->top>0) {
        if (gamer1->top == 0 || gamer2->top == 0) {
            break;
        }

        if (order % 2 == 0) {

            amount = pop(deck);
            if (amount < 0) {

                check(gamer1, gamer2, bin, amount);

            }

            else {

                check(gamer2, gamer1, bin, amount);
            }

        }

        else {
            amount = pop(deck);
            if (amount < 0) {

                check(gamer2, gamer1, bin, amount);

            } else {

                check(gamer1, gamer2, bin, amount);
            }
        }
        order++;
    }

    std::cout << bin->top;
    return 0;
}
