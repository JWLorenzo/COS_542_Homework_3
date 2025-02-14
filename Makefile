
all: run clean

all_alt: run_alt clean

build: monte_carlo.c
	gcc monte_carlo.c -lpthread -o monte_carlo.out

run: build
	time ./monte_carlo.out 

run_alt: build
	time ./montecarlo.out -alt

clean:
	rm monte_carlo.out
