CFLAGS = -std=c++11 -O3 -Wall

all: project

project: project.cpp
	g++ $(CFLAGS) project.cpp -o project -lm

clean:
	rm -f project
