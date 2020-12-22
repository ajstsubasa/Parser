// Parser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include"Pair.h"
#include"If.h"
#include"While.h"
#include"Else.h"
#include"For.h"
#include"Seq.h"

using namespace std;
//constexpr Pair *Parser(const char );
void printParsetree(Pair *);
//bool contains(const char *);
constexpr bool checkforwhile(const char *);
constexpr bool checkforElse(const char *);
constexpr bool checkforFor(const char *);
constexpr int calculateJump(const char *);

template<std::size_t amnt> struct Mem {
	Pair mem[amnt];
};

constexpr bool contains(const char *t)
{
	//char *opers = new char[10];
	char temp[10] = "+-=*/<>|&";
	int len = sizeof(temp) / sizeof(temp[0]);
	//opers = temp;
	for (char i = 0; i < len; i++)
	{
		if (*t == temp[i])
		{
			return true;

		}

	}
	//delete [] opers;
	return false;
}
constexpr bool isdig(char x)
{
	char digits[10] = { '0','1','2','3','4','5','6','7','8','9' };
	for (int i = 0; i < 10; i++)
	{
		if (x == digits[i])
		{
			return true;
		}
	}

	return false;

}
constexpr bool isalph(char x)
{

	if ((x >= 97 && x <= 122) || (x >= 65 && x <= 90))
	{
		return true;
	}
	return false;


}


