// Simple CLI Menus
#include "SCLIM.h"
#include <stdio.h> 

struct interface
{
};

struct input
{
};

struct inputState
{
};
struct inputHandler
{
    struct inputState *state;
};

static struct input *input_create()
{
    // allocate memory for input
    struct input *input = malloc(sizeof(struct input));
    // take input

    // return pointer to input
    return input;
}

static void handleInput(struct input *input, struct interface *interface)
{
    // handle input
    // call appropriate functions
}

static void loop(struct interface *interface)
{
    // loop to handle input and output
    // calling the appropriate functions

    // declare variable for input
    // assign return value of input function to variable
    // call handleInput function with variable and interface as arguments
    
}