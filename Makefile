all: mario.cc
	g++ mario.cc -o mario
	./mario

gdb: mario.cc
	g++ mario.cc -o mario -g
