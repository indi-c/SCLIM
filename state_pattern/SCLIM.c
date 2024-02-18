// Simple CLI Menus
#include "SCLIM.h"
#include "terminalFuncs.h"
#include <stdio.h> 
#include <unistd.h>

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

// function called entering state
typedef void (*p_onEnter)(void);
// function called exiting state
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
    int numTransitions; // number of transitions
};

struct Transition
{
    char input; // input to transition on
    InterfaceState *nextState; // state to transition to
};

static void clearInputBuffer()
{
    // clears input buffer
    char c;
    while (read(STDIN_FILENO, &c, 1) == 1)
        ;
}

static char *getInput()
{
    // reads one byte from input buffer and returns as char
    char *input = malloc(1);
    if (input == NULL)
    {
        printf("Error allocating memory for input\n");
        exit(1);
    }
    read(STDIN_FILENO, input, 1);

    clearInputBuffer();

    // return pointer to input
    return input;
}

static void handleInput(char *input, Interface *interface)
{
    for (int i = 0; i < interface->state->numTransitions; i++)
    {
        if (input == interface->state->transitions[i].input)
        {
            interface->state->onExit();
            interface->state = interface->state->transitions[i].nextState;
            interface->state->onEnter();
            break;
        }
    }
}

static void loop(struct interface *interface)
{
    // loop to handle input and output
    // calling the appropriate functions

    // declare variable for input
    // assign return value of input function to variable
    // call handleInput function with variable and interface as arguments
    
}

p_getInput getInput = getInput;
p_handleInput handleInput = handleInput;
p_loop loop = loop;

// takes input and state and returns a transition Struct
Transition *createTransition(char input, InterfaceState *nextState)
{
    // allocate memory for transition
    Transition *transition = malloc(sizeof(struct transition));
    // assign input and nextState to transition
    transition->input = input;
    transition->nextState = nextState;
    // return pointer to transition
    return transition;
}

// takes stateName, onEnter, onExit, transitions and returns a InterfaceState Struct
InterfaceState *createState(char *stateName, p_onEnter onEnter, p_onExit onExit, Transition *transitions, int numTransitions)
{
    // allocate memory for state
    InterfaceState *state = malloc(sizeof(InterfaceState));
    // assign stateName, onEnter, onExit, transitions to state
    state->stateName = stateName;
    state->onEnter = onEnter;
    state->onExit = onExit;
    state->transitions = transitions;
    state->numTransitions = numTransitions;
    
    // return pointer to state
    return state;
}

// dynamically adds a transition to a state
void addTransition(InterfaceState *state, Transition *transition)
{
    state->transitions = realloc(state->transitions, (state->numTransitions + 1) * sizeof(Transition));
    if (state->transitions == NULL)
    {
        printf("Error allocating memory for transition\n");
        exit(1);
    }

    state->transitions[state->numTransitions] = *transition;
    state->numTransitions++;
}

Interface *createInterface(InterfaceState *state)
{
    Interface *interface = malloc(sizeof(Interface));
    interface->state = state;
    interface->takeInput = getInput;
    interface->handleInput = handleInput;
    interface->loop = loop;
    return interface;
}