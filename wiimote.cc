#include "wiimote.h"

#include <fcntl.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

Wiimote::Wiimote() {
  // Write your code here

	fd=open("/dev/input/event2", O_RDONLY);
        if( fd==-1){
                std::cerr<< "Error: Could not open event file -forgot sudo?\n";
                exit(1);
        }
}
Wiimote::~Wiimote() {
  // Write your code here
	close(fd);
	
}

int Wiimote::Listen() {
  // Write your code here


	while(true){
		char buffer[32];
		read(fd, buffer, 32);
		int code= buffer[10];
		int value= buffer[12];	
		if (value == 1){
			return code;
		}else{
			return 0;
		}

	}


}
