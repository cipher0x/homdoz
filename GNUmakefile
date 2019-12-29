.PHONY: clean remote_clean sync remote install
	
CC := g++ # This is the main compiler
# CC := clang --analyze # and comment out the linker last line for sanity
SRCDIR := src
BUILDDIR := build
BUILDDIRICS := build/ics
TARGET := build/homdoz
CWD := $(shell pwd)
BUILD_SERVER := 10.0.10.15

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -l /lib64 -g -std=c++11# -Wall
LIB := -lwiringPi -lpthread
INC := -I include

$(TARGET): $(OBJECTS)
		@echo " Linking..."
		@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
		@mkdir -p $(BUILDDIR)
		@mkdir -p $(BUILDDIRICS)
		@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<
clean:
		@echo " Cleaning...";
		@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

remote_clean:
		@echo "Remote Cleaning $(BUILD_SERVER)...";
		ssh -C $(BUILD_SERVER) "cd $(CWD) && make clean"

sync:
		rsync -r $(CWD) $(BUILD_SERVER):~/code

remote: remote_clean sync
		ssh -C $(BUILD_SERVER) "cd $(CWD) && make"

install:
