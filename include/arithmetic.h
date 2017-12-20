// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#pragma once
#include <cstring>
#include <cstdlib>
#include  <cctype>
#include "stack.h"
#include <string>
#include <iostream>

using namespace std;

enum lextype{OP_BR,VAL,OPER,VAR,CL_BR};

const int mas = 10;

class lexem
{
		string lstr;
		lextype type;
	public:
		lexem(){};
		lexem(string s,lextype t);
		lexem(const lexem &l);
		lexem& operator = (const lexem &l);
		bool operator == (const lexem &l) const;
		int prior();
		void setlex(string s)
		{lstr=s;};
		void settype(lextype t) 
		{type = t;};
		lextype gettype() 
		{return type;}
		string getstr() 
		{return lstr;}
};

class variable
{
		string name;
		double value;
	public:
		variable(){};
		variable(string n,double val);
		variable(const variable &v);
		variable& operator = (const variable &v);
		string getname() 
		{return name;};
		void setvalue(double v) 
		{value = v;};
		double getvalue() 
		{return value;};
		void setname(string a) 
		{name=a;};
};

class ariphmetic
{
		string inps;
		lexem*lexemes;
		int nlex;
		lexem *polish;
		int npolish;
		variable *vars;
		int nvars;
	public:
		ariphmetic(string str);
		bool check();
		void getpolish();
		void setvars();
		double calculate();
		string getstrn(int i)
		{
			return lexemes[i].getstr();
		}
};

string minus(string s);