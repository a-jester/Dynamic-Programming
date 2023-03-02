# Target Variables
BASENAME = dynamic_demo
EXTENSION = .elf
TARGET = $(BASENAME)$(EXTENSION)

# Compiler Flags and Defines
CC = gcc
LD = 
LDFLAGS = -lm

# CFLAGS ---------------------------------------------------------------------
# -Wall     - Turn on all warnings covered by -Wall
# -Werror   - fail the compiler if a warning is encountered
# -g        - turn on debugging symbols
# -O0       - Optimize level 0
# -std=c17  - compile to the c17 standard
# ----------------------------------------------------------------------------
CFLAGS = -Wall -Werror -g -O0 -std=c17
CPPFLAGs = 

# Misc flags
AS =
ASFLAGS =
LDLIBS =

# Source files
SOURCES = dynamic_demo.c

# Additional variables
OBJS = $(SOURCES:.c=.o)
ASMS = $(SOURCES:.c=.asm)
PUREC = $(SOURCES:.c=.i)

# Makefile functions
define colorprint
      @tput setaf 2
      @echo $1
      @tput sgr0
endef

.PHONY: build
build: all
.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(call colorprint,"Target: " $(TARGET))
	$(CC) $(CPPFLAGS) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

.PHONY: compile-all
compile-all: $(OBJS) $(ASMS) $(PUREC)

%.i: %.c
	$(call colorprint,"Generating Pure C files" $(PUREC))
	$(CC) $(CPPFLAGS) $(CFLAGS) -E $(INCLUDES) -c $< -o $@

%.asm: %.c
	$(call colorprint, "Generating Assembly files" $(ASMS))
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INCLUDES) -S $< -o $@

%.o: %.c
	$(call colorprint, "Generating Object files" $(OBJS))
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(OBJS) $(ASMS) $(PUREC) $(TARGET)