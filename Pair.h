#pragma once
class Pair
{
public:
	Pair *left;
	Pair *right;
	char t ; // t is the type.
public:
	char value ; 

public:
	Pair(Pair *l, Pair *r, char t) {

		left = l;
		right = r;
		this->t = t;
		this->value = t;
	}
	Pair()
	{
		int r = 0;

	}
	Pair(char x, char type)
	{
		left = nullptr;
		right = nullptr;

		this->t = type;
		this->value = x;


	}




};

