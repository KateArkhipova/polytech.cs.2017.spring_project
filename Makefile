SHELL = /bin/sh

PROJECT := gonki

LIBS :=  -lallegro -lallegro_image -lallegro_ttf -lallegro_font -lallegro_primitives


# —----------------
# External programs 
# —----------------
CC := gcc
RM := rm -rf

# —------------------
# Directories & Files
# —------------------
D_SRC := ./src
D_TEST := $(D_SRC)/tests
FILES_C := $(wildcard $(D_SRC)/*.c)
FILES_O := $(FILES_C:.c=.o)
TEST_FILES_C := $(filter-out $(D_SRC)/$(PROJECT).c, $(wildcard $(D_SRC)/*.c))
TEST_FILES_C += $(wildcard $(D_TEST)/*.c)
TEST_FILES_O := $(TEST_FILES_C:.c=.o)

# —----------
# Flags
# —----------
CFLAGS := -Wall
LFLAGS :=

# —----------
# Targets
# —----------

default: $(PROJECT)

%.o: %.c
	$(CC) -c -I $(D_SRC) $(CFLAGS) $< -o $@  $(LIBS)

$(PROJECT): $(FILES_O)
	$(CC) -I $(D_SRC) $(LFLAGS) $(FILES_O) -o $@ $(LIBS)

test: $(TEST_FILES_O)
	$(CC) -I $(D_SRC) $(LFLAGS) $(TEST_FILES_O) -o $@ $(LIBS)

.phony: clean
clean:
	-$(RM) $(FILES_O) $(TEST_FILES_O) $(PROJECT) test

