#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define MAX  1000

double data[MAX];
double data_sorted[MAX];
double Time[MAX];
int test_times ;

// equations variables
double m ;   // y = mx+c;
double c ;
double m_integrated ;   // y`= m/2 * x*x  + c * x ;
double c_integreted;
double m_differentiated;
double c_differentiated;   // y „ ›«÷·Â  = m ;

/*find_median function gets the median value of a set of data (data )*/
double find_median();

/*find_mean function gets the mean value of a set of data (data )*/
double find_mean();

/*find_range function gets the range of a set of data (data )*/
double find_range();

/*find_stdev function gets the standard deviation of a set of data (data ) ,
 * it requires the mean value to return the stdev*/
double find_stdev(double* data , int test_times , double mean);

/*bestApproximate_Equ function find the constants of the equations to the set of data *
 * i/p the data from file
 * 		address to the m and c to function y = m  + c ;*/
void bestApproximate_Equ( double* m , double* c );

/*Equ_integral return the constants of the equations being integreted
 * it takes values m and c from the function return the m and c to the integreted function */
void Equ_integral (double m , double c , double * m_integrated , double *c_integreted );

/*Equ_differential return the constants of the equations being differentianted
 * it takes values m and c from the function return the m and c to the differentiated function */
void Equ_differential (double m , double c , double * m_differentiated , double *c_differentiated );

/*this function  Get_data takes the file name from the user
 * check if file name is valid
 * aquire the data from the file
 * store the data to the global variables time and data and test_times*/
void Get_data ( void );

/*this function sort_data makes sure to sorts the data to find values with it */
void sort_data ( );

/* this function Produce_File stores the analytics data to text file */
void Produce_File (double mean , double median , double range  , double stdev);

/* this function present a structure menu to choise from on the consle */
void strcture_menu (double mean , double median , double range  , double stdev);


/*this function opens gnuplot program and plot data to it */
void plotResults();

///////////////// helping functions ///////////////////////////////

/*find_largest function is used to find the largest number in an array of unsorted data  *
 * i/p data : array of data to search in
 *      x : number of element*/
double find_largest(double* data , int test_times);

/*find_smallest function is used to find the smallest number in an array of unsorted data  *
 * i/p data : array of data to search in
 *      x : number of element*/
double find_smallest(double* data ,  int test_times);

/*searchforExt function is used search for the string ".txt" and if it does not exist it add it to the file name  */
void searchforExt(char filename[]);

/*Get_Filename function is used to ask the user to enter the file name containing data  */
 void Get_Filename(char filename[] );

 /*clrscr function is used to clear the program screen   */
void clrscr();

/*delay function is used to delay the program in a certain point in seconds
 * i/p   number_of_seconds : number_of_seconds to be delayed */
void delay_sec(int number_of_seconds) ;

/*selection_sort function sort the array of data using the bubble sorting technique
 * i/p   array : the array of the data will be sorted in
 *         test_times :number of elements */
void selection_sort (double *data_sorted , int test_times );

/*copy_data function copys the entered data to be sorted in another array to keep the first data simple untouched
 * i/p   data_sorted : the array of the data will be sorted in
 *        data : the array of smpled data
 *         test_times :number of elements */
void copy_data (double *data_sorted ,double*data , int test_times );

/* convert_str_double function is used to convert string value nto a double value
 * i/p string
 * o/p double value to the strring */
double convert_str_double ( char str[] );

/* this function aquires the file directory from the user
void Get_dir (char dir []);*/




int main(int argc, char **argv)
{
	Get_data ();
	sort_data (  );
	double median = find_median();
	double mean = find_mean();
	double range =find_range();
	double stdev = find_stdev( data ,  test_times ,  mean);
	bestApproximate_Equ(& m , & c );
	Equ_integral ( m , c , &m_integrated ,  &c_integreted );
	Equ_differential ( m , c ,& m_differentiated ,&c_differentiated );
	Produce_File ( mean ,  median ,  range  ,  stdev);
	strcture_menu( mean ,  median ,  range  ,  stdev);
	return 0;
}




