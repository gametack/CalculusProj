#include <boost/rational.hpp>
#include <boost/config.hpp>
#include <boost\lexical_cast.hpp>
#include <iostream>	// cin, cout, etc.
#include <string>	// string class
#include <queue>


using namespace std;
using boost::rational;
using boost::lexical_cast;

string getdata(string x);// gets the function and splits it into smaller functions separated by operators
string derive(string x);
string chainrule(string x, string pow);
string sin(string inner, string outer);//sin
string cos(string inner, string outer);//cos
string tan(string inner, string outer);//tan
string csc(string inner, string outer);//cot
string sec(string inner, string outer);//csc
string cot(string inner, string outer);//sec
string arcsin(string inner, string outer);//arc
string arccos(string inner, string outer);//arc
string arctan(string inner, string outer);//arc
string arccsc(string inner, string outer);//arc
string arcsec(string inner, string outer);//arc
string arccot(string inner, string outer);//arc
string ln(string inner, string outer);//ln
string log(string inner, string outer);//log
string exponential(string x, string pow);//c^(u), ex 2^(x), or e^(x), where x is a constant
string logarithmic(string x, string pow);//u^(u), ex x^(x), where x is not a constant
string polynomial(string x);//polynomial

string getdata(string x)// gets the function and splits it into smaller functions separated by operators
{

    x=simplify(x);//simplifies the function before taking the derivative
    string result;
	vector <string> replacer(1);
    derivativesteps<<"`";
	replacer=rewriteseparatebyplusminus(x);
	for(int n=0; n<replacer.size(); n++)
	{
		
		if(replacer.size()>1)
		{
            derivativesteps<<"d/dx("+convert2ascii(replacer[n])+")";
			if(n<replacer.size()-1)
			{
				derivativesteps<<"+";
			}
		}
	}
    derivativesteps<<"`<br>"<<endl;
	for(int n=0; n<replacer.size(); n++)
	{
		if(replacer[n].find("x")==-1)
		{
			result+="0";
		}
		else
		{
			result+=derive(replacer[n]);
		}
		if(n<replacer.size()-1)
		{
			result+='+';
		}
	}

	return simplify(result);
}

