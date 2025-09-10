# -*- Makefile -*-

# target : dependencies
#   action

all : exec geom tip

# ensure exec dir exists
exec:
	mkdir -p exec

geom: exec geom.o gd.o
	clang geom.o gd.o -o exec/main_geom -lm

geom.o: geom.c gd.h
	clang -c geom.c

gd.o: gd.c
	clang -c gd.c

tip: exec tip.o gd.o
	clang tip.o gd.o -o exec/main_tip

tip.o: tip.c gd.h
	clang -c tip.c

clean:
	rm -rf *.o exec/
