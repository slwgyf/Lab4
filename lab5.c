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
#include <string.h>

#define MAX 2000

void loadArray(int array[], int number);
void scale(int array[], double scale, double arr[]);
void offset(int array[], double offset, double arr[]);
void saveScale(double arr[], int number, char *str);
void saveOffset(double arr[], int number, char *str);
double getMean(int *arr);
int findMax(int *arr);
void saveStatFile(double mean, int m, int number, char *str);
void centerSig(int *array, double *arr);
void normalSig(int *array, double *arr);
void saveCenter(double *arr, int number, char *str);
void saveNormal(double *arr, int number, char *str);
int check(char *str);
void renameFile(int n, char *str2);


int main(int argc, char* argv[])
{

	float change;
	int filenum = -1;
	char filename[25];
	char filename1[25];
	int i = 1;
	int numarray [MAX];//initialize arrays with max values
	double final [MAX];
	int j = 1;
	while (argv[j] != NULL)
	{
		if (argv[j][0] == '-')
		{
			if(argv[j][1] == 'n')
			{
				filenum = atoi (argv[j+1]);
				//printf("\n\nFile num: %02d\n\n", filenum);
				if (check(argv[j+1]) == 0)
					filenum = -1;
			}

		}
		j++;
	}

	if (filenum == -1)
	{
		printf("No file number given. Could not perform operations\n");
		return 0;
	}
	
	loadArray(numarray, filenum);
	j = 1;
	//printf("\n\n check for -r\n\n");
	while (argv[j] != NULL)
	{
		if (argv[j][0] == '-')
		{
			if(argv[j][1] == 'r')
			{
				strcpy(filename, argv[j+1]);
				//printf("\n%s", filename);
				strcpy(filename1, argv[j+1]);
				strcat (filename1, ".txt");
				//printf("\n\nName changed to: %s\n\n", filename);
				renameFile (filenum, filename1);
				break;
			}
			else
				strcpy(filename, "-1");

		}
		j++;
	}
	while (argv[i] != NULL)
	{

		if (argv[i][0] == '-' )
		{
			if (argv[i][1] == 'r' || argv[i][1] == 'n')
					i++;
			else if(argv[i][1] == 'o')
			{
				if (check(argv[i+1]) == 1)
				{
					printf("in offset block");
					change = strtod(argv[i+1], NULL);
					offset(numarray,change,final);
					printf("numbers offset");
					saveOffset(final, filenum, filename);
					i++;
				}
			}
			else if(argv[i][1] == 's')
			{
				if (check(argv[i+1]) == 1)
				{
					change = strtod(argv[i+1], NULL);
					scale(numarray, change, final);
					saveScale(final, filenum, filename);
					i++;
				}
			}
			else if(argv[i][1] == 'S')
			{
				saveStatFile (getMean(numarray), findMax(numarray), filenum, filename);
			}
			else if(argv[i][1] == 'C')
			{
				centerSig (numarray, final);
				saveCenter(final, filenum, filename);
			}
			else if(argv[i][1] == 'N')
			{
				normalSig (numarray, final);
				saveNormal(final, filenum, filename);
			}
			
			else if(argv[i][1] == 'h')
			{
				printf("-n File number (Value needed)\n-o offset value (value needed)\n-s scale factor (value needed)\n-S Get Statistics\n-C Center the signal\n-N Normalize the signal\n-r Rename files (name needed)\n-h Help");
				//return 0;
			}
		}
		else
		{
			if (argv[i][0] == '\0')
				return 0;
			printf("%s was an invalid input\n", argv[i]);
		}
		i++;
	}


	return 0;

}
void renameFile(int n, char *str2)
{
	FILE *fp1, *fp2;
	int a;
	
	char str1[16] = "Raw_data_nn.txt";
	str1[9] =  (n/10)+48;
	str1[10] = (n%10)+48;
	
	fp1 = fopen(str1, "r");
	fp2 = fopen(str2, "w");
	
	while(1)
	{
		a = fgetc(fp1);
		if(!feof(fp1))
		{
			fputc(a, fp2);
		}
		else
			break;
	}
	return;
}
int check (char* string)
{
	int good = 1;
	if (string[0] == '-' )
	{
		good = 0;
	}

	if (string[0] >'9' || string[0] < '0')
	{
		good = 0;
	}

	if (good == 0)
	{
		printf("\n%s is not valid.\n", string);
	}

	return good;

}


void loadArray (int array[], int number)
{
	FILE* fp;

	char strName[16] = "Raw_data_nn.txt";//base string for loading the array
	strName[9] =  (number/10)+48;//takes first digit of the file number
	strName[10] = (number%10)+48;//takes second digit of the file number
	
	//printf("%s", strName);

	if ((fp = fopen(strName, "r")) != NULL)
	{
		//	printf("\n\nFILE %s OPENED\n\n", strName);
	}
	int i;
	int len = 0;
	int max;

	fscanf (fp, "%d %d", &len, &max);
	//printf("%d", x);
	
	//printf("\n\nFILE PARAMETERS LOADED\n\n");
	array[0] = len;//the first location holds the length
	array[1] = max;//the second location holds the max value
	//printf("%d", len);

	for(i = 2; i < len+2; i++)
	{
		fscanf(fp, "%d", &array[i]);//loads the data from the file into array
		
	}
	//printf("\n\nARRAY LOADED\n\n");
	fclose(fp);
}
void scale (int array[], double scale, double arr[])
{
	int i;
	arr[1] = scale;//the second locations holds the scaling constant
	arr[0] = array[0];//the new array is the same length as the original
	for (i = 2; i < array[0]+2; i++)//iterates through the data after the length and scaling constant
	{
		arr [i] = array[i]*scale;//saves the scaled values into the new array
	}
}

void offset(int array[], double offset, double arr[])
{
	arr [1] = offset;//the second location get the offset value
	arr[0] = array[0];
	int i;
	for (i = 2; i < array[0]+2; i++)
	{
		arr [i] = array[i]+offset;//saves offset values into the new array
	}
	return;
}

void saveScale(double arr[], int number, char *str)
{
	FILE *fp;
	char strc [25];
	strcpy(strc, str);
	if(strcmp(str, "-1") != 0)
	{
		char *str2 = "_scaled_data.txt";
		str2 = strcat(strc, str2);
		printf("\n%s\n", str2);
		fp = fopen(str2, "w");
	}
	else
	{
		char strName[19] = "Scaled_data_nn.txt";
		strName[12] = (number/10)+48;
		strName[13] = (number%10)+48;

		fp = fopen(strName, "w");//opens the file for writing
	}
	int i;
	fprintf(fp, "%.0f %.4f\n", arr[0], arr[1]);
	for(i = 2; i < arr[0]+2; i++)
	{
		fprintf(fp, "%.4f\n", arr[i]);//writes the scaled values into a new file
	}
	fclose(fp);
	return;
}

void saveOffset(double arr[], int number, char *str)
{
	FILE *fp;
	char strc[25];
	strcpy(strc, str);
	printf("%s\n", str);
	if(strcmp(str, "-1") != 0)
	{
		char *str2 = "_offset_data.txt";
		str2 = strcat(strc, str2);
		printf("\n%s\n", str2);
		fp = fopen(str2, "w");
	}
	else
	{
		char strName[19] = "Offset_data_nn.txt";
		strName[12] = (number/10)+48;
		strName[13] = (number%10)+48;

		fp = fopen(strName, "w");
	}

	int i;
	fprintf(fp, "%.0f %.4f\n", arr[0], arr[1]);
	for(i = 2; i < arr[0]+2; i++)
	{
		fprintf(fp, "%.4f\n", arr[i]);//writes the offset values to the new file
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
		sum += arr[i];//sums each value in the array
	}

	mean = (1.0 * sum)/size;//divides the total sum by the size and holds it as a double
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
			m = arr[i];//iterates through the array updating m whenever a value is larger
		}
	}

	return m;//returns the largest value
}

void saveStatFile(double mean, int m, int number, char *str)
{
	FILE *fp;
	char strc[25];
	strcpy(strc, str);
	if(strcmp(str, "-1") != 0)
	{
		char *str2 = "_statistics_data.txt";
		str2 = strcat(strc, str2);
		printf("\n%s\n", str2);
		fp = fopen(str2, "w");
	}
	else
	{
		char strName[24] = "Statistics_data_nn.txt";
		strName[16] = (number/10)+48;
		strName[17] = (number%10)+48;

		fp = fopen(strName, "w");
	}
	fprintf(fp, "%.4f %d", mean, m);//saves the
	fclose(fp);
}

void centerSig(int *array, double *arr)
{
	double mean = getMean(array);
	offset(array, -mean, arr);//the signal is offset by the opposite of the mean
}

void normalSig(int *array, double *arr)
{
	int max = findMax(array);
	scale(array, (1.0/max), arr);//the signal is scaled by the reciprocal of the max
}

void saveCenter(double arr[], int number, char *str)
{
	FILE *fp;
	char strc [25];
	strcpy(strc, str);
	if(strcmp(str, "-1") != 0)
	{
		char *str2 = "_centered_data.txt";
		str2 = strcat(strc, str2);
		printf("\n%s\n", str2);
			fp = fopen(str2, "w");
	}
	else
	{
		char strName[21] = "Centered_data_nn.txt";
		strName[14] = (number/10)+48;
		strName[15] = (number%10)+48;

		fp = fopen(strName, "w");
	}
	int i;
	fprintf(fp, "%.0f %.4f\n", arr[0], arr[1]);//saves the length and the offset value in the file
	for(i = 2; i < arr[0]+2; i++)
	{
		fprintf(fp, "%.4f\n", arr[i]);
	}
	fclose(fp);
}

void saveNormal(double arr[], int number, char* str)
{
	FILE *fp;
	char strc[25];
	strcpy(strc, str);
	if(strcmp(str, "-1") != 0)
	{
		char *str2 = "_scaled_data.txt";
		str2 = strcat(strc, str2);
		printf("\n%s\n", str2);
		fp = fopen(str2, "w");
	}
	else
	{
		char strName[23] = "Normalized_data_nn.txt";
		strName[16] = (number/10)+48;
		strName[17] = (number%10)+48;

		fp = fopen(strName, "w");
	}

	int i;
	fprintf(fp, "%.0f %.4f\n", arr[0], arr[1]);//saves the length and the scaling constant in the file
	for(i = 2; i < arr[0]+2; i++)
	{
		fprintf(fp, "%.4f\n", arr[i]);
	}
	fclose(fp);
}
