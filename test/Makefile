# The MIT License
# 
# Copyright (c) 2018 Guillaume Bauer
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.




### Target Configuration

#Target binary name
TARGET = test.out




### Compiler configuration

#Compile command to use
CC = clang++
#compiler flags
CFLAGS = -O0 -Wall -Wextra -std=c++11 -g


### Project directories
BUILDDIR=build
BINDIR=$(BUILDDIR)/bin
OBJDIR=$(BUILDDIR)/obj
SRCDIR=src
IDIR = ../lib/include




### Utility variables
BIN = $(BINDIR)/$(TARGET)
SRC = $(wildcard $(SRCDIR)/*.cpp)
SRC_FILES = $(notdir $(SRC))
OBJ = $(SRC_FILES:.cpp=.o)
OBJECTS = $(addprefix $(OBJDIR)/, $(OBJ))

INCLUDES = -I $(IDIR)

LIBS = ../lib/build/bin/librpigpio.a


SHELL = /bin/sh








### Main make targets
# Inner targets
$(BIN): $(OBJECTS) | $(BINDIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) $(LIBS) -o $(BIN)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(OBJDIR)/$*.o

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)


# Targets for the user
.PHONY: all
all: $(BIN)

.PHONY: run
run: $(BIN)
	@$(SHELL) -c $(BIN)

.PHONY: clean
clean:
	rm -rf $(BUILDDIR)

.PHONY: rebuild
rebuild: clean all