string derive(string x)// Check to see what type of function is present, and takes the necessary actions
{
    string result;

	// check if multiply function in one term,  ex: sinx(x)  or (x^2)tan(x)
	int amountofx=0; // test for how many time x appears in a term

	for(int i=0; i<x.length();i++) //loop through function to determine how many times x appears
	{
		if(x[i]=='x')
		{
			amountofx++; //counts how many times x appears
		}
	}

	if(amountofx > 1) //if product rule function
	{
		vector <string> replacer(1);
		string check=x;
		bool can_do=true;
		replacer=rewriteseparatebymultiply(check);
		for (int n =0; n<replacer.size(); n++)
		{
			if(replacer[n].find("x") == -1)
			{
				can_do=false;
				break;
			}
		}
		if(replacer.size()>1 && can_do==true)
		{
			vector<string> replacer(1);//string array to pass x to
			string func=x;
			char count='u';
			string a;

			replacer=rewriteseparatebymultiply(x);//parses sin(x)cos(x) into [sin(x)] and [cos(x)] which is stored in replacer
			for(int n=0; n<replacer.size(); n++)
			{
				a.push_back(count);
				count++;
			}
			/*		
			The rule for product rule is dictated by, (uvw)' = (vw)(u')+(uw)(v')+uv(w')
			*/		


            derivativesteps<<endl<<endl<<"<p style=\"BACKGROUND-COLOR: #00FF00\">`d/dx("+convert2ascii(func)+") = `<br>"<<endl;
            derivativesteps<<"Using Product Rule `: d/dx(u*v*w) = (v*w)*((du)/dx)+(u*w)*((dv)/dx)+u*v*((dw)/dx)`<br>"<<endl;
			for(int n=0; n<replacer.size(); n++)
			{
                derivativesteps<<"`{`<br>"<<endl;
				result+="(";
                derivativesteps<<"`(";
				for(int i=0; i<replacer.size(); i++)
				{
					if(i!=n)
					{
						result+=replacer[i];
                        derivativesteps<<convert2ascii(replacer[i]);

					}
				}

                derivativesteps<<")";
				result+=")";
                derivativesteps<<"*(d/dx("+convert2ascii(replacer[n])+"))`<br>"<<endl;
                derivativesteps<<"Where `"<<a[n]<<" = "+convert2ascii(replacer[n])+"` and `(d"+a[n]+")/dx = `";

                result+="("+getdata(replacer[n])+")";
                derivativesteps<<"<p style=\"BACKGROUND-COLOR: #00FF00\">";
                derivativesteps<<"`}`<br><br>"<<endl<<endl;
                if(n+1!=replacer.size())
                {
                    derivativesteps<<"`+`";
                    result+="+";
                    derivativesteps<<"<br><br>"<<endl<<endl;
				}

            }
            derivativesteps<<"`d/dx("+convert2ascii(func)+") = "+convert2ascii(result)<<"`<br>"<<endl;
			result=simplifymathproperties(result);
            derivativesteps<<"Simplified: `d/dx("+convert2ascii(func)+") = "+convert2ascii(result)<<"`<br>"<<endl;
		}
	}

	if(result.empty()) // will test for exponential, logarithmic, and chain rule function and implement such rule is exists
	{
		string keep=x;
		if(x[x.length()-1]==')')
		{

			string collect,pow;
			int find=(parenpos(x,x.length()-1))-1;
			if(x[find]=='^')
			{
				int i=0;
				while(i<find)
				{
					collect+=x[0];
					x.erase(0,1);
					i++;
				}
				x.erase(0,1);
				pow=x;
				if(collect.find("x")==-1 && pow.find("x")!=-1)
				{
					
					result=exponential(collect,pow);
				}
				else if(collect.find("x")!=-1 && pow.find("x")!=-1)
				{
					
					result=logarithmic(collect,pow);
				}
				else if(rewriteseparatebyplusminus(collect).size()>1 || rewriteseparatebymultiply(collect).size()>1 || searchstrfirst(collect,0)!="poly")
				{
					result = chainrule(collect,pow);
				}
				else
					x=keep;
			}
		}
	}

	if(result.empty()) // will separate like, sin(x) to sin and (x) and pass it to specific function for chainrule implementation
	{
		string outer,inner;
		int pos,i=0;
		pos=searchstrpos(x,0);
		while(i<=pos)
		{
			outer+=x[0];
			x.erase(0,1);
			i++;
		}
		inner=x;
		
		if (searchstrfirst(outer,0)=="sin" && result.empty())//does the derivative for sin
		{
			result=sin(inner,outer);
		}
		if (searchstrfirst(outer,0)=="cos" && result.empty())//does the derivative for cos
		{
			result=cos(inner,outer);
		}
		if (searchstrfirst(outer,0)=="tan" && result.empty())
		{
			result=tan(inner,outer);
		}
		if (searchstrfirst(outer,0)=="csc" && result.empty())
		{
			result=csc(inner,outer);
		}
		if (searchstrfirst(outer,0)=="sec" && result.empty())
		{
			result=sec(inner,outer);
		}
		if (searchstrfirst(outer,0)=="cot" && result.empty())
		{
			result=cot(inner,outer);
		}
		if (searchstrfirst(outer,0)=="arcsin" && result.empty())
		{
			result=arcsin(inner,outer);
		}
		if (searchstrfirst(outer,0)=="arccos" && result.empty())
		{
			result=arccos(inner,outer);
		}
		if (searchstrfirst(outer,0)=="arctan" && result.empty())
		{
			result=arctan(inner,outer);
		}
		if (searchstrfirst(outer,0)=="arccsc" && result.empty())
		{
			result=arccsc(inner,outer);
		}
		if (searchstrfirst(outer,0)=="arcsec" && result.empty())
		{
			result=arcsec(inner,outer);
		}
		if (searchstrfirst(outer,0)=="arccot" && result.empty())
		{
			result=arccot(inner,outer);
		}
		if (searchstrfirst(outer,0)=="ln" && result.empty())
		{
			result=ln(inner,outer);
		}
		if (searchstrfirst(outer,0)=="log" && result.empty())
		{
			result=log(inner,outer);
		}
	}

	if (searchstring(x, "x") && searchstrpos(x,0)==-1 && result.empty())
	{
		result=polynomial(x);
	}

	if(result=="")//if derivative returns nothing, so if y=6 then derivative is 0 so it returns nothing
	{
	}
	else
	{
	result=simplify(result);
	}

	return result;
}

