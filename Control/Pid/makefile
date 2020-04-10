CC=gcc
CFLAGS=-I.
DEPS = globals.h Pid.h
OBJ = example.o Pid.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pidExample: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
