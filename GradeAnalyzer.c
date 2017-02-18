//Include necessary libraries
#include <stdio.h>
#include <math.h> // new
#include <string.h>

//Declaring constants
#define MAX_CLASS_SIZE  100
#define MAX_NAME_SIZE   40
#define MAX_LETTER_SIZE 3
#define W 30
#define Q 15
#define T 20
#define P 15
#define E 20

//List all prototypes
void computeTotal(float w[], float q[], float t[], float p[], float e[], float total[]);
void computeGrades(float total[], char grade[][MAX_LETTER_SIZE]);
void display(char name[][MAX_NAME_SIZE], float w[], float q[], float t[], float p[], float e[], float total[], char grade[][MAX_LETTER_SIZE]);
void displayReport(char grade[][MAX_LETTER_SIZE]);
void displayDistribution (float total[], char grade[][MAX_LETTER_SIZE]);
int search(char name[][MAX_NAME_SIZE], char specificName[]);
int read (char filename[], char name[][MAX_NAME_SIZE], float w[], float q[], float t[], float p[], float e[]);
void write(char filename2[], char name[][MAX_NAME_SIZE], float w[], float q[], float t[],float p[],float e[],float total[], char grade[][MAX_LETTER_SIZE]);

int main () {

    //Declare and define variables
    float w[MAX_CLASS_SIZE];
    float q[MAX_CLASS_SIZE];
    float t[MAX_CLASS_SIZE];
    float p[MAX_CLASS_SIZE];
    float e[MAX_CLASS_SIZE];
    float total[MAX_CLASS_SIZE];
    char grade[MAX_CLASS_SIZE][MAX_LETTER_SIZE];
    char name[MAX_CLASS_SIZE][MAX_NAME_SIZE];
    char specificName[MAX_NAME_SIZE];
    int found;
    char filename[MAX_NAME_SIZE] = {"student.dat"};
    char filename2[MAX_NAME_SIZE] = {"analysis.dat"};
    int ReadInput;
    int loop = 0;

    //calls read functiont to add data into arrays passing the required arguments
    ReadInput=read(filename,name,w,q,t,p,e);

    if(ReadInput == 0) {
    	//Calling the computeTotal function and sending the required values
    	computeTotal(w, q, t, p, e, total);

    	//Calling the computeGrades function and sending the required values
    	computeGrades(total, grade);

    	//Calling the display function
    	display(name, w, q, t, p, e, total, grade);

    	//Print an empty line for beauty
    	printf("\n");

       //Calling the display report function;
    	displayReport(grade);

    	//Print an empty line for beauty
    	printf("\n");

    	//Calling the displayDistribuition function
    	displayDistribution(total, grade);

    	//Print an empty line for beauty
    	printf("\n");


		while(loop == 0) {
    		//Ask the user to input a valid name
       		printf("Please enter the student's name you are looking for, or 'close' to close the program: ");

       		//Gets input from user
       		scanf(" %[^\n]", specificName);

       		// If user inputs 'close' the program will terminate
       		if(strcmp(specificName, "close") == 0) {
       			loop = 1;
       			break;
       		}

       		//Calls the search function, passes the needed values and assign the returned value to a variable
       		found=search(name, specificName);

       		//Prints the name of the student found and its grade or an error if the ftudent is not found
       		if (found != -1) {
        		printf("%s got %s\n", name[found], grade[found]);
       		}
       		else {
        		printf("Error, student not found!\n");
       		}

       		memset(specificName, '\0', MAX_NAME_SIZE);
       		found = -1;
		}

       		//Calling the write function to generate the file
		write(filename2, name, w, q, t, p, e, total, grade);

    } else if(ReadInput==-1)
		printf("Error reading the file!\n");

    return 0;
   }

    //This function calculates the total mark of each student
    void computeTotal(float w[], float q[], float t[], float p[], float e[], float total[]) {

        //declare counter
        int i;

        //This loop calculates the total grade for each student
        for (i=0; i<MAX_CLASS_SIZE; i++) {
            total[i] = (w[i]*0.30) + (q[i]*0.15) + (t[i]*0.20) + (p[i]*0.15) + (e[i]*0.20);
        }

    }

    //This function calculates the letter grades of each student
    void computeGrades(float total[], char grade[][MAX_LETTER_SIZE]) {
        int i;

        for (i=0; i<MAX_CLASS_SIZE; i++) {
            if (total[i]>89 && total[i]<=100) {
                strncpy(grade[i], "A+", MAX_LETTER_SIZE);
            }
            if (total[i]>79 && total[i]<=89) {
                strncpy(grade[i], "A", MAX_LETTER_SIZE);
            }
            if (total[i]>74 && total[i]<=79) {
                strncpy(grade[i], "B+", MAX_LETTER_SIZE);
            }
            if (total[i]>70 && total[i]<=74) {
                strncpy(grade[i], "B", MAX_LETTER_SIZE);
            }
            if (total[i]>65 && total[i]<=70) {
                strncpy(grade[i], "C+", MAX_LETTER_SIZE);
            }
            if (total[i]>59 && total[i]<=65) {
                strncpy(grade[i], "C", MAX_LETTER_SIZE);
            }
            if (total[i]>=55 && total[i]<=59) {
                strncpy(grade[i], "D+", MAX_LETTER_SIZE);
            }
            if (total[i]>=50 && total[i]<55) {
                strncpy(grade[i], "D", MAX_LETTER_SIZE);
            }
            if (total[i]<50) {
                strncpy(grade[i], "F", MAX_LETTER_SIZE);
            }
        }
    }

    //This function displays all the data in a form of table
    void display(char name[][MAX_NAME_SIZE], float w[], float q[], float t[], float p[], float e[], float total[], char grade[][MAX_LETTER_SIZE]) {

		int i;

        //This prints the nme of the table
        printf("                                       Students                                  \n\n");

        //This prints a general table format
        printf("Sudent Name\t\tW(30%%)\tQ(15%%)\tT(20%%)\tP(15%%)\tE(20%%)\tTOTAL(100%%)\tGRADE\n\n");

        //This loop prints the student names
        for (i=0; i<MAX_CLASS_SIZE; i++) {
        	printf("%-17s\t%3.0f\t%3.0f\t%3.0f\t%3.0f\t%3.0f\t %3.2f\t\t %-3s\n", name[i], w[i], q[i], t[i], p[i], e[i], total[i], grade[i]);
        }

    }

    void displayReport(char grade[][MAX_LETTER_SIZE]) {

        //Declare variables
        int i = 0;
        int A=0, a=0, B=0, b=0, C=0, c=0, D=0, d=0, F=0;
        const char sstar[2] = "*";
        char star[9][30] = {"", "", "", "", "", "", "", "", ""};
        char letterg[9][3] = {"A+", "A", "B+", "B", "C+", "C", "D+", "D", "F"};
        float bperecentage = (1.0f/100.0f)*100.0f;
        float percentage[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

        // This loops though the grade array and it counts the number of students who got the same mark,
        //  The number of stars to display and the percentage of the people who had the same mark
        for (i = 0; i < MAX_CLASS_SIZE; i++) {
            if (strcmp(grade[i], "A+") == 0) {
            	A++;
                strcat(star[0], sstar);
                percentage[0] = percentage[0] + bperecentage;
            }
            else if (strcmp(grade[i], "A") == 0) {
                a++;
                strcat(star[1], sstar);
                percentage[1] = percentage[1] + bperecentage;
            }
            else if (strcmp(grade[i], "B+") == 0) {
                B++;
                strcat(star[2], sstar);
                percentage[2] = percentage[2] + bperecentage;
            }
            else if (strcmp(grade[i], "B") == 0) {
                b++;
                strcat(star[3], sstar);
                percentage[3] = percentage[3] + bperecentage;
            }
            else if (strcmp(grade[i], "C+") == 0) {
                C++;
                strcat(star[4], sstar);
                percentage[4] = percentage[4] + bperecentage;
            }
            else if (strcmp(grade[i], "C") == 0) {
            	c++;
                strcat(star[5], sstar);
                percentage[5] = percentage[5] + bperecentage;
            }
            else if (strcmp(grade[i], "D+") == 0) {
            	D++;
                strcat(star[6], sstar);
                percentage[6] = percentage[6] + bperecentage;
            }
            else if (strcmp(grade[i], "D") == 0) {
                d++;
                strcat(star[7], sstar);
                percentage[7] = percentage[7] + bperecentage;
            }
            else {
                F++;
                strcat(star[8], sstar);
                percentage[8] = percentage[8] + bperecentage;
                }
        }

        //This loop in needed to round the persentages
        for (i = 0; i < 9; i++) {
        	roundf(percentage[i]);
        }

        //This prints the title
        printf("                     REPORT                          \n");

        //This prints all the collected data in this function
        printf("BTP100                                 Class size:%d\n", MAX_CLASS_SIZE);
        printf("%-2s %s                                 %d (%.0f%%)\n", letterg[0], star[0], A, percentage[0]);
        printf("%-2s %s                                 %d (%.0f%%)\n", letterg[1], star[1], a, percentage[1]);
		printf("%-2s %s                            %d (%.0f%%)\n", letterg[2], star[2], B, percentage[2]);
		printf("%-2s %s                             %d (%.0f%%)\n", letterg[3], star[3], b, percentage[3]);
		printf("%-2s %s                      %d (%.0f%%)\n", letterg[4], star[4], C, percentage[4]);
		printf("%-2s %s            %d (%.0f%%)\n", letterg[5], star[5], c, percentage[5]);
		printf("%-2s %s                        %d (%.0f%%)\n", letterg[6], star[6], D, percentage[6]);
		printf("%-2s %s                      %d (%.0f%%)\n", letterg[7], star[7], d, percentage[7]);
		printf("%-2s %s                     %d (%.0f%%)\n", letterg[8], star[8], F, percentage[8]);
    }

    void displayDistribution (float total[], char grade[][MAX_LETTER_SIZE]) {

        //Declare local variables
        int i, j, x=0;
        float temp;
        int A=0, a=0, B=0, b=0, C=0, c=0, D=0, d=0, F=0;
        float bperecentage = (1.0f/100.0f)*100.0f;
        float percentage[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

        // This loops though the grade array and it counts the number of students who got the same mark,
        //	The number of stars to display and the percentage of the people who had the same mark
        for (i = 0; i < MAX_CLASS_SIZE; i++) {
            if (strcmp(grade[i], "A+") == 0) {
            	A++;
                percentage[0] = percentage[0] + bperecentage;
			}
			else if (strcmp(grade[i], "A") == 0) {
				a++;
                percentage[1] = percentage[1] + bperecentage;
            }
            else if (strcmp(grade[i], "B+") == 0) {
                B++;
                percentage[2] = percentage[2] + bperecentage;
            }
            else if (strcmp(grade[i], "B") == 0) {
                b++;
                percentage[3] = percentage[3] + bperecentage;
            }
            else if (strcmp(grade[i], "C+") == 0) {
                C++;
                percentage[4] = percentage[4] + bperecentage;
            }
            else if (strcmp(grade[i], "C") == 0) {
                c++;
                percentage[5] = percentage[5] + bperecentage;
            }
            else if (strcmp(grade[i], "D+") == 0) {
                D++;
                percentage[6] = percentage[6] + bperecentage;
            }
            else if (strcmp(grade[i], "D") == 0) {
                d++;
                percentage[7] = percentage[7] + bperecentage;
            }
            else {
            	F++;
                percentage[8] = percentage[8] + bperecentage;
            }
        }

        //print table title
        printf("                                                 DISTRIBUTION TABLE                                                                \n");

        //Display all the data calculated in this functin
        printf("GRADE   TOTAL MARKS                                                                                   COUNT  PERCENTAGE OF CLASS(%%)\n");
        printf("=====   ======================                                                                        =====  ======================\n");
        printf("A+      ");
        for (i = 0; i<MAX_CLASS_SIZE; i++) {
            if (strcmp(grade[i], "A+") == 0)
                printf("%.2f ", total[i]);
        }
        printf("                                                                              %d    %.2f\n", A,percentage[0]);
        printf("A       ");
        for (i = 0; i<MAX_CLASS_SIZE; i++) {
            if (strcmp(grade[i], "A") == 0)
                printf("%.2f ", total[i]);
        }
        printf("                                                                              %d    %.2f\n", a,percentage[1]);
        printf("B+      ");
        for (i = 0; i<MAX_CLASS_SIZE; i++) {
            if (strcmp(grade[i], "B+") == 0)
                printf("%.2f ", total[i]);
        }
        printf("                                                %d    %.2f\n", B,percentage[2]);
        printf("B       ");
        for (i = 0; i<MAX_CLASS_SIZE; i++) {
            if (strcmp(grade[i], "B") == 0)
                printf("%.2f ", total[i]);
        }
        printf("                                                      %d    %.2f\n", b,percentage[3]);
		printf("C+      ");
        for (i = 0; i<MAX_CLASS_SIZE; i++) {
            if (strcmp(grade[i], "C+") == 0)
                printf("%.2f ", total[i]);
        }
        printf("           %d    %.2f\n", C,percentage[4]);
        printf("C       ");
        for (i = 0; i<MAX_CLASS_SIZE; i++) {
            if (strcmp(grade[i], "C") == 0) {
                printf("%.2f ", total[i]);
                x++;
            }
            if (x == 15)
                printf("\n        ");
        }
        printf("                                         %d    %.2f\n", c,percentage[5]);
		printf("D+      ");
        for (i = 0; i<MAX_CLASS_SIZE; i++) {
            if (strcmp(grade[i], "D+") == 0)
                printf("%.2f ", total[i]);
        }
        printf("                       %d    %.2f\n", d,percentage[7]);
        printf("D       ");
        for (i = 0; i<MAX_CLASS_SIZE; i++) {
            if (strcmp(grade[i], "D") == 0)
                printf("%.2f ", total[i]);
        }
        printf("           %d    %.2f\n", d,percentage[7]);
		printf("F       ");
        for (i = 0; i<MAX_CLASS_SIZE; i++) {
            if (strcmp(grade[i], "F") == 0)
                printf("%.2f ", total[i]);
        }
        printf("     %d    %.2f\n", F,percentage[8]);
		printf("\n");

        //Sort the Total array in ascendig order using Bubble Sort algorithm
        for (i = MAX_CLASS_SIZE - 1; i > 0; i--) {
            for (j = 0; j < i; j++) {
                if (total[j]>total[j+1]) {
                    temp = total[j];
                    total[j] = total[j+1];
                    total[j+1] = temp;
                }
            }
        }

        //Create three variables for highest, lowest and avarage marks and assign them their valuse
        float Highest_Mark = total[MAX_CLASS_SIZE-1];
        float Lowest_Mark = total[0];
        float Avarage_Mark = (Highest_Mark + Lowest_Mark) / 2;

		//Prints the class highest, lower and avarage mark
		printf("CLASS SIZE: %d\n", MAX_CLASS_SIZE);
		printf("HIGHEST MARK: %.2f        AVARAGE: %.2f           LOWEST MARK: %.2f\n", Highest_Mark, Avarage_Mark, Lowest_Mark);

    }

    //This funtion searches for a particular student in the list and returns its index or -1 if it fails to find a student
    int search(char name[][MAX_NAME_SIZE], char specificName[]) {

        //declare internal variables
        int i;
        int found = -1;

        //This loop looks for a student with the same name in the name list
        for (i = 0; i < MAX_CLASS_SIZE; i++) {
            if (strcmp(name[i], specificName) == 0) {
                found = i;
                break;
            }
        }
        return found;
    }

    int read (char filename[], char name[][MAX_NAME_SIZE], float w[], float q[], float t[], float p[], float e[]) {
        //Open the file for reading
        FILE *fp = fopen(filename, "r");

        //Declare local variables
        int result = -1;
        int i;

        //If the file is not NULL it loads
        if(fp != NULL) {
        while(!feof(fp))//loop until end of file
		{
            //loop for the number of sudents and stores the data where necessary
            for(i=0;i<MAX_CLASS_SIZE;i++){
                fscanf(fp,"%[^,],%f,%f,%f,%f,%f\n",name[i],&w[i],&q[i],&t[i],&p[i],&e[i]);
            }
            result = 0; //retruns 0 because successful
        }
        fclose(fp);//closes the file
    }
        return result;
    }

    void write(char filename2[], char name[][MAX_NAME_SIZE], float w[], float q[], float t[],float p[],float e[],float total[], char grade[][MAX_LETTER_SIZE]) {

	//load the second file
	FILE *fp = fopen(filename2,"w+");

	//load if the file is open
    if(fp!=NULL)
	{
        int i;
		//prints the table
        fprintf(fp,"                                        Table 1                                    \n");
        fprintf(fp,"  Student Name         W(30%%)   Q(15%%)   T(20%%)   P(15%%)   E(20%%)   TOTAL   GRADE \n");
        for(i=0;i<MAX_CLASS_SIZE;i++)//loop to print all the values
		{
            fprintf(fp,"  %-18s   %-6.0f   %-6.0f   %-6.0f   %-6.0f   %-6.0f   %-6.2f    %-4s  \n", name[i],w[i],q[i],t[i],p[i],e[i],total[i],grade[i]);
        }

        //close the file
        fclose(fp);
    }
}
