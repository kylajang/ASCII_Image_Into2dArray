CC := g++
CFLAGS := -Wall -pedantic -g --std=c++17

# My Variables
	PART1_EXE_NAME := lab14.bin
	PART1_EXE_PATH := ./$(PART1_EXE_NAME)

# Targets
default:	lab14

lab14:	$(PART1_EXE_PATH)
	@echo "Building $@"
	$(PART1_EXE_PATH)

$(PART1_EXE_PATH):	main.cpp
	@echo "Compiling $@"
	$(CC) $(CFLAGS) main.cpp -o $@ \
		&& chmod +x $@

clean:
	-rm $(PART1_EXE_PATH)
