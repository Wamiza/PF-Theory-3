#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validateEmail(char *email) {
    if (email == NULL || strlen(email) == 0) {
        return 0; 
    }

    int atCount = 0; 
    char *atPosition = NULL;

    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') {
            atCount++;
            if (atCount == 1) {
                atPosition = &email[i];
            }
        }
    }

    if (atCount != 1) {
        return 0;
    }

    if (atPosition != NULL) {
        char *dotPosition = strchr(atPosition, '.');
        if (dotPosition == NULL) {
            return 0; 
        }
    }

    return 1; 
}

int main() {
    char *email;
    size_t bufferSize = 100;

    email = (char *)malloc(bufferSize * sizeof(char));
    if (email == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter an email address: ");
    if (fgets(email, bufferSize, stdin) == NULL) {
        printf("Error reading input\n");
        free(email);
        return 1;
    }

    size_t len = strlen(email);
    if (len > 0 && email[len - 1] == '\n') {
        email[len - 1] = '\0';
    }

    if (validateEmail(email)) {
        printf("Valid Email\n");
    } else {
        printf("Invalid Email\n");
    }

    free(email);

    return 0;
}
