//============================================================================
// Name        : lab7.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


using namespace std;


class Signal
{
	private:
		
		double mean, maxV;//private members of the class
		int length;
		double* data;
		
	public:
		//public members of the class to be called
		Signal();//constructors
		Signal(int num);
		Signal(string name);
		~Signal();//destructor
		void offset(double val);
		void scale(double val);
		void centerSig();
		void normalSig();
		void statistics();
		void sigInfo();
		void saveSig(string name);
		void menu();//called to print the menu
};

Signal::Signal()//default constructors
{
	length = 0;
	data = NULL;
	mean = 0.0;
	maxV = 0.0;
}
Signal::Signal(int num)//contructor to be called if an integer is sent
{
	FILE *fp;
	char fname[16] = "Raw_data_nn.txt";//default name of files, nn to be over written below
	fname[9] = (num/10)+48;//loads first digit of num into nn
	fname[10] = (num%10)+48;//loads second digit of num into nn

	fp = fopen(fname, "r");//open the file
	fscanf(fp, "%d %lf", &length, &maxV);//assign values to length and max
	data = new double[length];//allocated memory of proper length

	int i;
	for(i = 0; i < length; i++)
	{
		fscanf(fp, "%lf", &data[i]);//load the values into the data variable
	}
	fclose(fp);//close the file
	//for(i = 0; i < length; i++)
	//{
	//	cout<< data[i] << endl;
	//}
	//statistics();
}
Signal::Signal(string name)//contructor called if a string is sent
{
	char nameC[name.size()+1];//as 1 char space for null is also required
	strcpy(nameC, name.c_str());
	
	FILE *fp;

	fp = fopen(nameC, "r");

	fscanf(fp, "%d %lf", &length, &maxV);//assign values to length and max
	//cout<<"length" << length<<endl;
	//cout<< "max"<< maxV << endl;
	data = new double[length];//allocates memory of proper length

	int i;
	for(i = 0; i < length; i++)
	{
		fscanf(fp, "%lf", &data[i]);//load the values into the data variable
	}
	fclose(fp);//close the file
	//statistics();
}
Signal::~Signal()//destructor
{
	//cout << "destructor called" << endl;
	delete[] data;
}

void Signal::offset(double val)
{
	int i;
	//cout << val << endl;
	for(i = 0; i < length; i++)//offsets each value of the array
	{
		data[i] += val;
	}
	
}

void Signal::scale(double val)
{
	int i;
	for(i = 0; i < length; i++)//scales each number of the data array
	{
		data[i] *= val;
	}
	
}

void Signal::centerSig()
{
	statistics();//updates the stat
	offset(-mean);//calls the mean with that
}

void Signal::normalSig()
{
	statistics();//updates the statistics
	//cout<< maxV << endl;
	scale((1.0/maxV));//calls the scale
}

void Signal::statistics()
{
	int i;
	maxV = data[0];
	for(i = 0; i < length; i++)
	{
		if(data[i] > maxV)
			maxV = data[i];
	}

	mean = 0.0;
	for(i = 0; i < length; i++)//recalculates the mean
	{
		mean += data[i];
	}
	mean = (mean / length);	
	//cout<< "mean" << mean << endl;
}

void Signal::sigInfo()
{
	statistics();//updates stats before printing the information
	cout << "The signals length is: " << length <<
			"\nThe signals mean is: " << mean <<
			"\nThe signals max value is: " << maxV << endl;
}

void Signal::saveSig(string name)
{
	char nameC[name.size()+1];//as 1 char space for null is also required
	strcpy(nameC, name.c_str());//copies the string and puts it in type char* 
	FILE* fp;
	fp = fopen(nameC, "w");
	
	//cout << "\nFile Opened\n";
	fprintf(fp, "%d %lf\n", length, maxV);//prints the stats
	//cout << "\nParameters saved\n";
	int i;
	for(i = 0; i < length; i++)//prints the data array to the file
	{
		fprintf(fp, "%.3lf\n", data[i]);
	}
	fclose(fp);
	cout << "\nFile Closed\n";
}


void Signal::menu ()
{
	int c = -1;
	string name;
	double op = 0.0;
	while(1)
	{
		cout << "\nEnter a command:"
				"\n1) Offset		2) Scale"
				"\n3) Center		4) Normalize"
				"\n5) Statistic		6) Print Signal"
				"\n7) Save Signal		8) Exit" 
				"\n> ";
		cin >> c;
		//cout << "from menu" << endl;

		switch(c)
		{
			case 1:
				cout << "Choose a value to offset by: ";
				cin >> op;
				offset(op);
				cout << "\nSignal has been offset" << endl;
				break;
			case 2:
				cout << "Choose a value to scale by: ";
				cin >> op;
				scale(op);
				cout << "\nSignal has been scaled" << endl;
				break;
			case 3:
				centerSig();
				cout << "Signal has been centered" << endl;
				break;
			case 4:
				normalSig();
				cout << "Signal has been normalized" << endl;
				break;
			case 5:
				statistics();
				cout << "Signal's statistics updated" << endl;
				break;
			case 6:
				sigInfo();
				break;
			case 7:
				cout << "Enter a name for the new file: ";
				cin.ignore(1000, '\n');//makes sure it doesn't take in the newline
				getline (cin,name);
				cout << "\nName loaded\n";
				saveSig(name);
				cout << "Signal saved to the file " << name << endl;
				break;
			case 8:
				cout << "Exiting program" << endl;
				return;
			default:
				cout << "Please enter a command number" << endl;
				break;
			
		}
		//cin.ignore (1000,'\n');
	}
}
int main(int argc, char* argv[])
{
	int c, num;
	string name;
	
	if (argc == 1)//if there are no command line arguements
	{
		cout << "\nEnter signal by (1)number or (2)name?" << endl;
		cin >> c;
		cin.ignore (1000, '\n');
		
		if (c == 1)//to choose file with a number
		{
			cout << "Enter the file number:";
			cin >> num;
			Signal sig1 (num);
			sig1.menu();
			
		}
		else if (c ==2)
		{
			cout << "Enter the file name:";
			getline (cin, name);
			Signal sig1(name);
			sig1.menu ();
		}
		else
		{
			Signal sig1;
			cout << "signal set to default" << endl;
			sig1.menu();
			}
	}
	else if((strcmp(argv[1], "-n")) == 0)//if there is a -n command line arguement
	{
		if(argv[2][0] >= '0' && argv[2][0] <= '9')
		{
			num = atoi(argv[2]);
			//cout << num << endl;
			Signal sig1 (num);
			sig1.menu();
		}
	}
	else if((strcmp(argv[1], "-f")) == 0)//if there is a if command line arguement
	{
		if(argv[2] != '\0' && argv[2] != NULL)
		{
			name = argv[2];
			Signal sig1 (name);
			sig1.menu ();
		}
	}
	
	return 0;
}
