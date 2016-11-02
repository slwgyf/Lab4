//============================================================================
// Name        : Lab 8
// Author      : Eric Wagner & Sammy Warren
// Version     :
// Copyright   : Your copyright notice
// Description : Morse code lab
//============================================================================

#include <iostream>
#include <cstring>
#include <string.h>

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
	cout << "Enter a string to translate: " << endl<<">>";
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
	morseCodeMessage obj("hello");//shows parametic contructor
	obj.translate();
	message obj2("hello");//shows a normal message object
	morseCodeMessage obj3;//shows the default constructor
	obj3.translate();
	cout << "Prints object 1:" << endl;
	obj.printMess();
	cout << "Prints object 2:" << endl;
	obj2.printMess();
	cout << "Prints object 3:"<< endl;
	obj3.printMess();
	
	cout <<endl<< "--------------------------------------------------------------------------"<< endl<< endl;
	
	msgst stack(&obj);//starts the stack
	stack.push(&obj2);//pushes onto the stack
	stack.push(&obj3);
	cout << "Pushes object1, 2, and 3 onto the stack and prints them:"<< endl;
	stack.printStack();//shows stack in current state
	
	cout << endl<<"--------------------------------------------------------------------------"<< endl<< endl;
	
	stack.pop();//pops off the stack
	stack.pop();
	stack.pop();
	cout << "Pops 1, 2, and 3 off the stack."<< endl;
	
		

	
	return 0;
}
