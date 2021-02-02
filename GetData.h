#include <boost/rational.hpp>
#include <iostream>	// cin, cout, etc.
#include <string>	// string class
#include <vector>
#include <stack>
#include <queue>



using namespace std;
using boost::rational;


string derive(string x);
string chainrule(string x);
string getdata(string function);// gets the function and splits it into smaller functions seperated by operators


string derive(string x)// Check to see what type of function is present, and takes the necessary actions
{
	string result,y;

	x=simplify(x);//simplifies the function before taking the derivative
	// check if multiply function in one term,  ex: sinx(x)  or (x^2)tan(x)
	int amountofx=0; // test for how many time x appears in a term
	int found =0;

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
		replacer=rewriteseperatebymultiply(check);
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
			queue <string> x1;
			int i =0,t=0;
			vector<string> replacer(1);//string array to pass x to
			string func=x;
			char count='u';
			string a;

			replacer=rewriteseperatebymultiply(x);//parses sin(x)cos(x) into [sin(x)] and [cos(x)] which is stored in replacer
			for(int n=0; n<replacer.size(); n++)
			{
				a.push_back(count);
				count++;
			}
			/*		
			The rule for product rule is dictated by, (uvw)' = (vw)(u')+(uw)(v')+uv(w')
			*/		


			calculations<<endl<<endl<<"d/dx("+rewriteproductfunction(func)+") = "<<endl;
			calculations<<"rule (Produce Rule): d/dx(u*v*w) = (v*w)*(du/dx)+(u*w)*(dv/dx)+u*v*(dw/dx)"<<endl<<endl;
			for(int n=0; n<replacer.size(); n++)
			{
				calculations<<"{"<<endl;
				result+="(";
				calculations<<"(";
				for(int i=0; i<replacer.size(); i++)
				{
					if(i!=n)
					{
						result+=replacer[i];
						calculations<<replacer[i];

					}
				}

				calculations<<")";
				result+=")";
				calculations<<"*(d/dx("+replacer[n]+"))"<<endl;
                calculations<<"Where "<<a[n]<<" = "+replacer[n]+" and d"+a[n]+"/dx = ";

				result+="("+getdata(replacer[n])+")";
				calculations<<"}"<<endl;
				if(n+1!=replacer.size())
				{
					calculations<<"+";
					result+="+";

				}
				calculations<<endl;
			}
			calculations<<"d/dx("+func+") = "+result<<endl;
			result=simplifymathproperties(result);
			calculations<<"Simplified: d/dx("+func+") = "+result<<endl;
		}
	}
	if(result.empty()) // will test for chain rule function and implement chain rule is exists
	{//test for chain rule
		bool chain=true;
		int find=x.find_last_of("^");
		int found=find+1;
		int l=find+2;
		while(l<x.size())
		{
			if(x[l]=='(' || x[l]==')')   //will move till the right closing parenthesis is found. 
			{
				if(x[l]=='(')
				{
					found++;
				}
				if(found==find+1 && x[l]==')')
				{
					break;
				}
				if(found!=find+1 && x[l]==')')
				{
					found--;
				}
			}
			l++;
		}

		if(l==x.size()-1)
		{
			find--;
			if(x[find]==')')
			{
				found=find;
				l=find-1;
				while(l!=0)
				{
					if(x[l]==')' || x[l]=='(')   //will move till the right closing parenthesis is found. 
					{
						if(x[l]==')')
						{
							found++;
						}
						if(found==find && x[l]=='(')
						{
							break;
						}
						if(found!=find && x[l]=='(')
						{
							found--;
						}
					}
					l--;
				}

				while(l!=0)
				{
					if(isalpha(x[l]))
					{
						chain=false;
						break;
					}
					l--;
				}
				if(chain==true)
				{
					result = chainrule(x);
				}
			}
		}
	}

	string firstinst=searchstrfirst(x,0);

	if (firstinst=="sin" && result.empty())//does the derivative for sin
	{
		string replacer;//will remove ^2 from sin^2x and place to the end, sin(x)^2
		int i=0;
		int l=0;

		if(!isdigit(x[0]) || x[0]=='-')//inserts a coefficient if none is present
		{
			if(x[0]=='-')
			{
				x.insert(1,"1");
			}
			else
			{
				x.insert(0,"1");
			}
		}

		while(isdigit(x[l]) || x[l]=='-' || x[l]=='/')//goes to the position after coefficient
		{
			l++;
		}


		if(x[l] != '(')// places a parenthesis around sin to make it a chain rule
		{
			x.insert(l,"(");
			x.insert(x.find(")",x.find("x")+1),")");// places the closing parenthesis after x is found, so if 2sin(x^2)^2, will make 2(sin(x^2))^2
		}



		i=x.find("^");//find "^" in sin(x)^2 to test whether to do chain rule or just derivative
		if(i==-1)//if the function is just (sin(x)) will remove parenthesis around it and take the derivative
		{
			x.erase(x.find("("),1);
			x.erase(x.find(")"),1);
			result=sin(x);
		}
		else//if not
		{
			if(x[i-1]=='x')//needs the power of the sin and not x so if the power is on x, will find the sin power
			{
				i=x.find("^",x.find("^")+1);			
			}
			if(i==-1)//if there is no power on sin and just on x, will not do chain rule and just do derivative
			{
				x.erase(x.find("("),1);
				x.erase(x.find(")"),1);
				result=sin(x);
			}
			else//if sin has a power, will do chain rule
			{
			result=simplifycoeffandpow(chainrule(x));
			}
		}
	}

	if (firstinst=="cos" && result.empty())//does the derivative for cos
	{
		string replacer;//will remove ^2 from cos^2x and place to the end, cos(x)^2
		int i=0;
		int l=0;

		if(!isdigit(x[0]) || x[0]=='-')//inserts a coefficient if none is present
		{
			if(x[0]=='-')
			{
				x.insert(1,"1");
			}
			else
			{
				x.insert(0,"1");
			}
		}

		while(isdigit(x[l]) || x[l]=='-' || x[l]=='-')//goes to the position after coefficient
		{
			l++;
		}


		if(x[l] != '(')// places a parenthesis around cos to make it a chain rule
		{
			x.insert(l,"(");
			x.insert(x.find(")",x.find("x")+1),")");// places the clocosg parenthesis after x is found, so if 2cos(x^2)^2, will make 2(cos(x^2))^2
		}



		i=x.find("^");//find "^" in cos(x)^2 to test whether to do chain rule or just derivative
		if(i==-1)//if the function is just (cos(x)) will remove parenthesis around it and take the derivative
		{
			x.erase(x.find("("),1);
			x.erase(x.find(")"),1);
			result=cos(x);
		}
		else//if not
		{
			if(x[i-1]=='x')//needs the power of the cos and not x so if the power is on x, will find the cos power
			{
				i=x.find("^",x.find("^")+1);			
			}
			if(i==-1)//if there is no power on cos and just on x, will not do chain rule and just do derivative
			{
				x.erase(x.find("("),1);
				x.erase(x.find(")"),1);
				result=cos(x);
			}
			else//if cos has a power, will do chain rule
			{
			result=simplifycoeffandpow(chainrule(x));
			}
		}
	}



	if (firstinst=="tan" && result.empty())
	{
		string replacer;//will remove ^2 from sin^2x and place to the end, sin(x)^2
		int i=0;
		int l=0;

		if(!isdigit(x[0]) || x[0]=='-')//inserts a coefficient if none is present
		{
			if(x[0]=='-')
			{
				x.insert(1,"1");
			}
			else
			{
				x.insert(0,"1");
			}
		}

		while(isdigit(x[l]) || x[l]=='-' || x[l]=='-')//goes to the position after coefficient
		{
			l++;
		}


		if(x[l] != '(')// places a parenthesis around sin to make it a chain rule
		{
			x.insert(l,"(");
			x.insert(x.find(")",x.find("x")+1),")");// places the closing parenthesis after x is found, so if 2sin(x^2)^2, will make 2(sin(x^2))^2
		}



		i=x.find("^");//find "^" in sin(x)^2 to test whether to do chain rule or just derivative
		if(i==-1)//if the function is just (sin(x)) will remove parenthesis around it and take the derivative
		{
			x.erase(x.find("("),1);
			x.erase(x.find(")"),1);
			result=tan(x);
		}
		else//if not
		{
			if(x[i-1]=='x')//needs the power of the sin and not x so if the power is on x, will find the sin power
			{
				i=x.find("^",x.find("^")+1);			
			}
			if(i==-1)//if there is no power on sin and just on x, will not do chain rule and just do derivative
			{
				x.erase(x.find("("),1);
				x.erase(x.find(")"),1);
				result=tan(x);
			}
			else//if sin has a power, will do chain rule
			{
			result=simplifycoeffandpow(chainrule(x));
			}
		}
	}
	if (firstinst=="cot" && result.empty())
	{
		string replacer;//will remove ^2 from sin^2x and place to the end, sin(x)^2
		int i=0;
		int l=0;

		if(!isdigit(x[0]) || x[0]=='-')//inserts a coefficient if none is present
		{
			if(x[0]=='-')
			{
				x.insert(1,"1");
			}
			else
			{
				x.insert(0,"1");
			}
		}

		while(isdigit(x[l]) || x[l]=='-' || x[l]=='-')//goes to the position after coefficient
		{
			l++;
		}


		if(x[l] != '(')// places a parenthesis around sin to make it a chain rule
		{
			x.insert(l,"(");
			x.insert(x.find(")",x.find("x")+1),")");// places the closing parenthesis after x is found, so if 2sin(x^2)^2, will make 2(sin(x^2))^2
		}



		i=x.find("^");//find "^" in sin(x)^2 to test whether to do chain rule or just derivative
		if(i==-1)//if the function is just (sin(x)) will remove parenthesis around it and take the derivative
		{
			x.erase(x.find("("),1);
			x.erase(x.find(")"),1);
			result=cot(x);
		}
		else//if not
		{
			if(x[i-1]=='x')//needs the power of the sin and not x so if the power is on x, will find the sin power
			{
				i=x.find("^",x.find("^")+1);			
			}
			if(i==-1)//if there is no power on sin and just on x, will not do chain rule and just do derivative
			{
				x.erase(x.find("("),1);
				x.erase(x.find(")"),1);
				result=cot(x);
			}
			else//if sin has a power, will do chain rule
			{
			result=simplifycoeffandpow(chainrule(x));
			}
		}
	}
	if (firstinst=="csc" && result.empty())
	{
		string replacer;//will remove ^2 from sin^2x and place to the end, sin(x)^2
		int i=0;
		int l=0;

		if(!isdigit(x[0]) || x[0]=='-')//inserts a coefficient if none is present
		{
			if(x[0]=='-')
			{
				x.insert(1,"1");
			}
			else
			{
				x.insert(0,"1");
			}
		}

		while(isdigit(x[l]) || x[l]=='-' || x[l]=='-')//goes to the position after coefficient
		{
			l++;
		}


		if(x[l] != '(')// places a parenthesis around sin to make it a chain rule
		{
			x.insert(l,"(");
			x.insert(x.find(")",x.find("x")+1),")");// places the closing parenthesis after x is found, so if 2sin(x^2)^2, will make 2(sin(x^2))^2
		}



		i=x.find("^");//find "^" in sin(x)^2 to test whether to do chain rule or just derivative
		if(i==-1)//if the function is just (sin(x)) will remove parenthesis around it and take the derivative
		{
			x.erase(x.find("("),1);
			x.erase(x.find(")"),1);
			result=csc(x);
		}
		else//if not
		{
			if(x[i-1]=='x')//needs the power of the sin and not x so if the power is on x, will find the sin power
			{
				i=x.find("^",x.find("^")+1);			
			}
			if(i==-1)//if there is no power on sin and just on x, will not do chain rule and just do derivative
			{
				x.erase(x.find("("),1);
				x.erase(x.find(")"),1);
				result=csc(x);
			}
			else//if sin has a power, will do chain rule
			{
			result=simplifycoeffandpow(chainrule(x));
			}
		}
	}
	if (firstinst=="sec" && result.empty())
	{
		string replacer;//will remove ^2 from sin^2x and place to the end, sin(x)^2
		int i=0;
		int l=0;

		if(!isdigit(x[0]) || x[0]=='-')//inserts a coefficient if none is present
		{
			if(x[0]=='-')
			{
				x.insert(1,"1");
			}
			else
			{
				x.insert(0,"1");
			}
		}

		while(isdigit(x[l]) || x[l]=='-' || x[l]=='-')//goes to the position after coefficient
		{
			l++;
		}


		if(x[l] != '(')// places a parenthesis around sin to make it a chain rule
		{
			x.insert(l,"(");
			x.insert(x.find(")",x.find("x")+1),")");// places the closing parenthesis after x is found, so if 2sin(x^2)^2, will make 2(sin(x^2))^2
		}



		i=x.find("^");//find "^" in sin(x)^2 to test whether to do chain rule or just derivative
		if(i==-1)//if the function is just (sin(x)) will remove parenthesis around it and take the derivative
		{
			x.erase(x.find("("),1);
			x.erase(x.find(")"),1);
			result=sec(x);
		}
		else//if not
		{
			if(x[i-1]=='x')//needs the power of the sin and not x so if the power is on x, will find the sin power
			{
				i=x.find("^",x.find("^")+1);			
			}
			if(i==-1)//if there is no power on sin and just on x, will not do chain rule and just do derivative
			{
				x.erase(x.find("("),1);
				x.erase(x.find(")"),1);
				result=sec(x);
			}
			else//if sin has a power, will do chain rule
			{
			result=simplifycoeffandpow(chainrule(x));
			}
		}
	}
	if (firstinst=="exp" && result.empty())
	{
		result=e(x);
	}
	if (firstinst=="ln" && result.empty())
	{
		string replacer;//will remove ^2 from sin^2x and place to the end, sin(x)^2
		int i=0;
		int l=0;

		if(!isdigit(x[0]) || x[0]=='-')//inserts a coefficient if none is present
		{
			if(x[0]=='-')
			{
				x.insert(1,"1");
			}
			else
			{
				x.insert(0,"1");
			}
		}

		while(isdigit(x[l]) || x[l]=='-' || x[l]=='/')//goes to the position after coefficient
		{
			l++;
		}


		if(x[l] != '(')// places a parenthesis around sin to make it a chain rule
		{
			x.insert(l,"(");
			x.insert(x.find(")",x.find("x")+1),")");// places the closing parenthesis after x is found, so if 2sin(x^2)^2, will make 2(sin(x^2))^2
		}



		i=x.find("^");//find "^" in sin(x)^2 to test whether to do chain rule or just derivative
		if(i==-1)//if the function is just (sin(x)) will remove parenthesis around it and take the derivative
		{
			x.erase(x.find("("),1);
			x.erase(x.find(")"),1);
			result=ln(x);
		}
		else//if not
		{
			if(x[i-1]=='x')//needs the power of the sin and not x so if the power is on x, will find the sin power
			{
				i=x.find("^",x.find("^")+1);			
			}
			if(i==-1)//if there is no power on sin and just on x, will not do chain rule and just do derivative
			{
				x.erase(x.find("("),1);
				x.erase(x.find(")"),1);
				result=ln(x);
			}
			else//if sin has a power, will do chain rule
			{
			result=simplifycoeffandpow(chainrule(x));
			}
		}
	}
	if (firstinst=="log" && result.empty())
	{
		log(x);
	}
	if (firstinst=="arc" && result.empty())
	{
		arc(x);
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

string chainrule(string x)//chain rule
{
/*
	The rule for chain rule is dictated by, (a(ux+b)^c)' = c*x((ux+b)^c-1)(ux+b)'.
	ex. 5(sin(x))^2 = 5*2((sin(x))^2-1)(sin(x))' = 10(sin(x))^1)(cos(x)) = 10sin(x)cos(x)
*/
	//outputs calculations to calculations folder for the right function
	string func=x;
	func=simplifycoeffandpow(func);
	calculations<<endl<<"d/dx("<<func<<"):"<<endl;
	calculations<<"rule (Chain Rule): d/dx(a(u)^b) = ((a*b)*(u)^(b-1))*(du/dx)"<<endl;

	int i=x.length()-1;
	string scoeff,spow,var,result;
	rational<int> coeff, pow;
	if(!isdigit(x[0]))
	{
		if(x[0]=='(' && x.find(")") > x.find("x"))//skips if coefficient is surrounded by parenthesis
		{
			x.insert(0,"1");
		}
	}
	while(x[i]!='^')//collect power, keep in mind ^(1/2) and such
	{
		if(x[i]==')')
		{
			x.erase(i,1);
			i--;
			while(x[i]!='(')//reverse the power; 2/1 to 1/2. since it goes in backwards
			{

				spow.insert(0,1,x[i]);
				x.erase(i,1);
				i--;
			}
			x.erase(i,1);
			break;
		}
		else
		{
			spow.insert(0,1,x[i]);
			x.erase(i,1);
			i--;
		}

	}
	if(x[x.length()-1]=='^')
	{
		x.erase(x.length()-1,1);
	}

	//at this point, there should be a coeffcient to be collected
	if(x[0]=='(')
	{
		x.erase(0,1);
		while(x[0]!=')')
		{
			scoeff.push_back(x[0]);
			x.erase(0,1);
		}
		x.erase(0,1);
	}
	else
	{
		while(x[0]!='(')//collects coefficient of x
		{
			scoeff.push_back(x[0]);//t1 holds the coefficient
			x.erase(0,1);// gets rid of the ')' which should be in the first array x[0]
		}
	}

	x.erase(0,1); // gets rid of the '(' which should be in the first array x[0]
	x.erase(x.find_last_of(")")); // gets rid of the ')' since '(' was taken away from the beginning
	int frac = scoeff.find("/"); //change integer number to rational number. frac returns position of fraction sign
	if(frac==-1)//if no fraction sign found, will add /1. if 2, will return 2/1
	{
		scoeff.append("/1");
	}
	int frac1 = spow.find("/"); //change integer number to rational number. frac returns position of fraction sign
	if(frac1==-1)//if no fraction sign found, will add /1. if 2, will return 2/1
	{
		spow.append("/1");
	}

	coeff = boost::lexical_cast<rational<int>>(scoeff);//converts string rational integer into rational integer
	pow = boost::lexical_cast<rational<int>>(spow);//converts string rational integer into rational integer

	scoeff= simplifyfraction(coeff*pow);
	spow = simplifyfraction(pow-1);

	calculations<<"d/dx("+func+") = ("<<simplifyfraction(coeff)<<"*"<<simplifyfraction(pow)<<")*("+x+")^("<<simplifyfraction(pow)<<"-1)*d/dx("+x+")"<<endl;
    calculations<<"Where u = "+x+" and du/dx is:";
	
	if(spow[0]=='(')
	{
		result="("+simplifymathproperties(scoeff+"*("+getdata(x)+")")+")"+"("+x+")"+"^"+spow;
	}
	else
	{
		result="("+simplifymathproperties(scoeff+"*("+getdata(x)+")")+")"+"("+x+")"+"^"+"("+spow+")";
	}
	//simplifymathproperties
	calculations<<endl<<"d/dx("+func+") = "+ result<<endl;
	result=simplify(result);
	calculations<<endl<<"Simplified: d/dx("+func+") = "+ result<<endl;
	return result;
}

string getdata(string x)// gets the function and splits it into smaller functions seperated by operators
{
	queue <string> function;
	string result;
	int i =0,t=0;
	vector <string> replacer(1);
	calculations<<endl;
	replacer=rewriteseperatebyplusminus(x);
	for(int n=0; n<replacer.size(); n++)
	{
		//outputs calculations to calculations folder for the right function
		if(replacer.size()>1)
		{
			calculations<<"d/dx("+replacer[n]+")";
			if(n<replacer.size()-1)
			{
				calculations<<"+";
			}
		}
	}
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

	//outputs calculations to calculations folder for the right function
	calculations<<endl;

	return simplify(result);
}
