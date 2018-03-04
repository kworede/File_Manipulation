// Kirubel Worede
// CSE 374 Homework 4
// gasp.c
// 10/30/2015
// The purpose of this assignment is to implementing a utility program that is similar to grep,
// but without the ability to process regular expressions (i.e., a lot like a simple version of fgrep).
// The program take string words and files and print out lines that contains the string word

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#define LINE_LENGTH 500 // Maximum number of lines that can be read 
#define STRING_LENGTH 100 // Maximum number of input string characters

int set_options(int k, char* argv[], int* i_flag, int* n_flag);
void make_upper(char* input_string, char* output_string, int flag);

// The main function reads file form the user,compare if string match is occur and prints out matched line.
// It will output error message if the file can not be read or if it is not existed.
int main(int argc, char *argv[]) {
 char line_to_search[LINE_LENGTH];
 char string_to_find[STRING_LENGTH];
 char line_with_case[STRING_LENGTH];
 int arg_number = 1, case_flag = 0, number_flag = 0;
 int i;
 
 if(argc<3){
   puts("Too few arguments.");
   exit(1);
 }
 
 arg_number = set_options(arg_number, argv, &case_flag, &number_flag);//check for options, increment arg_number if found
 arg_number = set_options(arg_number, argv, &case_flag, &number_flag);//runs twice to check for up to 2 options
 strncpy( string_to_find,argv[arg_number],STRING_LENGTH); // copy each line for the purpose of changing case
 make_upper(string_to_find, string_to_find, case_flag);// change the case of the charatcters.

 for(i=arg_number+1;i<argc;i++){

  FILE *file = fopen(argv[i], "r");
  if(file == NULL) {
    printf("The file '%s' does not exist!\n", argv[i]);
  }
  else{
   int line_number = 0;
   while( fgets(line_to_search, LINE_LENGTH, file) != ('\0')){
    line_number++;
    make_upper(line_to_search, line_with_case, case_flag);// pass the line to be changed to uppercase along with the flag
    if (strstr(line_with_case, string_to_find) != NULL) {
      if(number_flag){
        printf("%s\t%i\t%s",argv[i],line_number,line_to_search);   // if line contains the text, print it
      }
      else{
       printf("%s\t%s",argv[i],line_to_search);   // print it without line number
      }
    }
   } 
   fclose(file);
  }
 }
}

 //check for -i and -n option flags, and move past them if found
int set_options(int k, char* argv[], int* i_flag, int* n_flag){ 
  if(strcmp(argv[k], "-i")==0) {
    *i_flag = 1;
    k++;
  }
  if(strcmp(argv[k], "-n")==0) {
    *n_flag = 1;
    k++;
  }
  return k;
}

//change input string to all caps and put it in output string, but only if flag = 1.
void make_upper(char* input_string, char* output_string, int flag){  
  int i;
  strcpy(output_string, input_string);//copy string without changing it
  if(flag == 1){
   for(i=0;i<strlen(input_string);i++){
     output_string[i] = toupper(output_string[i]);//make each character capital
   }
  }
}
