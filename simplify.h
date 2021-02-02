#include <boost/rational.hpp>
#include <boost/config.hpp>
#include <boost\lexical_cast.hpp>
#include <iostream>	// cin, cout, etc.
#include <string>	// string class
#include <queue>



using namespace std;
using boost::rational;
using boost::lexical_cast;



string simplify(string x);//does selected simplification to return the right form of a function
string simplifyextras(string x);//does extra simplifications so the function will be in the right form
string simplifyaddliketerms(string x);//if similar terms exists in a function, will add or subtract them. so if sinx+sinx, will return 2sinx
string simplifymultiplyliketerms(string x);//if similar function exists, will multiply both. so if x+sinx*sinx+5, will return x+sin(x)^2+5
string simplifymathproperties(string x);//such as distributive property and associative property.
string simplifycoeffandpow(string x);//simply 1x^1 to x
string simplifyfraction(rational<int> x);// if fracton = n/1 just outputs n
string simplifypolynomial (rational<int> x, string y, rational<int> z);// formatted output for polynomial input (x);
string rewrite(string x);//does selected process to rewrite the function in a proper way
string rewritereduce(string x);//reduces function to it's simplest form. Used in integral.h
string rewritedoubleoperation(string x);//if x--4 or x+-3, will simplify to x+4 and x-3
vector<string> rewriteseparatebyplusminus(string x);//separates 2x+3 into [2x] and [+3]
vector<string> rewriteseparatebymultiply(string x);//separates 2x*3 into [2x] and [3]
string rewritepowerfunction(string x);//if sin^2x, will return sin(x)^2
string rewriteproductoperation(string x);//if x-sinx, but it's multiplied, will return -xsinx
string rewriteproductfunction(string x);//if x(sinx) will return x*(sinx)
string rewritequotientfunction(string x);//if x/sinx, will return x(sin(x))^(-1)
string rewritefunction(string x);//rewriting function for graphing.
string rewriterearrange(string x);//rearranges function so if sin(x^2)xcos(x), will return xsin(x^2)cos(x)
string trigidentities(string x,string option);//does trig identities with option to expand, tanx=sinx/cosx, or compress, sinx/cosx=tanx
int parenpos(string x, int i);//return the position of closing parenthesis. so if sec(x^(1/2)), the last closing parenthesis will be returned


string simplify(string x)//does selected simplification to return the right form of a function
{
	x=rewrite(x);//goes to rewrite to do necessary simplifications
	x=simplifyextras(x);
	x=simplifymathproperties(x);
	x=rewriterearrange(x);
	x=simplifymultiplyliketerms(x);
	x=simplifyaddliketerms(x);
	return x;
}

string rewrite(string x)//does selected process to rewrite the function in a proper way
{
	x=rewritedoubleoperation(x);
	x=rewritepowerfunction(x);
	x=rewriteproductoperation(x);
	x=rewritequotientfunction(x);
	return x;
}
string rewritereduce(string x)//reduces function to it's simplest form. Used in integral.h
{
	return x;
}

string simplifyextras(string x)//does extra simplifications so the function will be in the right form
{
	string result;

	//to parenthesize power if it is not already
	for(int i=0; i<x.size(); i++)
	{
		if(x[i]=='^')
		{
			i++;
			if(x[i]!='(')
			{
				x.insert(i,"(");
				i++;
				if(x[i]=='-')
				{
					i++;
				}
				i++;
				/*note, there has to be something after power, if x^44sinx, at this point, i will be at the position of the second 4, 
				since, there has to be something after power, it takes into consideration that 4 is what x is raised to, then checks if there are more,
				so the second 4 will go to be checked and since it is an integer, the program will add it to what x is raised to, so now x is raised to 44.
				so if, x^xsinx, at this point x is being raised to x and since the next character is s, will return x^(x)sinx.
				*/
				while(i<x.size() && (isdigit(x[i]) || x[i]=='/'))
				{
					i++;
				}
				x.insert(i,")");
			}
		}
	}

	for(int i=0; i<x.size(); i++)//collects expression surrounded by parenthesis and simplify if necessary
	{
		int at=i;//where the opening parenthesis was found.
		while(x[at]=='(')
		{
			i=at;
			string y;
			int found;
			found=parenpos(x,i);// goes to position of the correct closing parenthesis
			i++;
			for(int l=i;l<found;l++)// collects whats inside of parenthesis and passes it to string y
			{
				y.push_back(x[i]);
				x.erase(i,1);
			}
			
			y=simplify(y);//simplify whats was collect in string y

			//attempting to write a power property expression, have to move this to when final output of function is being processed
			//rewrite so it counts for every case, (x^(2))^(2), (4x^(2))^(3), (sin(x)cos(x))^(-2), ((x-sinx)^(2))^(3), (sin(x)cos(x))^(-sin(x))
			////expression below implements the power property, is (sin(x)^2)^2, will return sin(x)^4
			//int pow=i+1;
			//if(pow<x.size() && x[pow]=='^' && rewriteseparatebyplusminus(y).size()<2 && rewriteseparatebymultiply(y).size()<2)//if there is a power after whats in parenthesis and it is by itse;f, like (sinx)^2
			//{
			//	int type=searchstrpos(y,0);//test to see if it is not a polynomial but another type of function, testing content in string y
			//	if(type!=-1 && y.find("x")>type)//if it is and it is not like sin(1), a constant
			//	{
			//		type=parenpos(y,type+1)+1;//goes to position after the functiontype's inner product, so sin(5x)[]
			//		if(type<y.size() && y[type]=='^')//if there is a power sign after
			//		{
			//			string insidepow;//holds the power inside parenthesis which is in string y, y still holds the simplified string in x that was surrounded by parenthesis
			//			string outsidepow;//holds power outside parenthesis which is in string x

			//			type++;//goes to beginning of power. note: at this point, power should be covered by parenthesis
			//			found=parenpos(y,type);// goes to position of closing parenthesis of power
			//			while(type<=found)//collects inner power
			//			{
			//				insidepow.push_back(y[type]);
			//				y.erase(type,1);
			//				found--;
			//			}

			//			//collects outer power
			//			x.erase(pow,1);
			//			found=parenpos(x,pow);
			//			while(pow<=found)
			//			{
			//				outsidepow.push_back(x[pow]);
			//				x.erase(pow,1);
			//				found--;
			//			}

			//			y.insert(type,"("+simplifymultiplyliketerms(insidepow+"*"+outsidepow)+")");//combined inner and outer power
			//		}
			//	}
			//	else//if it is a polynomial
			//	{
			//		type=y.find("x")+1;//finds the position of x, testing content in string y
			//		if(type<y.size() && y[type]=='^' && searchstrpos(x,at-3)==-1)// is there is a power, also make sure x does not come from sin(x)
			//		{
			//			string insidepow;//holds the power inside parenthesis which is in string y, y still holds the simplified string in x that was surrounded by parenthesis
			//			string outsidepow;//holds power outside parenthesis which is in string x

			//			//collecting inner pow
			//			type++;
			//			found=parenpos(y,type);
			//			while(type<=found)
			//			{
			//				insidepow.push_back(y[type]);
			//				y.erase(type,1);
			//				found--;
			//			}

			//			//collecting outer pow
			//			x.erase(pow,1);
			//			found=parenpos(x,pow);
			//			while(pow<=found)
			//			{
			//				outsidepow.push_back(x[pow]);
			//				x.erase(pow,1);
			//				found--;
			//			}
			//			y.insert(type,"("+simplifymultiplyliketerms(insidepow+"*"+outsidepow)+")");//combines it
			//		}
			//	}
			//}

			x.insert(i,y);
			i+=y.size();
			if((i<x.size()-1 && (isdigit(x[i+1]) || x[i+1]=='(' || x[i+1]=='^' || x[i+1]=='*')) || (at>0 && (isdigit(x[at-1]) || isalpha(x[at-1]) || x[at-1]==')' || x[at-1]=='^' || x[at-1]=='-' || x[at-1]=='*')))//logic to determine if parenthesis is kept or removed from what was collected in string y
			{
				break;
			}
			else
			{
				x.erase(at,1);
				x.erase(i-1,1);
			}

		}
	}
	return x;
}

