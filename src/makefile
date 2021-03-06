src = $(wildcard *.cpp)
targets = $(patsubst %.cpp, %, $(src))

CC =  g++
CFLAGS = -lpthread -m32 -Wall -g

all:$(targets)

$(targets):%:%.cpp
	 $(CC) $< -o $@ 

clean:
	-rm -rf $(targets)

do: 
	 ./$(targets)

.PHONY:clean all do
