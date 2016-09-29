/*
 ============================================================================
 Name        : lab4-all.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX 2000

void loadArray(int array[], int number);
void scale(int array[], double scale, double arr[]);
void offset(int array[], double offset, double arr[]);
void saveScale(double arr[], int number);
void saveOffset(double arr[], int number);
double getMean(int *arr);
int findMax(int *arr);
void saveStatFile(double mean, int m, int number);
void centerSig(int *array, double *arr);
void normalSig(int *array, double *arr);
void saveCenter(double *arr, int number);
void saveNormal(double *arr, int number);


int main(void) {
	int selection;
	int selection2;
	float change;
	printf("Which file would you like to open?\n>>");
	scanf("%d", &selection);
	printf("%d", selection);
	int numarray [MAX];//initialize arrays with max values
	double final [MAX];
	loadArray(numarray, selection);//functions loads the array from selected file

	printf("What operation would you like to perform on the signal?\n1.Offset\n2.Scale\n3.Center\n4.Normalize\n5.Save stats\n>>");
	scanf("%d", &selection2);


	switch(selection2)//asks user for input based on the operation
	{
		case 1:
			printf("Enter a number to offset:");
			scanf("%f", &change);
			offset(numarray, change, final);
			saveOffset(final, selection);
			break;

		case 2:
			printf("Enter a number to scale:");
			scanf("%f", &change);
			scale (numarray, change, final);
			saveScale(final, selection);
			break;

		case 3:
			centerSig(numarray, final);
			saveCenter(final, selection);
			break;

		case 4:
			normalSig(numarray, final);
			saveNormal(final, selection);
			break;

		case 5:
			saveStatFile(getMean(numarray), findMax(numarray), selection);
			break;

		default:
			printf("invalid entry\n");
			break;
	}

	return 0;
}

void loadArray (int array[], int number)
{
	FILE* fp;

	switch(number)//switch statement
		{
		case 1 :
			fp = fopen ("Raw_data_01.txt ", "r");
			break;
		case 2 ://runs if this is true
			fp = fopen ("Raw_data_02.txt ", "r");
			break;//if it runs it breaks out of the switch statement
		case 3 ://runs if this is true;
			fp = fopen ("Raw_data_03.txt ", "r");
			break;//if it runs it breaks out of the switch statement
		case 4 ://runs if this is true
			fp = fopen ("Raw_data_04.txt ", "r");
			break;//if it runs it breaks out of the switch statement
		case 5 ://runs if this is true
			fp = fopen ("Raw_data_05.txt ", "r");
			break;
		case 6:
			fp = fopen ("Raw_data_06.txt ", "r");
			break;
		case 7:
			fp = fopen ("Raw_data_07.txt ", "r");
			break;
		case 8:
			fp = fopen ("Raw_data_08.txt ", "r");
			break;
		case 9:
			fp = fopen ("Raw_data_09.txt ", "r");
			break;
		case 10:
			fp = fopen ("Raw_data_10.txt ", "r");
			break;
		case 11:
			fp = fopen ("Raw_data_11.txt ", "r");
			break;
		default:
			printf("//FILE ERROR//");
			return;
			break;
		}

	//int array[MAX];
	int i;
	int len;
	int max;

	fscanf(fp, "%d %d", &len, &max);

	array[0]= len;
	array[1] = max;

	for(i = 2; i < len+2; i++)//scans in until the end of file using the length given in the file
	{
		fscanf(fp, "%d", &array[i]);
	}
}
void scale (int array[], double scale, double arr[])
{
	int i;
	arr[1] = scale;
	arr[0] = array[0];
	for (i = 2; i < array[0]+2; i++)
	{
		arr [i] = array[i]*scale;
	}
	//saveScale(arr, number);
}

void offset(int array[], double offset, double arr[])
{
	arr [1] = offset;
	arr[0] = array[0];//gives new array length
	int i;
	for (i = 2; i < array[0]+2; i++)//offsets the values and stores them into the new arrays
	{
		arr [i] = array[i]+offset;
	}
	//saveOffset(arr, number);
}

void saveScale(double arr[], int number)
{
	FILE *fp;
	switch(number)//switch statement
			{
			case 1 :
				fp = fopen ("Scaled_data_01.txt ", "w");
				break;
			case 2 ://runs if this is true
				fp = fopen ("Scaled_data_02.txt ", "w");
				break;//if it runs it breaks out of the switch statement
			case 3 ://runs if this is true;
				fp = fopen ("Scaled_data_03.txt ", "w");
				break;//if it runs it breaks out of the switch statement
			case 4 ://runs if this is true
				fp = fopen ("Scaled_data_04.txt ", "w");
				break;//if it runs it breaks out of the switch statement
			case 5 ://runs if this is true
				fp = fopen ("Scaled_data_05.txt ", "w");
				break;
			case 6:
				fp = fopen ("Scaled_data_06.txt ", "w");
				break;
			case 7:
				fp = fopen ("Scaled_data_07.txt ", "w");
				break;
			case 8:
				fp = fopen ("Scaled_data_08.txt ", "w");
				break;
			case 9:
				fp = fopen ("Scaled_data_09.txt ", "w");
				break;
			case 10:
				fp = fopen ("Scaled_data_10.txt ", "w");
				break;
			case 11:
				fp = fopen ("Scaled_data_11.txt ", "w");
				break;
			default:
				printf("//FILE ERROR//");
				return;
				break;
			}
	int i;
	fprintf(fp, "%.0f %.4f\n", arr[0], arr[1]);
	for(i = 2; i < arr[0]+2; i++)//prints the new array to the file
	{
		fprintf(fp, "%.4f\n", arr[i]);
	}
	fclose(fp);
}

void saveOffset(double arr[], int number)
{
	FILE *fp;
	switch(number)//switch statement
			{
			case 1 :
				fp = fopen ("Offset_data_01.txt ", "w");
				break;
			case 2 ://runs if this is true
				fp = fopen ("Offset_data_02.txt ", "w");
				break;//if it runs it breaks out of the switch statement
			case 3 ://runs if this is true;
				fp = fopen ("Offset_data_03.txt ", "w");
				break;//if it runs it breaks out of the switch statement
			case 4 ://runs if this is true
				fp = fopen ("Offset_data_04.txt ", "w");
				break;//if it runs it breaks out of the switch statement
			case 5 ://runs if this is true
				fp = fopen ("Offset_data_05.txt ", "w");
				break;
			case 6:
				fp = fopen ("Offset_data_06.txt ", "w");
				break;
			case 7:
				fp = fopen ("Offset_data_07.txt ", "w");
				break;
			case 8:
				fp = fopen ("Offset_data_08.txt ", "w");
				break;
			case 9:
				fp = fopen ("Offset_data_09.txt ", "w");
				break;
			case 10:
				fp = fopen ("Offset_data_10.txt ", "w");
				break;
			case 11:
				fp = fopen ("Offset_data_11.txt ", "w");
				break;
			default:
				printf("//FILE ERROR//");
				return;
				break;
			}
	int i;
	fprintf(fp, "%.0f %.4f\n", arr[0], arr[1]);
	for(i = 2; i < arr[0]+2; i++)//saves all of the points of the array to the file
	{
		fprintf(fp, "%.4f\n", arr[i]);//prints only with four decimal places
	}
	fclose(fp);
}

double getMean(int *arr)
{
	double mean, sum = 0;
	int size = arr[0];
	int i;
	for(i=2; i < size+2; i++)
	{
		sum += arr[i];//finds the sum by adding them all together
	}

	mean = (1.0 * sum)/size;//performs calculation to find the mean
	return mean;
}

int findMax(int *arr)
{
	int m=0, i;
	int size = arr[0];
	for(i=0; i < size+2; i++)
	{
		if(arr[i] > m)
		{
			m = arr[i];//find the max by saving the greatest value each time
		}
	}

	return m;
}

void saveStatFile(double mean, int m, int number)
{
	FILE *fp;
	switch(number)//switch statement
			{
			case 1 :
				fp = fopen ("Statistics_data_01.txt ", "w");
				break;
			case 2 ://runs if this is true
				fp = fopen ("Statistics_data_02.txt ", "w");
				break;//if it runs it breaks out of the switch statement
			case 3 ://runs if this is true;
				fp = fopen ("Statistics_data_03.txt ", "w");
				break;//if it runs it breaks out of the switch statement
			case 4 ://runs if this is true
				fp = fopen ("Statistics_data_04.txt ", "w");
				break;//if it runs it breaks out of the switch statement
			case 5 ://runs if this is true
				fp = fopen ("Statistics_data_05.txt ", "w");
				break;
			case 6:
				fp = fopen ("Statistics_data_06.txt ", "w");
				break;
			case 7:
				fp = fopen ("Statistics_data_07.txt ", "w");
				break;
			case 8:
				fp = fopen ("Statistics_data_08.txt ", "w");
				break;
			case 9:
				fp = fopen ("Statistics_data_09.txt ", "w");
				break;
			case 10:
				fp = fopen ("Statistics_data_10.txt ", "w");
				break;
			case 11:
				fp = fopen ("Statistics_data_11.txt ", "w");
				break;
			default:
				break;
			}

	fprintf(fp, "%.4f %d", mean, m);//writes the mean and max values to the file
	fclose(fp);
}

void centerSig(int *array, double *arr)
{
	double mean = getMean(array);//centers the signal by using the offset function already written
	offset(array, -mean, arr);
}

void normalSig(int *array, double *arr)
{
	int max = findMax(array);//finds the normalized signal by using the scale function already written
	scale(array, (1.0/max), arr);
}

void saveCenter(double arr[], int number)
{
	FILE *fp;
	switch(number)//switch statement
			{
			case 1 :
				fp = fopen ("Centered_data_01.txt ", "w");
				break;
			case 2 ://runs if this is true
				fp = fopen ("Centered_data_02.txt ", "w");
				break;//if it runs it breaks out of the switch statement
			case 3 ://runs if this is true;
				fp = fopen ("Centered_data_03.txt ", "w");
				break;//if it runs it breaks out of the switch statement
			case 4 ://runs if this is true
				fp = fopen ("Centered_data_04.txt ", "w");
				break;//if it runs it breaks out of the switch statement
			case 5 ://runs if this is true
				fp = fopen ("Centered_data_05.txt ", "w");
				break;
			case 6:
				fp = fopen ("Centered_data_06.txt ", "w");
				break;
			case 7:
				fp = fopen ("Centered_data_07.txt ", "w");
				break;
			case 8:
				fp = fopen ("Centered_data_08.txt ", "w");
				break;
			case 9:
				fp = fopen ("Centered_data_09.txt ", "w");
				break;
			case 10:
				fp = fopen ("Centered_data_10.txt ", "w");
				break;
			case 11:
				fp = fopen ("Centered_data_11.txt ", "w");
				break;
			default:
				printf("//FILE ERROR//");
				return;
				break;
			}
	int i;
	fprintf(fp, "%.0f %.4f\n", arr[0], arr[1]);
	for(i = 2; i < arr[0]+2; i++)
	{
		fprintf(fp, "%.4f\n", arr[i]);//writes all the values of the array to the file
	}
	fclose(fp);
}

void saveNormal(double arr[], int number)
{
	FILE *fp;
	switch(number)//switch statement
			{
			case 1 :
				fp = fopen ("Normalized_data_01.txt ", "w");
				break;
			case 2 ://runs if this is true
				fp = fopen ("Normalized_data_02.txt ", "w");
				break;//if it runs it breaks out of the switch statement
			case 3 ://runs if this is true;
				fp = fopen ("Normalized_data_03.txt ", "w");
				break;//if it runs it breaks out of the switch statement
			case 4 ://runs if this is true
				fp = fopen ("Normalized_data_04.txt ", "w");
				break;//if it runs it breaks out of the switch statement
			case 5 ://runs if this is true
				fp = fopen ("Normalized_data_05.txt ", "w");
				break;
			case 6:
				fp = fopen ("Normalized_data_06.txt ", "w");
				break;
			case 7:
				fp = fopen ("Normalized_data_07.txt ", "w");
				break;
			case 8:
				fp = fopen ("Normalized_data_08.txt ", "w");
				break;
			case 9:
				fp = fopen ("Normalized_data_09.txt ", "w");
				break;
			case 10:
				fp = fopen ("Normalized_data_10.txt ", "w");
				break;
			case 11:
				fp = fopen ("Normalized_data_11.txt ", "w");
				break;
			default:
				printf("//FILE ERROR//");
				return;
				break;
			}
	int i;
	fprintf(fp, "%.0f %.4f\n", arr[0], arr[1]);
	for(i = 2; i < arr[0]+2; i++)
	{
		fprintf(fp, "%.4f\n", arr[i]);//writes all the values of the array to the file with only four decimal places
	}
	fclose(fp);
}
