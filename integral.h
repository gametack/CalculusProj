#include <boost/rational.hpp>
#include <boost/config.hpp>
#include <boost\lexical_cast.hpp>
#include <iostream>	// cin, cout, etc.
#include <string>	// string class
#include <queue>

#include "integralReductionFormulas.h"

using namespace std;
using boost::rational;
using boost::lexical_cast;

string i_getdata(string x);// gets the function and splits it into smaller functions separated by operators
string i_integrate(string x);
string substitution(string x,string u);//integration by U-Substitution
string IBP(string x);//integration by parts
string PFD(string x);//partial fraction decomposition
string redform(string x);//Reduction Formula
string i_sin(string x);//sin
string i_cos(string x);//cos
string i_tan(string x);//tan
string i_csc(string x);//cot
string i_sec(string x);//csc
string i_cot(string x);//sec
string i_exponential(string x);//c^(u), ex 2^(x), or e^(x), where x is a constant
string i_polynomial(string x);//polynomial

string i_getdata(string x)// gets the function and splits it into smaller functions separated by operators
{
	string result;
	if(x=="0")
	{
		result="";
	}
	else
	{
		x=simplify(x);//simplifies the function before taking the integral
		vector <string> replacer(1);
		derivativesteps<<"`";
		replacer=rewriteseparatebyplusminus(x);
		for(int n=0; n<replacer.size(); n++)
		{

			if(replacer.size()>1)
			{
				derivativesteps<<"int "+convert2ascii(replacer[n]);
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
				result+=replacer[n]+"x";
			}
			else
			{
				result+=i_integrate(replacer[n]);
			}
			if(n<replacer.size()-1)
			{
				result+='+';
			}
		}
		if(result!="")
		{
			result=simplify(result);
		}
	}
	return result;
}

