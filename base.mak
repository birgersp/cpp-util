PROJECT_NAME ?= unnamed
BUILD_DIR ?= build
BINARIES_DIR ?= bin
LIB_DIR ?= lib
SOURCES_DIR ?= src
TEST_SOURCES_DIR ?= test
INCLUDE_DIR ?= include
INCLUDES += -I$(INCLUDE_DIR)

$(info PROJECT_NAME: $(PROJECT_NAME))
$(info BUILD_DIR: $(BUILD_DIR))
$(info BINARIES_DIR: $(BINARIES_DIR))
$(info LIB_DIR: $(LIB_DIR))
$(info INCLUDE_DIR: $(INCLUDE_DIR))
$(info SOURCES_DIR: $(SOURCES_DIR))
$(info TEST_SOURCES_DIR: $(TEST_SOURCES_DIR))

# Compiler flags
CC_FLAGS += $(INCLUDES) -c -std=c++11 -Wpedantic -Werror -Wfatal-errors

# Linker flags
LD_FLAGS += $(LIBRARIES)

# Compiler call
CC = g++

# Archiver call
AR = ar rcsv

# Find all .cpp files in source directory
SOURCES := $(shell (find $(SOURCES_DIR) -name '*.cpp' | sed 's/$(SOURCES_DIR)\///'))

TEST_SOURCES := $(SOURCES)
TEST_SOURCES := $(TEST_SOURCES:main.cpp=)
TEST_SOURCES += $(shell (find $(TEST_SOURCES_DIR) -name '*.cpp' | sed 's/$(TEST_SOURCES_DIR)\///'))

# Generate .o file name for each source file
OBJECTS := $(addprefix $(BUILD_DIR)/,$(SOURCES))
OBJECTS := $(OBJECTS:.cpp=.o)

TEST_OBJECTS := $(addprefix $(BUILD_DIR)/,$(TEST_SOURCES))
TEST_OBJECTS := $(TEST_OBJECTS:.cpp=.o)

# Create executable
$(BINARIES_DIR)/$(PROJECT_NAME): $(OBJECTS)
	mkdir -p $(shell dirname $@)
	$(CC) -o $@ $^ $(LD_FLAGS)

$(BINARIES_DIR)/$(PROJECT_NAME)-test: $(TEST_OBJECTS)
	mkdir -p $(shell dirname $@)
	$(CC) -o $@ $^ $(LD_FLAGS)

# Build .o files
$(BUILD_DIR)/%.o: $(SOURCES_DIR)/%.cpp
	mkdir -p $(shell dirname $@)
	$(CC) $(CC_FLAGS) -o $@ $<

$(BUILD_DIR)/%.o: $(TEST_SOURCES_DIR)/%.cpp
	mkdir -p $(shell dirname $@)
	$(CC) $(CC_FLAGS) $(TEST_CC_FLAGS) -o $@ $<

# Create static library
$(LIB_DIR)/lib$(PROJECT_NAME).a: $(OBJECTS)
	mkdir -p $(shell dirname $@)
	$(AR) $@ $^

# Executable target
executable: $(BINARIES_DIR)/$(PROJECT_NAME)

test: $(BINARIES_DIR)/$(PROJECT_NAME)-test

# Static library target
lib: $(LIB_DIR)/lib$(PROJECT_NAME).a

# Clean (wipe build directory)
clean:
	rm -rf $(BUILD_DIR)/*
	rm -rf $(BINARIES_DIR)/*

.PHONY: all clean
