#include <boost/rational.hpp>
#include <boost/config.hpp>
#include <boost\lexical_cast.hpp>
#include <iostream>	// cin, cout, etc.
#include <string>	// string class
#include <queue>

using namespace std;
using boost::rational;
using boost::lexical_cast;

void finaloutput(string function, string derivative, string integral);
void evaluationoutput(string function, string input, string answer);
void areaoutput(string function, string integral, string xfrom, string xto, string answer);
string convert2ascii(string x); // format the final output of the function so it can be properly outputted

void finaloutput(string function, string derivative, string integral)
{
	function=convert2ascii(function);
	derivative=convert2ascii(derivative);
	ofstream derivativeoutput("Formatted_Output\\Outputs\\derivative\\output.html");
    {
        derivativeoutput<<"<!DOCTYPE html>"<<endl;
        derivativeoutput<<"<html>"<<endl;
        derivativeoutput<<"<head>"<<endl;
        derivativeoutput<<"<script type=\"text/javascript\" src=\"../../MathJax.js?config=TeX-AMS-MML_SVG-full\"></script>"<<endl;
        derivativeoutput<<"<style>html,body{width:100%;margin-left:0px;margin-top:-8px;}</style>"<<endl;
        derivativeoutput<<"</head>"<<endl;
        derivativeoutput<<"<body><p><a href=\"#link\">`d/dx("<<function<<")="<<derivative<<"`</a></p></body>"<<endl;
		derivativeoutput<<"</html>"<<endl;
	}
//    ofstream integraloutput("Formatted_Output\\Outputs\\integral\\output.html");
//    {
//        integraloutput<<"<!DOCTYPE html>"<<endl;
//        integraloutput<<"<html>"<<endl;
//        integraloutput<<"<head>"<<endl;
//        integraloutput<<"<script type=\"text/javascript\" src=\"../../MathJax.js?config=TeX-AMS-MML_SVG-full\"></script>"<<endl;
//        integraloutput<<"<style>html,body{width:100%;margin-left:0px;margin-top:-8px;}</style>"<<endl;
//        integraloutput<<"</head>"<<endl;
//        if(integral=="NonElementary_Function")
//        {
//            integral="NonElementary_Function. Integral cannot be done by elementary function.";
//            integraloutput<<"<body><p>NonElementary_Function or Integration type not defined yet.</p></body>"<<endl;
//        }
//        else
//        {
//            integral=convert2ascii(integral);
//            integraloutput<<"<body><p><a href=\"#link\">`int"<<function<<"="<<integral<<"`</a></p></body>"<<endl;
//        }
//        integraloutput<<"</html>"<<endl;
//    }
}

void evaluationoutput(string function, string input, string answer)
{
    function=convert2ascii(function);
    while(function.find("x")!=-1)
    {
        int i=function.find("x");
        if(i>0 && ((function[i-1]=='(' && function[i+1]==')') || (function[i-1]=='|' && function[i+1]=='|')))
        {
            function.replace(function.find("x"),1,input);
        }
        else
        {
            function.replace(function.find("x"),1,"("+input+")");
        }

    }
    ofstream output("Formatted_Output\\Outputs\\evaluation.html");
    {
        output<<"<!DOCTYPE html>"<<endl;
        output<<"<html>"<<endl;
        output<<"<head>"<<endl;
        output<<"<script type=\"text/javascript\" src=\"../MathJax.js?config=TeX-AMS-MML_SVG-full\"></script>"<<endl;
        output<<"<style>html,body{width:100%;margin-left:0px;margin-top:-8px;margin-bottom:-15px;}</style>"<<endl;
        output<<"</head>"<<endl;
        output<<"<body><p style=\"margin-left:0px;margin-top:15px;\">`f("<<input<<") = "<<function<<"`</p></body><body><p style=\"margin-left:0px;margin-top:-20px;\">`f("<<input<<") = "<<answer<<"`</p></body>"<<endl;
        output<<"</html>"<<endl;

    }
}