string i_integrate(string x)// Check to see what type of function is present, and takes the necessary actions
{
	string result;

/*first test*/
	result=redform(x);

	if(result.empty())
	{

		// check if multiply function in one term,  ex: sinx(x)  or (x^2)tan(x)
		int amountofx=0; // test for how many time x appears in a term

		for(int i=0; i<x.length();i++) //loop through function to determine how many times x appears
		{
			if(x[i]=='x')
			{
				amountofx++; //counts how many times x appears
			}
		}

/*second test*/
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

				replacer=rewriteseparatebymultiply(x);

				string coeff;
				while(isdigit(replacer[0][0]) || replacer[0][0]=='-' || replacer[0][0] =='/')//collect coefficient in front of function and erases it, so it stays in front
				{
					coeff+=replacer[0][0];
					replacer[0].erase(0,1);
					if(replacer[0].empty())
					{
						replacer[0]=coeff;
						break;
					}
				}
				if(coeff.empty())//if there is no coefficient, will use placeholder 1
				{
					coeff="1";
				}
				if(coeff=="-")//if coefficient collected was just -, will add placeholder 1
				{
					coeff.append("1");
				}

				for (int n =0; n<replacer.size(); n++)
				{
					string derivreplacer,tester,derivtester;//if x=xsin(x)cos(x), for the first instant, replacer[n]=x and tester=sin(x)cos(x)
					string derivreplacercoeff;//holds the coefficient of the derivative
					string derivtestercoeff;//holds the coefficient
					string u;//what is collect to see if U-substitution is possible


					// skips current instant of replacer by n and collect the rest as tester, 
					//will test replacer[n] against tester to see if the derivative in tester exists as replacer[n].
					//If it does, then U-sub is possible. Will test ,vise-versa, tester against replacer[n] to see if the derivative in replacer[n] exists as tester
					for(int i=0; i<replacer.size(); i++)
					{
						if(i!=n)
						{
							tester+=replacer[i];
						}
					}


					//this might be redundant since a function will always appear as x(x^2+1)^(1/2), where the parenthesized quantity is always at the end, as defined in rewriterearrange(string x)
					//but will test to see if it is a parenthesized function like (x^2+1)^(1/2)x and will collect whats inside parenthesis as u
					if(replacer[n][0]=='(')
					{
						string collect;
						int find=parenpos(replacer[n],0);//moves the closing parenthesis
						for(int i=1;i<find;i++)//starts from pos after opening parenthesis and start collecting
						{
							collect+=replacer[n][i];
						}
						derivreplacer=getdata(collect);//gets the derivative of u to see if it exists as tester
						u=collect;
					}
					else//if it is not a parenthesized function, like sin(x)cos(x), u will be sin(x), where as tester will be cos(x)
					{
						derivreplacer=getdata(replacer[n]);//gets the derivative of u to see if it exists as tester
						u=replacer[n];
					}
					while(isdigit(derivreplacer[0]) || derivreplacer[0]=='-' || derivreplacer[0] =='/')//collect coefficient in front of function and erases it from the function, so it is held and stays in front
					{
						derivreplacercoeff+=derivreplacer[0];//collect the coefficient to be held
						derivreplacer.erase(0,1);//erases the coefficient from the function
						if(derivreplacer.empty())// if the function was a constant, will put it back
						{
							derivreplacer=derivreplacercoeff;
							break;
						}
					}
					if(derivreplacer==tester)//where it tests whether the derivative of u is present
					{//if it is
						//will get the coefficient from the derivative of u and the coefficient of the function will be divided by it
						//so if 3x(x^2+3)^(1/2), u=x^2+3, and du = 2x, will get 2 and since the coeffiecient of the function is 3, will divide 3 by 2 and it will roll through to the integral
						if(derivtestercoeff.empty())//if the derivative of u, inner product does not have a coefficient, will place 1 there
						{
							derivreplacercoeff="1";
						}
						if(derivtestercoeff=="-")//if the derivative of u, inner product collected coefficient was just -, will place 1 after it
						{
							derivreplacercoeff.append("1");
						}
						if(derivtestercoeff[0]=='-')//if the coefficient of the derivative of u is a negative number, will move it to coefficient, so if 1/-2, will return -1/2
						{
							derivtestercoeff.erase(0,1);
							coeff.insert(0,"-");
						}
						replacer[n].insert(0,coeff+"/"+derivreplacercoeff);//inserts the division of the coefficient of the function by the coefficient of the derivative of u to the function
						result=substitution(replacer[n], u);//takes the integral by U-substitution.
						break;
					}
/*third test*/
					if(result.empty())//if first substitution test didnt work, will do the reverse
					{
						//will test to see if it is a parenthesized function like x(x^2+1)^(1/2) and will collect whats inside parenthesis as u
						if(tester[0]=='(')
						{
							string collect;
							int find=parenpos(tester,0);//moves the closing parenthesis

							for(int i=1;i<find;i++)//starts from pos after opening parenthesis and start collecting
							{
								collect+=tester[i];
							}
							derivtester=getdata(collect);//gets the derivative of u to see if it exists as replacer[n]
							u=collect;
						}

						else//if it is not a parenthesized function, like 2x(x^2+1)^(1/2), u will be x^2+1, where as replacer[n], also du, will be 2x
						{
							derivtester=getdata(tester);//gets the derivative of u to see if it exists as replacer[n]
							u=tester;
						}

						while(isdigit(derivtester[0]) || derivtester[0]=='-' || derivtester[0] =='/')//collect coefficient in front of function and erases it from the function, so it is held and stays in front
						{
							derivtestercoeff+=derivtester[0];//collect the coefficient to be held
							derivtester.erase(0,1);//erases the coefficient from the fuction
							if(derivtester.empty())// if the function was a constant, will put it back
							{
								derivtester=derivtestercoeff;
								break;
							}
						}

						if (derivtester==replacer[n])//where it tests whether the derivative of u is present
						{//if it is
							//will get the coefficient from the derivative of u and the coefficient of the function will be divided by it
							//so if 3x(x^2+3)^(1/2), u=x^2+3, and du = 2x, will get 2 and since the coeffiecient of the function is 3, will divide 3 by 2 and it will roll through to the integral
							if(derivtestercoeff.empty())//if the derivative of u, inner product does not have a coefficient, will place 1 there
							{
								derivreplacercoeff="1";
							}
							if(derivtestercoeff=="-")//if the derivative of u, inner product collected coefficient was just -, will place 1 after it
							{
								derivreplacercoeff.append("1");
							}
							if(derivtestercoeff[0]=='-')//if the coefficient of the derivative of u is a negative number, will move it to coefficient, so if 1/-2, will return -1/2
							{
								derivtestercoeff.erase(0,1);
								coeff.insert(0,"-");
							}
							tester.insert(0,coeff+"/"+derivtestercoeff);//inserts the division of the coefficient of the function by the coefficient of the derivative of u to the function
							result=substitution(tester,u);//takes the integral by U-substitution.
							break;
						}
					}
/*fourth test*/
					if(result.empty())//will test for xsin(x^2)cos(x^2) where u will be x^2, the quantity inside of a function type ex: e^(x^2), and if du is present, will use U-sub integration
					{
						string collect;
						int find=searchstrpos(tester,0)+1;//goes to position of the opening parenthesis function inner product
						int pos=parenpos(tester,find);//goes to position of the closing parenthesis function inner product
						for(int i=find+1;i<pos;i++)//collects inner product
						{
							collect+=tester[i];
						}
						u=collect;//assign it to u
						derivtester=getdata(collect);//gets the derivative of u  to test to see if it present
						while(isdigit(derivtester[0]) || derivtester[0]=='-' || derivtester[0] =='/')//collect coefficient in front of function of the derivative of inner product and erases it, so it stays in front
						{
							derivtestercoeff="";//was used in previous test, so will empty it and use it again
							derivtestercoeff+=derivtester[0];
							derivtester.erase(0,1);
							if(derivtester.empty())
							{
								derivtester=derivtestercoeff;
								break;
							}
						}
						if(derivtestercoeff.empty())//if the derivative of u, inner product does not have a coefficient, will place 1 there
						{
							derivreplacercoeff="1";
						}
						if(derivtestercoeff=="-")//if the derivative of u, inner product collected coefficient was just -, will place 1 after it
						{
							derivreplacercoeff.append("1");
						}
						if(derivtestercoeff[0]=='-')//if the coefficient of the derivative of u is a negative number, will move it to coefficient, so if 1/-2, will return -1/2
						{
							derivtestercoeff.erase(0,1);
							coeff.insert(0,"-");
						}
						if(derivtester==replacer[n])//checks to see if du is present, which will be replacer[n]
						{
							if(rewriteseparatebymultiply(tester).size()>1)//if there are more function within tester, will check to see if they have the same inner product u
							{
								vector<string> replacer2(1);
								bool d=true;//holds true if they have the same inner product
								replacer2=rewriteseparatebymultiply(tester);//splits the functions in tester to test
								for(int n2=0;n2<replacer2.size();n2++)
								{
									int find=searchstrpos(tester,0);//searches for function type, ex: trig or exponential
									if(find==-1)//if it is not a function type, like trig or exp, or ln,, will not use this method of u-sub to integrate
									{
										d=false;
										break;
									}
									find++;//goes to position of opening parenthesis of function's inner product
									int pos=parenpos(tester,find);//goes to position of the closing parenthesis function inner product
									collect="";//empty collect and use it again.
									for(int i=find+1;i<pos;i++)//loop through the functions split in tester to see if they have the same inner product that was collected and assigned to u
									{
										collect+=tester[i];
									}
									if(collect!=u)//if one function does not have the same inner product, will not use this method if u-sub to integrate
									{
										d=false;
										continue;
									}
								}
								if(d!=false)//if all the functions have the same inner product will use u sub which will replace the functions inner prodect with u
								{
									tester.insert(0,coeff+"/"+derivtestercoeff);//inserts the division of the coefficient of the function by the coefficient of the derivative of u to the function
									result=substitution(tester,u);//takes the integral by U-substitution.
									break;
								}
							}
							else//if there is only one function within tester
							{
								tester.insert(0,coeff+"/"+derivtestercoeff);//inserts the division of the coefficient of the function by the coefficient of the derivative of u to the function
								result=substitution(tester,u);//takes the integral by U-substitution.
								break;
							}
						}
					}
				}
				if(result.empty())
				{
					result=IBP(x);
				}
			}
		}
		if(amountofx==1 && result.empty()) //if non product function
		{

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
							result=i_exponential(x);
						}
						else
							x=keep;
					}
				}
			}

			if(result.empty()) 
			{
				if (searchstrfirst(x,0)=="sin" && result.empty())//does the integral for sin
				{
					result=i_sin(x);
				}
				if (searchstrfirst(x,0)=="cos" && result.empty())//does the integral for cos
				{
					result=i_cos(x);
				}
				if (searchstrfirst(x,0)=="tan" && result.empty())
				{
					result=i_tan(x);
				}
				if (searchstrfirst(x,0)=="csc" && result.empty())
				{
					result=i_csc(x);
				}
				if (searchstrfirst(x,0)=="sec" && result.empty())
				{
					result=i_sec(x);
				}
				if (searchstrfirst(x,0)=="cot" && result.empty())
				{
					result=i_cot(x);
				}
				if (searchstrfirst(x,0)=="arcsin" && result.empty())
				{
					result=IBP(x);
				}
				if (searchstrfirst(x,0)=="arccos" && result.empty())
				{
					result=IBP(x);
				}
				if (searchstrfirst(x,0)=="arctan" && result.empty())
				{
					result=IBP(x);
				}
				if (searchstrfirst(x,0)=="arccsc" && result.empty())
				{
					result=IBP(x);
				}
				if (searchstrfirst(x,0)=="arcsec" && result.empty())
				{
					result=IBP(x);
				}
				if (searchstrfirst(x,0)=="arccot" && result.empty())
				{
					result=IBP(x);
				}
				if (searchstrfirst(x,0)=="ln" && result.empty())
				{
					result=IBP(x);
				}
				if (searchstrfirst(x,0)=="log" && result.empty())
				{
					result=IBP(x);
				}
			}

			if (searchstring(x, "x") && searchstrpos(x,0)==-1 && result.empty())
			{
				result=i_polynomial(x);
			}
		}
	}
	if(result.empty())//if integral returns nothing, so if y=6 then integral is 0 so it returns nothing
	{
	}
	else
	{
		result=simplify(result);
	}

	return result;
}