string simplifymultiplyliketerms(string x)//if similar function exists, will multiply both. so if x+sinx*sinx+5, will return x+sin(x)^2+5
{
	string finalresult;

	vector<string> replacer(1),replacer2(1);

	if(x.find("case")!=-1)//rewriteseparatebyplusminus will output a case statement whenever it needs to skip going though separating again, the case is used to test
	{
		x.erase(x.find("case"),4);
		replacer[0]=x;
	}
	else//if case statement was not issued, will skip
	{
		replacer=rewriteseparatebyplusminus(x);//separates by plus or minus
	}


	for (int n =0; n<replacer.size(); n++)
	{
		replacer2=rewriteseparatebymultiply(replacer[n]);//parses sin(x)cos(x) into [sin(x)] and [cos(x)] which is stored in replacer2
		if(replacer2.size() > 1) //if product rule function
		{
			string result;
			vector<string> stringcoeff(replacer2.size());//hold the coefficients of the functions
			vector<rational<int>> coeffs(replacer2.size());//will convert string of coefficients to rational integers of coefficients
			vector<string> stringpow(replacer2.size());//hold the powers of the functions
	

			for (int n2=0; n2<replacer2.size(); n2++)//remove coefficients and powers and places them into an array of strings
			{
				//a last attempt to separatebymultiply function trapped in parenthesis, so if (sinxcosx), will return sinxcosx and split and pass to replacer2 vector of strings

				if(rewriteseparatebyplusminus(replacer2[n2]).size()<2)
				{
					replacer2[n2]=simplifyextras(replacer2[n2]);//simplifyfinal will ensure that is parenthesis is removable, will remove
					if(rewriteseparatebymultiply(replacer2[n2]).size()>1)//if there are more functions inside parenthesis to separate
					{
						int nmove=n2;// placeholder for n2 counter, used to pass separated function to replacer2 while holding the position of n2 for testing
						int t=replacer2.size();// used to increase the size of replacer2 vector
						vector<string> splitagain=rewriteseparatebymultiply(replacer2[n2]);// vector split again holds the new separated function to be passed to replacer2
						replacer2[n2]=splitagain[0];
						for(int l=1; l<splitagain.size(); l++)//loop to pass splitagain to replacer2 one by one
						{
							replacer2.push_back(splitagain[l]);
							if(l<splitagain.size())
							{
								stringcoeff.resize(t+1);
								stringpow.resize(t+1);
								coeffs.resize(t+1);
								t++;
							}
							nmove++;
						}

					}
				}


				bool constant=true;//will say that sin(1) is not a constant, even though it is, just so "c" is not added to sin(1) and only added to integers
				for (int i=0; i<replacer2[n2].length(); i++)
				{
					if(isalpha(replacer2[n2][i]))
					{
						constant=false;
						break;
					}
				}
				if(constant==true)//if just a constant, will add c as a place holder
				{
					if(replacer2[n2][0]=='(')
					{
						replacer2[n2].erase(0,1);
                        replacer2[n2].erase(replacer2[n2].size()-1,1);
					}
					replacer2[n2].append("c");
					while(replacer2[n2][0]!='c')
					{
						stringcoeff[n2]+=replacer2[n2][0];
						replacer2[n2].erase(0,1);
					}

				}
				else
				{
					if(!isdigit(replacer2[n2][0]))//add coefficient of 1 as a place holder if needed
					{
						if(replacer2[n2][0]!='-')
						{
							stringcoeff[n2]="1";
						}
						else
						{
							if(replacer2[n2][0]=='-' && !isdigit(replacer2[n2][1]))
							{
								replacer2[n2].erase(0,1);
								stringcoeff[n2]="-1";
							}
						}
					}
				}

				if(stringcoeff[n2].empty())
				{
					while(isdigit(replacer2[n2][0]) || replacer2[n2][0]=='-' || replacer2[n2][0]=='+' || replacer2[n2][0]=='/')//separates the coefficient from it's																						                             variable, so if 3x, will pass 3 to                                                                                                                        stringcoeff[n] and erase it	from 3x.                                                                                                                   >>> stringcoeff[n]=3 replacer2[n]=x
					{
						stringcoeff[n2]+=replacer2[n2][0];
						replacer2[n2].erase(0,1);
					}
				}

				if(replacer2[n2][0]=='^')//if 2^(x) happens, will put stringcoeff, which will be 2, back and erase it from queue of coeff
				{
					replacer2[n2].insert(0,stringcoeff[n2]);
					stringcoeff[n2]="1";
				}
				int i=0;
				if(replacer2[n2][i]=='(')
				{
					i=parenpos(replacer2[n2],i);
				}
				else if(i<replacer2[n2].size() && (isalpha(replacer2[n2][i]) && replacer2[n2][i]!='x'))
				{
					i=searchstrpos(replacer2[n2],i)+1;
					i=parenpos(replacer2[n2],i);
				}

				int find =replacer2[n2].find("^",i);

				if(find!=-1)
				{
					find++;
					int powpos=parenpos(replacer2[n2],find);
					while(find<=powpos)
					{
						stringpow[n2]+=replacer2[n2][find];
						replacer2[n2].erase(find,1);
						powpos--;
					}
					stringpow[n2].erase(0,1);
                    stringpow[n2].erase(stringpow[n2].size()-1,1);
				}
				else
				{
					replacer2[n2].append("^");
					stringpow[n2]="1";
				}


				{		//change integer number to rational number (2 to 2/1)
					int frac = stringcoeff[n2].find("/"); 
					if(frac==-1)
					{
						stringcoeff[n2].append("/1");
					}
				}

				coeffs[n2] = boost::lexical_cast<rational<int>>(stringcoeff[n2]);//convert string fraction to rational fraction
			}


			for (int n2 =0; n2<replacer2.size()-1; n2++)//outer loop control. to go through each function, so if 2x+3x^3+4x, will check 2x, then 3x^3. then 4x to see if similarity is found
			{
				int nplus=n2+1;
				while(nplus<replacer2.size())
				{
					if(replacer2[n2]==replacer2[nplus])
					{
						stringpow[n2]=simplifyaddliketerms(stringpow[n2]+"+"+stringpow[nplus]);//if like term, will add powers 
						stringpow.erase(stringpow.begin()+nplus);
						replacer2.erase(replacer2.begin()+nplus);
					}
					else
					{
						nplus++;
					}
				}
			}

		
		
			for(int i=1; i<coeffs.size(); i++)//multiplies all the coeffs in the function and puts it in front. so ir 2x*6cos(x)^2, will return 12x*cos(x)^2
			{
				coeffs[0]*=coeffs[i];
			}

			string newcoeff=simplifyfraction(coeffs[0]);

			for(int i=0; i<replacer2.size(); i++)
			{
				if(stringpow[i]!="0" && stringpow[i]!="(0)")
				{
					if(stringpow[i][0]!='(')
					{
						stringpow[i] = "("+stringpow[i]+")"; // if 2/1 will return 2
					}
					if(replacer2[i]!="c^")
					{
						replacer2[i].append(stringpow[i]);//adds power to it's corresponding function
							result+=simplifycoeffandpow(replacer2[i]);//result will returns new simplified (combined like terms) function
					}
				}
			}

			if(newcoeff!="1")
			{
				result.insert(0,newcoeff);
			}
			finalresult+=result;


			if(n<replacer.size()-1)
			{
				finalresult+='+';
			}

		}
		else
		{
			finalresult +=replacer[n];
			if(n<replacer.size()-1)
			{
				finalresult+='+';
			}
		}
	}

	if(finalresult.empty())
	{
		finalresult="1";
	}
	return simplifycoeffandpow(rewritedoubleoperation(finalresult));
}

