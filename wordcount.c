#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Error: Expected one argument, found %d\n", argc-1);
		return -1;
	}

	const char* fn = argv[1];
	int fd = open(fn, O_RDONLY);

	if (fd == -1) {
		printf("Error: Could not open %s in read mode", argv[0]);
		return -1;
	}

	if (fn == NULL) {
		printf("Error: Could not find %s", argv[0]);
		return -1;
	}

	int numOfWords = 0;
	int numOfLines = 0;
	int numOfChars = 0;
	int atWord = 0;
	char buf;
	
	while (read(fd,&buf,1) > 0) {
		numOfChars++;
		if (buf == '\n') {
			numOfLines++;
			if (atWord) {
				numOfWords++;
				atWord = 0;
			}
		}
		else if (isspace(buf)) {
			if (atWord) {
				numOfWords++;
				atWord = 0;
			}
		}
		else
			atWord = 1;
	}
	if ((read(fd,&buf,1) == 0) & atWord) {
		numOfWords++;
	}
	
	close(fd);
	printf("%d %d %d %s", numOfLines, numOfWords, numOfChars, fn);
	return 0;
}