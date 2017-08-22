# file Makefile
CC= g++-5.4
RM= rm -vf
CFLAGS= -std=c++14
CPPFLAGS= -static-libstdc++
SRCFILES= $(wildcard *.cpp)
OBJFILES= $(patsubst %.cpp, %.o, $(SRCFILES))
PROGFILES= $(patsubst %.cpp, %, $(SRCFILES))

.PHONY: clean all

%: %.cpp
	$(CC) $(CFLAGS) -c $< $(CPPFLAGS)

all: $(basename $(wildcard *.cpp))

main:
	$(CC) $(CFLAGS) -c main.cpp $(CPPFLAGS)

widget:
	$(CC) $(CFLAGS) -c widget.cpp $(CPPFLAGS)

run:
	$(CC) -o run $(CFLAGS) $(OBJFILES) $(CPPFLAGS)

clean:
	$(RM) $(OBJFILES) $(PROGFILES) run
