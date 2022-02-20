#include <los/device.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHILD_STIRNG_LEN 256

void display_children(const char *path, int indent) {
    // Get children
    isize len = list_device_children(path, NULL, 0, 0);
    if (len < 0) {
        fprintf(stderr, "Error while getting device children: %s\n",
                strerror(len));
        exit(1);
    } else if (len == 0)
        return;

    char **children = (char **)malloc(len * sizeof(char *));
    for (int i = 0; i < len; i++)
        children[i] = malloc(CHILD_STIRNG_LEN * sizeof(char));

    isize new_len = list_device_children(path, children, len, CHILD_STIRNG_LEN);
    if (new_len < 0) {
        fprintf(stderr, "Error while getting device children: %s\n",
                strerror(len));
        exit(1);
    } else if (new_len < len) {
        len = new_len;
    }

    // Display children
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < indent; j++)
            printf("    ");

        printf(" - %s\n", children[i]);

        char *new_path = (char *)malloc(
            (strlen(path) + strlen(children[i]) + 2) * sizeof(char));

        strcpy(new_path, path);
        strcat(new_path, "/");
        strcat(new_path, children[i]);

        display_children(new_path, indent + 1);
    }
}

int main() { display_children("", 0); }