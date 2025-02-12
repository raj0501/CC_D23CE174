#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_TOKEN_LEN 100
typedef struct {
    char type[MAX_TOKEN_LEN];
    char value[MAX_TOKEN_LEN];
} Token;
char sourceCode[10000];
Token tokens[1000];
char lexicalErrors[100][MAX_TOKEN_LEN];
char symbolTable[100][MAX_TOKEN_LEN];
int tokenCount = 0, errorCount = 0, symbolCount = 0;
void readInputFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }
    fread(sourceCode, sizeof(char), 10000, file);
    fclose(file);
}
void removeCommentsAndWhitespace() {
    char temp[10000];
    int j = 0;
    for (int i = 0; sourceCode[i] != '\0'; i++) {
        if (sourceCode[i] == '/' && sourceCode[i + 1] == '/') {
            i += 2;
            while (sourceCode[i] != '\n' && sourceCode[i] != '\0') i++;
        } else if (sourceCode[i] == '/' && sourceCode[i + 1] == '*') {
            i += 2;
            while (sourceCode[i] != '\0' && !(sourceCode[i] == '*' && sourceCode[i + 1] == '/')) i++;
            if (sourceCode[i] != '\0') i++; // Skip the closing '/'
        } else if (!isspace(sourceCode[i])) {
            temp[j++] = sourceCode[i];
        }
    }
    temp[j] = '\0';
    strcpy(sourceCode, temp);
}
int isKeyword(const char *word) {
    const char *keywords[] = {"int", "char", "void", "struct", "return", "long", "float"};
    for (int i = 0; i < 7; i++) {
        if (strcmp(word, keywords[i]) == 0) return 1;
    }
    return 0;
}
void addSymbol(const char *identifier) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i], identifier) == 0) return;
    }
    strcpy(symbolTable[symbolCount++], identifier);
}
void addToken(const char *type, const char *value) {
    strcpy(tokens[tokenCount].type, type);
    strcpy(tokens[tokenCount].value, value);
    tokenCount++;
}
void addError(const char *error) {
    strcpy(lexicalErrors[errorCount++], error);
}
void tokenize() {
    char word[MAX_TOKEN_LEN];
    int index;
    for (int i = 0; sourceCode[i] != '\0'; i++) {
        if (isspace(sourceCode[i])) continue;
        if (isalpha(sourceCode[i]) || sourceCode[i] == '_') {
            index = 0;
            while (isalnum(sourceCode[i]) || sourceCode[i] == '_') {
                word[index++] = sourceCode[i++];
            }
            word[index] = '\0'; i--;
            if (isKeyword(word)) {
                addToken("KEYWORD", word);
            } else {
                addToken("IDENTIFIER", word);
                addSymbol(word);
            }
        } else if (isdigit(sourceCode[i])) {
            index = 0;
            while (isdigit(sourceCode[i])) {
                word[index++] = sourceCode[i++];
            }
            word[index] = '\0'; i--;
            addToken("CONSTANT", word);
        } else if (sourceCode[i] == '"' || sourceCode[i] == '\'') {
            char quote = sourceCode[i];
            index = 0;
            word[index++] = sourceCode[i++];
            while (sourceCode[i] != quote && sourceCode[i] != '\0') {
                word[index++] = sourceCode[i++];
            }
            if (sourceCode[i] == quote) {
                word[index++] = sourceCode[i];
            }
            word[index] = '\0';
            if (sourceCode[i] == '\0') {
                addError("Unterminated string");
            } else {
                addToken("STRING", word);
            }
        } else if (strchr("{}()[],;", sourceCode[i])) {
            word[0] = sourceCode[i];
            word[1] = '\0';
            addToken("PUNCTUATION", word);
        } else if (strchr("+-*/=<>!", sourceCode[i])) {
            word[0] = sourceCode[i];
            word[1] = '\0';
            addToken("OPERATOR", word);
        } else {
            word[0] = sourceCode[i];
            word[1] = '\0';
            addError(word);
        }
    }
}
void generateOutput() {
    printf("TOKENS\n");
    for (int i = 0; i < tokenCount; i++) {
        printf("%s: %s\n", tokens[i].type, tokens[i].value);
    }
    printf("\nLEXICAL ERRORS\n");
    for (int i = 0; i < errorCount; i++) {
        printf("%s\n", lexicalErrors[i]);
    }
    printf("\nSYMBOL TABLE ENTRIES\n");
    for (int i = 0; i < symbolCount; i++) {
        printf("%d) %s\n", i + 1, symbolTable[i]);
    }
}
int main() {
    const char *filename = "input.c";
    readInputFile(filename);
    removeCommentsAndWhitespace();
    tokenize();
    generateOutput();
    return 0;
}











