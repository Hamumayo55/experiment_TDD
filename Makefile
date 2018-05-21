PROGRAM = test_code
OBJS    = calc.o

CC  = clang
C++ = clang++

CFLAGS   = -Wall -g 
C++FLAGS = -Wall -g
LDFLAGS  = -lcurses

.SUFFIXES: .c .cpp .o

$(PROGRAM): $(OBJS)
	$(C++) $(LDFLAGS) -o $(PROGRAM) $^

test: $(PROGRAM)
	./$(PROGRAM)

.c.o:
	$(CC) $(CFLAGS) -c $<
.cpp.o:
	$(C++) $(C++FLAGS) -c $<

.PHONY: clean
clean:
	$(RM) $(PROGRAM) $(OBJS)
