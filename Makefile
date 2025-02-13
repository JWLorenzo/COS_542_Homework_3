
all: run clean

build: monte_carlo.c
	gcc monte_carlo.c -lpthread -o monte_carlo

run: build
	./monte_carlo.exe

clean:
	rm monte_carlo