string chainrule(string x, string pow)//chain rule
{
/*
	The rule for chain rule is dictated by, (a(ux+b)^c)' = c*x((ux+b)^c-1)(ux+b)'.
	ex. 5(sin(x))^2 = 5*2((sin(x))^2-1)(sin(x))' = 10(sin(x))^1)(cos(x)) = 10sin(x)cos(x)
	*/
	

	string derx,result;//holds the derivative of u, where u is a non constant function stored in string x;
    string coeff;
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #FF3333\">";
    derivativesteps<<endl<<"<br>`d/dx(("<<convert2ascii(x)<<")^"<<convert2ascii(pow)<<")`:<br>"<<endl;
    derivativesteps<<"Using Chain Rule `: d/dx(a(u)^(b)) = a*b(u)^(b-1)*((du)/dx),` Where a and b are constants<br>"<<endl;
    derivativesteps<<"`d/dx(("<<convert2ascii(x)<<")^"<<convert2ascii(pow)<<") = ";
	if(isdigit(x[0]) || (x[0]=='-' && isdigit(x[1])))
	{
		while(x[0]!='(' && !isalpha(x[0]))
		{
			coeff+=x[0];
			x.erase(0,1);
		}
	}
	else
	{
		if(x[0]=='-' && !isdigit(x[1]))
		{
			x.erase(0,1);
			coeff="-1";
		}
		else
		{
			coeff="1";
		}
	}
    derivativesteps<<"(("<<coeff<<"*"<<convert2ascii(pow)<<")*("<<convert2ascii(x)<<")^("<<convert2ascii(pow)<<"-1))*(d/dx("<<convert2ascii(x)<<"))`<br>"<<endl;
    derivativesteps<<"Where `u = "<<convert2ascii(x)<<"` and `(du)/dx = `";
	//erase parenthesis around function
	x=simplifyextras(x);
    string cpow=pow;
	coeff=simplifymultiplyliketerms(coeff+"*"+pow+"case");
	pow=simplifyaddliketerms(pow+"-1");

	derx=getdata(x);//get derivative of u. du/dx

    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #FF3333\">";

	result=coeff+"("+x+")^("+pow+")("+derx+")";
    derivativesteps<<endl<<"<br>`d/dx(("<<convert2ascii(x)<<")^"<<convert2ascii(cpow)<<") = "<<convert2ascii(result)<<"`<br>"<<endl;
	return result;
}



string sin(string inner, string outer)//sin
{
	
	string derinner,result;//holds the derivative of u, where u is a non constant function stored in string x;
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #CC3399\">";
    derivativesteps<<endl<<"`d/dx("<<convert2ascii(outer+inner)<<")`:<br>"<<endl;
    derivativesteps<<"Rule `: d/dx(sin(u)) = cos(u)*((du)/dx),` Where u is not a constant<br>"<<endl;
    derivativesteps<<"`d/dx("<<convert2ascii(outer+inner)<<") = ";
    string keepouter=outer;
	outer.replace(outer.find("sin"),3,"cos");
    derivativesteps<<convert2ascii(outer+inner)<<"(d/dx"<<convert2ascii(inner)<<")`<br>"<<endl;
    derivativesteps<<"Where `u = "<<convert2ascii(inner)<<"`and `(du)/dx = `";
    derinner=getdata(inner);

    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #CC3399\">";
	result=outer+inner+"("+derinner+")";
    derivativesteps<<endl<<"<br>`d/dx("<<convert2ascii(keepouter+inner)<<") = "<<convert2ascii(result)<<"`<br>"<<endl;
	return result;
}

string cos(string inner, string outer)//cos
{
	
	string derinner,result;//holds the derivative of u, where u is a non constant function stored in string x;
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #99FFFF\">";
    derivativesteps<<endl<<"`d/dx("<<convert2ascii(outer+inner)<<")`:<br>"<<endl;
    derivativesteps<<"Rule `: d/dx(cos(u)) = -sin(u)*(d/dx(u)),` Where u is not a constant<br>"<<endl;
    derivativesteps<<"`d/dx("<<convert2ascii(outer+inner)<<") = -";
    string keepouter=outer;
	outer.replace(outer.find("cos"),3,"sin");
    derivativesteps<<convert2ascii(outer+inner)<<"(d/dx"<<convert2ascii(inner)<<")`<br>"<<endl;
    derivativesteps<<"Where `u = "<<convert2ascii(inner)<<"`and `(du)/dx = `";

	derinner=getdata(inner);
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #99FFFF\">";
	result="-"+outer+inner+"("+derinner+")";
	result=rewritedoubleoperation(result);
    derivativesteps<<endl<<"<br>`d/dx("<<convert2ascii(keepouter+inner)<<") = "<<convert2ascii(result)<<"`<br>"<<endl;
	return result;
}

