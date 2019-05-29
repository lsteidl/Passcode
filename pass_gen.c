#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
// PRONOUN + ADJECTIVE + NOUN + VERB + ADJECTIVE + NOUN
// ADJECTIVE + NOUN + [will] + ADVERB + VERB + ADJECTIVE + NOUN 
// NOUN + VERB + NOUN
// adj : 1339
// adv : 666
// nouns : 6801
// pronouns : 71 
// verbs : 1011
// 71*1339*6801*1011*1339*6801
int main(int argc, char* argv[])
{
// to read files
char buffer[32];
char *b = buffer;
size_t buffer_size = 32;
size_t read_size = 0;
FILE * fp;
int fs [5]= { 1339 , 666, 6801, 71, 1011 };// number of lines (or words) in files
char * wordlist[5];
wordlist[0] = "adj.txt";
wordlist[1] = "adv.txt";
wordlist[2] = "nouns.txt";
wordlist[3] = "pronouns.txt";
wordlist[4] = "verbs.txt";
char arrays [5][6801][32];

printf("Welcome to Passphrase Generator!\n");
for(int i = 0; i < 5; i++){
	// open file
	fp = fopen( wordlist[i], "r");
	if( fp == NULL ) {
	        printf("%s not found\n", wordlist[i]);
        	exit(1);
	}
// load each  wordlist into arra
		for(int line = 0; line < fs[i]; line++){
        		read_size = getline(&b, &buffer_size, fp);
       		 	char* token = strtok(buffer, " \t\n");  // remove space chars and newline
			strcpy(arrays[i][line], token);
		}	
		fclose(fp);
}
printf("All wordlists loaded successfully!\n");
printf("Choose pass code complexity:\nLow (enter 1)\nMedium  (enter 2)\nHigh (enter 3)\n");

getline(&b, &buffer_size, stdin);
char * endpt = &b[sizeof(int)*2];
int input = strtol(buffer, &endpt, 10);
int level;
int order[3][7] = { {2,4,2} , {3,0,2,4,0,2} , {0,2,1,4,0,2} };
if(input == 1){
	level = 3;
	printf("Generating passcode of low complexity\n");
}
if(input == 2){
	level = 6;
	printf("Generating passcode of medium complexity\n");
}
if(input == 3){
	level = 7;
	printf("Generating long passcode\n");

}
	char output[7][32];
	int index; // chosen random index
	int type; // word type
	srand(time(0));
	for(int i = 0; i < level; i++){
		type = order[input-1][i];
		index = ( rand() % (fs[type]+1) );
		char * temp = arrays[type][index];
		strcpy(output[i], temp);
		printf("%s\n", output[i]);
	}
	if(input == 1)
		printf("Passphrase is: %s %s %s\n", output[0],output[1],output[2]);	
	if(input == 2)
		printf("Passphrase is: %s %s %s %s %s %s\n", output[0],output[1],output[2],output[3],output[4],output[5]);	
	if(input == 3)
		printf("Passphrase is: %s %s %s %s %s %s %s\n", output[0],output[1],output[2],output[3],output[4],output[5], output[6]);


}
