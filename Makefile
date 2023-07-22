MAKEFLAGS += --no-print-directory	# Do not print "Entering directory ..."

.PHONY: build
build:
	@mkdir -p ./build && \
	g++ -g -O0 -Wall -Wextra -Wpedantic -Wunused -std=c++14 main.cpp -o build/main

.PHONY: clean
clean:
	rm -rf ./build

# Generates compile_commands.json using bear.
.PHONY: compile_commands
compile_commands:
	@if [ ! -f build/compile_commands.json ]; then \
		bear -- make build && \
		mv compile_commands.json build; \
	fi

.PHONY: run
run: build
	@./build/main

.PHONY: format
format:
	@find . -name '*.cpp' -o -name '*.h' | xargs clang-format -i -style=file

.PHONY: check
check: compile_commands
	@clang-tidy -p build main.cpp
	@find . -name '*.cpp' -o -name '*.h' | xargs clang-format -style=file --dry-run --Werror