string substitution(string x, string u)//Integration by U-Substitution
{
	string result;
	while(x.find(u)!=-1)
	{
		x.replace(x.find(u),u.size(),"x");
	}

	result=i_getdata(x);
	result.replace(result.find_last_of("x"),1,"("+u+")");
	return result;
}

string IBP(string x)//Integration by Parts
{
	//assuming that function is already separated by plusminus because it went through i_getdata to get here
	vector<string> replacer(1),replacer2(1),result(1);//string array to pass x to
	string finalresult;

	replacer=rewriteseparatebymultiply(x);//parses sin(x)cos(x) into [sin(x)] and [cos(x)] which is stored in replacer

	replacer2.resize(replacer.size());//if uvw, holds the derivative of them, so [du] [dv] [dw]
	result.resize(replacer.size());//holds the arrangement of uvw-int(duvw)-int(dvuw)  int=integral

	for(int n2=0; n2<replacer.size(); n2++)
	{
		if(searchstrfirst(replacer[n2],0)=="ln" || searchstrfirst(replacer2[n2],0)=="log" || (replacer2[n2].find("arc")!=-1))//makes sure ln, log, and arc gets priority of being u so we can get du.
		{
			replacer2[n2]=getdata(replacer[n2]);
		}
		else if(searchstrpos(replacer[n2],0)==-1)//we make use x is also u if need be so we get rid of it faster, since the integral will make it grow and derivative will shrink it.
		{
			replacer2[n2]=getdata(replacer[n2]);
		}
		else if(n2==replacer.size()-1)//the last function will always be dw, and we get the integral, w. since replacer holds [u] [v] [dw] as the original function, replacer2 will hold [du] [dv] [w], so we swap w with dw
		{
			replacer2[n2]=i_getdata(replacer[n2]);
			replacer2[n2].swap(replacer[n2]);
		}
		else
		{
			replacer2[n2]=getdata(replacer[n2]);
		}
	}


	for(int i=0; i<replacer.size(); i++)//gets the first arrangement, uvw
	{
		result[0]+="("+replacer[i]+")";
	}
	result[0]=simplify(result[0]);//simplifies before moving on

	for(int r=0;r<result.size()-1;r++)//start collects the rest of the arrangement, -int(duvw)-int(dvuw)  int=integral
	{
		result[r+1]+="("+replacer2[r]+")";
		for(int i=0; i<replacer.size(); i++)
		{
			if(i!=r)
			{
				result[r+1]+="("+replacer[i]+")";

			}
		}
		result[r+1]=simplify(result[r+1]);//simplifies before moving on
	}

	char divide=1;//increments by one if any of the arrangement collected is the same as our original function
	for(int r=1;r<result.size();r++)//checks the arrangement collected to see if it is similar to our original function, if it is, will erase this particular arrangement and divide increments by 1, which will be divided by the final answer
	{//a good example of this is xsin(x)cos(x)
		if(result[r]==x)
		{
			divide+=1;
			result.erase(result.begin()+r);
		}

	}
	finalresult=result[0]+"-";//start writing the formula for by parts integration, uvw-
	for(int r=1;r<result.size();r++)
	{
		result[r]=i_getdata(result[r]);//gets the integral of the arrangement needed according to the formula of by parts integration
		finalresult+=result[r];
		if(r<result.size()-1)
		{
			finalresult+="-";
		}
	}


	return finalresult;
}