string tan(string inner, string outer)//tan
{
	
	string derinner,result;//holds the derivative of u, where u is a non constant function stored in string x;
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #FF66FF\">";
    derivativesteps<<endl<<"<br>`d/dx("<<convert2ascii(outer+inner)<<")`:<br>"<<endl;
    derivativesteps<<"Rule `: d/dx(tan(u)) = sec(u)^2*(d/dx(u)),` Where u is not a constant<br>"<<endl;
    derivativesteps<<"`d/dx("<<convert2ascii(outer+inner)<<") = ";
    string keepouter=outer;
	outer.replace(outer.find("tan"),3,"sec");
    derivativesteps<<convert2ascii(outer+inner)<<"^2(d/dx"<<convert2ascii(inner)<<")`<br>"<<endl;
    derivativesteps<<"Where `u = "<<convert2ascii(inner)<<"`and `(du)/dx = `";

	derinner=getdata(inner);
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #FF66FF\">";
	result=outer+inner+"^(2)("+derinner+")";
    derivativesteps<<endl<<"<br>`d/dx("<<convert2ascii(keepouter+inner)<<") = "<<convert2ascii(result)<<"`<br>"<<endl;
	return result;
}

string csc(string inner, string outer)//csc
{
	
	string derinner,result;//holds the derivative of u, where u is a non constant function stored in string x;
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #CC0000\">";
    derivativesteps<<endl<<"<br>`d/dx("<<convert2ascii(outer+inner)<<")`:<br>"<<endl;
    derivativesteps<<"Rule `: d/dx(csc(u)) = -csc(u)cot(u)*(d/dx(u)),` Where u is not a constant<br>"<<endl;
    derivativesteps<<"`d/dx("<<convert2ascii(outer+inner)<<") = -";
    string keepouter=outer;
    derivativesteps<<convert2ascii(outer+inner)<<"cot"<<convert2ascii(inner)<<"(d/dx"<<convert2ascii(inner)<<")`<br>"<<endl;
    derivativesteps<<"Where `u = "<<convert2ascii(inner)<<"`and `(du)/dx = `";

	derinner=getdata(inner);
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #CC0000\">";
    result="-"+outer+inner+"cot"+inner+"("+derinner+")";
	result=rewritedoubleoperation(result);
    derivativesteps<<endl<<"<br>`d/dx("<<convert2ascii(keepouter+inner)<<") = "<<convert2ascii(result)<<"`<br>"<<endl;
	return result;
}

string sec(string inner, string outer)//sec
{
	
	string derinner,result;//holds the derivative of u, where u is a non constant function stored in string x;
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #009999\">";
    derivativesteps<<endl<<"<br>`d/dx("<<convert2ascii(outer+inner)<<")`:<br>"<<endl;
    derivativesteps<<"Rule `: d/dx(sec(u)) = sec(u)tan(u)*(d/dx(u)),` Where u is not a constant<br>"<<endl;
    derivativesteps<<"`d/dx("<<convert2ascii(outer+inner)<<") = ";
    string keepouter=outer;
    derivativesteps<<convert2ascii(outer+inner)<<"tan"<<convert2ascii(inner)<<"(d/dx"<<convert2ascii(inner)<<")`<br>"<<endl;
    derivativesteps<<"Where `u = "<<convert2ascii(inner)<<"`and `(du)/dx = `";

	derinner=getdata(inner);
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #009999\">";
    result=outer+inner+"tan"+inner+"("+derinner+")";
    derivativesteps<<endl<<"<br>`d/dx("<<convert2ascii(keepouter+inner)<<") = "<<convert2ascii(result)<<"`<br>"<<endl;
	return result;
}

