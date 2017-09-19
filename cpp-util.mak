BUILD_DIR = build

SOURCES := \
	main.cpp

CC_FLAGS += -c -std=c++11

OBJECTS := $(addprefix $(BUILD_DIR)/,$(SOURCES))
OBJECTS := $(OBJECTS:.cpp=.o)
OBJECTS := $(OBJECTS:.cc=.o)

build/test: $(OBJECTS)
	mkdir -p $(shell dirname $@)
	g++ -o $@ $^

build/%.o: src/%.cpp
	mkdir -p $(shell dirname $@)
	g++ $(CC_FLAGS) -o $@ $<

all: build/cpp-util