string PFD(string x)//partial fraction decomposition
{
	return x;
}

string redform(string x)//Reduction Formula
{
	string result;
	vector<string> getformula(1);
	if(cando_redform(x)==true)
	{
		getformula=typeoffunction(x);
		if(!getformula[0].empty())
		{
			if(getformula[1]!="0" && getformula[1]!="(0)")
			{
				result=getformula[0]+"("+i_getdata(getformula[1])+")";
			}
			else
			{
				result=getformula[0];
			}
			
		}
	}
	return result;
}
string i_sin(string x)//sin
{
	string coeff,result,a;
	while(isdigit(x[0]) || x[0]=='-' || x[0] =='/')//collect coefficient in front of function and erases it, so it stays in front
	{
		coeff+=x[0];
		x.erase(0,1);
		if(x.empty())
		{
			x=coeff;
			break;
		}
	}	
	if(coeff.empty())//if there is no coefficient, will use placeholder 1
	{
		coeff="1";
	}
	if(coeff=="-")//if coefficient collected was just -, will add placeholder 1
	{
		coeff.append("1");
	}
	int find=searchstrpos(x,0)+1;//goes to the position of the opening parenthesis of inner product
	for(int i=find+1;i<x.find("x");i++)//collect coefficient of inner product
	{
		a+=x[i];
	}
	if(a.empty())//if there is no coefficient, will use placeholder 1
	{
		a="1";
	}
	if(a=="-")//if coefficient collected was just -, will add placeholder 1
	{
		a.append("1");
	}

	find=parenpos(x,find);//goes to the position of the closing parenthesis of inner product
	if(find==x.size()-1)//if just sin(x) and no power, will use rule -coeff/a(cos(ax)) to integrate
	{
		x.replace(x.find("sin"),3,"cos");//replacer function with cos
		result="(-"+coeff+"/"+a+")"+x;//rule
	}
	else if(x[find+1]=='^')//if there is a power
	{
		find+=3;//goes to position of the first character of the power
		if(x[find]=='-')//checks if power is a negative number, <0, if it is, will convert to cscx then integrate by rule of csc
		{
			x=trigidentities(x,"compress");//use trig identity to convert
			result="("+coeff+")"+"("+i_getdata(x)+")";//gets integral
		}
	}
	return result;
}

