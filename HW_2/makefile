CC = gcc-14
CFLAGS = -Wall -fPIC
LDLIBS = -lm


STATIC_LIB = libfoo.a 
SHARED_LIB = libbar.so
INTERPOSE_LIB = libinterpose_load.so


OBJS_STATIC = fred.o john.o
OBJS_SHARED = bill.o sam.o
OBJS_MAIN = program.o
OBJS_LINK = interpose_link.o
OBJS_LOAD = interpose_load.o

all: $(STATIC_LIB) $(SHARED_LIB) $(INTERPOSE_LIB) program

$(STATIC_LIB): $(OBJS_STATIC) 
	ar crs $@ $^  

$(SHARED_LIB): $(OBJS_SHARED)
	$(CC) -shared -o $@ $^ $(LDLIBS)

$(INTERPOSE_LIB): $(OBJS_LOAD)  
	$(CC) -shared -o $@ $^ -ldl



program: $(OBJS_MAIN) $(OBJS_LINK) $(STATIC_LIB)
	$(CC) -o $@ $^ -L. -lfoo -Wl,--wrap,fred -Wl,--wrap,john -L. -lbar $(LDLIBS)


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

run:
	LD_PRELOAD=./$(INTERPOSE_LIB) ./program

clean:
	rm -f *.o *.a *.so program
