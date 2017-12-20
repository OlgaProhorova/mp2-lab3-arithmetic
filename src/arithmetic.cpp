// реализация функций и классов для вычисления арифметических выражений

#include "arithmetic.h"
#include <ctype.h>

string op = "+*-/";
string opbr = "([";
string clbr = "])";
string sqbr = "[]";
string rbr = "()";

lexem::lexem(string s,lextype t)
{
	type=t;
	lstr=s;
};

lexem::lexem(const lexem &l)
{
	type=l.type;
	lstr=l.lstr;
};

lexem& lexem::operator = (const lexem &l)
{
	type=l.type;
	lstr=l.lstr;
	return *this;
};

bool lexem::operator == (const lexem &l) const
{
	bool res=true;
	if (type!=l.type) res=false;
	if (lstr!=l.lstr) res=false;
	return res;
};

int lexem::prior()
{
	int pr;
	if ((lstr==")")||(lstr=="(")) pr=0;
	if ((lstr=="-")||(lstr=="+")) pr=1;
	if ((lstr=="/")||(lstr=="*")) pr=2;
	return pr;
};

variable::variable(string n,double val)
{
	value=val;
	name=n;
};

variable::variable(const variable &v)
{
	value=v.value;
	name=v.name;
};

variable& variable::operator = (const variable &v)
{
	value=v.value;
	name=v.name;
	return *this;
};

ariphmetic::ariphmetic(string str)
{
	inps=str;
	lexemes=new lexem[inps.size()];
	nlex=0;
	vars=new variable[10];
	nvars=0;
	size_t p1,p2,p3;
	int kbr=0,i=0;
	while(i<inps.size())
	{
		p1 = opbr.find(inps[i]);
		if (p1 != std::string::npos)
		{
			string opbrs;
			opbrs = inps[i];
			lexemes[nlex].setlex(opbrs);
			lexemes[nlex].settype(OP_BR);
			nlex++;
			kbr++;
		}
		p2 = clbr.find(inps[i]);
		if (p2!= std::string::npos)
		{
			string clbrs;
			clbrs = inps[i];
			lexemes[nlex].setlex(clbrs);
			lexemes[nlex].settype(CL_BR);
			nlex++;
			kbr++;
		}
		p3 = op.find(inps[i]);
		if (p3 != std::string::npos)
		{
			string ops;
			ops = inps[i];
			lexemes[nlex].setlex(ops);
			lexemes[nlex].settype(OPER);
			nlex++;
		}
		if (isalpha(inps[i]))
		{
			char a[10];
			string as;
			int j = 0;
			while ((i < inps.size()) && (isalpha(inps[i])))
			{
				a[j] = inps[i];
				j++;
				i++;			
			 }
			i--;
			a[j++] = '\0';
			as = a;
			vars[nvars].setname(as);
			nvars++;
			lexemes[nlex].setlex(as);
			lexemes[nlex].settype(VAR);
			nlex++;
		}
		if (isdigit(inps[i]) != 0)
		{
			char c[16];
			string cs;
			int j = 0;
			while (((isdigit(inps[i]) != 0)||(inps[i]=='.'))&&(i < inps.size()))
			{
				c[j] = inps[i];
				j++;
				i++;
			}
			i--;
			cs = c;
			cs.erase(j);
			lexemes[nlex].setlex(cs);
			lexemes[nlex].settype(VAL);
			nlex++;
		}
		i++;
	}
	lexem *lex;
	lex = new lexem[nlex];
	for (int i = 0;i < nlex;i++)
		lex[i] = lexemes[i]; 
	delete[] lexemes;
	lexemes = new lexem[nlex];
	for (int i = 0;i < nlex;i++)
		lexemes[i] = lex[i]; 
	delete[] lex;
	variable *vr;
	vr = new variable[nvars];
	for (int i = 0;i < nvars;i++)
		vr[i] = vars[i];
	delete[] vars;
	vars = new variable[nvars];
	for (int i = 0;i < nvars;i++)
		vars[i] = vr[i];
	delete[] vr;
	polish = new lexem[nlex - kbr];
	npolish = 0;
};

