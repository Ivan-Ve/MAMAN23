#include <stdio.h>
FILE* commentDelete(FILE* fd, FILE* new_fd);
void f2(FILE* fd, FILE* new_fd, char** m, char* t);
void f3(char* buf, char** m, char* t, int count);
void printWord(char** m,int count);
void addString(char** m, int count, char word[]);
//Preprocessor.c
void main() {
	FILE* fd;
	FILE* new_file01;
	FILE* new_file02;
	int ch;



	//open the file to read from it ====>name.c
	if (!(fd = fopen("name.c", "r+"))) {
		fprintf(stderr, "cannot open file\n");
		exit(0);
	}
	//open the new file to write on it ====>name.c1
	if (!(new_file01 = fopen("name.c1", "w+"))) {
		fprintf(stderr, "cannot open file\n");
		exit(0);
	}
	//fd=name.c
	//new_file01=name.c1
	/*
	printf("\n********************\The original file********************\n");
	while (!feof(fd)) { // flag of end of file
		ch = fgetc(fd);
		printf("%c", ch);
	}
	rewind(fd);
	
	printf("\n********************\END of original file********************\n");
	*/
	new_file01= commentDelete(fd, new_file01);// COPY TO NEW FILE the fd without comments
	rewind(fd);
	rewind(new_file01);
	/*
	printf("\n********************\The NEW FILE WITHOUT COMMENTS file********************\n");
	while (!feof(new_file01)) {
		putchar(ch = fgetc(new_file01));
	}	
	printf("\n********************\TheEND OF NEW FILE WITHOUT COMMENTS file********************\n");
	*/
	//open the new file to write on it ====>name.c2
	if (!(new_file02 = fopen("name.c2", "w+"))) {
		fprintf(stderr, "cannot open file\n");
		exit(0);
	}
	
	/**************************************************************************************/
	char** m;
	m = (char**)malloc(10 * sizeof(char*));
	char* t;
	t = (char*)malloc(500 * sizeof(char));

	f2(new_file01, new_file02,m,t);
}
//this function is deleate the comment from the each row(LINE)
//return new buf(new LINE)

enum status { OUT, IN_STRING, LEFT_SLASH, IN_COMMENT, RIGHT_STAR};
FILE* commentDelete(FILE* fd,FILE* new_fd) {
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

//this function send to f3 each row that contains include
enum flag { FALSE, TRUE };
void f2(FILE* fd, FILE* new_fd,char**m,char*t) {
	rewind(fd);
	int flag=FALSE;
	int ch;
	char buf[500];
	char include_s[8] = {"#include"};
	
	int count=0;
	rewind(fd);
	while (!feof(fd)) {
		fgets(buf, 501, fd);//buf MEKABEL SHURA BE KOL PAM
		int i;
		for (i = 0; i < 8; i++) {
			if (buf[i] == include_s[i]) {
				flag = TRUE;
			}
			else {
				flag = FALSE;
				break;
			}
		}	
		if (flag==TRUE) {
			
			f3(buf,m,t,count);
			
			
			count++;
			
			flag = FALSE;
		}	
		
	}
	printWord(m, count);
}
//add BUF TO M
void f3(char* buf,char**m,char*t,int count) {
	int i = 0;
	int k = 0;
	enum status { OUT, IN };
	int state = OUT;

	char* x = (char*)malloc(500 * sizeof(char));
	if (*x == NULL) {
		printf("ERROR X ");
		exit();
	}
	while ((buf[i]) != EOF) {
		switch (state)
		{
		case OUT:
			if (buf[i] == '"' || buf[i] == '<') {
				state = IN;
			}
			i++;
			break;
		case IN:
			if (buf[i] == '"' || buf[i] == '>') {
				state = OUT;
				*(x + k) = '\0';
				i++;
				
				break;
			}
			else {
				*(x + k) = buf[i];
				k++;
				i++;
			}
			break;
		default:
			break;
		}
	}
	addString(m, count, x);	
	
}

void addString(char** m, int count, char word[]) {
	*(m + count) = word;
}
void printWord(char** m,int count) {
	int i;
	
	for (i = 0; i < count; i++) {
		printf("\nFOR LOOP i =%d ",i);
		printf("%s", *(m + i));
		printf("\n");
	}
	printf("\n");
}


