string simplifyaddliketerms(string x)//if similar terms exists in a function, will add or subtract them. so if sinx+sinx, will return 2sinx
{
	string result;
	vector<string> replacer;
	x=rewritedoubleoperation(x);
	replacer=rewriteseparatebyplusminus(x);//see declaration for documentation. (separates 2x+3 into [2x] and [+3]

	string stringcoeff[100];//hold the coefficients of the funcitons
	rational<int> coeffs[100];//will convert string of coefficients to rational integers of coefficients


	for (int n =0; n<replacer.size(); n++)//if function does not come with a coefficient, will give it 1 as a replacement
	{
		replacer[n]=simplifyextras(replacer[n]);//gets rid of any extra parenthesis that may have pulled through, so if (x)-2x came through, it will remove parenthesis around x
		if(!isdigit(replacer[n][0]) )
		{
			if(replacer[n][0]=='+' || replacer[n][0]=='-')
			{
				if(!isdigit(replacer[n][1]))
				{
					replacer[n].insert(1,"1");//if -x, will return -1x
				}
			}
			else
			{
				replacer[n].insert(0,"1");//if x, will return 1x
			}
		}
	}


	for (int n =0; n<replacer.size(); n++)//to go through each function, so if 2x+3x^3+4x, will check 2x, then 3x^3. then 4x
	{
		while(!replacer[n].empty() && (isdigit(replacer[n][0]) || replacer[n][0]=='-' || replacer[n][0]=='+' || replacer[n][0]=='/'))//separates the coefficient from it's variable, so from 3x. >>> stringcoeff[n]=3 replacer[n]=x
		{
			stringcoeff[n]+=replacer[n][0];
			replacer[n].erase(0,1);
		}
		if(replacer[n].empty())//if just a constant, will add c as a place holder
		{
			replacer[n]="c";
		}

		{		//change integer number to rational number (2 to 2/1)
			int frac = stringcoeff[n].find("/"); 
			if(frac==-1)
			{
				stringcoeff[n].append("/1");
			}
		}
		coeffs[n] = boost::lexical_cast<rational<int>>(stringcoeff[n]);//convert string fraction to rational fraction
	}



	for (int n =0; n<replacer.size(); n++)//outer loop control. to go through each function, so if 2x+3x^3+4x, will check 2x, then 3x^3. then 4x
	{
		if(n==replacer.size()-1)
		{
			break;
		}
		int nplus=1;//inner loop control
		int lengthofstringsrray=0;
		while(!replacer[n].empty())//compares current function with others for like terms
		{
			int find=replacer[n].find_last_of("^");//if whats is in power if not constant, ex: 2^x or x^x, will skip
			if(replacer[n].find("x",find)!=-1)
			{
				break;
			}
				if(replacer[n]==replacer[n+nplus])
				{
					coeffs[n]=coeffs[n]+coeffs[n+nplus];//if like term, will add coefficients 
					coeffs[n+nplus]=0;
					replacer[n+nplus]="";
				}
			
			nplus++;
			lengthofstringsrray++;
			if(n+nplus>replacer.size()-1)
			{
				break;
			}
		}

	}
	int i1=0;
	while(i1<replacer.size())
	{
		string newcoeff;
		if(coeffs[i1]!=0)
		{
			newcoeff = simplifyfraction(coeffs[i1]); // if 2/1 will return 2
			if(replacer[i1]!="c")
			{
				replacer[i1].insert(0,newcoeff);//adds coefficient to it's corresponding function
				result+=replacer[i1];//result will returns new simplified (combined like terms) function
			}
			else
			{
				result+=newcoeff;
			}
			i1++;
		}
		else
		{
			i1++;
		}
		if(i1<replacer.size()&&coeffs[i1]>0)
		{
			result+="+";
		}

	}
	if(result.empty())//result will only be empty if what came in to be "addedliketermed" (string x), was 0.
	{
		result+="0";
	}
	return result=simplifycoeffandpow(result);//returns new simplified (combined like terms) function if like terms found
}

string simplifymathproperties(string x)//such as distributive property and associative property.
{
	string result;
	vector <string> replacer(1);

	if(x.find("case")!=-1)//rewriteseparatebyplusminus will output a case statement whenever it needs to skip going though seperating again, the case is used to test
	{
		x.erase(x.find("case"),4);
		replacer[0]=x;
	}
	else//if case statement was not issued, will skip
	{
		replacer=rewriteseparatebyplusminus(x);//separates by plus or minus
	}


	for(int n=0; n<replacer.size(); n++)
	{
		int n2=0;
		vector <string> replacer2(1);
		if(replacer[n].find("case")!=-1)//if there is a case, will do a separate
		{
			replacer2[n2]=simplifymathproperties(replacer[n]);//goes and does math properties
		}

		else//if it is a normal case, will split by multiplication
		{
			replacer2=rewriteseparatebymultiply(replacer[n]);//separates by product sign
		}

		while((n2<replacer2.size()-1))//goes through vector of separated by product sign
		{
			vector <string> replacer3(1);//used to hold separated next vector value
			string insideresult;

			if(rewriteseparatebyplusminus(replacer2[n2]).size() > rewriteseparatebyplusminus(replacer2[n2+1]).size())//checks to see if (2x+5)(4), then will switch to (4)(2x+5) so it can do distributive property
			{
				replacer2[n2].swap(replacer2[n2+1]);
			}
			replacer3=rewriteseparatebyplusminus(replacer2[n2+1]);//replacer3 assigned the value of separated next vector value
			if(replacer3.size() == 1)//if associative property, (4)(2x), so [2x] will return replacer3.size()=1
			{
				replacer2[n2]=simplifymultiplyliketerms(replacer2[n2]+"*"+replacer2[n2+1]+"case");//will multiple current vector value with next value
				replacer2.erase(replacer2.begin()+(n2+1));//erases next vector value since it has been combined with current vector value
			}
			else//if distributive property, (4)(2x+5), so [2x+5] will return replacer3.size()>1
			{
				if(searchstrpos(replacer2[n2],0)==-1)
				{
					for(int n3=0; n3<replacer3.size(); n3++)//goes through next separated vector value and will multiply through
					{
						replacer3[n3]=simplifymathproperties(replacer3[n3]+"*"+replacer2[n2]);
						insideresult+=replacer3[n3];
						if(n3<replacer3.size()-1)
						{
							insideresult+='+';
						}
					}
					replacer2[n2]="("+rewritedoubleoperation(insideresult)+")";//current vector value will hold the new multiplied value
					replacer2.erase(replacer2.begin()+(n2+1));//erases next vector value since it has been combined with current vector value
				}
				else
				{
					replacer2[n2]=replacer2[n2]+replacer2[n2+1];//current vector value will hold the new multiplied value
					replacer2.erase(replacer2.begin()+(n2+1));//erases next vector value since it has been combined with current vector value
				}
			}
		}


		result+=replacer2[n2];
		if(n<replacer.size()-1)
		{
			result+='+';
		}
	}

	return rewritedoubleoperation(result);
}

string simplifycoeffandpow(string x)//simply 1x^1 to x
{
	string result;
	int t=0;
	vector<string> replacer(1);

	replacer=rewriteseparatebyplusminus(x);

	for(int n=0; n<replacer.size(); n++) //t+1 = how many string in replacer vector
	{

		if(replacer[n].find('x')==-1)//while an integer
		{
			result+=replacer[n];

		}
		else//while not an integer
		{
			int l=0;
			vector <string> y(1);//could use a resizable vector, future improvement
			for(int i=0;i<replacer[n].size();i++)
			{
				while(isdigit(replacer[n][i])|| replacer[n][i]=='/')//takes integers, if it is a fraction, will take the fraction value with it
				{//fraction value so it does not confuse 1/2, thinking 1 as an integer and passing /2 to a different array for checking
					y[l].push_back(replacer[n][i]);//pushes integer and fraction sign into a one part of the string array
					i++;
					if(i==replacer[n].size())//will get out of loop if the end of string has been reached
					{
						break;
					}
					if(!(isdigit(replacer[n][i])|| replacer[n][i]=='/') )//if it is not an integer or a fraction sign
					{
						l++;
						y.resize(l+1);
					}

				}
				if(i!=replacer[n].size())//if the end of string has not been reached, takes care of error when string is out of range
				{
					y[l].push_back(replacer[n][i]);//pushes non integer into array
					l++;
					if(i<replacer[n].size()-1)
					{
						y.resize(l+1);
					}
				}
			}

			for(int i=0; i<y.size(); i++)//goes through the y array
			{
				if(y[i]=="^" )//if it indicates a power
				{
					if(y[i+1]=="1")//if whats after power is just a 1 will skip the power and 1
					{
						i+=2;
					}
					else
					{
						if(y[i+1]=="(")//if whats after power is an opening parenthesis, indication x^(1)
						{
							if(y[i+2]=="1" && y[i+3]==")")//will check if thats in the parenthesis is just 1 and will erase ^(1) from x^(1) and just leave x
							{
								i+=4;
							}
						}
					}
				}
				else if(y[i]=="1" )//if 1x, will remove 1
				{
					if(i<y.size()-1 && (y[i+1]=="/" || y[i+1]=="+" || y[i+1]=="*" || y[i+1]=="-"|| y[i+1]==")"))
					{
					}
					else
					{
						i++;
					}
				}

				if(i<y.size())//so it does not roll over and cause string out of range
				{
					result+=y[i];

				}
			}
		}
		if(n<replacer.size()-1)
		{
			result+='+';
		}
	}

	return rewritedoubleoperation(result);
}

string simplifyfraction(rational<int> x) // if fracton = n/1 just outputs n
{
	string result;
	 // reassign values, and converts any integers back to string
	string coeff = boost::lexical_cast<string>(x);
	if (coeff[coeff.length()-1]=='1' && coeff[coeff.length()-2]=='/')
	{
		coeff.erase((coeff.length()-2),2);
		result=coeff;
	}
	else
	{
		result=coeff;
	}

	return result;
}