double find_median(){
	    double median=0;
	    // if number of elements are even
	    if(test_times%2 == 0)
	        median = (data_sorted[(test_times-1)/2] + data_sorted[test_times/2])/2.0;
	    // if number of elements are odd
	    else
	        median = data_sorted[test_times/2];
return median;}

double find_mean(){
    double ret = 0;
    double sum = 0 ;
     int i;
	 /* sum all data  */
    for(i = 0 ; i < test_times ; i++)
        {sum+=*(data+i);}
		/* devide the sum by its numbers */
    ret = sum / (double)test_times ;
return ret;}

double find_range(){
    double ret = 0;
    double gratest = find_largest(data , test_times);
    double smallest = find_smallest(data , test_times);
   ret = gratest - smallest ;   /* range = largest - smallest  */
return ret;}

void bestApproximate_Equ(double* m , double* c )
{   double *y = data ;
    double *x = Time ;
    int i;
    double  sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;
    for (i = 0; i < test_times; i++) {
		/* sum all x values*/
        sum_x += x[i];
		/* sum all y values*/
        sum_y += y[i];
		/* sum all x*y values*/
        sum_xy += x[i] * y[i];
		/* sum all x*x values*/
        sum_x2 += (x[i] * x[i]);
    }
    * m = (test_times * sum_xy - sum_x * sum_y) / (test_times * sum_x2 - (sum_x * sum_x));  // m equation
    * c = ((sum_y - ( (*m) * sum_x)) / test_times); 										// c equation
}

void Equ_integral (double m , double c , double * m_integrated , double *c_integreted )
{
    * m_integrated = m/2.0 ;   /*integration of m = m/2*/
    *c_integreted = c;   		/*integration of c = c*/
}

void Equ_differential (double m , double c , double * m_differentiated , double *c_differentiated )
{
    * m_differentiated = m ;    	/*differential m = m */
    *c_differentiated = 0;   		/*differential c = 0 */
}

void Get_data ( void ){
    char s_1[20];
    char s_2[20];
    char filename[100] ;
	//char file_dir [2000];
	//Get_dir(file_dir);
    Get_Filename(filename );
    FILE *fp;
    fp = fopen(filename, "r");
	fscanf(fp,"%s %s", s_1, s_2);  /* scan file data parameters */
    if ((strcmp(s_1 , "time" ) || strcmp(s_2 ,"x")) == 0){    /* if time comes first read time values first then data */
        while (fscanf(fp,"%s %s",s_1 ,s_2) != EOF){
			/*store s_1 and s_2 to it`s index in array after convert to double type */
			*(Time+test_times)= convert_str_double ( s_1 );
			*(data+test_times)= convert_str_double ( s_2 );
			test_times++;
			}
		}
	else if ((strcmp(s_2 , "time") || strcmp(s_1 ,"x")) == 0){     /* if x comes first read  data first then time values */
		while (fscanf(fp,"%s %s",s_1 ,s_2) != EOF){
			/*store s_1 and s_2 to it`s index in array after convert to double type */
			*(Time+test_times)= convert_str_double ( s_1 );
			*(data+test_times)= convert_str_double ( s_2 );
			test_times++;
            }
        }
	else {
			printf("data parameters is not identified");  			/* if not read time and x then it`s not the right file */
			delay_sec(3);
			exit(1);
    }
	  fflush( fp );
	  fclose(fp);
}

double find_stdev(double* data , int test_times , double mean){
    double SD = 0.0;
    int count;
    for (count = 0; count < test_times; ++count) /* st_dec = (pow (data- mean )2)to all variables / n_number of variables */
        SD += pow(data[count] - mean, 2);
return sqrt(SD / test_times);}

void sort_data ( ){
    copy_data ( data_sorted , data ,  test_times );
    selection_sort (data_sorted , test_times );
}

