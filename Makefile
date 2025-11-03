# Usage:
#   make            # clean + build
#   make clean      # remove binary, objects, and dependency files

CC       := gcc
CFLAGS   := -std=c11 -g
LDFLAGS  := 
TARGET   := sim
SRC      := project1.c
OBJ      := $(SRC:.c=.o)
DEP      := $(OBJ:.o=.d)

.PHONY: all clean

all: clean $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEP)

clean:
	@echo "Cleaning build artifacts..."
	@rm -f $(TARGET) $(OBJ) $(DEP)
