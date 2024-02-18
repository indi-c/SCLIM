// Simple CLI Menus
#include "SCLIM.h"
#include "terminalFuncs.h"
#include <stdio.h> 

// type definitions for structs
typedef struct Interface Interface;
typedef struct InterfaceState InterfaceState;
typedef struct Transition Transition;

// function pointers for Interface Struct

// reads one byte from input buffer and returns as char
typedef char *(*p_getInput)(void);
// iterates through state transitions and transitions to correct state
typedef void (*p_handleInput)(char *input, struct interface *interface);
// loops to handle input and output
typedef void (*p_loop)(struct interface *interface);

// function pointers for interfaceState Struct
typedef void (*p_onEnter)(void);
typedef void (*p_onExit)(void);

// definitions of structs

// stores current state and function pointers for input
// output is handled by the state
struct Interface
{
    InterfaceState *state;
    p_getInput takeInput;
    p_handleInput handleInput;
    p_loop loop;
};


struct InterfaceState
{
    p_onEnter onEnter; // function called entering state
    p_onExit onExit; // function called exiting state
    char *stateName; // for debug purposes
    Transition *transitions; // array of transitions
};

struct Transition
{
    char input; // input to transition on
    InterfaceState *nextState; // state to transition to
};

static char *getInput()
{
    // allocate memory for input
    char *input = malloc(sizeof(struct input));
    // take input

    // return pointer to input
    return input;
}

static void handleInput(char *input, struct interface *interface)
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