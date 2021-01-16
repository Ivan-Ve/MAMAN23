#include <stdio.h>
FILE* f1(FILE* fd, FILE* new_fd);
FILE* f2(FILE* fd, FILE* new_fd);
//Preprocessor.c
void main() {
	FILE* fd;
	FILE* new_file01;
	FILE* new_file02;
	int ch;

	char* arr;

	if (!(fd = fopen("name.c", "r+"))) {
		fprintf(stderr, "cannot open file\n");
		exit(0);
	}
	//open the new file to write on it
	if (!(new_file01 = fopen("name.c1", "w+"))) {
		fprintf(stderr, "cannot open file\n");
		exit(0);
	}
	//fd=name.c
	//new_file01=name.c1
	printf("\n********************\The original file********************\n");
	while (!feof(fd)) { // flag of end of file
		ch = fgetc(fd);
		printf("%c", ch);
	}
	rewind(fd);
	printf("\n********************\END of original file********************\n");

	new_file01=f1(fd, new_file01);// COPY TO NEW FILE the fd without comments
	rewind(fd);
	rewind(new_file01);
	printf("\n********************\The NEW FILE WITHOUT COMMENTS file********************\n");
	while (!feof(new_file01)) {
		putchar(ch = fgetc(new_file01));
	}	
	printf("\n********************\TheEND OF NEW FILE WITHOUT COMMENTS file********************\n");

	if (!(new_file02 = fopen("name.c2", "w+"))) {
		fprintf(stderr, "cannot open file\n");
		exit(0);
	}
	new_file02 = f2(new_file01, new_file02);


}
//this function is deleate the comment from the each row(LINE)
//return new buf(new LINE)

enum status { OUT, IN_STRING, LEFT_SLASH, IN_COMMENT, RIGHT_STAR};
FILE* f1(FILE* fd,FILE* new_fd) {
	int c;
	int state = OUT;
	while (!feof(fd)) {
		c = fgetc(fd);
		switch (state)
		{
		case OUT:
			if (c == '/') {
				state = LEFT_SLASH;
			}
			else {
				fputc(c, new_fd);
				if (c == '\"') {
					state = IN_STRING;
				}
			}
			break;

		case LEFT_SLASH:
			if (c == '*') {
				state = IN_COMMENT;
			}
			else {
				fputc(c, new_fd);
				state = OUT;
			}
			break;

		case IN_COMMENT:
			if (c == '*') {
				state = RIGHT_STAR;
			}
			break;

		case RIGHT_STAR:
			if (c == '/') {
				state = OUT;
			}
			else if (c != '*') {
				state = IN_COMMENT;
			}
			break;

		case IN_STRING:
			if (c == '\"') {
				state = OUT;
			}
			fputc(c, new_fd);
			break;

		default:
			break;
		}
	}

	return new_fd;
}

enum flag { FALSE, TRUE };
FILE* f2(FILE* fd, FILE* new_fd) {
	rewind(fd);
	int flag=FALSE;
	int ch;
	char buf[500];
	char include_s[8] = {"#include"};
	
	rewind(fd);
	while (!feof(fd)) {

		fgets(buf, 501, fd);

		int j = 0, k = 0;
		int i;
		for (i = 0; i < 8; i++) {
			if (buf[i] == include_s[i]) {
				printf("\nTRUE %c buf[%d]",buf[i],i);
				flag = TRUE;
			}
			else {
				flag = FALSE;
				break;
			}
		}
	
		if (flag==TRUE) {
			printf("\nFLAG IS TRUE\n");
			printf("%s\n", buf);
			flag = FALSE;
		}
		
		
	}


}