string cot(string inner, string outer)//cot
{
	
	string derinner,result;//holds the derivative of u, where u is a non constant function stored in string x;
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #FF0066\">";
    derivativesteps<<endl<<"<br>`d/dx("<<convert2ascii(outer+inner)<<")`:<br>"<<endl;
    derivativesteps<<"Rule `: d/dx(cot(u)) = -csc(u)^2*(d/dx(u)),` Where u is not a constant<br>"<<endl;
    derivativesteps<<"`d/dx("<<convert2ascii(outer+inner)<<") = -";
    string keepouter=outer;
	outer.replace(outer.find("cot"),3,"csc");
    derivativesteps<<convert2ascii(outer+inner)<<"^2(d/dx"<<convert2ascii(inner)<<")`<br>"<<endl;
    derivativesteps<<"Where `u = "<<convert2ascii(inner)<<"`and `(du)/dx = `";

	derinner=getdata(inner);
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #FF0066\">";
    result="-"+outer+inner+"^(2)("+derinner+")";
	result=rewritedoubleoperation(result);
    derivativesteps<<endl<<"<br>`d/dx("<<convert2ascii(keepouter+inner)<<") = "<<convert2ascii(result)<<"`<br>"<<endl;
	return result;
}

string arcsin(string inner, string outer)//arcsin
{
	
	string derinner,result;//holds the derivative of u, where u is a non constant function stored in string x;
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #FF6600\">";
    derivativesteps<<endl<<"<br>`d/dx("<<convert2ascii(outer+inner)<<")`:<br>"<<endl;
    derivativesteps<<"Rule `: d/dx(arcsin(u)) = 1/(1-u^2)^(1/2)*(d/dx(u)),` Where u is not a constant<br>"<<endl;
    derivativesteps<<"`d/dx("<<convert2ascii(outer+inner)<<") = ";
    string keepouter=outer;
	outer.replace(outer.find("arcsin"),6,"");
	if(outer.empty())
	{
		outer="1";
	}
    derivativesteps<<"1/(1-"<<simplify(inner+"("+inner+")")<<")^(1/2)"<<"*(d/dx"<<convert2ascii(inner)<<")`<br>"<<endl;
    derivativesteps<<"Where `u = "<<convert2ascii(inner)<<"`and `(du)/dx = `";

	derinner=getdata(inner);
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #FF6600\">";
    result="("+simplify(outer+"("+derinner+")")+")(1-"+simplify(inner+"("+inner+")")+")^(-1/2)";
    derivativesteps<<endl<<"<br>`d/dx("<<convert2ascii(keepouter+inner)<<") = "<<convert2ascii(result)<<"`<br>"<<endl;
	return result;
}

string arccos(string inner, string outer)//arccos
{
	
	string derinner,result;//holds the derivative of u, where u is a non constant function stored in string x;
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #3399FF\">";
    derivativesteps<<endl<<"<br>`d/dx("<<convert2ascii(outer+inner)<<")`:<br>"<<endl;
    derivativesteps<<"Rule `:  d/dx(arccos(u)) = -1/(1-u^2)^(1/2)*(d/dx(u)),` Where u is not a constant<br>"<<endl;
    derivativesteps<<"`d/dx("<<convert2ascii(outer+inner)<<") = ";
    string keepouter=outer;
	outer.replace(outer.find("arccos"),6,"");
	if(outer.empty())
	{
		outer="1";
	}
    derivativesteps<<"-1/(1-"<<simplify(inner+"("+inner+")")<<")^(1/2)"<<"*(d/dx"<<convert2ascii(inner)<<")`<br>"<<endl;
    derivativesteps<<"Where `u = "<<convert2ascii(inner)<<"`and `(du)/dx = `";

	derinner=getdata(inner);
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #3399FF\">";
    result="-1("+simplify(outer+"("+derinner+")")+")(1-"+simplify(inner+"("+inner+")")+")^(-1/2)";
	result=rewritedoubleoperation(result);
    derivativesteps<<endl<<"<br>`d/dx("<<convert2ascii(keepouter+inner)<<") = "<<convert2ascii(result)<<"`<br>"<<endl;
	return result;
}

string arctan(string inner, string outer)//arctan
{
	
	string derinner,result;//holds the derivative of u, where u is a non constant function stored in string x;
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #993399\">";
    derivativesteps<<endl<<"<br>`d/dx("<<convert2ascii(outer+inner)<<")`:<br>"<<endl;
    derivativesteps<<"Rule `:  d/dx(arctan(u)) = 1/(1+u^2)*(d/dx(u)),` Where u is not a constant<br>"<<endl;
    derivativesteps<<"`d/dx("<<convert2ascii(outer+inner)<<") = ";
    string keepouter=outer;
	outer.replace(outer.find("arctan"),6,"");
	if(outer.empty())
	{
		outer="1";
	}
    derivativesteps<<"1/(1+"<<simplify(inner+"("+inner+")")<<")"<<"*(d/dx"<<convert2ascii(inner)<<")`<br>"<<endl;
    derivativesteps<<"Where `u = "<<convert2ascii(inner)<<"`and `(du)/dx = `";

	derinner=getdata(inner);
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #993399\">";
    result=simplify(outer+"("+derinner+")")+"(1+"+simplify(inner+"("+inner+")")+")^(-1)";
    derivativesteps<<endl<<"<br>`d/dx("<<convert2ascii(keepouter+inner)<<") = "<<convert2ascii(result)<<"`<br>"<<endl;
	return result;
}

