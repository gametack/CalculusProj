#define _USE_MATH_DEFINES

#include <boost/rational.hpp>
#include <boost/config.hpp>
#include <boost\lexical_cast.hpp>
#include <iostream>	// cin, cout, etc.
#include <string>	// string class
#include <queue>
#include <math.h>

using namespace std;

double evaluatefunction(string x,long double input,string type);//type = degree or radian mode
double evaluateArea(string x,long double xfrom,long double xto);

double evaluatefunction(string x, long double input,string type)//type = degree or radian mode
{
    long double result1=1.0,result=1.0,finalresult=0.0;
	vector<string> replacer(0),replacer2(0);

	x=simplify(x);
	replacer=rewriteseparatebyplusminus(x);

	for(int n=0; n<replacer.size(); n++)
	{
			replacer2=rewriteseparatebymultiply(replacer[n]);

			for(int n2=0; n2<replacer2.size(); n2++)
			{
				
				if(rewriteseparatebyplusminus(replacer2[n2]).size()>1)
				{
					result=evaluatefunction(replacer2[n2],input,type);
				}
				else
				{


					if(replacer2[n2][replacer2[n2].length()-1]==')')
					{
						string power,collect,keep=replacer2[n2];//keep will make sure if string collect become "e", will move on and now do pow(e,expression), instead do exp(expression)
						int find=(parenpos(replacer2[n2],replacer2[n2].length()-1))-1;
						if(replacer2[n2][find]=='^')
						{
							int i=0;
							while(i<find)
							{
								collect+=replacer2[n2][0];
								replacer2[n2].erase(0,1);
								i++;
							}
							replacer2[n2].erase(0,1);
							power=replacer2[n2];
							if(collect.find("e")!=-1 && collect.find("x")==-1)
							{
								replacer2[n2]=keep;
							}
							else
							{
								if(collect.find("x")!=-1)// make sure 2^(sinx), that 2 is not mistaken for coefficient
								{//collect coefficient			
									if(!isdigit(collect[0]))
									{
										if(collect[0]=='-')
										{
											if(!isdigit(collect[1]))
											{
												collect.insert(1,"1");
											}
										}
										else
										{
											collect.insert(0,"1");
										}
									}


									string scoeff;
									rational<int> coeff;
									while(!collect.empty() && (isdigit(collect[0]) || collect[0]=='-' || collect[0]=='/'))
									{
										scoeff+=collect[0];
										collect.erase(0,1);

									}
									if(collect.empty())
									{
										collect="c";
									}
									{	
										//change integer number to rational number (2 to 2/1)
										int frac = scoeff.find("/"); 
										if(frac==-1)
										{
											scoeff.append("/1");
										}
									}
									coeff=boost::lexical_cast<rational<int>>(scoeff);
									result=boost::rational_cast<long double>(coeff);
								}


								result*=pow(evaluatefunction(collect,input,type),evaluatefunction(power,input,type));
								result1*=result;
								continue;
							}
						}
					}

					{//collect coefficient			
						if(!isdigit(replacer2[n2][0]))
						{
							if(replacer2[n2][0]=='-')
							{
								if(!isdigit(replacer2[n2][1]))
								{
									replacer2[n2].insert(1,"1");
								}
							}
							else
							{
								replacer2[n2].insert(0,"1");
							}
						}


						string scoeff;
						rational<int> coeff;
						while(!replacer2[n2].empty() && (isdigit(replacer2[n2][0]) || replacer2[n2][0]=='-' || replacer2[n2][0]=='/'))
						{
							scoeff+=replacer2[n2][0];
							replacer2[n2].erase(0,1);

						}
						if(replacer2[n2].empty())
						{
							replacer2[n2]="c";
						}
						{	
							//change integer number to rational number (2 to 2/1)
							int frac = scoeff.find("/"); 
							if(frac==-1)
							{
								scoeff.append("/1");
							}
						}
						coeff=boost::lexical_cast<rational<int>>(scoeff);
						result=boost::rational_cast<long double>(coeff);
					}


					int i=0;
					if(searchstrpos(replacer2[n2],i)!=-1)
					{

						string collect;
						while(replacer2[n2][0]!='(')
						{
							collect+=replacer2[n2][0];
							replacer2[n2].erase(0,1);
						}
						if(replacer2[n2][0]=='(')
						{
							replacer2[n2].erase(0,1);
						}
						if(replacer2[n2].back()==')')
						{
                            replacer2[n2].erase(replacer2[n2].size()-1,1);
						}

                        if(type=="degree" || type=="Degree" || type=="degree mode" || type=="Degree Mode")
                        {
                            if(collect=="sin")
                            {
                                result*=sin((evaluatefunction(replacer2[n2],input,type)*M_PI/180));
                            }
                            if(collect=="cos")
                            {
                                result*=cos((evaluatefunction(replacer2[n2],input,type)*M_PI/180));
                            }
                            if(collect=="tan")
                            {
                                result*=tan((evaluatefunction(replacer2[n2],input,type)*M_PI/180));
                            }
                            if(collect=="csc")
                            {
                                result*=1/sin((evaluatefunction(replacer2[n2],input,type)*M_PI/180));
                            }
                            if(collect=="sec")
                            {
                                result*=1/cos((evaluatefunction(replacer2[n2],input,type)*M_PI/180));
                            }
                            if(collect=="cot")
                            {
                                result*=1/tan((evaluatefunction(replacer2[n2],input,type)*M_PI/180));
                            }
                            if(collect=="arcsin")
                            {
                                result*=(asin(evaluatefunction(replacer2[n2],input,type)))*180/M_PI;
                            }
                            if(collect=="arccos")
                            {
                                result*=(acos(evaluatefunction(replacer2[n2],input,type)))*180/M_PI;
                            }
                            if(collect=="arctan")
                            {
                                result*=(atan(evaluatefunction(replacer2[n2],input,type)))*180/M_PI;
                            }
                            if(collect=="arccsc")
                            {
                                result*=(asin(1/evaluatefunction(replacer2[n2],input,type)))*180/M_PI;
                            }
                            if(collect=="arcsec")
                            {
                                result*=(acos(1/evaluatefunction(replacer2[n2],input,type)))*180/M_PI;
                            }
                            if(collect=="arccot")
                            {
                                result*=(atan(1/evaluatefunction(replacer2[n2],input,type)))*180/M_PI;
                            }
                        }
                        else
                        {
                            if(collect=="sin")
                            {
                                result*=sin(evaluatefunction(replacer2[n2],input,type));
                            }
                            if(collect=="cos")
                            {
                                result*=cos(evaluatefunction(replacer2[n2],input,type));
                            }
                            if(collect=="tan")
                            {
                                result*=tan(evaluatefunction(replacer2[n2],input,type));
                            }
                            if(collect=="csc")
                            {
                                result*=1/sin(evaluatefunction(replacer2[n2],input,type));
                            }
                            if(collect=="sec")
                            {
                                result*=1/cos(evaluatefunction(replacer2[n2],input,type));
                            }
                            if(collect=="cot")
                            {
                                result*=1/tan(evaluatefunction(replacer2[n2],input,type));
                            }
                            if(collect=="arcsin")
                            {
                                result*=asin(evaluatefunction(replacer2[n2],input,type));
                            }
                            if(collect=="arccos")
                            {
                                result*=acos(evaluatefunction(replacer2[n2],input,type));
                            }
                            if(collect=="arctan")
                            {
                                result*=atan(evaluatefunction(replacer2[n2],input,type));
                            }
                            if(collect=="arccsc")
                            {
                                result*=asin(1/evaluatefunction(replacer2[n2],input,type));
                            }
                            if(collect=="arcsec")
                            {
                                result*=acos(1/evaluatefunction(replacer2[n2],input,type));
                            }
                            if(collect=="arccot")
                            {
                                result*=atan(1/evaluatefunction(replacer2[n2],input,type));
                            }
                        }
                        if(collect=="log")
						{
							result*=log10(evaluatefunction(replacer2[n2],input,type));
						}
						if(collect=="ln")
						{
							result*=log(evaluatefunction(replacer2[n2],input,type));
						}
						if(collect=="e^")
						{
							result*=exp(evaluatefunction(replacer2[n2],input,type));
						}
						if(collect=="abs")
						{
							result*=abs(evaluatefunction(replacer2[n2],input,type));
						}

                    }

                    else
                    {
                        if(replacer2[n2].find("x")!=-1)
                        {
                            result=result*input;
                        }
                    }
                }

				result1*=result;
			}
		finalresult+=result1;
		result1=1.0;
	}

	return finalresult;
}

double evaluateArea(string x,long double xfrom,long double xto)
{
    return evaluatefunction(x,xto,"radian")-evaluatefunction(x,xfrom,"radian");
}


