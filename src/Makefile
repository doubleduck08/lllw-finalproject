AR       := ar
ARFLAGS  := cr
CXX      := g++
CPPFLAGS := -g


all: ../bin/lllw
	@echo -n ""

clean:
	rm *.o ../bin/lllw


../bin/lllw: main.o pattern.o ../lib/lib.a
	$(CXX) $^ -o $@

main.o: main.cpp pattern.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

pattern.o: pattern.cpp pattern.h
	$(CXX) $(CPPFLAGS) -c $< -o $@
