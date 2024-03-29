#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#define KB *1024

int main(int argc, char ** argv) 
{
	int c;
	int index;
	int M = 512;
	int b = 128;
	while ((c = getopt (argc, argv, "b:s:")) != -1) {
		switch(c) {
		case 'b':
			b = atoi(optarg);
			break;
		case 's':
			M = atoi(optarg);
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
	printf("M: %u \n", M);
	printf("b: %u \n", b);
	Init (M,b); // initialize
	
	// test operations
	int testnums [] = {100, 5, 200, 7, 39, 25, 400, 50, 200, 300};
	int i = 0;
	char test[] = "Hello this is thirty one bytes ";
	for (i=0; i< 10; i ++)
	{
		Insert (testnums[i],test,32);
	}
	PrintList ();
	Delete (7);
	int test2 = 55;
	Insert (13,&test2,sizeof(test2));
	//char *test3= Lookup(5);
	//printf("%s\n",test3);
	Delete (55);
	Delete (3);
	PrintList ();
	//end test operations
	Destroy ();
	PrintList ();
	
	for (index = optind; index < argc; ++index) {
		printf("Non-option argument %s\n", argv[index]);
	}
	return 0;
}