void Produce_File (double mean , double median , double range  , double stdev){
	FILE *fp;
	fp= fopen("Data_Analysis.txt", "w");
	if(fp==NULL)exit(1);

	fprintf(fp, "%s : %.10lf \n"  ,"The Mean value of the data is" ,mean);
	fprintf(fp, "%s : %.10lf \n"  ,"The Median value of the data is", median);
	fprintf(fp, "%s : %.10lf \n"  ,"The Range of the data is", range );
	fprintf(fp, "%s : %.10lf \n"  ,"The Standrad Devision of the data is", stdev );
	if (c > 0)
	fprintf(fp, "%s : Y=%.10lf X+%.10lf \n"  ,"The Best Equation represent the data is",m ,c );
	else
	fprintf(fp, "%s : Y=%.10lf X%.10lf \n"  ,"The Best Equation represent the data is",m ,c );
	fprintf(fp, "%s : (dY/dX)=%.10lf  \n"  ,"The Dervative of the Best Equation represent the data is",m_differentiated );
	if (c > 0)
	fprintf(fp, "%s : Y=%.10lf X*X +%.10lf X \n"  ,"The Integral of the Best Equation represent the data is",m_integrated ,c_integreted );
	else
	fprintf(fp, "%s : Y=%.10lf X*X %.10lf X \n"  ,"The Integral of the Best Equation represent the data is",m_integrated ,c_integreted );
	fclose(fp);
}

void strcture_menu (double mean , double median , double range  , double stdev){
	int number ;
	clrscr();
	printf ("Enter the number of the operation required :::::\n" );
	printf ("\n");
	printf (" 1 - Show Mean Value \n");
	printf ("\n");
	printf (" 2 - Show Median Value\n");
	printf ("\n");
	printf (" 3 - Show Range value\n");
	printf ("\n");
	printf (" 4 - Show Standard Deviation\n");
	printf ("\n");
	printf (" 5 - Show Best Approximate Equation of data\n");
	printf ("\n");
	printf (" 6 - Show Best Approximate Equation differentiation\n");
	printf ("\n");
	printf (" 7 - Show Best Approximate Equation integration\n");
	printf ("\n");
	printf (" 8 - Show Graph of the represented data\n");
	printf ("\n");
	printf (" 9 - Exit the program !\n");
	printf ("\n");

	scanf ("%d" , &number);
	switch (number){
		case(1):
		printf( "%s : %.10lf \n"  ,"The Mean value of the data is" ,mean);
		break;

		case(2):
		printf("%s : %.10lf \n"  ,"The Median value of the data is", median);
		break;

		case(3):
		printf( "%s : %.10lf \n"  ,"The Range of the data is", range );
		break;

		case(4):
		printf( "%s : %.10lf \n"  ,"The Standrad Devision of the data is", stdev );
		break;

		case(5):
			if (c > 0)
				printf("%s : Y=%.10lf X+%.10lf \n"  ,"The Best Equation represent the data is",m ,c );
			else
				printf("%s : Y=%.10lf X%.10lf \n"  ,"The Best Equation represent the data is",m ,c );
		break;

		case(6):
		printf("%s : (dY/dX)=%.10lf  \n"  ,"The Dervative of the Best Equation represent the data is",m_differentiated );
		break;

		case(7):
		if (c > 0)
		printf( "%s : Y=%.10lf X*X +%.10lf X \n"  ,"The Integral of the Best Equation represent the data is",m_integrated ,c_integreted );
		else
		printf("%s : Y=%.10lf X*X %.10lf X \n"  ,"The Integral of the Best Equation represent the data is",m_integrated ,c_integreted );
		break;

		case(9):
		exit(0);
		break;

		default:
		printf ("operation number is Invalid");
		break;

		case(8):
		/* string parts: any of "rgbm": color; "-": draw line; "o": draw symbol */
		plotResults();
		break;


		}
		delay_sec(4);
        clrscr();
		strcture_menu( mean ,  median ,  range  ,  stdev);
	}