void areaoutput(string function, string integral, string xfrom, string xto, string answer)
{
    function=convert2ascii(function);
    integral=convert2ascii(integral);
    ofstream output("Formatted_Output\\Outputs\\CalculateOutput.html");
    {
        output<<"<!DOCTYPE html>"<<endl;
        output<<"<html>"<<endl;
        output<<"<head>"<<endl;
        output<<"<script type=\"text/javascript\" src=\"../MathJax.js?config=TeX-AMS-MML_SVG-full\"></script>"<<endl;
        output<<"<style>html,body{width:100%;margin-left:0px;margin-top:-8px;margin-bottom:-15px;}</style>"<<endl;
        output<<"</head>"<<endl;
        output<<"<body><p style=\"margin-left:0px;margin-top:15px;\">`int_"+xfrom+"^"+xto+function+"dx`</p></body><br>"<<endl;
        output<<"<body><p style=\"margin-left:0px;margin-top:-20px;\">`["+integral+"]_"+xfrom+"^"+xto+"`</p></body><br>"<<endl;

        string integralcopy=integral;

        while(integral.find("x")!=-1)
        {
            int i=integral.find("x");
            if(i>0 && ((integral[i-1]=='(' && integral[i+1]==')') || (integral[i-1]=='|' && integral[i+1]=='|')))
            {
                integral.replace(integral.find("x"),1,xto);
            }
            else
            {
                integral.replace(integral.find("x"),1,"("+xto+")");
            }

        }

        while(integralcopy.find("x")!=-1)
        {
            int i=integralcopy.find("x");
            if(i>0 && ((integralcopy[i-1]=='(' && integralcopy[i+1]==')') || (integralcopy[i-1]=='|' && integralcopy[i+1]=='|')))
            {
                integralcopy.replace(integralcopy.find("x"),1,xfrom);
            }
            else
            {
                integralcopy.replace(integralcopy.find("x"),1,"("+xfrom+")");
            }

        }
        output<<"<body><p style=\"margin-left:0px;margin-top:-20px;\">`("+integral+")-("+integralcopy+")="+answer+"`</p></body>"<<endl;
        output<<"</html>"<<endl;

    }
}