string i_cos(string x)//cos
{
		string coeff,result,a;
		while(isdigit(x[0]) || x[0]=='-' || x[0] =='/')//collect coefficient in front of function and erases it, so it stays in front
		{
			coeff+=x[0];
			x.erase(0,1);
			if(x.empty())
			{
				x=coeff;
				break;
			}
		}	
		if(coeff.empty())//if there is no coefficient, will use placeholder 1
		{
			coeff="1";
		}
		if(coeff=="-")//if coefficient collected was just -, will add placeholder 1
		{
			coeff.append("1");
		}
		int find=searchstrpos(x,0)+1;//goes to the position of the opening parenthesis of inner product
		for(int i=find+1;i<x.find("x");i++)//collect coefficient of inner product
		{
			a+=x[i];
		}
		if(a.empty())//if there is no coefficient, will use placeholder 1
		{
			a="1";
		}
		if(a=="-")//if coefficient collected was just -, will add placeholder 1
		{
			a.append("1");
		}

		find=parenpos(x,find);//goes to the position of the closing parenthesis of inner product
		if(find==x.size()-1)//if just cos(x) and no power, will use rule -coeff/a(sin(ax)) to integrate
		{
			x.replace(x.find("cos"),3,"sin");//replacer function with cos
			result="("+coeff+"/"+a+")"+x;//rule
		}
		else if(x[find+1]=='^')//if there is a power
		{
			find+=3;//goes to position of the first character of the power
			if(x[find]=='-')//checks if power is a negative number, <0, if it is, will convert to secx then integrate by rule of sec
			{
				x=trigidentities(x,"compress");//use trig identity to convert
				result="("+coeff+")"+"("+i_getdata(x)+")";//gets integral
			}
		}
		return result;
}