string simplifypolynomial (rational<int> x, string y, rational<int> z)// formatted output for polynomial input (x);
{
	string result;
	string // reassign values, and converts any integers back to string
		coeff = boost::lexical_cast<string>(x),
		var = y,
		pow = boost::lexical_cast<string>(z);

	if (coeff[coeff.length()-1]=='1' && coeff[coeff.length()-2]=='/')//checks from the back of the string if it is /1
	{
		coeff.erase((coeff.length()-2),2);//if /1 will remove /1
	}
	if (pow[pow.length()-1]=='1' && pow[pow.length()-2]=='/')//checks from the back of the string if it is /1
	{
		pow.erase((pow.length()-2),2);//if /1 will remove /1
	}
	if(pow=="0")//if x^0, will return nothing
	{
		return result=coeff;

	}
	else
	{
		return result=coeff+var+"^"+"("+pow+")";//if 2/1x^3/1, will return 2x^3

	}
}

string rewritedoubleoperation(string x)//if x--4 or x+-3, will simplify to x+4 and x-3
{
	int i=0;
	while(i!=x.length())
	{
		if(x[i]=='-')// if the character is a subtraction sign
		{
			if(x[i+1]=='-')//if the next character is a subtraction sign, will erase it
			{
				x.erase(i,1);
				x[i]='+';
			}
			else
			{
				if(x[i+1]=='+')//if the next character is an addition sign, will erase the addition sign
				{
					x.erase(i+1,1);
				}
			}

		}


		if(x[i]=='+')// if the character is an addition sign
		{
			if(x[i+1]=='+')//if the next character is an addition sign, will erase it
			{
				x.erase(i+1,1);
			}
			else
			{
				if(x[i+1]=='-')//if the next character is a subtraction sign, will erase the addition sign
				{
					x.erase(i,1);
				}
			}
		}
		i++;
	}
	return x;
}

vector<string> rewriteseparatebyplusminus(string x)//separates 2x+3 into [2x] and [+3]
{
	vector<string> replacer(1);//holds separated function by plus minus. so if x+3, holds [x] [3]
	int i =0,t=0;
	bool negative=false;//keeps track ot  minus signs and places it where necessary, so if cosx-(x-5), will return cosx-x+5
	do//splits passed string of function into a vector of strings, separated by the operands - and +; passes - and + to it's corresponding function.
	{
		if(x[i] == '+' || x[i] == '-'  )//xfront!='-' takes care of if -3x-3x appears as opposed to 3x-3x
		{
			if(i==0)
			{
				if(x[i]=='-')//if minus sign appears
				{
					negative=true;
				}
			}
			else if(x[i-1]!='^' && x[i-1]!='*')//if the negative sign indicated a power and the power is surrounded by parenthesis
			{
				t++;
				replacer.resize(t+1);
				if(x[i]=='-')//if minus sign appears
				{
					negative=true;
				}
			}
			
			if(x[i+1]=='(')//if parenthesis appears, will collect everythign inside and then separate again
			{
				i++;
				vector <string> replacer2(1);
				string y;
				int at=i;
				int found=parenpos(x,i);
				i++;
				for(i;i<found;i++)
				{
					y.push_back(x[i]);
				}
				i++;
				if(rewriteseparatebyplusminus(y).size()>1)//if it is splittable, will split it
				{
					if(i==x.size() || (i<x.size() && x[i]=='-' || x[i]=='+'))
					{
						if(negative==true)
						{

							replacer2=rewriteseparatebyplusminus(y);
							for(int n2=0; n2<replacer2.size(); n2++)
							{
								replacer[t].push_back('-');
								replacer[t].append(replacer2[n2]);
								if(n2<replacer2.size()-1)
								{
									t++;
									replacer.resize(t+1);
								}
							}
						}
						else//if not, will re
						{

							replacer2=rewriteseparatebyplusminus(y);
							for(int n2=0; n2<replacer2.size(); n2++)
							{
								replacer[t].append(replacer2[n2]);
								if(n2<replacer2.size()-1)
								{
									t++;
									replacer.resize(t+1);
								}
							}
						}
					}
					else
					{
						if(negative==true)
						{
							replacer[t].push_back('-');
						}
						replacer[t].append("("+y+")");
					}
				}
				else
				{
					if(i<x.size() && (rewriteseparatebymultiply(y).size()>1 && x[i]=='^'))
					{
						if(negative==true)
						{
							replacer[t].push_back('-');
						}
						replacer[t].append("("+y+")");
					}
					else
					{
						if(negative==true)
						{
							replacer[t].push_back('-');
						}
						replacer[t].append(y);
					}

				}
				if(i>x.size()-1)
				{
					break;
				}
			}
			else
			{
				replacer[t].push_back(x[i]);
				i++;
			}
		}
		else if(x[i]=='(')//if parenthesis appears, will collect everythign inside and then separate again
		{
			int at=i;
			string collect;
			int found=parenpos(x,i);
			i++;
			while(i<found)
			{
				collect+=x[i];
				i++;
			}
			i++;
			if(rewriteseparatebyplusminus(collect).size()>1 && (at==0 && (i==x.size() || x[i]=='-' || x[i]=='+')))
			{
				vector<string> splitagain(0);
				splitagain=rewriteseparatebyplusminus(collect);
				for(int n=0;n<splitagain.size();n++)
				{
					replacer[t].append(splitagain[n]);
					if(n<splitagain.size()-1)
					{
						t++;
						replacer.resize(t+1);
					}
				}
			}
			else
			{
				replacer[t].append("("+collect+")");
			}
		}

		else if(i<x.length())
		{
			replacer[t].push_back(x[i]);
			i++;
		}

		negative=false;
	}while(i<x.length());

	for(int n=0; n<replacer.size(); n++)
	{
		replacer[n]=rewritedoubleoperation(replacer[n]);
		if(replacer[n][0]=='+')
		{
			replacer[n].erase(0,1);
		}
	}
	return replacer;
}

vector<string> rewriteseparatebymultiply(string x)//separates 2x*3 into [2x] and [3]
{
	x=rewriteproductfunction(x);
	vector<string> replacer(1);
	int i =0,t=0;
	char xfront=x[0];
	do//splits passed string of function into a vector of strings, separated by the operands *
	{

		if(xfront!='-' && (x[i] == '*'))//xfront!='-' takes care of if -3x-3x appears as opposed to 3x-3x
		{
			i++;
			t++;
			replacer.resize(t+1);		
		}
		else if(x[i]=='(')
		{
			vector <string> replacer2(1);
			string y;
			int found=parenpos(x,i);
			int at=i;
			for(i;i<=found;i++)
			{
				y.push_back(x[i]);
			}
			while(y.find("*")!=-1)
			{
				y.erase(y.find("*"),1);
			}
			replacer[t].append(y);
		}
		else
		{
			replacer[t].push_back(x[i]);
			xfront=' ';
			i++;
		}
	}while(i<x.length());

	return replacer;
}

string rewritepowerfunction(string x)//if sin^2x, will return sin(x)^2
{
	int i=0;
	while(searchstrpos(x,i)!=-1)
	{
		string change;
		i=searchstrpos(x,i);
		if(i!=-1)
		{
			if(x[i+1] == '^')
			{
				i++;
				if(x[i+1]=='(')
				{
					while(x[i]!=')')
					{

						change.push_back(x[i]);//collects everything before x which is what will be moved to the back
						x.erase(i,1);
						if(x[i+1]=='x')
						{
							break;
						}
					}
					change.push_back(x[i]);
					x.erase(i,1);
				}
				else
				{
					while(x[i]!='x' && x[i]!='(')
					{

						change.push_back(x[i]);//collects everything before x which is what will be moved to the back
						x.erase(i,1);
						if(x[i]=='x' || x[i]=='(')
						{
							break;
						}
					}
				}

				if(x[i]!='(')
				{
					x.insert(i,"(");
					i=x.find("x",i)+1;
					if(i<x.size() && x[i] == '^')
					{
						i++;
						if(x[i]=='(')
						{
							i=x.find(")",i);
							i++;
						}
						else
						{
							if(x[i]=='-')
								i++;
							while(i<x.size() && (isdigit(x[i]) || x[i]=='/'))
							{
								i++;
							}
						}
						x.insert(i,")");
						i++;
						x.insert(i,change);
					}
					else
					{
						x.insert(i,")");
						i++;
						x.insert(i,change);
					}
				}
				else
				{
					int at=i;
					at=parenpos(x,at)+1;
					x.insert(at,change);
				}
			}

			else
			{
				if(x[i+1] != '(')
				{
					i++;
					x.insert(i,"(");
					i=x.find("x",i)+1;
					if(i<x.size() && x[i] == '^')
					{
						i++;
						if(x[i]=='(')
						{
							i=x.find(")",i);
							i++;
						}
						else
						{
							if(x[i]=='-')
								i++;
							while(i<x.size() && (isdigit(x[i]) || x[i]=='/'))
							{
								i++;
							}
						}

						x.insert(i,")");
					}
					else
					{
						x.insert(i,")");
					}
				}
			}
		}
		i++;
	}

	return x;
}

