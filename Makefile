all: gvol

gvol: obj obj/main.o obj/ui.o
	g++  obj/main.o obj/ui.o -o gvol -lncurses
obj:
	mkdir -p obj
obj/main.o: source/main.cpp source/ui.h
	g++ -c source/main.cpp -o obj/main.o
obj/ui.o: source/ui.cpp source/ui.h
	g++ -c source/ui.cpp -o obj/ui.o
clean:
	rm -rf gvol obj