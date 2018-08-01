# Formatted-TV-Guide
Assignment completed in the unit Unix and C Programming [COMP1000] while at Curtin University.

## Objective
The objective of the assignment is to create a C89 compiled program that turns raw input data into a formatted TV guide according to the user's requirements. 

## Assumptions
#### _The format of the input can be assumed valid if_:

Raw input data consists of two lines per entry; the first line contains the TV show name (may contain spacing), and the second line contains the day of the week and time of day (24 hr time).

Example input:

How I Met Your Mother  
Wednesday 17:30


#### _The format of the output can be assumed valid if_:

Each entry occupies only one line and is the same in screen output and output file.

Example output (for Wednesday):

17:30 - How I Met Your Mother                                       
 6:30 - Sunrise
 
## Functionality
The specifications require the program to work as follows:
1) The program should accept 2 command line arguments: input and output filenames
2) The program should read 2 strings from the user: day of the week, and sorting type (time/name)
This step should validate input and re-prompt until input is valid.
3) The program should read from the input file, place each TV entry into a suitable structure and then store it in a generic linked list.
4) Once the input file has been read, the program should copy the linked list contents into a dynamically allocated array.
5) The program should sort the arrray by time or name, according to the user's input (step 2). Standard C qsort() function is to be used.
6) The program should filter the array to a day of the week, according to the user's input (step 2).
7) The program should display the sorted and filtered TV guide to the screen, and save a copy to the output file initially specified.

## Report
1) For each function, describe its purpose.
2) Regarding filtering TV guide entries (step 6 in functionality): describe how you implemented this & an alternative approach that would also work.
3) Show that the program works by using sample input and output. Include the command-line command used for program execution, user inputs, input file contents, and the output to file and screen. 
