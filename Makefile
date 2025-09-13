CC=g++
LD=$(CC)
CFLAGS =-std=c++23 -Wall -pedantic -g -fsanitize=address
SOURCE=src


.PHONY: run

all: main doxygen

main: $(SOURCE)/main.o $(SOURCE)/perceptron.o 
	$(LD) $(CFLAGS) -o $@ $^ 

%.o: $(SOURCE)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

doxygen:
	doxygen docs/Doxyfile


run:
	@./main $(ARGS)

clean:
	rm -rf src/*.o main docs/html docs/latex 
