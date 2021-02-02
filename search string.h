#include <boost/rational.hpp>
#include <ctime>	// time()
#include <iomanip>	// setw(), setprecision(), setfill() etc.
#include <iostream>	// cin, cout, etc.
#include <string>	// string class
#include <vector>
#include <stack>
#include <queue>
#include <sstream>

using namespace std;

bool searchstring (string stringtosearch, string wordtolookfor);
int searchstrpos (string stringtosearch, int i);

bool searchstring (string stringtosearch, string wordtolookfor)//search a string for a given string, returns true if string we are looking is found 
{
	const char *str1= stringtosearch.c_str();
	const char *search= wordtolookfor.c_str();
  for (int i = 0; i < strlen(str1); ++i)
  {
    if (strncmp (&str1[i], search, strlen(search)) == 0)
      return true;
  }

  return false;
}

string searchstrfirst (string stringtosearch, int i)//search for function type and returns first instance of function type
{
	int sinpos=-1,cospos=-1,tanpos=-1,cscpos=-1,secpos=-1,cotpos=-1,arcsinpos=-1,arccospos=-1,arctanpos=-1,arccscpos=-1,arcsecpos=-1,arccotpos=-1,lnpos=-1,logpos=-1,exppos=-1,abspos=-1,sqrtpos=-1,pipos=-1;
	priority_queue <int,vector<int>,greater<int>> x;

	if(stringtosearch.find("sin",i)!=-1)
	{
		sinpos=stringtosearch.find("sin",i);
		x.push(sinpos);
	}
	if(stringtosearch.find("cos",i)!=-1)
	{
		cospos=stringtosearch.find("cos",i);
		x.push(cospos);
	}
	if(stringtosearch.find("tan",i)!=-1)
	{
		tanpos=stringtosearch.find("tan",i);
		x.push(tanpos);
	}
	if(stringtosearch.find("csc",i)!=-1)
	{
		cscpos=stringtosearch.find("csc",i);
		x.push(cscpos);
	}
	if(stringtosearch.find("sec",i)!=-1)
	{
		secpos=stringtosearch.find("sec",i);
		x.push(secpos);
	}
	if(stringtosearch.find("cot",i)!=-1)
	{
		cotpos=stringtosearch.find("cot",i);
		x.push(cotpos);
	}
	if(stringtosearch.find("arcsin",i)!=-1)
	{
		arcsinpos=stringtosearch.find("arcsin",i);
		x.push(arcsinpos);
	}
	if(stringtosearch.find("arccos",i)!=-1)
	{
		arccospos=stringtosearch.find("arccos",i);
		x.push(arccospos);
	}
	if(stringtosearch.find("arctan",i)!=-1)
	{
		arctanpos=stringtosearch.find("arctan",i);
		x.push(arctanpos);
	}
	if(stringtosearch.find("arccsc",i)!=-1)
	{
		arccscpos=stringtosearch.find("arccsc",i);
		x.push(arccscpos);
	}
	if(stringtosearch.find("arcsec",i)!=-1)
	{
		arcsecpos=stringtosearch.find("arcsec",i);
		x.push(arcsecpos);
	}
	if(stringtosearch.find("arccot",i)!=-1)
	{
		arccotpos=stringtosearch.find("arccot",i);
		x.push(arccotpos);
	}
	if(stringtosearch.find("ln",i)!=-1)
	{
		lnpos=stringtosearch.find("ln",i);
		x.push(lnpos);
	}
	if(stringtosearch.find("log",i)!=-1)
	{
		logpos=stringtosearch.find("log",i);
		x.push(logpos);
	}
	if(stringtosearch.find("e^",i)!=-1)
	{
		exppos=stringtosearch.find("e^",i);
		x.push(exppos);
	}
	if(stringtosearch.find("abs",i)!=-1)
	{
		abspos=stringtosearch.find("abs",i);
		x.push(abspos);
	}
	if(stringtosearch.find("sqrt",i)!=-1)
	{
		sqrtpos=stringtosearch.find("sqrt",i);
		x.push(sqrtpos);
	}
	if(stringtosearch.find("pi",i)!=-1)
	{
		pipos=stringtosearch.find("pi",i);
		x.push(pipos);
	}

	if(!x.empty())
	{
		if(x.top()==sinpos)
			return "sin";
		if(x.top()==cospos)
			return "cos";
		if(x.top()==tanpos)
			return "tan";
		if(x.top()==cscpos)
			return "csc";
		if(x.top()==secpos)
			return "sec";
		if(x.top()==cotpos)
			return "cot";
		if(x.top()==arcsinpos)
			return "arcsin";
		if(x.top()==arccospos)
			return "arccos";
		if(x.top()==arctanpos)
			return "arctan";
		if(x.top()==arccscpos)
			return "arccsc";
		if(x.top()==arcsecpos)
			return "arcsec";
		if(x.top()==arccotpos)
			return "arccot";
		if(x.top()==lnpos)
			return "ln";
		if(x.top()==logpos)
			return "log";
		if(x.top()==exppos)
			return "exp";
		if(x.top()==abspos)
			return "abs";
		if(x.top()==sqrtpos)
			return "sqrt";
		if(x.top()==pipos)
			return "pi";
	}
	else if(stringtosearch.find("x")!=-1)
	{
		return "poly";//poly for polynomial type
	}
	return "constant";
}