string arccsc(string inner, string outer)//arc
{
	
	string derinner,result;//holds the derivative of u, where u is a non constant function stored in string x;
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #FF3366\">";
    derivativesteps<<endl<<"<br>`d/dx("<<convert2ascii(outer+inner)<<")`:<br>"<<endl;
    derivativesteps<<"Rule `:  d/dx(arccsc(u)) = -1/(|u|(1-u^2)^(1/2))*(d/dx(u)),` Where u is not a constant<br>"<<endl;
    derivativesteps<<"`d/dx("<<convert2ascii(outer+inner)<<") = ";
    string keepouter=outer;
	outer.replace(outer.find("arccsc"),6,"");
	if(outer.empty())
	{
		outer="1";
	}
    derivativesteps<<"-1/(|"<<convert2ascii(inner)<<"|(1-"<<simplify(inner+"("+inner+")")<<")^(1/2))"<<"*(d/dx"<<convert2ascii(inner)<<")`<br>"<<endl;
    derivativesteps<<"Where `u = "<<convert2ascii(inner)<<"`and `(du)/dx = `";

	derinner=getdata(inner);
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #FF3366\">";
    result="-1("+simplify(outer+"("+derinner+")")+")(("+simplify(inner+"("+inner+")")+")-1)^(-1/2)abs("+inner+")^(-1)";
	result=rewritedoubleoperation(result);
    derivativesteps<<endl<<"<br>`d/dx("<<convert2ascii(keepouter+inner)<<") = "<<convert2ascii(result)<<"`<br>"<<endl;
	return result;
}

string arcsec(string inner, string outer)//arc
{
	
	string derinner,result;//holds the derivative of u, where u is a non constant function stored in string x;
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #FF3399\">";
    derivativesteps<<endl<<"<br>`d/dx("<<convert2ascii(outer+inner)<<")`:<br>"<<endl;
    derivativesteps<<"Rule `: d/dx(arcsec(u)) = 1/(|u|(1-u^2)^(1/2))*(d/dx(u)),` Where u is not a constant<br>"<<endl;
    derivativesteps<<"`d/dx("<<convert2ascii(outer+inner)<<") = ";
    string keepouter=outer;
	outer.replace(outer.find("arcsec"),6,"");
	if(outer.empty())
	{
		outer="1";
	}
    derivativesteps<<"1/(|"<<convert2ascii(inner)<<"|(1-"<<simplify(inner+"("+inner+")")<<")^(1/2))"<<"*(d/dx"<<convert2ascii(inner)<<")`<br>"<<endl;
    derivativesteps<<"Where `u = "<<convert2ascii(inner)<<"`and `(du)/dx = `";

	derinner=getdata(inner);
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #FF3399\">";
    result="("+simplify(outer+"("+derinner+")")+")(("+simplify(inner+"("+inner+")")+")-1)^(-1/2)abs("+inner+")^(-1)";
    derivativesteps<<endl<<"<br>`d/dx("<<convert2ascii(keepouter+inner)<<") = "<<convert2ascii(result)<<"`<br>"<<endl;
	return result;
}

string arccot(string inner, string outer)//arccot
{
	
	string derinner,result;//holds the derivative of u, where u is a non constant function stored in string x;
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #CC99FF\">";
    derivativesteps<<endl<<"<br>`d/dx("<<convert2ascii(outer+inner)<<")`:<br>"<<endl;
    derivativesteps<<"Rule `: d/dx(arccot(u)) = -1/(1+u^2)*(d/dx(u)),` Where u is not a constant<br>"<<endl;
    derivativesteps<<"`d/dx("<<convert2ascii(outer+inner)<<") = ";
    string keepouter=outer;
	outer.replace(outer.find("arccot"),6,"");
	if(outer.empty())
	{
		outer="1";
	}
    derivativesteps<<"-1/(1+"<<simplify(inner+"("+inner+")")<<")"<<"*(d/dx"<<convert2ascii(inner)<<")`<br>"<<endl;
    derivativesteps<<"Where `u = "<<convert2ascii(inner)<<"`and `(du)/dx = `";

	derinner=getdata(inner);
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #CC99FF\">";
    result="-1("+simplify(outer+"("+derinner+")")+")(1+"+simplify(inner+"("+inner+")")+")^(-1)";
	result=rewritedoubleoperation(result);
    derivativesteps<<endl<<"<br>`d/dx("<<convert2ascii(keepouter+inner)<<") = "<<convert2ascii(result)<<"`<br>"<<endl;
	return result;
}

