MODULE=combat

CXXFLAGS=$(CCFLAGS) -I../.. -I../../hdrs

SRC_FILES := $(shell ls *.cpp)
OBJ_FILES = $(SRC_FILES:%.cpp=obj/%.o)

LIB = lib$(MODULE).a

CXX = g++

.SUFFIX:
.SUFFIX: .cpp .h

obj/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: objdir main

main: $(OBJ_FILES)
	rm -f $(LIB)
	$(AR) rcs $(LIB) $(OBJ_FILES)

clean:
	rm -f $(LIB) obj/*.o *~

objdir:
	mkdir -p obj