string rewriteproductoperation(string x)//if x(-sinx), but it's multiplied, will return -xsinx
{
	string result;
	vector<string> replacer(1);//holds separated function by plus minus. so if x+3, holds [x] [3]

	replacer=rewriteseparatebyplusminus(x);

	for(int n=0; n<replacer.size(); n++) //t+1 = how many string in replacer vector
	{
		replacer[n]=rewriteproductfunction(replacer[n]);
		for(int i=1; i< replacer[n].length(); i++)
		{
			if(replacer[n][i]=='*')//if there is a product which is followed by a subtraction sign, will move it to the beginning
			{
				if(replacer[n][i+1]=='(')
				{
					i++;
					//this is used to check if whats in parenthesis is seperable by plus or minus sign, if it is, will skip moving operator
					int found=parenpos(replacer[n],i);
					int at=i;
					string test;
					while(at<=found)
					{
						if(replacer[n][at]!='*')//removes multiply sign '*' when collecting
						test+=replacer[n][at];
						at++;
					}
					if(rewriteseparatebyplusminus(test).size()>1)
					{
						i=found-1;
					}

				}
				if(replacer[n][i+1]=='-')
				{
					replacer[n].erase(i+1,1);
					if(replacer[n][0]=='(')
					{
						replacer[n].insert(1,"-");
					}
					else
					{
						replacer[n].insert(0,"-");
					}
				}
			}
			else
			{
				if(i<replacer[n].size()-1 && replacer[n][i]==')' && replacer[n][i+1]=='(')//if there is a product which is )(, if (x)-(cos(x)) and it's being multiplied, will return -(x)(cos(x))
				{
					i++;
					if(replacer[n][i+1]=='-')
					{
						replacer[n].erase(i+1,1);
						if(replacer[n][0]=='(')
						{
							replacer[n].insert(1,"-");
						}
						else
						{
							replacer[n].insert(0,"-");
						}
					}
				}
			}
		}
		result+=replacer[n];

		if(n<replacer.size()-1)
		{
			result+='+';
		}
	}
	while(result.find("*")!=-1)
	{
		result.erase(result.find("*"),1);
	}
	return rewritedoubleoperation(result);
}

string rewriteproductfunction(string x)//if x(sinx) will return x*(sinx)
{	
	for(int i=0; i<x.size(); i++)
	{
		if(i!=x.length()-1)
		{
			if(x[i]==')' && x[i+1]=='(')//if )( occurs, so if (x)(cos(x)), will return (x)*(cos(x)), or if (1/2)(2x+3), will return (1/2)*(2x+3)
			{
				i++;
				if(x[i]!='*' && x[i]!='+' && x[i]!='-')
				{
					x.insert(i,"*");// if it's not, will insert * 
					i++;
				}
			}
			if(i>0 && (x[i]=='(' && (!isalpha(x[i-1]) && x[i-1]!='-'  && x[i-1]!='+' && x[i-1]!='^' && x[i-1]!='*' && x[i-1]!='(' && x[i-1]!='/' || x[i-1]=='x')))//adds product sign before  integers that cover parenthesis, so if (x)2, will return (x)*2 (with special cases)
			{
				if(x[i]!='*' && x[i]!='+' && x[i]!='-')
				{
					x.insert(i,"*");// if it's not, will insert * 
					i++;
				}	
			}
			if(i<x.size()-1 && (x[i]==')' && (x[i+1]!='-' && x[i+1]!='+' && x[i+1]!='^' && x[i+1]!='*' && x[i+1]!=')' && x[i-1]!='/')))//adds product sign after integers that cover parenthesis, so if 2(x), will return 2*(x) (with special cases)
			{
				i++;
				if(x[i]!='*' && x[i]!='+' && x[i]!='-')
				{
					x.insert(i,"*");// if it's not, will insert * 
					i++;
				}			
			}
		}
	}

	for(int i=0; i<x.size();i++)
	{
		if(x[i]=='(')//makes sure something like (sinx(2x))^(1/2) is not split
		{
			int find =parenpos(x,i);//goes to postion of closing parenthesis before power and if power is after, will not split
			if(find<x.size()-1 && x[find+1]=='^')
			{
				find+=2;//position of opening parenthesis of power
				find=parenpos(x,find);//goes to position of closing parenthesis of power, assuming that all power is surrounded by parenthesis
				i=find;
			}
			else
			{
				i=find;
			}
		}


		if(i<x.size() && (isalpha(x[i]) && x[i]!='x'))
		{
			i=searchstrpos(x,i)+1;
			i=parenpos(x,i)+1;
			if(i<x.size() && x[i]=='^')
			{
				i=parenpos(x,i+1);
				i++;
			}
			if(x.find("x",i)!=-1)
			{
				if(x[i]!='*' && x[i]!='+' && x[i]!='-')
				{
					x.insert(i,"*");// if it's not, will insert * 
				}
			}
		}
		else if(i<x.size() && x[i]=='x')
		{
			i++;
			if(i<x.size() && x[i]=='^')
			{
				i=parenpos(x,i+1);
				i++;
			}
			if(x.find("x",i+1)!=-1)
			{
				if(x[i]!='*' && x[i]!='+' && x[i]!='-')
				{
					x.insert(i,"*");// if it's not, will insert * 
				}
			}
		}

	}
		
	return x;
}

string rewritequotientfunction(string x)//if x/sinx, will return x(sin(x))^(-1)
{
	vector<string> replacer(0);
	vector<string> replacer2(0);
	string finalresult;

	replacer=rewriteseparatebyplusminus(x);
	
	for(int n=0;n<replacer.size();n++)
	{
		string result;

		replacer2=rewriteseparatebymultiply(replacer[n]);


		for(int n2=0;n2<replacer2.size();n2++)
		{
			{//if x/sin(x), it is seperated as [x] and [/sin(x)], since sin(x) is shown as dividing, will rewrite it as (sin(x)^(-1)
				if(replacer2[n2][0]=='/')
				{
					replacer2[n2].erase(0,1);//removes the division sign
					if(replacer2[n2].find("x")!=-1)//if not just a constant, 
					{
						replacer2[n2].insert(0,"(");
						replacer2[n2].append(")^(-1)");
					}
					else//if it is a constant, will make it (1/c) where c is the constant
					{
						replacer2[n2].insert(0,"(1/");
						replacer2[n2].append(")");
					}
				}
			}

			{//if replacer[n2] hold a function like 1/sin(x)
				string coeff;
				while(!replacer2[n2].empty() && !isalpha(replacer2[n2][0]) && replacer2[n2][0]!='(')//collects coefficient infront of replacer[n2]
				{
					coeff+=replacer2[n2][0];
					replacer2[n2].erase(0,1);
				}
				if(!coeff.empty() && coeff[coeff.size()-1]=='/')//makes sure there is a division sign indication the division method, then removes division sign and return 1(sin(x))^(-1)
				{
					coeff.erase(coeff.size()-1,1);//removes the division sign 
					replacer2[n2].insert(0,"(");
					replacer2[n2].append(")^(-1)");
					replacer2[n2].insert(0,coeff);
				}
				else if(!coeff.empty())//if it is not being divided, will return the coefficient and move on
				{
					replacer2[n2].insert(0,coeff);
				}
			}

			{//if replacer2[n2] hold a function like sin(x)/2, will return (sin(x))1/2
				int find=replacer2[n2].find_last_of("/");//finds the division sign
				if(find!=-1 && replacer2[n2].find_last_of("x",find)!=-1 && replacer2[n2].find_last_of(")")<find)//makes sure numerator is not constant 
				{
					string collect;//collects numerator
					for(int i=0;i<find;i++)
					{
						collect+=replacer2[n2][0];
						replacer2[n2].erase(0,1);
					}
					replacer2[n2].insert(0,"1");// adds 1 as the new numerator
					replacer2[n2].append(collect);//for some reason appends the new fraction after the function, but there is a case at the bottom removes all coefficient thats behind function and puts it up front
				}

			}

			{//if sin(x)^(0), will return 1, if sin(x)^(1), will return sin(x)
				int find=replacer2[n2].find_last_of("^");//find position of power
				if(find!=-1)// if there is power
				{
					int pos=parenpos(replacer2[n2],find+1);//move to closing parenthesis of power *all power are parenthesized*
					if(pos=replacer2[n2].size()-1)//makes sure the position of the closing parenthesis of power is the last character
					{
						string collect;//holds the value of the power
						for(int i=find+2;i<pos;i++)
						{
							collect+=replacer2[n2][i];
						}
						if(collect=="0")//if power =0, will return function=1
						{
							replacer2[n2]="(1)";
						}
						//if(collect=="1")//if power =
						//{
						//	replacer2[n2].erase(find,pos+1-find);
						//}
					}
				}
			}

			result+=replacer2[n2];

			//move coefficient that may appear in the back to the front
			string collect;//collects whats in the back of function
            while(result.find("x")!=-1 && result.back()!='^' && !isalpha(result.back()) && result.back()!=')')//collect assuming it is only digits
			{
				string hold;
				hold+=result.back();
				collect.insert(0,hold);
                result.erase(result.size()-1,1);
			}
			if(!result.empty() && result.back()=='^')
			{
				result.append(collect);
			}
			else if(!collect.empty())
			{
				result.insert(0,"("+collect+")");
			}
		}


		finalresult+=result;
		if(n<replacer.size()-1)
		{
			finalresult+="+";
		}
	}
	return rewritedoubleoperation(finalresult);
}

