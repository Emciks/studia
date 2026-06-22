#include <iostream>
#include <cstdio>
#include <string.h>

void removeNewLine(char *text) {
    while (*text) {
        if (*text == '\n') {
            *text = '\0';
            break;
        }
        text++;
    }
}

int textLen(const char *text) {
    int len = 0;
    while (*(text + len)){
        len++;
    }
    return len;
}

void toLower(char *text) {
    while (*text) {
        if ('A' <= *text && *text <= 'Z') {
            *text += ('a' - 'A');
        }
        text++;
    }
}

void toUpper(char *text) {
    while (*text) {
        if ('a' <= *text && *text <= 'z') {
            *text -= ('a' - 'A');
        }
        text++;
    }
}


int main(int argc, char* argv[]) {

    for(int i=1; i<argc-1; i++) {
        strcat(argv[1]," ");
        strcat(argv[1],argv[i+1]);

    }
    printf("text: %s\n",argv[1]);

    removeNewLine(argv[1]);

    printf("Text length is: %i\n", textLen(argv[1]));
    toLower(argv[1]);
    printf("Lowercase text is: %s\n", argv[1]);
    toUpper(argv[1]);
    printf("Uppercase text is: %s\n", argv[1]);
}