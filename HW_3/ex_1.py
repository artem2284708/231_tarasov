#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define INITIAL_BUFFER_SIZE 1024

void replace_all(const char *pattern, const char *text, const char *replacement) {
    regex_t regex;
    regmatch_t match;

   
    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        fprintf(stderr, "Ошибка компиляции регулярного выражения\n");
        return;
    }

    size_t buffer_size = INITIAL_BUFFER_SIZE;
    char *result = malloc(buffer_size);
    if (!result) {
        perror("malloc");
        regfree(&regex);
        return;
    }

    result[0] = '\0';
    size_t result_len = 0;

    const char *p = text;

    while (regexec(&regex, p, 1, &match, 0) == 0) {
       
        size_t prefix_len = match.rm_so;

       
        while (result_len + prefix_len + strlen(replacement) + 1 > buffer_size) {
            buffer_size *= 2;
            result = realloc(result, buffer_size);
            if (!result) {
                perror("realloc");
                regfree(&regex);
                return;
            }
        }

        
        strncat(result, p, prefix_len);
        result_len += prefix_len;

      
        strcat(result, replacement);
        result_len += strlen(replacement);

        
        p += match.rm_eo;
    }

 
    strcat(result, p);

   
    printf("Результат: %s\n", result);

   
    free(result);
    regfree(&regex);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Использование: %s <regexp> <text> <replacement>\n", argv[0]);
        return 1;
    }

    replace_all(argv[1], argv[2], argv[3]);
    return 0;
}