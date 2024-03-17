CXX := g++
CXXFLAGS := -Wall -Werror -Wextra -pedantic -std=c++23 -march=native -O3
LDLIBS := -lncurses -lcurl

TARGET := main

SRC := src/main.cpp src/menu.cpp src/xml_news.cpp src/utils.cpp
OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJ)