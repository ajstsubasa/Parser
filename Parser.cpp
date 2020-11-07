// Parser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include"Pair.h"

using namespace std;
Pair *Parser(char *);
void printParsetree(Pair *);
bool contains(char *);
bool checkforwhile(char *);
bool checkforElse(char *);

int main()
{
	char *buffer = new char[150];

	char temp[40] ="x=2;y=2;";
	char temp2[55] = "x=2;y=2;if(x=2){x=2;}";
	char temp3[55] = "if(x<2){y=2;}x=2;";
	char temp4[55] = "if(x<2){z=2;}else{z=2;}z=2;";
	buffer = temp4;
	
	Pair *p = Parser(buffer); //new Pair(nullptr, Parser(buffer), '[');;
	printParsetree(p);

	return 0;
}
Pair *Parser(char *buff)
{

	Pair *result=nullptr;
	if (*buff == '\0')
	{

		return nullptr;
	}
	if (*buff == ' ')
	{

		buff=buff+1;
	}
	
	//if (*(buff+1) == '\0')
	//{
	
		//return nullptr;
	//}

	
	if (*(buff) == 'i' &&*(buff + 1) == 'f') // "we have a if"
	{
		Pair *p = new Pair('I', 'F'); //If is Type I
		; // move the buffer forward.
		buff = buff + 3; //if(x) , iterator moves to x.
		Pair *t = Parser(buff);
		//MoveIfLeft(Pair *p,Pair *t);
		p->right = t;
	
		return p;

	}
	if (checkforwhile(buff))   //check if we have to parse a while loop
	{
		Pair *p = new Pair('W', 'C'); //If is Type I
		; // move the buffer forward.
		buff = buff + 6; //while(x) , iterator moves to x.
		Pair *t = Parser(buff);
		//MoveIfLeft(Pair *p,Pair *t);
		p->right = t;

		return p;
		
	}
	if (checkforElse(buff))   //check if we have to parse a while loop
	{
		Pair *p = new Pair('E', 'F'); //If is Type I
		; // move the buffer forward.
		buff = buff + 5; //else(x) , iterator moves to x.
		Pair *t = Parser(buff);
		//MoveIfLeft(Pair *p,Pair *t);
		p->right = t;

		return p;

	}


	
	
	if (contains(buff + 1))
	{
		
		Pair *p = new  Pair(*(buff), 'v');
		Pair *t = Parser(buff + 2);  //pass the second char after buff
		result = new  Pair(p, t, *(buff + 1));
		//cout << *(buff + 2) << endl;

		if (*(buff + 3) == ';' && *(buff + 4) != '\0')
		{
			//cout << "yo";
			if (*(buff + 4) == '}')
			{
				buff = buff + 1;
					if (*(buff + 4) == '\0')
					{
						return result;

					}
					Pair *res = new Pair(result, Parser(buff + 4), ')');
					return res;
			}

			Pair *res = new Pair(result, Parser(buff + 4), '[');

			return res;

			//Pair *t = Parser(buff + 1);
			//return t;
		}
		if (*(buff + 4) == '{' && *(buff + 5) != '\0')
		{
			//cout << "yo";

			Pair *res = new Pair(result, Parser(buff + 5), '(');   //if(x=2){z=2;z=3;}x=2;

			return res;

			//Pair *t = Parser(buff + 1);
			//return t;
		}
		
		return result;
		

	}
	


	if (*(buff) == '4' || (*(buff) == '2'))
	{
		Pair *q = new Pair(*(buff), 'v');

		return q;
	}
	
	
	
	
	
	return nullptr;

}
bool contains(char *t)
{
	char *opers = new char[10];
	char temp[10] = "+-=*/<>|&";
	int len = sizeof(temp) / sizeof(temp[0]);
	opers = temp;
	for (char i = 0; i < len; i++)
	{
		if (*t == opers[i])
		{
			return true;

		}

	}

	return false;
}
void printParsetree(Pair *p)
{
	if (p)
	{
		printParsetree(p->left);
		cout << p->value;
		printParsetree(p->right);

	}


}
bool checkforwhile(char *buff)
{
	if (*(buff) == 'w' &&*(buff + 1) == 'h') // "we have a if"
	{
		if (*(buff + 2) == 'i'&&*(buff + 3) == 'l' &&*(buff + 4) == 'e')
		{
			return true;
		}

	}
	return false;

}
bool checkforElse(char *buff)
{
	if (*(buff) == 'e' &&*(buff + 1) == 'l') // "we have a else"
	{
		if (*(buff + 2) == 's'&&*(buff + 3) == 'e')
		{
			return true;
		}

	}
	return false;

}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
