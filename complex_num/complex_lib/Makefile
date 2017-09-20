
SOURCES = complex_num.cpp

.PHONY: all clean

vpath %.o out

all: out/libcomplex.a

out/%.o: %.cpp %.h | out
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -o $@ $<

out/libcomplex.a: $(SOURCES:%.cpp=out/%.o) | out
	ar cr $@ $^

out:
	mkdir -p out

clean: 
	rm -rf out/*