string i_tan(string x)//tan
{
	string coeff,result,a;
	while(isdigit(x[0]) || x[0]=='-' || x[0] =='/')//collect coefficient in front of function and erases it, so it stays in front
	{
		coeff+=x[0];
		x.erase(0,1);
		if(x.empty())
		{
			x=coeff;
			break;
		}
	}	
	if(coeff.empty())//if there is no coefficient, will use placeholder 1
	{
		coeff="1";
	}
	if(coeff=="-")//if coefficient collected was just -, will add placeholder 1
	{
		coeff.append("1");
	}
	int find=searchstrpos(x,0)+1;//goes to the position of the opening parenthesis of inner product
	for(int i=find+1;i<x.find("x");i++)//collect coefficient of inner product
	{
		a+=x[i];
	}
	if(a.empty())//if there is no coefficient, will use placeholder 1
	{
		a="1";
	}
	if(a=="-")//if coefficient collected was just -, will add placeholder 1
	{
		a.append("1");
	}

	find=parenpos(x,find);//goes to the position of the closing parenthesis of inner product
	if(find==x.size()-1)//if just tan(x) and no power, will convert tanx to sinx(cosx^-1) then integrate by rule of ln which is 1/u=ln|u|
	{
		x=trigidentities(x,"expand");//use trig identity to convert
		result="("+coeff+")"+"("+i_getdata(x)+")";//gets integral
	}
	else if(x[find+1]=='^')//if there is a power
	{
		find+=3;//goes to position of the first character of the power
		if(x[find]=='-')//checks if power is a negative number, <0, if it is, will convert to cotx then integrate by rule of cot
		{
			x=trigidentities(x,"compress");//use trig identity to convert
			result="("+coeff+")"+"("+i_getdata(x)+")";//gets integral
		}
	}
	return result;
}

string i_csc(string x)//csc
{
	string coeff,result,a,n;
	while(isdigit(x[0]) || x[0]=='-' || x[0] =='/')//collect coefficient in front of function and erases it, so it stays in front
	{
		coeff+=x[0];
		x.erase(0,1);
		if(x.empty())
		{
			x=coeff;
			break;
		}
	}	
	if(coeff.empty())//if there is no coefficient, will use placeholder 1
	{
		coeff="1";
	}
	if(coeff=="-")//if coefficient collected was just -, will add placeholder 1
	{
		coeff.append("1");
	}

	int find=searchstrpos(x,0)+1;//goes to the position of the opening parenthesis of inner product
	for(int i=find+1;i<x.find("x");i++)//collect coefficient of inner product
	{
		a+=x[i];
	}
	if(a.empty())//if there is no coefficient, will use placeholder 1
	{
		a="1";
	}
	if(a=="-")//if coefficient collected was just -, will add placeholder 1
	{
		a.append("1");
	}

	find=parenpos(x,find);//goes to the position of the closing parenthesis of inner product
	if(find==x.size()-1)//if just cos(x) and no power, will use rule -coeff/a(ln(|csc(ax)+cot(ax)|)) to integrate
	{
		x="(ln(abs(csc("+a+"x)+cot("+a+"x))))";
		result="(-"+coeff+"/"+a+")"+x;//rule
	}
	else if(x[find+1]=='^')//if there is a power
	{
		find+=2;//goes to the position of the opening parenthesis of the power
		int pos=parenpos(x,find);//goes to the position of the closing parenthesis of the power
		for(int i=find+1;i<pos;i++)
		{
			n+=x[i];
		}
		if(x[find]=='-')//checks if power is a negative number, <0, if it is, will convert to sinx then integrate by rule of sin
		{
			x=trigidentities(x,"compress");//use trig identity to convert
			result="("+coeff+")"+"("+i_getdata(x)+")";//gets integral
		}
	}
	return result;
}

