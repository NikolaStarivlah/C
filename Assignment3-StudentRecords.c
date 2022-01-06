//Nikola Starivlah 
//Assignment 3
//2019-11-15
//The goal of this project is to allow for user input of int, char, and double to display according to the specificatins of th



#include<stdio.h>//libray main
#include<string.h>//string library
#include<stdlib.h>

int main()
{
   int num_of_students = 0;//total number of students
   char input[100];//char varible for user input
   int id[300];// student id first part
   char names[300][60];// name second part 
   double marks[500];// double for third part
   double averagemarks = 0.0;// double for average marks
  
   printf("=== Enter number of students : ");//prompts to enter student total
   gets(input); // Takes the user input for the number of students
   printf("=== Enter ID, Name, and mark seperated by comma\n");  //prompts uer to enter student details
	                     
  num_of_students = atoi(input); // converting char to int
  int i=0;//declaration of i for the for loop
  
   for(i=0;i<num_of_students;i++)//for loop going over number of students
   {
       printf("Student %d:", i+1);//student number plus 1 so its not 0
       gets(input);//scans for input
    
      
       char int_temp[20];//temporary char array
       int j;//j initialization outside of ffor loop for running
       for(j=0;input[j]!=',';j++)//for the input at the current character dose not equal ','
       {
           int_temp[j] = input[j];//current input is now equal to int_temp
       }
       int_temp[j] = '\0';//null character limiter 
       id[i] = atoi(int_temp);//student id is equal to the converted int_temp char
       j++;// j counter
       int k=0;//varibale for next for loop
       for(;input[j]!=',';j++)//for the input at the current character dose not equal ','
       {
           names[i][k] = input[j];//double array for names is equal to the character position at j
           k++;
       }
       names[i][k] = '\0';//double array for the names array initializer to construct an array equivalent to a null-terminated string
       j++;
      
       char double_temp[20];//temp double for average 
       k=0;
       for(;input[j]!='\0';j++)//for loop that loops evertime the loop iterator dose not equal a null terminated string  
       {
           double_temp[k++] = input[j];//temp double 
       }
       double_temp[k] = '\0';
       marks[i] = atof(double_temp);//marks at 
      
   }
  int k;
  //int p = 1;

  printf("---------------------------------------------\n");
       printf("#       Id             Name        Mark\n");
       //for loop for each student in the row
   for(i=0;i<num_of_students;i++)
   {
       averagemarks += marks[i];//summation for the average marks
       
       
      
      printf("%d         ", i+1);//student at counter usues i from for loop as row counter
    printf("%d          ",id[i]);//prints the student inputted nuber
       
       //printf("%d",)
       
       for(k=0;names[i][k]!='\0';k++)//for loops for names
       {
           if(names[i][k] >= 'a' && names[i][k] <= 'z')//checks for alphabet characters between a and z
           {
               printf("%c",names[i][k]-32);//ensures all charters are printed in uppercase
           }
           else
           {
               printf("%c",names[i][k]);//prints all not already uppercase
           }
       }
      
       printf("           %lf \n",marks[i]);//prints marks in row
   }
   
  printf("-------------------------------------------\n");
   averagemarks /= num_of_students;//calcuates average
   printf("Average                          : %lf\n",averagemarks);//prints average
   printf("-------------------------------------------\n");
  
  while(1)//while true run search code
   {  
       printf("Please enter a key for searching or press q/Q for exit : \n");//promots us
       gets(input);
      
       if(input[1] == '\0' && (input[0] == 'q' || input[0] == 'Q'))//if the first input equals a Q character
       {
           printf("=== See you next time! ===");  
           break;//ends code 
       }
       
       double average = 0.0;
       int records_found = 0;
      
      
       printf("---------------------------------------------\n");
       printf("#       Id             Name        Mark\n");
       for(i=0;i<num_of_students;i++)
       {
           if(strstr(names[i],input) != NULL)// if the strings function dose not equal a NULL then run the counter for the characters matched with input
           {
               records_found++;//counter for records found
               average += marks[i];//average counter for all marks entered
               printf("%d         ", i+1);//student at counter usues i from for loop as row counter
       			printf("%d      ",id[i]);//prints the student inputted nuber
       
       //printf("%d",)
       
       for(k=0;names[i][k]!='\0';k++)//for loops for names
       {
           if(names[i][k] >= 'a' && names[i][k] <= 'z')//checks for alphabet characters between a and z
           {
               printf("%c",names[i][k]-32);//ensures all charters are printed in uppercase
           }
           else
           {
               printf("%c",names[i][k]);//prints all not already uppercase
           }
       }
      
       printf("%lf \n",marks[i]);//prints marks in ro
            }
              	printf("-----------------------------------------\n");
   				averagemarks /= num_of_students;//calcuates average
   				printf("Average                          : %lf\n",averagemarks);//prints average
   				
				   printf(", Student marks : %lf \n",marks[i]);       
				   printf("-----------------------------------------\n");
            }
        
   return 0;
}