constexpr Pair *Parser(Mem<100> *m, const char *buff, int curr_index)
{
	

	if (*buff == '\0')
	{

		return nullptr;
	}
	if (*buff == ' ')
	{

		buff = buff + 1;
	}

	

	if (*(buff) == 'i' &&*(buff + 1) == 'f') // "we have a if"
	{
		If r = If('I', 'F');
		If *p = &r;  //If is Type I//  new If('I', 'F')





		buff = buff + 3; //if(x) , iterator moves to x.
		Pair *t = Parser(m, buff, curr_index + 2);
		//MoveIfLeft(Pair *p,Pair *t);
		p->setRight(t);
		p->setright_index(curr_index + 1);
		m->mem[curr_index] = *p;
	
		return nullptr;


	}


	if (checkforwhile(buff))   //check if we have to parse a while loop
	{
	
		While r = While('W', 'C');
		While *p = &r;

		// move the buffer forward.
		buff = buff + 6; //while(x) , iterator moves to x.
		Pair *t = Parser(m, buff, curr_index + 2);
		//MoveIfLeft(Pair *p,Pair *t);
		p->setRight(t);
		p->setright_index(curr_index + 1);
		m->mem[curr_index - 1] = *p;
		m->mem[curr_index - 1].setcurr_index(curr_index - 1);

		
		return nullptr;

		//return p;

	}

	if (checkforElse(buff))   //check if we have to parse a Else loop
	{
		//Else *p = new Else('E', 'F'); //If is Type I
		Else r = Else('E', 'F');
		Else *p = &r;

		buff = buff + 5; //else(x) , iterator moves to x.
		Pair *t = Parser(m, buff, curr_index + 2);
		//MoveIfLeft(Pair *p,Pair *t);
		p->setRight(t);
		p->setright_index(curr_index + 1);
		m->mem[curr_index - 1] = *p; // Else can never start first so i subtract one from curr_index;
		m->mem[curr_index - 1].setcurr_index(curr_index - 1);

		return nullptr;
		//return p;

	}

	if (checkforFor(buff))   //check if we have to parse a Else loop
	{
		For *p = new For('F', 'C'); //If is Type I
		; // move the buffer forward.
		m->mem[curr_index] = *p;
		buff = buff + 4; //for(x) , iterator moves to x.
		Pair *t = Parser(m, buff, curr_index + 2);
		//MoveIfLeft(Pair *p,Pair *t);
		p->setRight(t);
		p->setright_index(curr_index + 1);
		m->mem[curr_index + 1] = *t;

		return p;

	}

	if (contains(buff + 1))
	{
		char oper[2] = { '0','0' };
		const char *dummy = buff + 1;
		int i = 0;
		while (contains(dummy))
		{
			oper[i] = *(dummy);
			dummy = dummy + 1;
			i = i + 1;


		}
		int operjump = i - 1;// oper jump is used to fix issue with len>1 operators like i++; ==;


		 Pair r = Pair(*(buff), 'v');
		 Pair *p = &r;


		Parser(m, buff + 2 + operjump, curr_index);  //pass the second char after buff
		//result = nullptr;

		Pair *result = nullptr;

		

		if (operjump == 0)
		{

	

			 Pair s = Pair(nullptr, nullptr, *(buff + 1));


			

			
			s.setcurr_index(curr_index);

		    s.setleft_index(curr_index + 1);
			s.setright_index(curr_index + 2);

			m->mem[curr_index] = s;

	
			m->mem[s.getleft_index()] = *p;
			
		
		}
		else
		{
			Pair  s =   Pair(nullptr, nullptr, *(buff + 1), 'E'); // if the operator length >1;
			result = &s;
			result->setcurr_index(curr_index);
			result->setleft_index(result->getcurr_index() + 1);
			result->setright_index(result->getcurr_index() + 2);

			result->setcurr_index(curr_index);
			m->mem[curr_index] = *result;

		//	m->mem[result->getright_index()] = *t;
			m->mem[result->getleft_index()] = *p;

		}

	

		int jump = calculateJump(buff) + operjump;
		jump = jump - 1;
		buff = buff + jump; //move buffer ahead by jump so below logic works.//since i am moving buffer by constant.
		if (*(buff + 3) == ';' && *(buff + 4) != '\0')
		{
			//cout << "yo";
			if (*(buff + 4) == '}')
			{
				buff = buff + 1;
				if (*(buff + 4) == '\0')
				{
					
					 
					m->mem[curr_index - 1] = m->mem[curr_index];
					return nullptr;
					//return result;

				}
				//cout << "yo";
				//Pair *res = new Pair(result, Parser(m,buff + 4,result->getright_index()+2), ')');
				int me = m->mem[curr_index].getright_index() + 2;
				int right = me - 1;
				Pair q = Pair(result, Parser(m, buff + 4, me), ')');
				Pair *res = &q;

				res->setleft_index(curr_index);
				res->setright_index(right);
				//	res->setcurr_index(result->getright_index() + 2);

				m->mem[curr_index - 1] = *res;

				//return res;
				return nullptr;
			}

			//Pair *res = new  Pair(result, Parser(m, buff + 4, result->getright_index() + 2), '[');
			int me = m->mem[curr_index].getright_index() + 2;
			Pair q = Pair(result, Parser(m, buff + 4, me), '[');
			Pair *res = &q;

			res->setleft_index(curr_index);
			res->setright_index(me-1);
			

			m->mem[curr_index - 1] = *res;    

			
			return nullptr;
		}
		

		if (*(buff + 4) == '{' && *(buff + 5) != '\0')
		{
			//cout << "yo";

			//Pair *res = new Pair(result, Parser(m,buff + 5, result->getright_index() + 2), '(');   //if(x=2){z=2;z=3;}x=2;
			int me = m->mem[curr_index].getright_index() + 2;
			int right = me - 1;
			Pair q = Pair(result, Parser(m, buff + 5, me ), '(');
		    
			 Pair *res = &q;
			res->setleft_index(curr_index);

			//cout << curr_index << " " << result->getright_index() + 1;
			//cout << "yo";
			res->setright_index(right); // 334 325 267 217


			

			int now  = m->mem[curr_index].getcurr_index()-1;
			m->mem[now] = *res;

			//Pair *res = &q;
		

 			//return  res;
			return nullptr;

			//Pair *t = Parser(buff + 1);
			//return t;
		}
		if ((isalph(*(buff + 4))))
		{
			//cout << "yo";

			Pair *res = new Pair(result, Parser(m, buff + 4, result->getright_index() + 2), '(');   //if(x=2){z=2;z=3;}x=2;
			res->setleft_index(curr_index);

			res->setright_index(result->getright_index() + 1);
			//res->setcurr_index(result->getright_index() + 2);


			//m->mem[result->getright_index() + 1] = *res;

			m->mem[result->getcurr_index() - 1] = *res;

			//return res;
			return nullptr;

			
		}
		
		m->mem[curr_index - 1] = *result;

		//m->mem[3] = *result;
		return nullptr;
		//return result;


	}



	//if (*(buff) == '4' || (*(buff) == '2')) //Checking for digits.
	char val[10] = { 'N','N','N','N' ,'N','N' ,'N','N','N','N' };
	for (int i = 0; i < sizeof(val) / sizeof(val[0]); i++)
	{
		val[i] = 'N';

	}


	while (isdig(*(buff)))
	{ //This is where you ar going to fix the more then 1 digit parsing 
		// problem //.
		char temp = *(buff);
		for (int i = 0; i < sizeof(val) / sizeof(val[0]); i++)
		{
			if (val[i] == 'N')
			{
				val[i] = temp;
				break;
			}

		}
		buff = buff + 1;
		if (!isdig(*(buff)))
		{
			buff = buff - 1; //set buff back to last digit

			Pair q =  Pair(val, 'd');
	
			m->mem[curr_index + 2] = q;

			return nullptr;
		}


	}


	return nullptr;

}

