#include "../includes/shell.h"

void shell(char* input) {
	if(strcmp(input, "help\n") == 0) {
		print("help is under construction please try again when the os is finished\n");
	}else if(strcmp(input, " clr\n") == 0){
		clear(0x0);
	}else if(strcmp(input, "timer\n") == 0){
        int seconds = second();
		print(toString(seconds));
		print("\n");
    }else if(strcmp(input, "sleep\n") == 0){
        sleep(100);
		print("just wake up\n");
    }else {
		print("Unknown command: ");
		print(input);
	}
}
