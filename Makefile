COMP = g++
CFLAGS = -Wall
TARG = seascape
SRCS = interpreter.cpp schemas.h datautils.h datautils.cpp

all: $(TARG) run
$(TARG): $(SRCS)
	$(COMP) $(CFLAGS) -o $(TARG) $(SRCS) -l sqlite3
run:
	./$(TARG)

clean:
	rm -f $(TARG)