void printParsetree(Pair *p)
{
	if (p)
	{
		printParsetree(p->getLeft());
		if (p->gettype() == 'd')
		{
			cout << p->getval();
		}
		else
		{
			cout << p->getvalue();
		}
		printParsetree(p->getRight());

	}


}
constexpr bool checkforwhile(const char *buff)
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
constexpr bool checkforElse(const char *buff)
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
constexpr bool checkforFor(const char *buff)
{
	if (*(buff) == 'f' &&*(buff + 1) == 'o') // "we have a else"
	{
		if (*(buff + 2) == 'r')
		{
			return true;
		}

	}
	return false;

}
constexpr int calculateJump(const char *buffer)
{
	int jump = 0;
	while (!(isdig(*buffer)))
	{
		buffer = buffer + 1;
	}


	while ((isdig(*buffer)))
	{
		jump = jump + 1;
		buffer = buffer + 1;
	}


	return jump;
}
void deleteParsetree(Pair *p)
{
	if (p)
	{
		deleteParsetree(p->getLeft());
		delete p;
		deleteParsetree(p->getRight());

	}


}
void print(Mem<100> *m, int  i)
{
	//cout << m->mem[0].getvalue();
	if (i != -1)
	{
		//cout << m->mem[i].getleft_index() << " " << m->mem[i].getright_index() <<"  "<<i<< endl;;
		print(m, m->mem[i].getleft_index());
		if (m->mem[i].gettype() == 'd')
		{
			cout << m->mem[i].getval();
		}
		else
		{
			cout << m->mem[i].getvalue();
		}

		print(m, m->mem[i].getright_index());

	}


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

constexpr  Mem<100> constexpr_wrapper( const char *buff) {

	//l.Current = Pair('i', 'j');
	//r.Current = Pair('i', 'u');;
	Mem<100> m;
	Parser(&m, buff, 0);



	return m;

}






int main()
{
	const char *buffer = new char[150];

	constexpr char temp[40] = "x=2;y=2;";
	char temp2[55] = "x=2;y=2;if(x=2){x=2;}";
	char temp3[55] = "if(x==2){y=222;}x=2;";
	char temp4[55] = "if(x<2){z=3;}else{z=3;}z=3;";
	char temp5[62] = "for(i=0;i<56;i++){for(j=0;j<56;j++){if(x=2){x=3;}";
	char temp6[55] = "if(x<1){y=2;x=2;z=2;t=2;}";
	 constexpr char temp7[55] = "if(x<1){x=2;}while(x<1){y=2;x=2;z=2;t=2;}";
	constexpr char temp8[55] = "if(x<1){y=2;}";
	buffer = temp7;



    constexpr Mem<100> m = constexpr_wrapper(temp7);

	static_assert(m.mem[0].getvalue() == 'I', "Failed test");
	static_assert(m.mem[m.mem[0].getright_index()].getvalue() == '(', "Failed test");
	static_assert(m.mem[0].getleft_index()==-1, "Failed test");
  

	//print(&m, 0);

	//printParsetree(p);
	//deleteParsetree(p);

	//printParsetree(p);

	return 0;
}

