# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -o2

all	: bin/lllw
	@echo -n ""

# optimized version
bin/lllw	: lllw_opt.o main_opt.o lib
			$(CC) $(OPTFLAGS) lllw_opt.o main_opt.o -ltm_usage -Llib -o bin/lllw
main_opt.o 	   	: src/main.cpp lib/tm_usage.h
			$(CC) $(CFLAGS) $< -Ilib -o $@
lllw_opt.o	: src/pattern.cpp src/pattern.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

# DEBUG Version
dbg : bin/lllw_dbg
	@echo -n ""

bin/lllw_dbg	: pattern.o main_dbg.o lib
			$(CC) $(DBGFLAGS) pattern.o pattern_dbg.o -ltm_usage -Llib -o bin/lllw_dbg
main_dbg.o: src/main.cpp lib/tm_usage.h
			$(CC) $(CFLAGS) $< -Ilib -o $@
pattern.o	: src/pattern.cpp src/pattern.h
			$(CC) $(CFLAGS) $(DBGFLAGS) $< -o $@

lib: lib/libtm_usage.a

lib/libtm_usage.a: tm_usage.o
	$(AR) $(ARFLAGS) $@ $<
tm_usage.o: lib/tm_usage.cpp lib/tm_usage.h
	$(CC) $(CFLAGS) $<

# clean all the .o and executable files
clean:
		rm -rf *.o lib/*.a lib/*.o bin/*

