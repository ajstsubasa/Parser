#pragma once
class Pair
{
public:
	Pair *left;
	Pair *right;
	char type ; // t is the type.
public:
	char value;

public:
	 char val[10];
	 char oper[2];

public:
	Pair(Pair *l, Pair *r, char t) {

		left = l;
		right = r;
		this->type = t;
		this->value = t;
	}
	Pair(Pair *l, Pair *r, char t, char value) {

		left = l;
		right = r;
		this->type = t;
		this->value = value;
		
	}
	Pair()
	{
		int r = 0;

	}
	Pair(char x, char type)
	{
		left = nullptr;
		right = nullptr;

		this->type = type;
		this->value = x;


	}
	Pair(char x[], char type)
	{
		this->type = type;
		int len = sizeof(val) / sizeof(x[0]);
		for (int i = 0; i < len;i++)
		{
			if (x[i] == 'N')
			{
				val[i] ='\0';
				break;
			}
			val[i] = x[i];

		}
		
	

	}




};

