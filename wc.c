#include <fcntl.h>
#include <search.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFSIZE 30

typedef struct {
	char word[42];
	unsigned count;
} WORD_T;

WORD_T *words = NULL;
size_t total_words = 0;

void print_and_free(WORD_T*, size_t, char*);
int comparator(const void *a, const void *b) {
	return strcmp(a,((WORD_T *)b)->word);
}

int main(int argc, char **argv) {
	// Checking whether the correct number of arguments is passed on when executing the file
	if (argc != 2) {
		printf("Usage: ./wc filename");
		return -1;
	}

	char *infile = argv[1];
	// TODO: open the file O_RDONLY
	// Initializing Buffere, File Descriptor, and Read Bytes to store the return value from read()
	int fd, read_bytes, skip_buffer=0;
	char buffer[BUFSIZE];
	
	// Opening file
	fd = open(infile, O_RDONLY);
	// Catch Errors for opening file
	if (fd == -1) perror("open()");

	// TODO: repeatedly call `read()` into a buffer of
	//       size BUFSIZE. Split the text in the buffer
	//       on newlines and spaces. For each token:
	//       search the `words` array to see if that
	//       word has already been added and if so
	//       increment the count. Otherwise add a new
	//       WORD_T struct to the end of the array of
	//       structs `words` and set the fields accordingly.
	//
	
	while (1){
		// Reading the file and storing the returning value of the bytes read.
		int size_to_read = ((BUFSIZE-1) - skip_buffer);
		read_bytes = read(fd, buffer + skip_buffer, size_to_read);
		// setting the last byte as null pointer
		buffer[read_bytes + skip_buffer] = 0;
		
		// declaring stringp and token character pointer for strsep()
		char *token, *stringp = buffer;
		while(stringp != NULL){
			// Appying the strsep() to split the words.
			token = strsep(&stringp, " \n");
		
			// If stringp is NULL, then we are at the last token.			      // So, move it to the first of the buffer
			if(stringp == NULL){
				// Storing the length of the last token. This will be used in the next iteration to skip some bytes in buffer when reading.
				skip_buffer = strlen(token);
				// Moving the last token to the beginning of the buffer.
				memmove(buffer, token, skip_buffer);
				
			}
			else {
			// Checking if we got a valid token.
				if(strlen(token) != 0){
					// Valid token
					
					// Checking whether the token already exists.
					WORD_T *res = lfind(token, words, &total_words, sizeof(WORD_T),comparator);
					// If match found
					if(res != NULL){
						res->count++;
					} else {
					// No match found
						// Reallocating the space of the array
						words = (WORD_T *) realloc(words, sizeof(WORD_T) * (total_words + 1));
						
						strcpy(words[total_words].word, token);
						words[total_words++].count = 1;
					}
				}
			}
		}
		// File completely read
		if(read_bytes < size_to_read){
			break;
		}

	}

	print_and_free(words, total_words, infile);
	// TODO: close the file
	close(fd);
	return 0;
}

void print_and_free(WORD_T *words, size_t total_words, char *infile) {
	int sum = 0;
	for (int i = 0; i < total_words; ++i) {
		if (words[i].count > 1)
			printf("%s: %u\n", words[i].word, words[i].count);
		sum += words[i].count;
	}
	printf("\n%d %s\n", sum, infile);

	free(words);
}

