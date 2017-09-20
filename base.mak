ifndef PROJECT_NAME
$(error PROJECT_NAME variable not set)
endif

ifndef BUILD_DIR
BUILD_DIR = build
endif
$(info BUILD_DIR: $(BUILD_DIR))

ifndef BINARIES_DIR
BINARIES_DIR = bin
endif
$(info BINARIES_DIR: $(BINARIES_DIR))

ifndef LIB_DIR
LIB_DIR = lib
endif
$(info LIB_DIR: $(LIB_DIR))

ifndef INCLUDE_DIR
INCLUDE_DIR = include
endif
$(info INCLUDE_DIR: $(INCLUDE_DIR))

ifndef SOURCES_DIR
SOURCES_DIR = src
endif
$(info SOURCES_DIR: $(SOURCES_DIR))

INCLUDES += -I$(INCLUDE_DIR)

# Debug flags
DEBUG += -g

# Compiler flags
CC_FLAGS += $(DEBUG) $(INCLUDES) -c -std=c++11 -Wfatal-errors

# Linker flags
LD_FLAGS += $(DEBUG) $(LIBRARIES)

# Compiler call
CC = g++

# Archiver call
AR = ar rcsv

# Find all .cc/.cpp files in source directory
SOURCES := $(shell (find $(SOURCES_DIR) -name '*.cpp' -o -name '*.cc' | sed 's/$(SOURCES_DIR)\///'))

# Generate .o file name for each source file
OBJECTS := $(addprefix $(BUILD_DIR)/,$(SOURCES))
OBJECTS := $(OBJECTS:.cpp=.o)
OBJECTS := $(OBJECTS:.cc=.o)

# Create executable
$(BINARIES_DIR)/$(PROJECT_NAME): $(OBJECTS)
	mkdir -p $(shell dirname $@)
	$(CC) -o $@ $^ $(LD_FLAGS)

# Build .o files
$(BUILD_DIR)/%.o: $(SOURCES_DIR)/%.cpp
	mkdir -p $(shell dirname $@)
	$(CC) $(CC_FLAGS) -o $@ $<

$(BUILD_DIR)/%.o: $(SOURCES_DIR)/%.cc
	mkdir -p $(shell dirname $@)
	$(CC) $(CC_FLAGS) -o $@ $<

# Create static library
$(LIB_DIR)/lib$(PROJECT_NAME).a: $(OBJECTS)
	mkdir -p $(shell dirname $@)
	$(AR) $@ $^

# Executable target
executable: $(BINARIES_DIR)/$(PROJECT_NAME)

# Static library target
lib: $(LIB_DIR)/lib$(PROJECT_NAME).a

# Clean (wipe build directory)
clean:
	rm -rf $(BUILD_DIR)/*

.PHONY: all clean
