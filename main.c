#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#define KB *1024

int main(int argc, char ** argv) 
{
	int c;
	int index;
	int M = 1024;
	int b = 128;
	while ((c = getopt (argc, argv, "bs:")) != -1) {
		switch(c) {
		case 'b':
			M = optarg;
			break;
		case 's':
			b = optarg;
			break;
		case '?':
			if (optopt == 'c')
				fprintf(stderr, "Option -%c requires an argument.\n", optopt);
			else if (isprint (optopt))
				fprintf(stderr, "Unknown option '-%c'.\n", optopt);
			else
				fprintf(stderr, "Unknown option character '\\x%x'.\n", optopt);
			return 1;
		default:
			abort();
		}
	}
	Init (M,b); // initialize
	
	// test operations
	int testnums [] = {100, 5, 200, 7, 39, 25, 400, 50, 200, 300};
	int i = 0;
	for (i=0; i< 10; i ++)
	{
		Insert (testnums [i]);
	}
	PrintList ();
	Delete (7);
	Insert (13);
	Delete (55);
	Delete (3);
	PrintList ();
	//end test operations
	Destroy ();
	
	for (index = optind; index < argc; ++index) {
		printf("Non-option argument %s\n", argv[index]);
	}
	return 0;
}