int searchstrpos (string stringtosearch, int i)//search for function type and returns position of function type
{
	int sin=-1,cos=-1,tan=-1,csc=-1,sec=-1,cot=-1,arcsin=-1,arccos=-1,arctan=-1,arccsc=-1,arcsec=-1,arccot=-1,ln=-1,log=-1,exp=-1,abs=-1,sqrt=-1,pi=-1;
	int sinpos=-1,cospos=-1,tanpos=-1,cscpos=-1,secpos=-1,cotpos=-1,arcsinpos=-1,arccospos=-1,arctanpos=-1,arccscpos=-1,arcsecpos=-1,arccotpos=-1,lnpos=-1,logpos=-1,exppos=-1,abspos=-1,sqrtpos=-1,pipos=-1;
	priority_queue <int,vector<int>,greater<int>> x;
	if(stringtosearch.find("sin",i)!=-1)
	{
		sin=stringtosearch.find("sin",i)+2;
		sinpos=stringtosearch.find("sin",i);
		x.push(sinpos);
	}
	if(stringtosearch.find("cos",i)!=-1)
	{
		cos=stringtosearch.find("cos",i)+2;
		cospos=stringtosearch.find("cos",i);
		x.push(cospos);
	}
	if(stringtosearch.find("tan",i)!=-1)
	{
		tan=stringtosearch.find("tan",i)+2;
		tanpos=stringtosearch.find("tan",i);
		x.push(tanpos);
	}
	if(stringtosearch.find("csc",i)!=-1)
	{
		csc=stringtosearch.find("csc",i)+2;
		cscpos=stringtosearch.find("csc",i);
		x.push(cscpos);
	}
	if(stringtosearch.find("sec",i)!=-1)
	{
		sec=stringtosearch.find("sec",i)+2;
		secpos=stringtosearch.find("sec",i);
		x.push(secpos);
	}
	if(stringtosearch.find("cot",i)!=-1)
	{
		cot=stringtosearch.find("cot",i)+2;
		cotpos=stringtosearch.find("cot",i);
		x.push(cotpos);
	}
	if(stringtosearch.find("arcsin",i)!=-1)
	{
		arcsin=stringtosearch.find("arcsin",i)+5;
		arcsinpos=stringtosearch.find("arcsin",i);
		x.push(arcsinpos);
	}
	if(stringtosearch.find("arccos",i)!=-1)
	{
		arccos=stringtosearch.find("arccos",i)+5;
		arccospos=stringtosearch.find("arccos",i);
		x.push(arccospos);
	}
	if(stringtosearch.find("arctan",i)!=-1)
	{
		arctan=stringtosearch.find("arctan",i)+5;
		arctanpos=stringtosearch.find("arctan",i);
		x.push(arctanpos);
	}
	if(stringtosearch.find("arccsc",i)!=-1)
	{
		arccsc=stringtosearch.find("arccsc",i)+5;
		arccscpos=stringtosearch.find("arccsc",i);
		x.push(arccscpos);
	}
	if(stringtosearch.find("arcsec",i)!=-1)
	{
		arcsec=stringtosearch.find("arcsec",i)+5;
		arcsecpos=stringtosearch.find("arcsec",i);
		x.push(arcsecpos);
	}
	if(stringtosearch.find("arccot",i)!=-1)
	{
		arccot=stringtosearch.find("arccot",i)+5;
		arccotpos=stringtosearch.find("arccot",i);
		x.push(arccotpos);
	}
	if(stringtosearch.find("ln",i)!=-1)
	{
		ln=stringtosearch.find("ln",i)+1;
		lnpos=stringtosearch.find("ln",i);
		x.push(lnpos);
	}
	if(stringtosearch.find("log",i)!=-1)
	{
		log=stringtosearch.find("log",i)+2;
		logpos=stringtosearch.find("log",i);
		x.push(logpos);
	}
	if(stringtosearch.find("e^",i)!=-1)
	{
		exp=stringtosearch.find("e^",i)+1;
		exppos=stringtosearch.find("e^",i);
		x.push(exppos);
	}
	if(stringtosearch.find("abs",i)!=-1)
	{
		abs=stringtosearch.find("abs",i)+2;
		abspos=stringtosearch.find("abs",i);
		x.push(abspos);
	}
	if(stringtosearch.find("sqrt",i)!=-1)
	{
		sqrt=stringtosearch.find("sqrt",i)+3;
		sqrtpos=stringtosearch.find("sqrt",i);
		x.push(sqrtpos);
	}
	if(stringtosearch.find("pi",i)!=-1)
	{
		pi=stringtosearch.find("pi",i)+1;
		pipos=stringtosearch.find("pi",i);
		x.push(pipos);
	}

	if(!x.empty())
	{
		if(x.top()==sinpos)
			return sin;
		if(x.top()==cospos)
			return cos;
		if(x.top()==tanpos)
			return tan;
		if(x.top()==cscpos)
			return csc;
		if(x.top()==secpos)
			return sec;
		if(x.top()==cotpos)
			return cot;
		if(x.top()==arcsinpos)
			return arcsin;
		if(x.top()==arccospos)
			return arccos;
		if(x.top()==arctanpos)
			return arctan;
		if(x.top()==arccscpos)
			return arccsc;
		if(x.top()==arcsecpos)
			return arcsec;
		if(x.top()==arccotpos)
			return arccot;
		if(x.top()==lnpos)
			return ln;
		if(x.top()==logpos)
			return log;
		if(x.top()==exppos)
			return exp;
		if(x.top()==abspos)
			return abs;
		if(x.top()==sqrtpos)
			return sqrt;
		if(x.top()==pipos)
			return pi;
	}
	else
		return -1;
}