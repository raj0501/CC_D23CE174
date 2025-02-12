#include <stdio.h>
#include <string.h>

#define MAX_STATES 100
#define MAX_SYMBOLS 100

int transitions[MAX_STATES][MAX_SYMBOLS];
int accepting_states[MAX_STATES];

int main() {
    int num_states, num_symbols;
    char symbols[MAX_SYMBOLS];
    int accepting_states[100];
    int initial_state, num_accepting_states;
    char input_string[100];

    // Input number of states and symbols
    printf("Enter number of states: ");
    scanf("%d", &num_states);

    printf("Enter number of input symbols: ");
    scanf("%d", &num_symbols);

    printf("Enter input symbols (no spaces): ");
    scanf("%s", symbols);

    // Input initial state
    printf("Enter initial state: ");
    scanf("%d", &initial_state);

    // Input accepting states
    printf("Enter number of accepting states: ");
    scanf("%d", &num_accepting_states);

    printf("Enter accepting states: ");
    for (int i = 0; i < num_accepting_states; i++) {
        scanf("%d", &accepting_states[i]);
    }

    // Initialize transitions
    for (int i = 0; i < MAX_STATES; i++) {
        for (int j = 0; j < MAX_SYMBOLS; j++) {
            transitions[i][j] = -1; // -1 indicates no transition
        }
    }

    // Input transition table
    printf("Enter transitions in format (from_state symbol to_state), type -1 to stop:\n");
    while (1) {
        int from_state, to_state;
        char symbol;
        scanf("%d", &from_state);
        if (from_state == -1) {
            break;
        }
        scanf(" %c %d", &symbol, &to_state);

        // Map symbol to its index
        int symbol_index = strchr(symbols, symbol) - symbols;
        if (symbol_index >= 0 && symbol_index < num_symbols) {
            transitions[from_state][symbol_index] = to_state;
        } else {
            printf("Invalid symbol: %c\n", symbol);
        }
    }

    // Input string to validate
    printf("Enter input string: ");
    scanf("%s", input_string);

    // Validate string
    int current_state = initial_state;
    for (int i = 0; input_string[i] != '\0'; i++) {
        char symbol = input_string[i];
        int symbol_index = strchr(symbols, symbol) - symbols;

        if (symbol_index < 0 || symbol_index >= num_symbols) {
            printf("Invalid string\n");
            return 0;
        }

        current_state = transitions[current_state][symbol_index];
        if (current_state == -1) {
            printf("Invalid string\n");
            return 0;
        }
    }

    // Check if current state is accepting
    for (int i = 0; i < num_accepting_states; i++) {
        if (current_state == accepting_states[i]) {
            printf("Valid string\n");
            return 0;
        }
    }

    printf("Invalid string\n");
    return 0;
}

