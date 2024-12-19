#include <stdio.h>
#include <string.h>
int main() {
    char pattern[100];
    int i = 0;
    printf("Enter a string: ");
    scanf("%s", pattern);

    while (pattern[i] == 'a') {
        i++;
    }
    if (pattern[i] == 'b' && pattern[i + 1] == 'b' && pattern[i + 2] == '\0') {
        printf("Valid String\n");
    } else {
        printf("Invalid String\n");
    }

    return 0;
}

