
# Module name and version
include module.cfg

# Installation options
include options.cfg

ifdef PENNMUSH
# PennMUSH flags and includes
MUSH = PENNMUSH
MUSHINC = -I$(MUSHDIR) -I$(MUSHDIR)/hdrs -I$(MUSHDIR)/pcre2/include
MUSHFLAGS = 
else ifdef RHOSTMUSH
# RhostMUSH flags and includes
MUSH = RHOSTMUSH
MUSHINC = -I$(MUSHDIR)
MUSHFLAGS =
else ifdef TM3
# TinyMUX3 flags and includes
MUSH = TM3
MUSHINC = -I$(MUSHDIR)
MUSHFLAGS =
endif

# Compiler flags
CXXFLAGS = -g $(MUSHINC) $(MUSHFLAGS)

# Compile all source files into corresponding object files
SRC_FILES := $(shell ls *.cpp)
OBJ_FILES = $(SRC_FILES:%.cpp=obj/%.o)

# Name of the module library
LIB = lib$(MODULE).a

# C++ compiler
CXX = g++

.SUFFIX:
.SUFFIX: .cpp .h

# Compile source files into object files
obj/%.o: %.cpp module.cfg options.cfg
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: objdir header main

# Compile library source and link objects together
main: $(OBJ_FILES)
	rm -f $(LIB)
	$(AR) rcs $(LIB) $(OBJ_FILES)

# Rebuild the MUSH server
mush: all
	(cd $(MUSHDIR); make)

# Remove object and temporary files
clean:
	rm -f *.a obj/*.o *~

# Create the object directory, if it doesn't exist
objdir:
	@mkdir -p obj

# Module header
header:
	@echo "Building module header."
	@echo "#define MODULE $(MODULE)" > _module.h
	@echo "#define MODULE_VERSION $(VERSION)" >> _module.h
	@echo "#define $(MUSH)" >> _module.h