///////helping functions ////////////////////
double find_largest(double* data , int x){
    double largest = *data ;
     int i;
    for(i = 0 ; i < x ; i++ ){
        if (*(data+ i) > largest){
            largest = *(data+ i);		/* store largest number found in largest */
        }
    }
return largest;}

double find_smallest(double* data ,  int x){
    double smallest = *data ;
     int i;
    for(i = 0 ; i < x ; i++ ){
        if (*(data+ i) < smallest){
            smallest = *(data+ i);				/* store smallest number found in smallest */
        }
    }
return smallest;}

 void Get_Filename(char filename[] ){
     printf ("Enter File Name without space:::");
     scanf("%s" ,filename);
     searchforExt(filename);			/* search if ".txt " exist or not */
     FILE *fp ;
    fp= fopen(filename, "r");
    if(fp==NULL){						/* checks if file exist or not */
        printf ("File Name is Invalid");
        delay_sec(2);
        clrscr();
		//Get_dir (dir);
        Get_Filename(filename);
		  fflush( fp );
		  fclose(fp);
    }
 }

 void clrscr()
{
    system("@cls||clear");
    //system("cls");
}

 void searchforExt(char filename[]){		/* search if ".txt " exist or not */
     char txt[5] = ".txt";
     int filename_length = strlen(filename);
     int txt_length = 4;
     int count ;
     int exist = 1 ;
		 for (count = 1; count < 4 ; count++ ){
			if(filename [ filename_length - count] != txt[txt_length - count]){		/*compare if ".txt " charcters exist or not */
				exist = 0 ;
				}
			}
        if (exist == 0 ){
			strcat ( filename ,".txt" );   /* add " .txt " to the file name */
            }
        }

void delay_sec(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Stroing start time
    clock_t start_time = clock();

    // looping till required time is not acheived
    while (clock() < start_time + milli_seconds) ;
}

void selection_sort (double *array , int index ){
    int counter_1 = 0 ;
    int counter_2 = 0 ;
    int lowest_index ;
    double swap ;
    for (; counter_1 < index-1 ; counter_1++){
        lowest_index = counter_1 ;
            for (counter_2 = counter_1 ; counter_2 < index ; counter_2++){
                if (*(array+counter_2) < *(array+lowest_index)){			/* search for lowest index in the selected array length*/
                    lowest_index = counter_2 ;
                }
            }
			/* if found put it in it`s right index */
                swap =  *(array+lowest_index);
                *(array+lowest_index) =  *(array+counter_1);
                *(array+counter_1) =  swap;}
}

void copy_data (double *data_sorted ,double*data , int test_times ){
        int count;
        for ( count = 0 ; count < test_times ; count++){
            *(data_sorted+count)=*(data+count);				/* copy all data from data array to data_sorted array */
        }
    }

double convert_str_double ( char str[] ){
	char *ptr;
	double ret;
	ret = strtod(str, &ptr);			/* converts string to double */
	return ret;}



void plotResults() {
  FILE *gnuplotPipe,*tempDataFile;
char tempDataFileName[30] = "Data";
  int i;
tempDataFile = fopen(tempDataFileName,"w");   /* opens a temp file and store data to this file */
 for (i=0; i < test_times; i++) {
          fprintf(tempDataFile,"%.10lf %.10lf\n",Time[i],data[i]);

 }
 fclose(tempDataFile);

  gnuplotPipe = popen("gnuplot -persist","w");
	if (gnuplotPipe) {
		fprintf(gnuplotPipe,"set xlabel 'Time (seconds)' \n");   /* use gnu plot to plot data to the file */
		fprintf(gnuplotPipe,"set ylabel 'X' \n");
		fprintf(gnuplotPipe,"plot \"%s\" \n",tempDataFileName);
		fflush(gnuplotPipe);
		delay_sec(10);
		remove(tempDataFileName);
  }

}






