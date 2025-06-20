CPP=g++

SRCDIR=src/
OBJDIR=obj/
IDIR=include/

CFLAGS=-I$(IDIR) 
FLAGS=-std=c++17 -Wall -Wextra -pthread

_SRC=main.cpp delay_op.cpp inventory.cpp processor.cpp
_OBJ=$(_SRC:.cpp=.o)
TARGET=lsc

OBJ=$(patsubst %, $(OBJDIR)%, $(_OBJ))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CPP) $(FLAGS) -o $@ $^ $(CFLAGS)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	$(CPP) $(FLAGS) -o $@ -c $< $(CFLAGS)

clean:
	$(RM) $(OBJ) $(TARGET)

.PHONY: all clean