string ln(string inner, string outer)//ln
{
	
	string derinner,result;//holds the derivative of u, where u is a non constant function stored in string x;
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #99FF33\">";
    derivativesteps<<endl<<"<br>`d/dx("<<convert2ascii(outer+inner)<<")`:<br>"<<endl;
    derivativesteps<<"Rule `: d/dx(ln(u)) = 1/(u)*(d/dx(u)),` Where u is not a constant<br>"<<endl;
    derivativesteps<<"`d/dx("<<convert2ascii(outer+inner)<<") = ";
    string keepouter=outer;
	outer.replace(outer.find("ln"),3,"");
	if(outer.empty())
	{
		outer="1";
	}
    derivativesteps<<"1/"<<convert2ascii(inner)<<"*(d/dx"<<convert2ascii(inner)<<")`<br>"<<endl;
    derivativesteps<<"Where `u = "<<convert2ascii(inner)<<"`and `(du)/dx = `";

	derinner=getdata(inner);
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #99FF33\">";
    result="("+simplify(outer+"("+derinner+")")+")("+inner+")^(-1)";
    derivativesteps<<endl<<"<br>`d/dx("<<convert2ascii(keepouter+inner)<<") = "<<convert2ascii(result)<<"`<br>"<<endl;
	return result;
}

string log(string inner, string outer)//log
{
	
	string derinner,result;//holds the derivative of u, where u is a non constant function stored in string x;
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #3399CC\">";
    derivativesteps<<endl<<"<br>`d/dx("<<convert2ascii(outer+inner)<<")`:<br>"<<endl;
    derivativesteps<<"Rule `: d/dx(log(u)) = 1/(uln(10))*(d/dx(u)),` Where u is not a constant<br>"<<endl;
    derivativesteps<<"`d/dx("<<convert2ascii(outer+inner)<<") = ";
    string keepouter=outer;
	outer.replace(outer.find("log"),3,"");
	if(outer.empty())
	{
		outer="1";
	}
    derivativesteps<<"1/("<<convert2ascii(inner)<<"ln(10))*(d/dx"<<convert2ascii(inner)<<")`<br>"<<endl;
    derivativesteps<<"Where `u = "<<convert2ascii(inner)<<"`and `(du)/dx = `";

	derinner=getdata(inner);
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #3399CC\">";
    result="("+simplify(outer+"("+derinner+")")+")("+inner+"ln(10))^(-1)";
    derivativesteps<<endl<<"<br>`d/dx("<<convert2ascii(keepouter+inner)<<") = "<<convert2ascii(result)<<"`<br>"<<endl;
	return result;
}

string exponential(string x, string pow)//c^(u), ex 2^(x), where x is a constant
{
	string derpow,result;//holds the derivative of u, where u is a non constant function stored in string pow;
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #993399\">";
    derivativesteps<<endl<<"<br>`d/dx("<<convert2ascii(x)<<"^"<<convert2ascii(pow)<<")`:<br>"<<endl;
	if(x.find("e")!=-1 && searchstrfirst(x,0)=="poly")
	{
        derivativesteps<<"Using rule of Exponential Function `: d/dx(ae^(u)) = (ae^(u))*((du)/dx),` Where u is not a constant<br>"<<endl;
        derivativesteps<<"`d/dx("<<convert2ascii(x)<<"^"<<convert2ascii(pow)<<") = ("+x+"^("+pow+"))*d/dx("+pow+")`<br>"<<endl;
        derpow=getdata(pow);
		result=x+"^("+pow+")("+derpow+")";
	}
	else
	{
        derivativesteps<<"Using rule of Exponential Function: `d/dx(a^(u)) = ln(a)*(a^(u))*((du)/dx),` Where u is not a constant<br>"<<endl;
        derivativesteps<<"`d/dx("<<convert2ascii(x)<<"^"<<convert2ascii(pow)<<") = ln("+x+")*("+x+"^("+pow+"))*d/dx("+pow+")`<br>"<<endl;
        derpow=getdata(pow);
		result="ln("+x+")("+x+"^("+pow+"))("+derpow+")";
	}
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #993399\">";
    derivativesteps<<"`d/dx("<<convert2ascii(x)<<"^"<<convert2ascii(pow)<<") = "<<convert2ascii(result)<<"`<br>"<<endl;
	return result;
}

