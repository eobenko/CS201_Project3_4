# Alexander Loff 11-10-2026

FILES = bTree.cpp doctor.cpp hospital.cpp main.cpp patient.cpp person.cpp randomizer.cpp visuals.cpp 
BINARY_NAME = main.out
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
COMPILE_FLAGS = -o $(BINARY_NAME) -std=c++20 $(SFML_FLAGS)
DEBUG_COMPILE_FLAGS = -g -O0
COMPILER = g++

.PHONY: build build_debug run clean

# Create the binary
build: $(FILES)
	$(COMPILER) $(COMPILE_FLAGS) $(FILES)

# Create the binary with debug symbols that gdb can interpret
build_debug: $(FILES)
	$(COMPILER) $(DEBUG_COMPILE_FLAGS) $(COMPILE_FLAGS) $(FILES)

# Run the compiled binary
run:
	./$(BINARY_NAME)

# Remove the compiled binary
clean:
	rm -f $(BINARY_NAME)

