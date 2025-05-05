#include <stdio.h>             


void __real_fred(int);
void __real_john(double);



void __wrap_fred(int arg) {
    printf("fred is called (interposed)\n"); 
    __real_fred(arg);                         
}

void __wrap_john(double arg) {
    printf("john is called (interposed)\n");
    __real_john(arg);
}
