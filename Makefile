COMP = g++
CFLAGS = -Wall -fsanitize=address -Og -g 
TARG = seascape
SRCS = interpreter.cpp schemas.h datautils.h datautils.cpp

all: $(TARG) run
$(TARG): $(SRCS)
	$(COMP) -o $(TARG) $(SRCS) -l sqlite3
run:
	./$(TARG)

clean:
	rm -f $(TARG)