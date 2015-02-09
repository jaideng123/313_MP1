#include <stdlib.h>
#include <string.h>
#include <string.h>

int main(int argc, char ** argv) 
{
	int b = 128;
	int M = b * 4;  // so we have space for 4 items in each of the lists
	int t = 4;		// 4 tiers
	
	char buf [1024];
	memset (buf, 1, 1024);		// set each byte to 1
	
	char * msg = "a sample message";
	
	int c;
	while ((c = getopt (argc, argv, "b:s:t:")) != -1) {
		switch(c) {
		case 'b':
			b = atoi(optarg);
			break;
		case 's':
			M = atoi(optarg);
			break;
		case 't':
			t = atoi(optarg);
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
	printf("t: %u \n", t);
	
	Init (M, b, t); // initialize
	// test operations
	int testnums [] = {0, 1<<29 , (1<<29) + 5 , 50, (1<<30) + 5, (1<<30) - 500};
	int i = 0;
	// some sample insertions
	for (i=0; i< 10; i ++)
	{
		Insert (testnums [i], buf, 50);   // insert 50 bytes from the buffer as value for each of the insertions
	}
	PrintList ();
		
	// end test operations	
	Destroy ();
	
	int index;
	for (index = optind; index < argc; ++index) {
		printf("Non-option argument %s\n", argv[index]);
	}
	return 0;
}