string logarithmic(string x, string pow)//u^(u), ex x^(x), where x is not a constant
{
	string derpow,result;//holds the derivative of u, where u is a non constant function stored in string pow;
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #990000\">";
    derivativesteps<<endl<<"<br>`d/dx("<<convert2ascii(x)<<"^"<<convert2ascii(pow)<<")`:<br>"<<endl;
    derivativesteps<<"Rule of Logarithmic Function `: d/dx(u^(w)) = u^(w)*(d/dx(w*ln(u))),` Where u and w are not constants<br>"<<endl;
    derivativesteps<<"`d/dx("<<convert2ascii(x)<<"^"<<convert2ascii(pow)<<") = "<<convert2ascii(x)<<"^("<<convert2ascii(pow)<<")*(d/dx("<<convert2ascii(pow)<<"*ln("<<convert2ascii(x)<<")))`<br>"<<endl;
    derpow=pow+"ln("+x+")";
	derpow=getdata(derpow);
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #990000\">";
	result=x+"^("+pow+")"+"("+derpow+")";
    derivativesteps<<"`d/dx("<<convert2ascii(x)<<"^"<<convert2ascii(pow)<<") = "<<convert2ascii(result)<<"`<br>"<<endl;
	return result;
}

string polynomial(string x)//polynomial
{
	string func=x;
    derivativesteps<<"<p style=\"BACKGROUND-COLOR: #FFFF00\">";
    derivativesteps<<endl<<"<br>`d/dx("+func+")`:<br>"<<endl;
    derivativesteps<<"Rule of Polynomial Function `: d/dx(ax^b) = (a*b)*x^(b-1)`<br>"<<endl;
	string t1,var,result;
	rational<int> coeff, pow;
	if(!isdigit(x[0]) )
	{
		if(x[0]=='+' || x[0]=='-')
		{
			if(!isdigit(x[1]))
			{
				x.insert(1,"1");//if -x, will return -1x
			}
		}
		else
		{
			x.insert(0,"1");//if x, will return 1x
		}
	}
	if(x[x.length()-1] == 'x')//if x is not raised to a number, will raise it to 1
	{
		x.append("^1");
	}

	//calculation
	{
		{ // prep for calculation
			while(x.front()!='x' && x.front()!='(')//collects coefficient of x
			{
				t1.push_back(x.front());//t1 holds the coefficient
				x.erase(0,1);
			}
			int frac = t1.find("/"); //change integer number to rational number. frac returns position of fraction sign
			if(frac==-1)//if no fraction sign found, will add /1. if 2, will return 2/1
			{
				t1.append("/1");
			}

			coeff = boost::lexical_cast<rational<int>>(t1);//converts string rational integer into rational integer
			while(x.front()!='^')
			{
				x.erase(0,1);
			}
			x.erase(0,1);

			if(x[0]=='(' && x[x.length()-1]==')')
			{
				x.erase(0,1);
				x.erase(x.length()-1,1);
			}
			int frac1 = x.find("/");
			if(frac1==-1)
			{
				x.append("/1");
			}

			pow = boost::lexical_cast<rational<int>>(x);//converts string rational integer into rational integer
		}
		
		derivativesteps<<"`d/dx("+convert2ascii(func)+") = ("<<simplifyfraction(coeff)<<"*"<<simplifyfraction(pow)<<")*x^("<<simplifyfraction(pow)<<"-1)`<br>"<<endl;
		//rules of derivative of polynomial
		string scoeff=simplifyfraction(coeff*pow);
		if((pow-1)==(0/1))
		{
			result=scoeff;

		}
		else
		{
			string spow=simplifyfraction(pow-1);
			result=simplifycoeffandpow(scoeff+"x^("+spow+")");
		}
		derivativesteps<<"`d/dx("+convert2ascii(func)+") = "+convert2ascii(result)<<"`<br>"<<endl;
		return result;


	}

}
