CC = g++
CPPFLAGS = -Wall -Wextra -g -std=c++20
CFLAGS =
LDFLAGS = 
LDLIBS =

TARGET = main
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
DEP = $(SRC:.cpp=.d)

all: $(OBJ)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS) $(LDLIBS)

-include $(DEP)

.PHONY: clean

clean:
	rm -f $(OBJ) $(DEP) $(TARGET)
