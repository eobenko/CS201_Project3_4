# Alexander Loff 11-10-2026

FILES = doctor.cpp hospital.cpp main.cpp patient.cpp person.cpp randomizer.cpp visuals.cpp 
BINARY_NAME = main.out
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
COMPILE_FLAGS = -o $(BINARY_NAME) -std=c++20
DEBUG_COMPILE_FLAGS = -g -O0
COMPILER = g++

.PHONY: build build_debug run clean test_visuals compile_visuals run_visuals clean_visuals

build: $(FILES)
	$(COMPILER) $(COMPILE_FLAGS) $(FILES) $(SFML_FLAGS)

build_debug: $(FILES)
	$(COMPILER) $(DEBUG_COMPILE_FLAGS) $(COMPILE_FLAGS) $(FILES) $(SFML_FLAGS)

# Run the compiled binary
run:
	./$(BINARY_NAME)

# Remove the compiled binary
clean:
	rm -f $(BINARY_NAME)

# compile, run, and remove visuals binary
test_visuals: compile_visuals run_visuals clean_visuals
# compile visuals
compile_visuals:
	$(COMPILER) -std=c++20 -DTEST_VISUALS visuals.cpp -o visuals $(SFML_FLAGS)
# run visuals
run_visuals:
	./visuals
# remove visuals
clean_visuals:
	rm ./visuals
