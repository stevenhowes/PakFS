TARGET1 = example1
TARGET2 = example2

SRCS_TARGET1 = example1.cpp $(wildcard PakFS/*.cpp)
SRCS_TARGET2 = example2.cpp $(wildcard PakFS/*.cpp)

CXX = g++
CXXFLAGS = -Wall -Wextra

OBJ_DIR  := ./objects
OBJS_TARGET1 := $(SRCS_TARGET1:%.cpp=$(OBJ_DIR)/%.o)
OBJS_TARGET2 := $(SRCS_TARGET2:%.cpp=$(OBJ_DIR)/%.o)

all: build $(TARGET1) $(TARGET2)

build:
	@mkdir -p ./$(OBJ_DIR)/PakFS
valgrind: all
	valgrind ./$(TARGET1)
	valgrind ./$(TARGET2)

$(TARGET1): $(OBJS_TARGET1)
	$(CXX) $(CXXFLAGS) -o $(TARGET1) $(OBJS_TARGET1)

$(TARGET2): $(OBJS_TARGET2)
	$(CXX) $(CXXFLAGS) -o $(TARGET2) $(OBJS_TARGET2)

$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET1) $(TARGET2)
	rm -rf $(OBJ_DIR)


.PHONY: all clean
