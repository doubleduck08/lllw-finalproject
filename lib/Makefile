AR       := ar
ARFLAGS  := cr
CXX      := g++
CPPFLAGS := -O2

all: lib.a
	@echo -n ""

clean:
	rm *.a *.o

lib.a: tm_usage.o
	$(AR) $(ARFLAGS) $@ $^

tm_usage.o: tm_usage.cpp tm_usage.h
	$(CXX) $(CPPFLAGS) -c $< -o $@
