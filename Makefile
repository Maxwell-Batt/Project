
    CXX := g++
    CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Werror -Iinclude
    LDFLAGS := 
    SRC := $(wildcard src/*.cpp) 
    OBJ := $(SRC:.cpp=.o)
    BIN := bin/game

    all: $(BIN)

    $(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(LDFLAGS)

    src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

    run: $(BIN)
	./$(BIN)

    clean:
	rm -f src/*.o $(BIN) bin/tests

    tests: $(BIN) tests/tests.cpp
	$(CXX) $(CXXFLAGS) -o bin/tests tests/tests.cpp src/Map.cpp src/Scoreboard.cpp

    .PHONY: all run clean tests