string i_sec(string x)//sec
{
	string coeff,result,a,n;
	while(isdigit(x[0]) || x[0]=='-' || x[0] =='/')//collect coefficient in front of function and erases it, so it stays in front
	{
		coeff+=x[0];
		x.erase(0,1);
		if(x.empty())
		{
			x=coeff;
			break;
		}
	}	
	if(coeff.empty())//if there is no coefficient, will use placeholder 1
	{
		coeff="1";
	}
	if(coeff=="-")//if coefficient collected was just -, will add placeholder 1
	{
		coeff.append("1");
	}

	int find=searchstrpos(x,0)+1;//goes to the position of the opening parenthesis of inner product
	for(int i=find+1;i<x.find("x");i++)//collect coefficient of inner product
	{
		a+=x[i];
	}
	if(a.empty())//if there is no coefficient, will use placeholder 1
	{
		a="1";
	}
	if(a=="-")//if coefficient collected was just -, will add placeholder 1
	{
		a.append("1");
	}

	find=parenpos(x,find);//goes to the position of the closing parenthesis of inner product
	if(find==x.size()-1)//if just cos(x) and no power, will use rule coeff/a(ln(|sec(ax)+tan(ax)|)) to integrate
	{
		x="(ln(abs(tan("+a+"x)+sec("+a+"x))))";
		result="("+coeff+"/"+a+")"+x;//rule
	}
	else if(x[find+1]=='^')//if there is a power
	{
		find+=2;//goes to the position of the opening parenthesis of the power
		int pos=parenpos(x,find);//goes to the position of the closing parenthesis of the power
		for(int i=find+1;i<pos;i++)
		{
			n+=x[i];
		}
		if(x[find]=='-')//checks if power is a negative number, <0, if it is, will convert to cosx then integrate by rule of cos
		{
			x=trigidentities(x,"compress");//use trig identity to convert
			result="("+coeff+")"+"("+i_getdata(x)+")";//gets integral
		}
		else if(n=="2")
		{
			x="(tan("+a+"x))";
			result="("+coeff+"/"+a+")"+x;//rule
		}
	}
	return result;
}

string i_cot(string x)//cot
{
	string coeff,result,a;
	while(isdigit(x[0]) || x[0]=='-' || x[0] =='/')//collect coefficient in front of function and erases it, so it stays in front
	{
		coeff+=x[0];
		x.erase(0,1);
		if(x.empty())
		{
			x=coeff;
			break;
		}
	}	
	if(coeff.empty())//if there is no coefficient, will use placeholder 1
	{
		coeff="1";
	}
	if(coeff=="-")//if coefficient collected was just -, will add placeholder 1
	{
		coeff.append("1");
	}
	int find=searchstrpos(x,0)+1;//goes to the position of the opening parenthesis of inner product
	for(int i=find+1;i<x.find("x");i++)//collect coefficient of inner product
	{
		a+=x[i];
	}
	if(a.empty())//if there is no coefficient, will use placeholder 1
	{
		a="1";
	}
	if(a=="-")//if coefficient collected was just -, will add placeholder 1
	{
		a.append("1");
	}

	find=parenpos(x,find);//goes to the position of the closing parenthesis of inner product
	if(find==x.size()-1)//if just cot(x) and no power, will convert cotx to sinx^-1(cosx) then integrate by rule of ln which is 1/u=ln|u|
	{
		x=trigidentities(x,"expand");//use trig identity to convert
		result="("+coeff+")"+"("+i_getdata(x)+")";//gets integral
	}
	else if(x[find+1]=='^')//if there is a power
	{
		find+=3;//goes to position of the first character of the power
		if(x[find]=='-')//checks if power is a negative number, <0, if it is, will convert to tanx then integrate by rule of tan
		{
			x=trigidentities(x,"compress");//use trig identity to convert
			result="("+coeff+")"+"("+i_getdata(x)+")";//gets integral
		}
	}
	return result;
}

string i_exponential(string x)//c^(u), ex 2^(x), where x is a constant
{
	string result;
	return result;
}

string i_polynomial(string x)//polynomial
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
	if(x[x.length()-1] == 'x')//if x is not raied to a number, will raise it to 1
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
		string scoeff=simplifyfraction(coeff/(pow+1));

		string spow=simplifyfraction(pow+1);
		result=simplifycoeffandpow(scoeff+"x^("+spow+")");

		derivativesteps<<"`int ("+convert2ascii(func)+") = "+convert2ascii(result)<<"+C`<br>"<<endl;
		return result;


	}

}