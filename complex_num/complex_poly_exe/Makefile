

SOURCES := main.cpp
LIB_PATH = ../complex_lib/out/

override CPPFLAGS += -I../complex_lib
override CXXFLAGS += -std=c++11
override LDFLAGS += -L$(LIB_PATH) -lcomplex

vpath %.o out
vpath %.h ../complex_lib

.PHONY: all clean

all: out/complex_poly

out/complex_poly: $(SOURCES:%.cpp=out/%.o) $(LIB_PATH)/libcomplex.a | out
	$(CXX) $(LDFLAGS) -o $@ $^

out/%.o: %.cpp complex_num.h | out
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

out:
	mkdir -p out

clean: 
	rm -rf out/*