
all: run clean

build: monte_carlo.c
	gcc monte_carlo.c -lpthread -o monte_carlo.out

run: build
	time ./monte_carlo.out

clean:
	rm monte_carlo.out