string convert2ascii(string x) // format the final output of the function so it can be properly outputted
{
	string result;
	
	vector<string> replacer(1),replacer2(1);
	replacer=rewriteseparatebyplusminus(x);
	
	for(int n=0;n<replacer.size();n++)
	{
		string numerator,denominator;
		replacer2=rewriteseparatebymultiply(replacer[n]);

		for(int n2=0;n2<replacer2.size();n2++)
		{

			{//this collects coefficient in front of expression and split it to denominator and numerator if possible.
				string coeff;
				while(!replacer2[n2].empty() && (isdigit(replacer2[n2][0]) || replacer2[n2][0]=='-' || replacer2[n2][0]=='/'))//collects coefficient and stores it in string coeff. replacer2[n2].empty() makes sure when it is just an integer it does not roll over
				{
					coeff+=replacer2[n2][0];
					replacer2[n2].erase(0,1);//erases coeff from expression
				}

				if(!coeff.empty() && coeff.find("/")!=-1)//collects numerator from coefficient if it is a fraction and places it in numerator and the rest in denominator
				{
					while(coeff[0]!='/')//collects numerator
					{
						numerator+=coeff[0];
						coeff.erase(0,1);
					}
					coeff.erase(0,1);//erases fraction sign '/'
					denominator+=coeff;//rest in denimator
				}
				else if(!coeff.empty())//if it is not a fraction will put it in numerator
				{
					numerator+=coeff;
				}

			}

			int find=replacer2[n2].find_last_of("^");//find power of expression
			if(find!=-1 && replacer2[n2][find+2]=='-')//if it is a negative power, meaning it belongs in the denominator, (checking if possible to change expression^(1/2) to sqrt(expression)
			{
				replacer2[n2].erase(find+2,1);//erases  the negative sign from power
				find++;//moves to opening parenthesis of power
				int at=find;//at holds the position of the opnening parenthesis of power
				string collect;//collects power including opening and closing parenthesis
				find=parenpos(replacer2[n2],find);//goes to closing parenthesis of power
				while(at<=find)//countes from open to close parenthesis while collects the expression of power and passing it to string collect
				{//note: does not delete from replacer2[n2]
					collect+=replacer2[n2][at];
					at++;
				}
				if(collect=="(1/2)" || collect=="(0.5)")//if expression is being squarooted
				{
					at--;//int at is at the position of the size of the expression, is ont step passed the last character, this bring it back to the last character
					find=parenpos(replacer2[n2],find);//goes to opening parenthesis of power
					while(at>=find)//moves back to opening parenthesis of power while erasing the power of the expression
					{
						replacer2[n2].erase(at,1);
						at--;
					}
					replacer2[n2].erase(at,1);//erases the power sign '^'
					find=at;//int at is at one position passed the last character again
					find--;//holds the position of the expression that was raised to (1/2)
					if(replacer2[n2][find]==')')
					{
						int hold=find;
						bool moved=false;//used to test is (x+5)^(1/2)=false or sin(x)^(1/2)=true, moved=true if second expression is present
						//at this point find is at the closing parenthesis of the expression being squarooted's position
						find=parenpos(replacer2[n2],find);//goes to the opening parenthesis of expression being squarooted
						

						while(find>0 &&(isalpha(replacer2[n2][find-1]) && replacer2[n2][find-1]!='x'))//used to test if what is in parenthesis is part of function type of selected type ex, sin, cos, arctan
						{
							find--;
							moved=true;
						}
						if(moved==true)//meaning that sin(x)^(1/2) occured
						{
							replacer2[n2].insert(hold+1,")");
							replacer2[n2].insert(find,"sqrt(");
						}
						else//if (x+5)^(1/2) occured
						{
							replacer2[n2].insert(find,"sqrt");
						}
					}
					else//is whats is being raised to (1/2) is not surrounded by parenthesis, will asume only one character is. 
					{
						replacer2[n2].insert(find+1,")");
						replacer2[n2].insert(find,"sqrt(");
					}
				}

				denominator+=replacer2[n2];
			}
			else if(find!=-1)//if there is a power but it is greator than 0, meaning it belongs in the numerator (checking if possible to change expression^(1/2) to sqrt(expression)
			{
				find++;//moves to opening parenthesis of power
				int at=find;//at holds the position of the opnening parenthesis of power
				string collect;//collects power including opening and closing parenthesis
				find=parenpos(replacer2[n2],find);//goes to closing parenthesis of power
				while(at<=find)//countes from open to close parenthesis while collects the expression of power and passing it to string collect
				{//note: does not delete from replacer2[n2]
					collect+=replacer2[n2][at];
					at++;
				}
				if(collect=="(1/2)" || collect=="(0.5)")//if expression is being squarooted
				{
					at--;//int at is at the position of the size of the expression, is ont step passed the last character, this bring it back to the last character
					find=parenpos(replacer2[n2],find);//goes to opening parenthesis of power
					while(at>=find)//moves back to opening parenthesis of power while erasing the power of the expression
					{
						replacer2[n2].erase(at,1);
						at--;
					}
					replacer2[n2].erase(at,1);//erases the power sign '^'
					find=at;//int at is at one position passed the last character again
					find--;//holds the position of the expression that was raised to (1/2)
					if(replacer2[n2][find]==')')
					{
						int hold=find;
						bool moved=false;//used to test is (x+5)^(1/2)=false or sin(x)^(1/2)=true, moved=true if second expression is present
						//at this point find is at the closing parenthesis of the expression being squarooted's position
						find=parenpos(replacer2[n2],find);//goes to the opening parenthesis of expression being squarooted
						

						while(find>0 &&(isalpha(replacer2[n2][find-1]) && replacer2[n2][find-1]!='x'))//used to test if what is in parenthesis is part of function type of selected type ex, sin, cos, arctan
						{
							find--;
							moved=true;
						}
						if(moved==true)//meaning that sin(x)^(1/2) occured
						{
							replacer2[n2].insert(hold+1,")");
							replacer2[n2].insert(find,"sqrt(");
						}
						else//if (x+5)^(1/2) occured
						{
							replacer2[n2].insert(find,"sqrt");
						}
					}
					else//is whats is being raised to (1/2) is not surrounded by parenthesis, will asume only one character is. 
					{
						replacer2[n2].insert(find+1,")");
						replacer2[n2].insert(find,"sqrt(");
					}
                }
				numerator+=replacer2[n2];
			}
			else
            {
				numerator+=replacer2[n2];
			}
		}
		if(numerator.empty() || numerator=="-")//if everything was passed to denominator, so if sin(x)^(-1/2) occured
		{
			if(numerator=="-")
			{
				result+="(-1)/("+denominator+")";
			}
			else
			{
				result+="(1)/("+denominator+")";
			}
		}
		else if(denominator.empty())//if nothing was passed to denominator, so if sin(x)^(1/2) occured
		{
			result+=numerator;
		}
		else//if we passed stuff to numerator and denominator so if xsin(x)^(-1/2) occured
		{
            result+="("+simplifycoeffandpow(numerator)+")/("+denominator+")";
		}

		if(n<replacer.size()-1)
		{
			result+="+";
		}
	}

	result=rewritedoubleoperation(result);

	for(int i=0; i<result.size(); i++)//collects expression surrounded by parenthesis and simplify if necessary (taken from simplifyfinal(string x))
	{
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

			y=convert2ascii(y);//perform finaloutput format to what was collect in string y
			result.insert(i,y);
			i+=y.size();
		}
	}
	while(result.find("abs")!=-1)//erases absolute value "abs" and replaces it with | |
	{

		int absopenparen=result.find("abs")+3;
		int abscloseparen=parenpos(result,absopenparen);
		result.replace(absopenparen,1,"|");
		result.replace(abscloseparen,1,"|");
		result.erase(result.find("abs"),3);
	}
	while(result.find("^(1)")!=-1)//erases power is it is raise to 1
    {
        result.erase(result.find("^(1)"),4);
    }
//    for(int i=0;i<result.size();i++)
//    {
//        if(result.find("arc",i)!=-1)//there is a problem with asciimath displaying arccsc, this takes care of it. outputs `arc``expression`
//        {
//            result.replace(result.find("arc",i),3,"arc``");
//        }
//        else
//        {
//            break;
//        }
//        i+=3;
//    }

    return result;
}
