CXX = g++
CXXFLAGS = -g -Wall -pthread -I. -Werror -Wpedantic -fopenmp
CXX_FLAG = -Iinclude
GTEST_LIBS = -lgtest -lgtest_main -lpthread

SRC_DIR = src
# wildcard - satisfies the pattern 
PROJ_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(PROJ_FILES:.cpp=.o)

# Exclude main.o from object files
OBJ_FILES_WITHOUT_MAIN = $(filter-out $(SRC_DIR)/main.o, $(OBJ_FILES))

EXE_1 = parallel

all: $(EXE_1)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp 
	$(CXX) $(CXXFLAGS) $(CXX_FLAG) -c $< -o $@

# executables
$(EXE_1): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(CXX_FLAG) $^ -o $@

# "*" - for terminal, "%" - for Makefile
clean:
	rm -f $(SRC_DIR)/*.o

cleanall:
	rm -f $(SRC_DIR)/*.o $(EXE_1) *.bmp