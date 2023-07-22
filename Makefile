.PHONY: build
build:
	@mkdir -p build && \
	g++ -g -O0 -Wall -Wextra -Wpedantic -Wunused -std=c++14 main.cpp -o build/main

.PHONY: run
run: build
	@./build/main
