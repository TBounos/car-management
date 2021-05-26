/*	Description:	Check README,
 *		Notice(s):	The data are in a .txt(cars.txt).
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>

typedef struct {	//Includes all the variables to read a single line from cars.txt
	char m[25], c[25];	//25 characters is more than enough for the manufacturer & the color of the car
	int n, d;
}car;

void UI(int x) {	//For easier management, a lot of the complex printing elements are stored and called from here
	int i;
	
	switch(x) {
		case 1: {		//Horizontal double top line
			printf("\311");
			for(i=0; i<77; i++)		printf("\315");
			printf("\273\n");
			
			return;
		}
		case 2: {		//Horizontal double middle line
			printf("\314");
			for(i=0; i<77; i++)		printf("\315");
			printf("\271\n");
			
			return;
		}
		case 3: {		//Horizontal single middle line
			printf("\307");
			for(i=0; i<77; i++)		printf("\304");
			printf("\266\n");
			
			return;
		}
		case 4: {		//Horizontal double bottom line
			printf("\310");
			for(i=0; i<77; i++)		printf("\315");
			printf("\274\n");
			
			return;
		}
		case 5: {		//Stop and then clean
			printf("\n\n");
			system("pause");
			system("cls");
			
			return;
		}
		case 6: {		//Error message
			for(i=0; i<106; i++)		printf("\260");
			printf("Error: invalid_value...");
			for(i=0; i<111; i++)		printf("\260");
			printf("\n");
		
			return;
		}
		case 7: {		//.txt Error message
			for(i=0; i<102; i++)		printf("\260");
			printf("Error opening the file \"cars.txt\"...");
			for(i=0; i<102; i++)		printf("\260");
			
			return;
		}
		case 8: {		//Search(5) message
			for(i=0; i<109; i++)		printf("\260");
			printf("No results found...");
			for(i=0; i<112; i++)		printf("\260");
			
			break;
		}
	}
}

int display_scan()	{	//The menu that user sees when launching the program
	int in=-1;
	char temp[5];
	
	UI(1);
	printf("\272 Developer: Thanasis Bounos%-37sVersion: 1.5 \272\n", "");
	UI(2);
	printf("%-32sBasic Menu:%-35s\272\n", "\272", "");
	UI(3);
	printf("\272  Choose one of the following:%-47s\272\n", "");
	printf("\272%-4s%-73s\272\n", "", "1. Show all");
	printf("\272%-4s%-73s\272\n", "", "2. Enter a new record");
	printf("\272%-4s%-73s\272\n", "", "3. Delete a record");
	printf("\272%-4s%-73s\272\n", "", "4. Modify a record");
	printf("\272%-4s%-73s\272\n", "", "5. Search");
	printf("\272%-4s%-73s\272\n", "", "6. Update database");
	printf("\272%-4s%-73s\272\n", "", "0. Terminate");
	UI(4);
	
	UI(1);
	printf("\272 To apply changes made to the database, you have to press six(6), else any%-3s\272\n\272 changes made will be lost.%-50s\272\n", "", "");
	UI(4);
	
	do {	//Ensures only: 0, 1, 2, 3, 4, 5, 6, will get returned in main
		printf("\n> ");
		scanf("%s", temp);
		in = atof(temp);
		if(temp[0]!='\60' && in!=1 && in!=2 && in!=3 && in!=4 && in!=5 && in!=6)		UI(6);
	}while(temp[0]!='\60' && in!=1 && in!=2 && in!=3 && in!=4 && in!=5 && in!=6);
	
	return in;
}

int lines() {	//"lines" returns the number of lines in "cars.txt"
	FILE *fl;
	char temp[100];
	int i;
	
	if(!(fl = fopen("cars.txt", "r")))	UI(7);
	else {	for(i=0; !feof(fl); i++)	fgets(temp, 100, fl);	fclose(fl);	}
	
	return i;
}

void print() {	//"print" is the fuction called when user selects 1. It prints all the records
	FILE *fl;
	int n;
	car a;
	
	if(fl = fopen("cars.txt", "r"))	{
		n = lines();	//We get the number of records, so we can print it below
		
		UI(1);
		printf("%-26s1. Show all:(%d Records)%-28s\272\n", "\272", n, "");
		UI(2);
		printf("\272  Reading \"cars.txt\"...%-54s\272\n", "");
		UI(2);
		printf("\272%-4s%-15s%-15s%-22s%-21s\272\n", "", "Car Number", "Colour", "Manufacturer", "Purchase Date");
		UI(3);
		while(!feof(fl)) {	//Until the end of the file, we scan line-by-line the file and print it
			fscanf(fl, "%d %s %s %d", &a.n, a.c, a.m, &a.d);
			
			printf("\272%-4s%-15d%-15s%-22s%-21d\272\n", "", a.n, a.c, a.m, a.d);
		}
		UI(4);
		
		fclose(fl);
	}
	else	UI(7);
}

car new_record(int x, int y) {	//"new_record" is the fuction called when user selects 2(and 4). It asks and checks for the user input, to create a new record(or modify one)
	FILE *fl;
	int i, n=0, t;
	car a, *b;
	char temp[100];
	
	if(fl = fopen("cars.txt", "r")) {
		n = lines();	//Counting the lines of cars.txt to create an array equal to that
		b = malloc(n*sizeof(car));	//Creating an array, in the exact dimesions of the txt
		
		for(i=0; i<n; i++) 	fscanf(fl, "%d %s %s %d", &b[i].n, b[i].c, b[i].m, &b[i].d);	//Loading all the records of cars.txt to ram
		fclose(fl);
	}	
	
	do {	//Getting the new car number
		printf("%-15sWrite the car's number> ", "");
		scanf("%s", temp);
		a.n = atof(temp);
		
		for(i=0, t=0; i<n; i++)	if(a.n==b[i].n && b[i].n!=y)	{	t=-1;	break;	}	//Checking that the number is not repeated
		
		if(a.n>9999 || a.n<1000 || t==-1)	UI(6);
	}while(a.n>9999 || a.n<1000 || t==-1);
	if(fl = fopen("cars.txt", "r"))	free(b);
		
	printf("%-15sWrite the car's colour> ", "");	//Getting the new car colour
	scanf("%s", a.c);
		
	printf("%-15sWrite the car's manufacturer> ", "");	//Getting the new car manufacturer
	scanf("%s", a.m);
		
	do {	//Getting the new car purchase date
		printf("%-15sWrite the car's purchase date> ", "");
		scanf("%s", temp);
		a.d = atof(temp);
		if(a.d>1959 || a.d<2007)	UI(6);
	}while(a.d>2010 || a.d<1980);
		
	return a;
}

int bubblesort_scan() {	//"bubblesort_scan" is the fuction called both for 3 and 4
	FILE *fl;
	char temp[25];
	int i, j, n=0, c=0, in=1;
	car *a, tmp;
	
	if(!(fl = fopen("cars.txt", "r")))
		UI(7);
	else {
		n = lines();	//Getting the number of lines in cars.txt
  		a = malloc(n*sizeof(car));	//Creating an equal array
   		
		for(i=0; i<n; i++) 	fscanf(fl, "%d %s %s %d", &a[i].n, a[i].c, a[i].m, &a[i].d);	//Loading the txt in RAM
		fclose(fl);
		
		for(i=1; i<n; i++)	//Bubblesort
			for(j=0; j<n-1; j++)
				if(a[j].n>a[j+1].n)	{
					tmp = a[j];
					a[j] = a[j+1];
					a[j+1] = tmp;
				}
		
		printf("%-5sAll the car numbers:%-53s\272\n", "\272", "");	//Printing the numbers
		UI(4);
		for(i=0; i<n; i++)	printf("\t%d\t", a[i].n);
		
		do {	//Input
			printf("\n\n> ");
			scanf("%s", temp);
			in = atof(temp);
			for(i=0; i<n && temp[0]!='\60'; i++)	if(in==a[i].n)	c=1;
			if(c==0)		UI(6);
		}while(c==0);
		
		system("cls");	//Displaying the selected record
		UI(1);
		printf("\272%-4s%-15s%-15s%-22s%-21s\272\n", "", "Car Number", "Colour", "Manufacturer", "Purchase Date");
		UI(3);
		for(i=0; i<n; i++)	if(in==a[i].n)	printf("\272%-4s%-15d%-15s%-22s%-21d\272\n", "", a[i].n, a[i].c, a[i].m, a[i].d);
		UI(4);
		
		free(a);
		return in;
	}
}

int search_display_scan() {	//"search_display_scan" is the fuction called for displaying the search menu and getting the user's input 
	int in;
	char temp[5];
	
	UI(1);
	printf("%-32sSearch Menu:%-34s\272\n", "\272", "");
	UI(3);
	printf("\272  Choose one of the following:%-47s\272\n", "");
	printf("\272%-4s%-73s\272\n", "", "1. By number");
	printf("\272%-4s%-73s\272\n", "", "2. By colour");
	printf("\272%-4s%-73s\272\n", "", "3. By manufacturer");
	printf("\272%-4s%-73s\272\n", "", "4. By manufacturing date");
	printf("\272%-4s%-73s\272\n", "", "0. Return to basic menu");
	UI(4);

	do {	//Input
		printf("\n> ");
		scanf("%s", temp);
		in = atof(temp);
		if(temp[0]!='\60' && in!=1 && in!=2 && in!=3 && in!=4)		UI(6);
	}while(temp[0]!='\60' && in!=1 && in!=2 && in!=3 && in!=4);
	
	return in;
}

void search_number(car x[], int size) {	//"search_number" is the fuction called for searching by number
	int i, in, c=0;
	char cin, temp[5];
	
	printf("%-28s5.1. Search - By Number:%-26s\272\n", "\272", "");
	UI(2);
	printf("%-5sAll the car numbers:%-53s\272\n", "\272", "");
	UI(4);
	for(i=0; i<size; i++)	printf("\t%d\t", x[i].n);	//printing all the numbers
	
	do {	//getting the users input
		printf("\n\n> ");
		scanf(" %c%s", &cin, temp);
		in=atof(temp);
		if(temp[0]=='\60' || in<1000 || in>9999)	UI(6);
	}while(temp[0]=='\60' || in<1000 || in>9999);
	system("cls");
	
	switch(cin) {	//Depending the user's choice, we show the results
		case '=': {	//For =
			for(i=0; i<size; i++) {
				if(x[i].n==in) {	//If true, then it is the record we are looking for
					UI(1);	//Displaying the record
					printf("\272%-4s%-15s%-15s%-22s%-21s\272\n", "", "Car Number", "Colour", "Manufacturer", "Purchase Date");
					UI(3);
					printf("\272%-4s%-15d%-15s%-22s%-21d\272\n", "", x[i].n, x[i].c, x[i].m, x[i].d);
							
					c=1;	break;
				}
			}
			break;
			system("pause");
		}
		case '>': {	//For >
			for(i=0; i<size; i++) {
				if(x[i].n>in) {	//If true, then it fits the user's choice
					if(c==0) {	//This is to display the top part only once
						UI(1);
						printf("\272%-4s%-15s%-15s%-22s%-21s\272\n", "", "Car Number", "Colour", "Manufacturer", "Purchase Date");
						UI(3);
					}
					printf("\272%-4s%-15d%-15s%-22s%-21d\272\n", "", x[i].n, x[i].c, x[i].m, x[i].d);	//Displaying the record(s)
					
					c=1;
				}	
			}
			break;
		}
		case '<': {	//For <
			for(i=0; i<size; i++) {
				if(x[i].n<in) {	//If true, then it fits the user's choice
					if(c==0) {	//This is to display the top part only once
						UI(1);
						printf("\272%-4s%-15s%-15s%-22s%-21s\272\n", "", "Car Number", "Colour", "Manufacturer", "Purchase Date");
						UI(3);
					}
					printf("\272%-4s%-15d%-15s%-22s%-21d\272\n", "", x[i].n, x[i].c, x[i].m, x[i].d);	//Displaying the record(s)
					
					c=1;
				}
			}
			break;
		}
	}
	if(c==0)	UI(8);	//If nothing was found, we show the appropriate message
	else	UI(4);	//This is to display the bottom part only once
}

void search_colour(car x[], int size) {	//"search_colour" is the fuction called for searching by colour
	int i, n=0, c, j;
	char in[25], temp[size][25];
	
	printf("%-29s5.2. Search - By Colour:%-25s\272\n", "\272", "");
	UI(2);
	printf("%-5sAll the car colours:%-53s\272\n", "\272", "");
	UI(4);
	for(i=0; i<size; i++) {
		strcpy(temp[i], x[i].c);
		for(j=0, c=0; j<i; j++)		if(!strcmp(temp[i], x[j].c))	c=1;	//making sure the colour we are about to print, is not already printed
		if(c==0)	printf("%-10s%-10s", "", temp[i]);	//printing all the colours
	}
	
	printf("\n\n(Not case sensitive) > ");	//getting the users input
	scanf("%s", in);
	system("cls");
	
	n = strlen(in);
	for(i=0; in[i]; i++)	in[i] = toupper(in[i]);	//We make sure that the string is capital letters
	for(i=0, c=0; i<size; i++)	if(!(strncmp(x[i].c, in, n))) {
		if(c==0) {	//This is to display the top part only once
			UI(1);
			printf("\272%-4s%-15s%-15s%-22s%-21s\272\n", "", "Car Number", "Colour", "Manufacturer", "Purchase Date");
			UI(3);
		}
		printf("\272%-4s%-15d%-15s%-22s%-21d\272\n", "", x[i].n, x[i].c, x[i].m, x[i].d);	//Displaying the record(s)
		
		c=1;	
	}
	
	if(c==0)	UI(8);	//If nothing was found, we show the appropriate message
	else UI(4);	//This is to display the bottom part only once
}

void search_manufacturer(car x[], int size) {	//"search_manufacturer" is the fuction called for searching by manufacturer
	int i, n, c, j;
	char in[25], temp[size][25];
	
	printf("%-26s5.3. Search - By Manufacturer:%-22s\272\n", "\272", "");
	UI(2);
	printf("%-5sAll the car manufacturers:%-47s\272\n", "\272", "");
	UI(4);
	for(i=0; i<size; i++) {
		strcpy(temp[i], x[i].m);
		for(j=0, c=0; j<i; j++)		if(!strcmp(temp[i], x[j].m))	c=1;	//making sure the colour we are about to print, is not already printed
		if(c==0)	printf("%-10s%-10s", "", temp[i]);	//printing all the manufacturers
	}
	
	printf("\n\n(Not case sensitive) > ");	//getting the users input
	scanf("%s", in);
	system("cls");
	
	n = strlen(in);
	for(i=0; in[i]; i++)	in[i] = toupper(in[i]);	//We make sure that the string is capital letters
	for(i=0, c=0; i<size; i++)	if(!(strncmp(x[i].m, in, n))) {
		if(c==0) {	//This is to display the top part only once
			UI(1);
			printf("\272%-4s%-15s%-15s%-22s%-21s\272\n", "", "Car Number", "Colour", "Manufacturer", "Purchase Date");
			UI(3);
		}
		printf("\272%-4s%-15d%-15s%-22s%-21d\272\n", "", x[i].n, x[i].c, x[i].m, x[i].d);	//Displaying the record(s)
		
		c=1;	
	}
	
	if(c==0)	UI(8);	//If nothing was found, we show the appropriate message
	else UI(4);	//This is to display the bottom part only once
}

void search_date(car x[], int size) {	//"search_date" is the fuction called for searching by date
	int i, in, c=0, j;
	char cin, temp[5];
	
	printf("%-28s5.4. Search - By Date:%-28s\272\n", "\272", "");
	UI(2);
	printf("%-5sAll the car manufacture dates:%-43s\272\n", "\272", "");
	UI(4);
	for(i=0; i<size; i++) {
		for(j=0, c=0; j<i; j++)		if(x[i].d==x[j].d)	c=1;
		if(c==0)	printf("\t%d\t", x[i].d);	//printing all the numbers
	}
	
	do {	//getting the users input
		printf("\n\n> ");
		scanf(" %c%s", &cin, temp);
		in=atof(temp);
		if(temp[0]=='\60' || in<1000 || in>9999)	UI(6);
	}while(temp[0]=='\60' || in<1000 || in>9999);
	system("cls");
	
	switch(cin) {	//Depending the user's choice, we show the results
		case '=': {	//For =
			for(i=0; i<size; i++) {
				if(x[i].d==in) {	//If true, then it is the record we are looking for
					UI(1);	//Displaying the record
					printf("\272%-4s%-15s%-15s%-22s%-21s\272\n", "", "Car Number", "Colour", "Manufacturer", "Purchase Date");
					UI(3);
					printf("\272%-4s%-15d%-15s%-22s%-21d\272\n", "", x[i].n, x[i].c, x[i].m, x[i].d);
							
					c=1;	break;
				}
			}
			break;
		}
		case '>': {	//For >
			for(i=0, c=0; i<size; i++) {
				if(x[i].d>in) {	//If true, then it fits the user's choice
					if(c==0) {	
						UI(1);
						printf("\272%-4s%-15s%-15s%-22s%-21s\272\n", "", "Car Number", "Colour", "Manufacturer", "Purchase Date");
						UI(3);
					}
					printf("\272%-4s%-15d%-15s%-22s%-21d\272\n", "", x[i].n, x[i].c, x[i].m, x[i].d);	//Displaying the record(s)
					
					c=1;
				}	
			}
			break;
		}
		case '<': {	//For <
			for(i=0, c=0; i<size; i++) {
				if(x[i].d<in) {	//If true, then it fits the user's choice
					if(c==0) {
						UI(1);
						printf("\272%-4s%-15s%-15s%-22s%-21s\272\n", "", "Car Number", "Colour", "Manufacturer", "Purchase Date");
						UI(3);
					}
					printf("\272%-4s%-15d%-15s%-22s%-21d\272\n", "", x[i].n, x[i].c, x[i].m, x[i].d);	//Displaying the record(s)
					
					c=1;
				}
			}
			break;
		}
	}
	if(c==0)	UI(8);	//If nothing was found, we show the appropriate message
	else	UI(4);	//This is to display the bottom part only once
}

void search_main() {	//"search_main" is the 'main' for search(5)
	int in, i, n=0;
	FILE *fl;
	char temp[100];
	car *a;
	
	if(!(fl = fopen("cars.txt", "r")))	UI(7);
	else {
		n = lines();	//Getting the txt's lines
  		a = malloc(n*sizeof(car));	//Creating an equal array
   		fclose(fl);
   		
   		fl = fopen("cars.txt", "r");
		for(i=0; i<n; i++) 	fscanf(fl, "%d %s %s %d", &a[i].n, a[i].c, a[i].m, &a[i].d);	//Loading the txt in RAM
		fclose(fl);
	}
		
	do {
		in = search_display_scan();	//Calling the interface and getting the user's input
		system("cls");
		
		if(in!=0)	UI(1);
		switch(in) {	//Depending the user's choice we call the appropriate function
			case 1: {
				search_number(a, n);
				
				break;
			}
			case 2: {
				search_colour(a, n);
				
				break;
			}
			case 3: {
				search_manufacturer(a, n);
				
				break;
			}
			case 4: {
				search_date(a, n);
				
				break;
			}	
		}
		if(in!=0)	UI(5);
	}while(in!=0);
	
	if(fl = fopen("cars.txt", "r")) {	free(a);	fclose(fl);	}
}

void update(int choice, car x, int t) {	//"update" is the fuction called to update the txt with all the new details
	int i, j=0, tmp, c=0;
	FILE *fl;
	char temp[100];
	car *a;
	
	if(!(fl = fopen("cars.txt", "r")) && choice!=1)	UI(7);	//If there is an error opening the txt, we show the appropriate message
	else if(!(fl = fopen("cars.txt", "r")) && choice==1) {	//If there is an error opening the txt, but we have a new record, we create a new txt
		fl = fopen("cars.txt", "w");
		fprintf(fl, "%d %s %s %d", x.n, x.c, x.m, x.d);
		fclose(fl);
	}
	else {	//else either we delete a record or modify one
		for(j=0; !feof(fl); j++)	fgets(temp, 100, fl);	//Getting the lines of the txt
  		a = malloc(j*sizeof(car));	//Creating an equal array
  		tmp = strlen(temp);	//Getting the lenght of the last line of the txt, so we can see if there is \n, or not
  		rewind(fl);	//Setting the cursor back to the top of the txt
  		
		if(choice==1) {	//If choice is 1, then we have a new record
			fclose(fl);
			
			fl = fopen("cars.txt", "a");
			
			if(temp[tmp-1]!='\n')	fprintf(fl, "\n");	//If we need a \n, we fprintf one
			fprintf(fl, "%d %s %s %d", x.n, x.c, x.m, x.d);	//printing the new record
		}
		else {	//For delete and modify
			for(i=0; i<j; i++) 	fscanf(fl, "%d %s %s %d", &a[i].n, a[i].c, a[i].m, &a[i].d);	//Loading the txt to RAM
			fclose(fl);
			fl = fopen("cars.txt", "w");
			
			switch(choice) {
				case 2: {	//For delete
					for(i=0; i<j; i++) {
						if(!(t == a[i].n)) {	//If it is the deleted record, we skip it
							if(c==0)	{	fprintf(fl, "%d %s %s %d", a[i].n, a[i].c, a[i].m, a[i].d);	c=1;	}
							else	fprintf(fl, "\n%d %s %s %d", a[i].n, a[i].c, a[i].m, a[i].d);
						}
					}
					
					break;
				}
				case 3: {	//For modify
					for(i=0; i<j; i++) {
						if(!(t == a[i].n)) {
							if(c==0)	{	fprintf(fl, "%d %s %s %d", a[i].n, a[i].c, a[i].m, a[i].d);	c=1;	}
							else	fprintf(fl, "\n%d %s %s %d", a[i].n, a[i].c, a[i].m, a[i].d);
						}
						else {	//If it is the modified record, we fprintf the new details
							if(c==0)	{	fprintf(fl, "%d %s %s %d", x.n, x.c, x.m, x.d);	c=1;	}
							else	fprintf(fl, "\n%d %s %s %d", x.n, x.c, x.m, x.d);
						}
					}
					
					break;
				}
			}
		}
		
		fclose(fl);
	}
}

int main () {
	int in, i, temp=-1;
	car a = {0};
	
	do {
		in = display_scan();		//Calling "display_scan" to get the users choice
		system("cls");
		
		switch(in) {
			case 1: {
				print();
				UI(5);
				
				break;
			}
			case 2: {				//"new_record" is also used for modifying a record
				UI(1);
				printf("%-32s2. New record:%-32s\272\n", "\272", "");
				UI(4);
				a = new_record(1, 0);	//We save the input in a "car" variable called "a"
				temp=-1;
				system("cls");
				
				break;
			}
			case 3: {				//"bubblesort_scan" is also used for modifying a record
				UI(1);
				printf("%-32s3. Delete a record:%-27s\272\n", "\272", "");
				UI(2);
				temp = bubblesort_scan();	//We save the number plate in a "int" variable called "temp"
				UI(5);
				
				break;
			}
			case 4: {				//To modify a record we use the same fuction as delete(3), and new record(2)
				UI(1);
				printf("%-32s4. Modify a record:%-27s\272\n", "\272", "");
				UI(2);
				temp = bubblesort_scan();	//We have to save both the number plate of the car we modified
				a = new_record(2, temp);		//and the new details
				system("cls");
				
				break;
			}
			case 5: {
				search_main();		//Calls "search_main", so user can choose the exact way to search
				system("cls");
				
				break;
			}	
			case 6: {
				if(a.n == 0 && temp==-1) {	//Check to see if user has made any changes
						for(i=0; i<94; i++)		printf("\260");
						printf("Error: choose 2/3/4, and then update the database...");
						for(i=0; i<94; i++)		printf("\260");
						printf("\n\n");
				}
				else if(temp==-1)	update(1, a, 0);	//Calling fuction "update", to add a new record
				else if(a.n==0)		update(2, a, temp);	//Calling fuction "update", to delete a record
				else	update(3, a, temp);	//Calling fuction "update", to modify a record
				
				if(!(a.n == 0 && temp==-1))	{	//Printing a success message
						for(i=0; i<108; i++)		printf("\260");
						printf("Updating Database...");
						for(i=0; i<112; i++)		printf("\260");
						printf("\n\n");
						a.n=0;	temp=-1;	
				}
				UI(5);
				
				break;
			}
		}
	}while(in!=0);					//If user selects to terminate the program(0), then we escape the infite loop
	
	for(i=0; i<112; i++)		printf("\260");	//Printing a "terminating" success message
	printf("Terminating...");
	for(i=0; i<114; i++)		printf("\260");
	
	printf("\n\n");
	system("pause");
	return 0;
}
