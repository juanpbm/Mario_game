all: mario.cc wiimote.cc wiimote.h
	g++ mario.cc wiimote.cc wiimote.h -o mario
	sudo ./mario

gdb: mario.cc
	g++ mario.cc -o mario -g
