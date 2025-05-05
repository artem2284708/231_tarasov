#define _GNU_SOURCE    
#include <stdlib.h>             
#include <dlfcn.h>              

void bill(const char *msg) {

    void (*orig_bill)(const char *) = dlsym(RTLD_NEXT, "bill");
    printf("bill is called (interposed)\n"); 
    orig_bill(msg);                          
}

void sam(double x) {
    void (*orig_sam)(double) = dlsym(RTLD_NEXT, "sam");
    printf("sam is called (interposed)\n");
    orig_sam(x);
}