string rewritefunction(string x)//rewriting function for graphing.
{
    string result,finalresult;
    vector<string> replacer(1);//holds separated function by plus minus. so if x+3, holds [x] [3]
	replacer=rewriteseparatebyplusminus(x);
	//comes with a + added sofix it

	for(int n=0; n<replacer.size(); n++) //t+1 = how many string in replacer vector
	{
        string coeff;
        while(!replacer[n].empty() && !isalpha(replacer[n][0]) && replacer[n][0]!='(')
        {
            coeff+=replacer[n][0];
            replacer[n].erase(0,1);
        }
        if(coeff.find("/")!=-1)
        {
            rational<int> hold=boost::lexical_cast<rational<int>>(coeff);
            double hold1=boost::rational_cast<double>(hold);
            replacer[n].insert(0,boost::lexical_cast<string>(hold1));
        }
        else
        {
            replacer[n].insert(0,coeff);
        }
        result=rewriteproductfunction(replacer[n]);
        for(int i=0; i<result.size(); i++)//collects expression surrounded by parenthesis and simplify if necessary (taken from simplifyfinal(string x))
        {
            if(i!=result.length()-1)
            {
                if(isdigit(result[i]) && isalpha(result[i+1]))
                {
                    result.insert(i+1,"*");
                }

                if(result[i] == ')' && result[i+1] == '(')
                {
                    result.insert(i+1,"*");

                }
                if(result[i]=='^')
                {
                    result.replace(i,1,"**");
                }
            }
            int at=i;//where the opening parenthesis was found.
            if(result[at]=='(')
            {
                string y;
                int found;
                found=parenpos(result,i);// goes to position of the correct closing parenthesis
                i++;
                for(int l=i;l<found;l++)// collects whats inside of parenthesis and passes it to string y
                {
                    y.push_back(result[i]);
                    result.erase(i,1);
                }

                y=rewritefunction(y);//perform rewritefunction format to what was collect in string y
                result.insert(i,y);
                i+=y.size();
            }


		}
        finalresult+=result;
		if(n<replacer.size()-1)
		{
            finalresult+='+';
		}
	}

    for(int i=0; i<finalresult.size(); i++)//collects expression surrounded by parenthesis and simplify if necessary (taken from simplifyfinal(string x))
     {
         if(searchstrfirst(finalresult,i)=="arcsin")//search through and find arcsin and change it to asin
           {
			   i=searchstrpos(finalresult,i)-5;
               finalresult.replace(i,6,"asin");
			   i+=3;
           }
           else if(searchstrfirst(finalresult,i)=="arccos")//search through and find arccos and change it to acos
           {
			   i=searchstrpos(finalresult,i)-5;
               finalresult.replace(i,6,"acos");
			   i+=3;
           }
           else if(searchstrfirst(finalresult,i)=="arctan")//search through and find arctan and change it to atan
           {
			   i=searchstrpos(finalresult,i)-5;
               finalresult.replace(i,6,"atan");
			   i+=3;
           }
           else if(searchstrfirst(finalresult,i)=="arccsc")//search through and find arccsc and change it to acsc
           {
			   i=searchstrpos(finalresult,i)-5;
               finalresult.replace(i,6,"acsc");
			   i+=3;
           }
           else if(searchstrfirst(finalresult,i)=="arcsec")//search through and find arcsec and change it to asec
           {
			   i=searchstrpos(finalresult,i)-5;
               finalresult.replace(i,6,"asec");
			   i+=3;
           }
           else if(searchstrfirst(finalresult,i)=="arccot")//search through and find arccot and change it to acot
           {
			   i=searchstrpos(finalresult,i)-5;
               finalresult.replace(i,6,"acot");
			   i+=3;
           }
          else  if(searchstrfirst(finalresult,i)=="log")//search through and find log and change it to log10
           {
			   i=searchstrpos(finalresult,i)-2;
               finalresult.replace(i,3,"log10");
			   i+=3;
           }
           else if(searchstrfirst(finalresult,i)=="ln")//search through and find ln and change it to log
           {
			   i=searchstrpos(finalresult,i)-1;
               finalresult.replace(i,2,"log");
			   i+=2;
           }
           else if(finalresult.find("e**",i)!=-1)//search through and find e and change it to exp
           {
               i=finalresult.find("e**",i);
               finalresult.replace(i,3,"exp");
               i+=3;
           }
 }

    return rewritedoubleoperation(finalresult);
}

string rewriterearrange(string x)//rearranges function so if sin(x^2)xcos(x), will return xsin(x^2)cos(x)
{
	vector <string> replacer(1),replacer2(1),holder(1);
	string finalresult;


	replacer=rewriteseparatebyplusminus(x);


	for(int n=0; n<replacer.size(); n++)
	{	
		string result;
		vector<int> order;//holds the numbered order of functions
		replacer2=rewriteseparatebymultiply(replacer[n]);
		holder.resize(replacer2.size()+19);
		string coeff;//holds the coefficient
		if(replacer2.size()==1)
		{
			finalresult+=replacer2[0];
			if(n+1!=replacer.size())
			{
				finalresult+="+";
			}
			continue;
		}
		while(!replacer2[0].empty() && (isdigit(replacer2[0][0]) || replacer2[0][0]=='-' || replacer2[0][0] =='/'))//collects coefficient in front of function and erases it, so it stays in front
		{
			coeff+=replacer2[0][0];
			replacer2[0].erase(0,1);
		}
		if(replacer2[0].empty() || replacer2[0][0]=='^')//coefficient might indicate an exponential function like 2^x, so will put it back and if there was a negative, will take it out
		{
			replacer2[0].insert(0,coeff);
			if(replacer2[0][0]=='-')//holds the negative sign if it exists and keeps it in front
			{
				replacer2[0].erase(0,1);
				result+="-";
			}
		}
		else//if coefficient does not indicate an exponential function, will hold coefficient and keep it in front
		{
			result+=coeff;
		}
		for(int n2=0; n2<replacer2.size(); n2++)//test for the right function and assign it it's order
		{
			//checks for the right function and makes sure it 's not trapped in the power of an exponential, so will skip 2^(sin(x))
			//everything but polynomials, 2^x and x^x and assigned a number greater than 1, all else is given 0
			if(replacer2[n2][0]=='(')
			{
				order.push_back(16);
			}
			else if(searchstrfirst(replacer2[n2],0)=="exp" && (replacer2[n2].find("e^") < replacer2[n2].find("^")))
			{
				order.push_back(1);
			}
			else if(searchstrfirst(replacer2[n2],0)=="ln" && (replacer2[n2].find("ln") < replacer2[n2].find("^")))
			{
				order.push_back(2);
			}
			else if(searchstrfirst(replacer2[n2],0)=="log" && (replacer2[n2].find("log") < replacer2[n2].find("^")))
			{
				order.push_back(3);
			}
			else if(searchstrfirst(replacer2[n2],0)=="sin" && (replacer2[n2].find("sin") < replacer2[n2].find("^")))
			{
				order.push_back(4);
			}
			else if(searchstrfirst(replacer2[n2],0)=="cos" && (replacer2[n2].find("cos") < replacer2[n2].find("^")))
			{
				order.push_back(5);
			}
			else if(searchstrfirst(replacer2[n2],0)=="tan" && (replacer2[n2].find("tan") < replacer2[n2].find("^")))
			{
				order.push_back(6);
			}
			else if(searchstrfirst(replacer2[n2],0)=="csc" && (replacer2[n2].find("csc") < replacer2[n2].find("^")))
			{
				order.push_back(7);
			}
			else if(searchstrfirst(replacer2[n2],0)=="sec" && (replacer2[n2].find("sec") < replacer2[n2].find("^")))
			{
				order.push_back(8);
			}
			else if(searchstrfirst(replacer2[n2],0)=="cot" && (replacer2[n2].find("cot") < replacer2[n2].find("^")))
			{
				order.push_back(9);
			}
			else if(searchstrfirst(replacer2[n2],0)=="arcsin" && (replacer2[n2].find("arcsin") < replacer2[n2].find("^")))
			{
				order.push_back(10);
			}
			else if(searchstrfirst(replacer2[n2],0)=="arccos" && (replacer2[n2].find("arccos") < replacer2[n2].find("^")))
			{
				order.push_back(11);
			}
			else if(searchstrfirst(replacer2[n2],0)=="arctan" && (replacer2[n2].find("arctan") < replacer2[n2].find("^")))
			{
				order.push_back(12);
			}
			else if(searchstrfirst(replacer2[n2],0)=="arccsc" && (replacer2[n2].find("arccsc") < replacer2[n2].find("^")))
			{
				order.push_back(13);
			}
			else if(searchstrfirst(replacer2[n2],0)=="arcsec" && (replacer2[n2].find("arcsec") < replacer2[n2].find("^")))
			{
				order.push_back(14);
			}
			else if(searchstrfirst(replacer2[n2],0)=="arccot" && (replacer2[n2].find("arccot") < replacer2[n2].find("^")))
			{
				order.push_back(15);
			}
			else
			{
				order.push_back(0);
			}

		}
		//if two of the same orders appear, i.e. 0 1 0, will increment like 0 2 1 so the function is properly placed
		for(int n2=0; n2<replacer2.size(); n2++)
		{
			for(int l=n2+1;l<order.size();l++)
			{
				if(order[n2]==order[l])//checks to see if two of the same orders appear
				{
					//the loop to increment all orders
					for(int i=n2+1; i<order.size();i++)
					{
						order[i]+=1;
					}
					break;
				}

			}

			holder[order[n2]]=replacer2[n2];
		}

		// holder holds the ordered function, the function is placed in it's specified position in holder, specified position is labeled in vector<int> order
		//so if function contains sin(x)xcos(x), order will hold [4][0][5], then holder will place functions in position 4, 0 and 5
		//the size of holder= the size of the split function + the number of function types, for safe measures.
		//unused slots in holder are skipped
		for(int i=0; i<holder.size();i++)
		{
			if(!holder[i].empty())
			{
				result+=holder[i];
			}
		}

		finalresult+=result;
		if(n+1!=replacer.size())
		{
			finalresult+="+";
		}
	}

	finalresult=rewritedoubleoperation(finalresult);

	return finalresult;
}

