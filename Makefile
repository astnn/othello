
BIN = othello
SRC = main.cpp othello.cpp
OBJ = $(SRC:.cpp=.o)
HDR = othello.h

CXX = g++
CFLAGS = -Wall

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) -o $@ $(OBJ) $(CFLAGS)

%.o: %.c $(HDR)
	$(CXX) -c $< $(CFLAGS)

clean:
	rm -rvf *.o $(BIN)
