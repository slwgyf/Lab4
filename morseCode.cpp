//============================================================================
// Name        : Lab 8
// Author      : Eric Wagner & Sammy Warren
// Version     :
// Copyright   : Your copyright notice
// Description : Morse code lab
//============================================================================

#include <iostream>
#include <cstring>
#include <string>
#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

class message//base class
{
	private:

	protected:
		string mess;//available to derived classes
	public:
		message();//available to everyone
		message(string input);
		~message();
		virtual void printMess();
};
message :: message()//default constructor
{
	cout << "Enter a string to translate: " << endl;
	getline(cin, mess);
}
message :: message(string input)//parametric constructor
{
	mess = input;
}
message :: ~message()//destructor
{
	cout << "Message destroyed" << endl;
}
void message :: printMess()
{
	cout << mess << endl;
}

class morseCodeMessage : public message//derived class from message
{
	private:
		string *str;//only accessed by this class
	public:
		morseCodeMessage ();
		morseCodeMessage(string m);
		~morseCodeMessage();
		void translate();
		void transToLED();
		void printMess();
};
morseCodeMessage :: morseCodeMessage() : message()//default constructor which calls base class contrsuctor too
{
	str = new string[mess.length()];//allocates space for a new string
}

morseCodeMessage :: morseCodeMessage(string m) : message(m)//parametic constructor that calls base class constructor
{
	str = new string[m.length()];
}
void morseCodeMessage :: translate()
{
	//libraries of each alphabet to translate
	static string morseCode[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
	static string letters = "abcdefghijklmnopqrstuvwxyz";
	char c;
	int i, index;
	for(i = 0; i < mess.length(); i++)
	{
		c = mess[i];//get one character
		if(isupper(c))//to ignore capitals
		{
			c = tolower(c);
		}
		index = letters.find(c);//get the index where the letter is
		str[i] = morseCode[index];//gives that index of the string the correct morse code character
	}
}
void morseCodeMessage :: transToLED()
{
	int fd;		// for the file descriptor of the special file we need to open.
	unsigned long *BasePtr;		// base pointer, for the beginning of the memory page (mmap)
	unsigned long *PBDR, *PBDDR;	// pointers for port B DR/DDR

	fd = open("/dev/mem", O_RDWR|O_SYNC);	// open the special file /dem/mem
	if(fd == -1){
		printf("\n error\n");
		//return(-1);  // failed open
	}

	// We need to map Address 0x80840000 (beginning of the page)
	BasePtr = (unsigned long*)mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0x80840000);
	if(BasePtr == MAP_FAILED){
		printf("\n Unable to map memory space \n");
		//return(-2);
	}  // failed mmap

	// To access other registers in the page, we need to offset the base pointer to reach the
	// corresponding addresses. Those can be found in the board's manual.
	PBDR = BasePtr + 1;		// Address of port B DR is 0x80840004
	PBDDR = BasePtr + 5;	// Address of port B DDR is 0x80840014

	printMess();

	int i, k;
	for(i = 0; i < mess.length(); i++)
	{
		for(k = 0; k < str[i].length(); k++)
		{
			if(str[i][k] == '.')
			{
				*PBDDR |= 0x20;
				*PBDDR &= 0xFFFFFFFE;

				*PBDR |= 0x20;	// ON: write a 1 to port B0. Mask all other bits.
				usleep(100000);	// How can you sleep for less than a second?
				*PBDR &= ~0x20;	// OFF: write a 0 to port B0. Mask all other bits.
			}
			if(str[i][k] == '-')
			{
				*PBDDR |= 0x40;
				*PBDDR &= 0xFFFFFFFE;

				*PBDR |= 0x40;	// ON: write a 1 to port B0. Mask all other bits.
				usleep(100000);	// How can you sleep for less than a second?
				*PBDR &= ~0x40;	// OFF: write a 0 to port B0. Mask all other bits.
			}
			usleep(100000);
		}
		usleep(1000000);
	}
	*PBDDR |= 0x80;
	*PBDDR &= 0xFFFFFFFE;

	*PBDR |= 0x80;	// ON: write a 1 to port B0. Mask all other bits.
	sleep(1);	// How can you sleep for less than a second?
	*PBDR &= ~0x80;	// OFF: write a 0 to port B0. Mask all other bits.
    sleep(1);
}
morseCodeMessage :: ~morseCodeMessage()//destructor
{
	cout << "Morse code message destroyed" << endl;
}
void morseCodeMessage :: printMess()//prints the message char by char
{
	int i;
	for(i = 0; i < mess.length(); i++)
	{
		cout << str[i] <<" ";
	}
	cout << endl;
}

class msgst//independent class
{
public: //all methods are public
		msgst(message* obj);
		~msgst();
		message* ptrst[10];
		int num_obs;
		void pop();
		void push(message *obj);
		void printStack();
};
msgst :: msgst(message* obj)//use a pointer in order to dynamically bind
{
	ptrst[0] = obj;//sets the beginning to the obj
	num_obs = 1;
}
void msgst :: pop()//take things off the stack
{
	int x = num_obs-1;

	if(x < 0)
	{
		cout << "No objects\n";
		return;
	}

	delete *(ptrst + x);

	num_obs = x;
	cout << "Object popped from stack"<< endl;
}
void msgst :: push(message *obj)//contructor
{
	int x = num_obs;
	ptrst[x] = obj;
	num_obs ++;
}
void msgst :: printStack()//prints the contents of the stack by calling the print function of the specific object
{
	int i;
	message *ptr;
	for(i = 0; i < num_obs; i++)
	{
		ptr = ptrst[i];
		ptr->printMess();//knows which printMess to use because of dynamic binding
	}
}
msgst :: ~msgst()//destructor
{

	while(num_obs >= 1)
	{
		pop();//uses pop function to delete everything off the stack
	}
	cout<< "stack cleared"<< endl;
}

int main()
{
	morseCodeMessage obj;//shows parametic contructor
	obj.translate();
	obj.transToLED();
	/*message obj2("hello");//shows a normal message object
	morseCodeMessage obj3;//shows the default constructor
	obj3.translate();
	obj3.printMess();
	obj.printMess();
	obj2.printMess();
	msgst stack(&obj);//starts the stack
	stack.push(&obj2);//pushes onto the stack
	stack.push(&obj3);
	stack.printStack();//shows stack in current state
	stack.pop();//pops off the stack
	stack.pop();
	stack.pop();*/



	return 0;
}