string trigidentities(string x,string option)//does trig identities with option to expand, tanx=sinx/cosx, or compress, sinx/cosx=tanx
{//more identities to come when needed

	if(option=="expand")//if we want tanx=sinx/cosx
	{
		vector<string> replacer(1),replacer2(1);
		string finalresult;
		replacer=rewriteseparatebyplusminus(x);
		for(int n=0;n<replacer.size();n++)
		{
			string result;
			replacer2=rewriteseparatebymultiply(replacer[n]);
			for(int n2=0;n2<replacer2.size();n2++)
			{
				if(searchstrfirst(replacer2[n2],0)=="tan")//searches for tan to expand
				{
					string denom=replacer2[n2].replace(replacer2[n2].find("tan"),3,"sin");//does two things, replaces tan with sin, and denom holds that value, which will be changed to cos
					denom.replace(denom.find("sin"),3,"cos");//denom changed to cos
					replacer2.insert(replacer2.begin()+n2+1,"("+denom+")^(-1)");//adds denom which is cos as a denominator in sin(x)/cos(x), to the list of string, so not [tan(x)] was split to [sin(x)][cos(x)^(-1)]
				}
				if(searchstrfirst(replacer2[n2],0)=="cot")//searches for tan to expand
				{
					string denom=replacer2[n2].replace(replacer2[n2].find("cot"),3,"cos");//does two things, replaces cot with cos, and denom holds that value, which will be changed to sin
					denom.replace(denom.find("cos"),3,"sin");//denom changed to sin
					replacer2.insert(replacer2.begin()+n2+1,"("+denom+")^(-1)");//adds denom which is cos as a denominator in cos(x)/sin(x), to the list of string, so not [cot(x)] was split to [cos(x)][sin(x)^(-1)]
				}
				result+=replacer2[n2];
			}
			finalresult+=result;
			if(n<replacer.size()-1)
			{
				finalresult+='+';
			}
		}
		return finalresult;
	}
	else if(option=="compress")//if we want sinx/cosx=tanx
	{
		vector<string> replacer(1),replacer2(1);
		string finalresult;
		replacer=rewriteseparatebyplusminus(x);
		for(int n=0;n<replacer.size();n++)
		{
			replacer2=rewriteseparatebymultiply(replacer[n]);
			for(int n2=0;n2<replacer2.size();n2++)
			{
				int find=searchstrpos(replacer2[n2],0)+1;//finds pos of trig function, so if sin(x) find =[(]=3
				find=parenpos(replacer2[n2],find)+1;//goes to position after closing parenthesis of trig quantity, so if sin(x)^(-2) find=[^]=6
				if(find!=replacer2[n2].size() && replacer2[n2][find]=='^')//makes sure power of sin is > 1, and double checks for pow sign '^'
				{
					find+=2;//goes to position of first character of the power
					if(replacer2[n2][find]=='-')//if it is negative, so sin(x)^(-2), which means 1/sin(x)^(2)
					{
						replacer2[n2].erase(find,1);//removes the negative sign
						if(searchstrfirst(replacer2[n2],0)=="sin")//converts sin(x)^-1 to csc(x) or if cos(x)sin(x)^-1, will convert to tan(x)
						{
							if(n2<replacer2.size()-1 && searchstrfirst(replacer2[n2+1],0)=="cos")//checks to see if sin(x)^(-1)cos(x), we are at pos of sin(x)^-1 of replacer2, and we checks the value after of replacer2, so we first have to make sure we are not out of range of replacer2
							{
								string collect1,collect2;//holds trig quantity, so if sin(x), holds x
								int find1=searchstrpos(replacer2[n2],0)+1;//goes to the position of opening parenthesis of sin(x) quantity
								int find2=searchstrpos(replacer2[n2+1],0)+1;//goes to the position of opening parenthesis of cos(x) quantity
								int pos1=parenpos(replacer2[n2],find1);//goes to the position of closing parenthesis of sin(x) quantity
								int pos2=parenpos(replacer2[n2+1],find2);//goes to the position of closing parenthesis of cos(x) quantity
								for(int i1=find1+1;i1<pos1;i1++)//collects the quantity of sin(x) which is x
								{
									collect1+=replacer2[n2][i1];
								}
								for(int i2=find2+1;i2<pos2;i2++)//collects the quantity of cos(x) which is x
								{
									collect2+=replacer2[n2+1][i2];
								}
								if(collect1==collect2)//makes sure both quantity of cos and sin are the same, will skip out if it is not and just convert sin(x)^-1 to csc(x)
								{
									//at this point, we assume that the power of cos is positive and sin is negative, which should be taken cared of the order of the loop of replacer2
									string pow1,pow2;//holds the value of power
									if(pos1==replacer2[n2].size()-1)//if there is no power indicated, will use 1 as a placeholder, since it means it's raised to the 1 power
									{
										pow1="1";
									}
									else if(replacer2[n2][pos1+1]=='^')//if there is a power indicated, will go on to collect the power
									{
										find1=pos1+2;//goes to position of the opening parenthesis of power
										pos1=parenpos(replacer2[n2],find1);//goes to the position of the closing parenthesis of power
										for(int i1=find1+1;i1<pos1;i1++)//loop to collect power
										{
											pow1+=replacer2[n2][i1];
										}
									}
									if(pos2==replacer2[n2+1].size()-1)//if there is no power indicated, will use 1 as a placeholder, since it means it's raised to the 1 power
									{
										pow2="1";
									}
									else if(replacer2[n2+1][pos2+1]=='^')//if there is a power indicated, will go on to collect the power
									{
										find2=pos2+2;//goes to position of the opening parenthesis of power
										pos2=parenpos(replacer2[n2+1],find2);//goes to the position of the closing parenthesis of power
										for(int i2=find2+1;i2<pos2;i2++)//loop to collect power
										{
											pow2+=replacer2[n2+1][i2];
										}
									}
									if(pow2[0]!='-')
									{
										//toInt(variable) is a function i wrote which is located in global-variable.h to convert from any variable to int, it has other conversions
										if(toInt(pow1)>toInt(pow2))//if cos(x)/sin^2x
										{
											replacer2[n2+1]=replacer2[n2+1].replace(replacer2[n2+1].find("cos"),3,"cot");//returns cot(x)
											replacer2[n2].replace(replacer2[n2].find(pow1,find1),pow1.size(),"-"+simplify(pow1+"-"+pow2));//and leaves out remaining sin(x)
										}
										else if(toInt(pow1)<toInt(pow2))//if cos(x)^(2)/sin(x)
										{
											replacer2[n2]=replacer2[n2].replace(replacer2[n2].find("sin"),3,"cot");//returns cot(x)
											replacer2[n2+1].replace(replacer2[n2+1].find(pow2,find2),pow2.size(),simplify(pow2+"-"+pow2));//and leaves out remaining cos(x)
										}
										else if(toInt(pow1)==toInt(pow2))//if cos(x)/sin(x)
										{
											replacer2[n2+1]=replacer2[n2+1].replace(replacer2[n2+1].find("cos"),3,"cot");//returns cot(x)
											replacer2.erase(replacer2.begin()+n2);//and removes remaining sin(x)
										}
										n2-=1;
									}
									else//from the previous, if the quantities are not the same, that means we cannot compress to cot(x), will compress 1/sinx to cscx
									{
										replacer2[n2].replace(replacer2[n2].find("sin"),3,"csc");
									}
								}
								else//from the previous, if the quantities are not the same, that means we cannot compress to cot(x), will compress 1/sinx to cscx
								{
									replacer2[n2].replace(replacer2[n2].find("sin"),3,"csc");
								}
							}
							else//if there is no cos(x) from previous, will compress 1/sinx to cscx
							{
								replacer2[n2].replace(replacer2[n2].find("sin"),3,"csc");
							}
						}
						else if(searchstrfirst(replacer2[n2],0)=="cos")//converts cos(x)^-1 to sec(x) or if sin(x)cos(x)^-1, will convert to tan(x)
						{
							if(n2!=0 && searchstrfirst(replacer2[n2-1],0)=="sin")
							{
								string collect1,collect2;//holds trig quantity, so if cos(x), holds x
								int find1=searchstrpos(replacer2[n2],0)+1;//goes to the position of opening parenthesis of cos(x) quantity
								int find2=searchstrpos(replacer2[n2-1],0)+1;//goes to the position of opening parenthesis of sin(x) quantity
								int pos1=parenpos(replacer2[n2],find1);//goes to the position of closing parenthesis of cos(x) quantity
								int pos2=parenpos(replacer2[n2-1],find2);//goes to the position of closing parenthesis of sin(x) quantity
								for(int i1=find1+1;i1<pos1;i1++)//collects the quantity of cos(x) which is x
								{
									collect1+=replacer2[n2][i1];
								}
								for(int i2=find2+1;i2<pos2;i2++)//collects the quantity of sin(x) which is x
								{
									collect2+=replacer2[n2-1][i2];
								}
								if(collect1==collect2)//makes sure both quantity of sin and cos are the same, will skip out if it is not and just convert cos(x)^-1 to sec(x)
								{
									//at this point, we assume thatthe power of sin is positive and cos is negative, which should be taken cared of the order of the loop of replacer2
									string pow1,pow2;//holds the value of power
									if(pos1==replacer2[n2].size()-1)//if there is no power indicated, will use 1 as a placeholder, since it means it's raised to the 1 power
									{
										pow1="1";
									}
									else if(replacer2[n2][pos1+1]=='^')//if there is a power indicated, will go on to collect the power
									{
										find1=pos1+2;//goes to position of the opening parenthesis of power
										pos1=parenpos(replacer2[n2],find1);//goes to the position of the closing parenthesis of power
										for(int i1=find1+1;i1<pos1;i1++)//loop to collect power
										{
											pow1+=replacer2[n2][i1];
										}
									}
									if(pos2==replacer2[n2-1].size()-1)//if there is no power indicated, will use 1 as a placeholder, since it means it's raised to the 1 power
									{
										pow2="1";
									}
									else if(replacer2[n2-1][pos2+1]=='^')//if there is a power indicated, will go on to collect the power
									{
										find2=pos2+2;//goes to position of the opening parenthesis of power
										pos2=parenpos(replacer2[n2-1],find2);//goes to the position of the closing parenthesis of power
										for(int i2=find2+1;i2<pos2;i2++)//loop to collect power
										{
											pow2+=replacer2[n2-1][i2];
										}
									}
									//toInt(variable) is a function i wrote which is located in global-variable.h to convert from any variable to int, it has other conversions
									if(toInt(pow1)>toInt(pow2))//if sin(x)/cos^2x
									{
										replacer2[n2-1]=replacer2[n2-1].replace(replacer2[n2-1].find("sin"),3,"tan");//returns tan(x)
										replacer2[n2].replace(replacer2[n2].find(pow1,find1),pow1.size(),"-"+simplify(pow1+"-"+pow2));//and leaves out remaining cos(x)
									}
									else if(toInt(pow1)<toInt(pow2))//if sin(x)^(2)/cos(x)
									{
										replacer2[n2]=replacer2[n2].replace(replacer2[n2].find("cos"),3,"tan");//returns tan(x)
										replacer2[n2-1].replace(replacer2[n2-1].find(pow2,find2),pow2.size(),simplify(pow2+"-"+pow1));//and leaves out remaining sin(x)
									}
									else if(toInt(pow1)==toInt(pow2))//if sin(x)/cos(x)
									{
										replacer2[n2-1]=replacer2[n2-1].replace(replacer2[n2-1].find("sin"),3,"tan");//returns tan(x)
										replacer2.erase(replacer2.begin()+n2);//and removes remaining cos(x)
									}
									n2-=1;
								}
								else//from the previous, if the quantities are not the same, that means we cannot compress to tan(x), will compress 1/cosx to secx
								{
									replacer2[n2].replace(replacer2[n2].find("cos"),3,"sec");
								}
							}
							else//if there is no sin(x) from previous, will compress 1/cosx to secx
							{
								replacer2[n2].replace(replacer2[n2].find("cos"),3,"sec");
							}
						}
						else if(searchstrfirst(replacer2[n2],0)=="tan")//converts tan(x)^-1 to cot(x)
						{
							replacer2[n2].replace(replacer2[n2].find("tan"),3,"cot");
						}
						else if(searchstrfirst(replacer2[n2],0)=="csc")//converts csc(x)^-1 to sin(x)
						{
							replacer2[n2].replace(replacer2[n2].find("csc"),3,"sin");
						}
						else if(searchstrfirst(replacer2[n2],0)=="sec")//converts sec(x)^-1 to cos(x)
						{
							replacer2[n2].replace(replacer2[n2].find("sec"),3,"cos");
						}
						else if(searchstrfirst(replacer2[n2],0)=="cot")//converts cot(x)^-1 to tan(x)
						{
							replacer2[n2].replace(replacer2[n2].find("cot"),3,"tan");
						}
					}

				}

			}
			string result;
			for(int n2=0;n<replacer2.size();n2++)
			{
				result+=replacer2[n2];
			}
			finalresult+=result;
			if(n<replacer.size()-1)
			{
				finalresult+='+';
			}
		}
		return finalresult;
	}
	else//specific rules dictated by string option
	{
		return x;
	}
}

int parenpos(string x,int i)//return the position of closing parenthesis. so if sec(x^(1/2)), the last closing parenthesis will be returned
{
	if(x[i]=='(')
	{
		int at =i;
		int found=i;
		i++;
		while(i<x.size())
		{
			if(x[i]=='(' || x[i]==')')//makes sure it reaches the right closing parenthesis
			{
				if(x[i]=='(')
				{
					found++;
				}
				if(found==at && x[i]==')')
				{
					break;
				}
				if(found!=at && x[i]==')')
				{
					found--;
				}

			}
			i++;
		}
	}
	else if(x[i]==')')
	{
		int at =i;
		int found=i;
		i--;
		while(i<x.size())
		{
			if(x[i]==')' || x[i]=='(')//makes sure it reaches the right closing parenthesis
			{
				if(x[i]==')')
				{
					found++;
				}
				if(found==at && x[i]=='(')
				{
					break;
				}
				if(found!=at && x[i]=='(')
				{
					found--;
				}

			}
			i--;
		}
	}

	return i;
}