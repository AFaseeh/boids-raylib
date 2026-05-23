configure:
	cmake -S . -B build

build:
	cmake --build build

all: build run

clean:
	cmake -E rm -rf build

run:
	./build/boids-raylib/boids-raylib

.PHONY: all configure build run clean