bool ariphmetic::check() 
{
	size_t p1,p2,p3,p4,p5,p6;
	stack <char> st(100);
	for (int i=0;i<inps.length();i++)
	{
		p1 = opbr.find(inps[i]);
		p2 = clbr.find(inps[i]);
		p3 = rbr.find(inps[i]);
		p4 = sqbr.find(inps[i]);
		if (p1!= std::string::npos) st.push(inps[i]);
		else
		{
			if (p2!= std::string::npos)
			{
				if (st.isempty() == true)
				{
					cout << "Error. Closing bracket before opening.";
					return false;
				}
				p5 = rbr.find(st.gettop());
				p6 = sqbr.find(st.gettop());
				if (((p3!=std::string::npos)&&(p6!=std::string::npos))||((p4!=std::string::npos)&&(p5!=std::string::npos)))
				{
					cout << "Error. Can't put different closing bracket.";
					return false;
				}
				else st.pop();
			}
		}
     }
	 if (st.isempty()==false)
		{
		    cout << "Error. More opening brackets than closing.";
			return false;
		}
	 for (int i=0;i<inps.length();i++)
	{
		if (inps[i]==' ')
		{
			cout << "Error. Spaces.";
			return false;
		}
		if(i!=(inps.length()-1))
		{
			p1 = op.find(inps[i]);
			p2 = op.find(inps[i+1]); 
			if ((inps[i]=='(')&&(p2!=std::string::npos)&&(inps[i+1]!='-'))
			{
				cout << "Error. Can't put " << inps[i+1] << " after " << inps[i];
				return false;
			}
			if ((p1!=std::string::npos)&&(p2!=std::string::npos))
			{
				cout << "Error.Two operators in row: " << inps[i] << inps[i+1];
				return false;
			}
			if ((p1!=std::string::npos)&&(inps[i+1]==')'))
			{
				cout << "Error. an't put " << inps[i] << " before" << inps[i+1];
				return false;
			}
		}
	}
	int p = op.find(inps[inps.length()-1]);
	if (p!=std::string::npos)
	{
		cout << "Error. Can't put an operator in the end of expression";
		return false;
	}	
	return true;
};

void ariphmetic::getpolish() 
{
	lexem c;
	stack<lexem> st;
	lexem x;
	for(int i=0;i<nlex;i++)
	{
		c=lexemes[i];
		if((c.gettype()==VAL)||(c.gettype()==VAR))
		{
			polish[npolish]=c;
			npolish++;
	    }
		if(c.gettype()==OP_BR) st.push(c);
		if(c.gettype()==OPER)
		{
			if(st.isempty()) st.push(c);
			else
			{
				x = st.gettop();
				while(c.prior()<=x.prior())
				{
					x = st.pop();
					polish[npolish] = x;
					npolish++;
					if(!(st.isempty())) x = st.gettop();
					else break;
				}
				st.push(c);
			}
		}
		if (c.getstr()==")")
		{
			x = st.pop();
			while (x.getstr()!="(")
			{
				polish[npolish] = x;
				npolish++;
				x = st.pop();
			}
		}
	}
	while (!st.isempty())
	{
		x = st.pop();
		polish[npolish] = x;
		npolish++;
	}
};

void ariphmetic::setvars()
{
	double zn;
	bool f;
	for (int i=0;i<nvars;i++)
	{		
		f = true;
		for(int j=0;(j<i)&&(f);j++)
		{
			if(vars[i].getname()==vars[j].getname())
			{
				vars[i].setvalue(vars[j].getvalue());
				f = false;
			}
		}
		if (f)
		{
			string str = vars[i].getname();
			cout << "Enter the value of the variable " << str << endl;
			cin >>zn;
			vars[i].setvalue(zn);
		}
	}
};

double ariphmetic::calculate() 
{
	double res;
	stack<double> st;
	double x;
	int nvar=0;
	for (int i=0;i<npolish;i++)
	{
		if (polish[i].gettype()==VAL) 
		{
			x = atof(polish[i].getstr().c_str());
			st.push(x);
		}
		if (polish[i].gettype()==VAR)
		{
			x = vars[nvar].getvalue();
			st.push(x);
			nvar++;
		}
		if (polish[i].gettype()==OPER)
		{
			double c,b = st.pop();
			double a = st.pop();
			if (polish[i].getstr()=="+")
				c = a + b;
			if (polish[i].getstr()=="-")
				c = a - b;
			if (polish[i].getstr()=="*")
				c = a*b;
			if (polish[i].getstr()=="/")
				c = a/b;
			st.push(c);
		}
	}
	res = st.pop();
	return res;
};

string minus(string s)
{
	size_t p;
	if (s[0]=='-')
	{
		s.insert(0, "0");
	}
	for (int i=01;i<s.length();i++)
	{
		p = opbr.find(s[i-1]);
		if ((s[i]=='-')&&(p!=std::string::npos))
		{
			s.insert(i, "0");
		}
	}
	return s;
};
