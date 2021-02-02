bool cando_redform(string x);//checks if reduction formula is possible, saves time by not going through formulation and waiting for a return of nothing to see that it wasnt possible
vector<string> typeoffunction(string x);//finds the right formula type

bool cando_redform(string x)//checks if reduction formula is possible, saves time by not going through formulation and waiting for a return of nothing to see that it wasnt possible
{
	vector<string> replacer2(1);//no separate by plusminus, because since it goes through i_getdata first, it is already separated	
	replacer2=rewriteseparatebymultiply(x);
	if(replacer2.size()==1)
	{
			if(searchstrfirst(replacer2[0],0)=="sin")
			{
				return true;
			}
			else if(searchstrfirst(replacer2[0],0)=="cos")
			{
				return true;
			}
			else if(searchstrfirst(replacer2[0],0)=="tan")
			{
				return true;
			}
			else if(searchstrfirst(replacer2[0],0)=="csc")
			{
				return true;
			}
			else if(searchstrfirst(replacer2[0],0)=="sec")
			{
				return true;
			}
			else if(searchstrfirst(replacer2[0],0)=="cot")
			{
				return true;
			}
			else if(searchstrfirst(replacer2[0],0)=="arcsin")
			{
				return true;
			}
			else if(searchstrfirst(replacer2[0],0)=="arccos")
			{
				return true;
			}
			else if(searchstrfirst(replacer2[0],0)=="arctan")
			{
				return true;
			}
			else if(searchstrfirst(replacer2[0],0)=="arccsc")
			{
				return true;
			}
			else if(searchstrfirst(replacer2[0],0)=="arcsec")
			{
				return true;
			}
			else if(searchstrfirst(replacer2[0],0)=="arccsc")
			{
				return true;
			}
			else if(searchstrfirst(replacer2[0],0)=="ln")
			{
				return true;
			}
			else if(searchstrfirst(replacer2[0],0)=="log")
			{
				return true;
			}
			else if(searchstrfirst(replacer2[0],0)=="exp")
			{
				return true;
			}
	}
	else if(replacer2.size()==2)
	{
		if(searchstrfirst(replacer2[0],0)=="poly")
		{
			if(searchstrfirst(replacer2[1],0)=="sin")
			{
				return true;
			}
			else if(searchstrfirst(replacer2[1],0)=="cos")
			{
				return true;
			}
			else if(searchstrfirst(replacer2[1],0)=="arcsin")
			{
				return true;
			}
			else if(searchstrfirst(replacer2[1],0)=="arccos")
			{
				return true;
			}
			else if(searchstrfirst(replacer2[1],0)=="arctan")
			{
				return true;
			}
			else if(searchstrfirst(replacer2[1],0)=="arccsc")
			{
				return true;
			}
			else if(searchstrfirst(replacer2[1],0)=="arcsec")
			{
				return true;
			}
			else if(searchstrfirst(replacer2[1],0)=="arccot")
			{
				return true;
			}
			else if(searchstrfirst(replacer2[1],0)=="ln")
			{
				return true;
			}
			else if(searchstrfirst(replacer2[1],0)=="log")
			{
				return true;
			}
			else if(searchstrfirst(replacer2[1],0)=="exp")
			{
				return true;
			}
		}
		if(searchstrfirst(replacer2[0],0)=="exp")
		{
			if(searchstrfirst(replacer2[1],0)=="sin")
			{
				return true;
			}
			else if(searchstrfirst(replacer2[1],0)=="cos")
			{
				return true;
			}
		}
		if(searchstrfirst(replacer2[0],0)=="sin")
		{
			if(searchstrfirst(replacer2[1],0)=="cos")
			{
				return true;
			}
		}
	}
	return false;
}
vector<string> typeoffunction(string x)//finds the right formula type
{
	vector<string> result(2);
	string coeff;
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
	vector<string> replacer2(1);//no separate by plusminus, because since it goes through i_getdata first, it is already separated	
	replacer2=rewriteseparatebymultiply(x);
	if(replacer2.size()==1)
	{
		//for example of a function like 3ln(4x^(5))^(2)
		//coeff=3 a=4 m=5 n=2
		string a,n,m;
		int find1;
		int find=searchstrpos(replacer2[0],0)+2;//goes to the position of the first character of trig quantity, so if sin(2x) find will be at 2
		if(replacer2[0][find]=='x')//if there is no coefficient of the trig quantity, will add 1 as a placeholder
		{
			a="1";
			find1=find;
		}
		else//if there is a coefficient, will start collecting into a
		{
			for(int i=find;i<replacer2[0].find("x");i++)
			{
				a+=replacer2[0][i];
				if(i+1==replacer2[0].find("x"))
				{
					find1=i+1;
				}
			}
		}
		if(replacer2[0][find1+1]=='^')
		{
			find1+=2;
			int pos=parenpos(replacer2[0],find1);
			for(int i=find1+1;i<pos;i++)//start collecting the value of power into n
			{
				m+=replacer2[0][i];
			}			
		}
		else
		{
			m="1";
		}

		find=searchstrpos(replacer2[0],0)+1;//goes back to position of opening parenthesis of trig quantity
		find=parenpos(replacer2[0],find);//goes to closing parenthesis of trig quantity
		if(find==replacer2[0].size()-1)//if there is no power on function
		{
			n="1";
		}
		else if(find!=replacer2[0].size()-1 && replacer2[0][find+1]=='^')//if there is power after function, collect it.
		{
			find+=2;//goes to position of opening parenthesis of power
			int pos=parenpos(replacer2[0],find);//goes to position of closing parenthesis of power
			for(int i=find+1;i<pos;i++)//start collecting the value of power into n
			{
				n+=replacer2[0][i];
			}
		}
			if(n[0]!='-')//if power is a negative number, will convert to csc using trigidentities. so if sin(x)^(-1), will return csc(x) then integrate that
			{
				if(searchstrfirst(replacer2[0],0)=="sin" && n!="1")
				{
					//intgeral(sin(ax)^(n) dx)=(-1/a*n)sin(ax)^(n-1)cos(ax)+((n-1)/n)*intgeral(sin(ax)^(n-2) dx)
					replacer2[0].replace(replacer2[0].find(n,find),n.size(),simplify(n+"-2"));
					result[0]="(-1/"+simplify(a+"("+n+")")+")sin("+a+"x)^("+simplify(n+"-1")+")cos("+a+"x)+("+simplify(n+"-1")+"/"+n+")";
					result[1]=replacer2[0];
					return result;			
				}
				else if(searchstrfirst(replacer2[0],0)=="cos" && n!="1")
				{

					//intgeral(cos(ax)^(n) dx)=(1/a*n)cos(ax)^(n-1)sin(ax)+((n-1)/n)*intgeral(cos(ax)^(n-2) dx)
					replacer2[0].replace(replacer2[0].find(n,find),n.size(),simplify(n+"-2"));
					result[0]="(1/"+simplify(a+"("+n+")")+")cos("+a+"x)^("+simplify(n+"-1")+")sin("+a+"x)+("+simplify(n+"-1")+"/"+n+")";
					result[1]=replacer2[0];
					return result;
				}
				else if(searchstrfirst(replacer2[0],0)=="tan" && n!="1")
				{
					//intgeral(tan(ax)^(n) dx)=(1/a*(n-1))tan(ax)^(n-1)-intgeral(tan(ax)^(n-2) dx)
					replacer2[0].replace(replacer2[0].find(n,find),n.size(),simplify(n+"-2"));
					result[0]="(1/"+simplify(a+"("+simplify(n+"-1")+")")+")tan("+a+"x)^("+simplify(n+"-1")+")-";
					result[1]=replacer2[0];
					return result;		
				}
				else if(searchstrfirst(replacer2[0],0)=="csc" && (n!="2" || n!="1"))
				{
					//intgeral(csc(ax)^(n) dx)=(-1/a*(n-1))csc(ax)^(n-2)cot(ax)+((n-2)/(n-1))*intgeral(csc(ax)^(n-2) dx)
					replacer2[0].replace(replacer2[0].find(n,find),n.size(),simplify(n+"-2"));
					result[0]="(-1/"+simplify(a+"("+simplify(n+"-1")+")")+")csc("+a+"x)^("+simplify(n+"-2")+")cot("+a+"x)+("+simplify(n+"-2")+"/"+simplify(n+"-1")+")";
					result[1]=replacer2[0];
					return result;
				}
				else if(searchstrfirst(replacer2[0],0)=="sec" && (n!="2" || n!="1"))
				{
					//intgeral(sec(ax)^(n) dx)=(1/a*(n-1))sec(ax)^(n-2)tan(ax)+((n-2)/(n-1))*intgeral(sec(ax)^(n-2) dx)
					replacer2[0].replace(replacer2[0].find(n,find),n.size(),simplify(n+"-2"));
					result[0]="(1/"+simplify(a+"("+simplify(n+"-1")+")")+")sec("+a+"x)^("+simplify(n+"-2")+")tan("+a+"x)+("+simplify(n+"-2")+"/"+simplify(n+"-1")+")";
					result[1]=replacer2[0];
					return result;
				}
				else if(searchstrfirst(replacer2[0],0)=="cot" && n!="1")
				{
					//intgeral(cot(ax)^(n) dx)=(1/a*(n-1))cot(ax)^(n-1)-intgeral(cot(ax)^(n-2) dx)
					replacer2[0].replace(replacer2[0].find(n,find),n.size(),simplify(n+"-2"));
					result[0]="(-1/"+simplify(a+"("+simplify(n+"-1")+")")+")cot("+a+"x)^("+simplify(n+"-1")+")-";
					result[1]=replacer2[0];
					return result;
				}
				else if(searchstrfirst(replacer2[0],0)=="arcsin")
				{
					if(n=="1")
					{

					}
					else
					{
						//integral(arcsin(ax)^(n) dx)=xarcsin(ax)^(n)+(n/a)((1-a^(2)x^(2))^(1/2)arcsin(ax)^(n-1))-n(n-1)(integral(arcsin(ax)^(n-2))
						string keep=replacer2[0];//makes a copy of the function
						string nminusone=keep;//makes another copy of the function
						nminusone.replace(nminusone.find(n,find),n.size(),simplify(n+"-1"));//gets the function with power -1 so we can use it in the formula
						replacer2[0].replace(replacer2[0].find(n,find),n.size(),simplify(n+"-2"));//gets the function with power -2 so we can use it in the formula
						result[0]=coeff+"x"+keep+"+("+simplify("("+coeff+")"+"("+n+")")+"/"+a+")(1-"+"("+a+")("+a+")x^(2))^(1/2)"+nminusone+"-("+simplify("("+coeff+")("+n+")("+simplify(n+"-1")+")")+")";
						result[1]=replacer2[0];
						return result;//returns a vector of the written formula and the function with power -2, can't use i_getdata() here so we implement it in redform()
					}
				}
				else if(searchstrfirst(replacer2[0],0)=="arccos")
				{
					if(n=="1")
					{
						//integral(arcsin(ax)^(n) dx)=xarcsin(ax)^(n)+(n/a)((1-a^(2)x^(2))^(1/2)arcsin(ax)^(n-1))-n(n-1)(integral(arcsin(ax)^(n-2))
						result[0]=coeff+"x"+replacer2[0]+"-(coeff/"+simplify("(2)("+a+")")+")(ln(("+a+")("+a+")x^(2)))";
						result[1]="0";
						return result;//returns a vector of the written formula and the function with power -2, can't use i_getdata() here so we implement it in redform()
					}
					else
					{
						//integral(arccos(ax)^(n) dx)=xarccos(ax)^(n)+(n/a)((1-a^(2)x^(2))^(1/2)arccos(ax)^(n-1))-n(n-1)(integral(arcsin(ax)^(n-2))
						string keep=replacer2[0];//makes a copy of the function
						string nminusone=keep;//makes another copy of the function
						nminusone.replace(nminusone.find(n,find),n.size(),simplify(n+"-1"));//gets the function with power -1 so we can use it in the formula
						replacer2[0].replace(replacer2[0].find(n,find),n.size(),simplify(n+"-2"));//gets the function with power -2 so we can use it in the formula
						result[0]=coeff+"x"+keep+"-("+simplify("("+coeff+")"+"("+n+")")+"/"+a+")(1-"+"("+a+")("+a+")x^(2))^(1/2)"+nminusone+"-("+simplify("("+coeff+")("+n+")("+simplify(n+"-1")+")")+")";
						result[1]=replacer2[0];
						return result;//returns a vector of the written formula and the function with power -2, can't use i_getdata() here so we implement it in redform()
					}
				}
				else if(searchstrfirst(replacer2[0],0)=="arctan" && n=="1")
				{
					//integral(arctan(ax) dx)=xarctan(ax)-(1/2a)ln(a^(2)x^(2)-1)
					result[0]=coeff+"x"+replacer2[0]+"-("+coeff+"/"+simplify("(2)("+a+")")+")(ln(("+a+")("+a+")x^(2)+1))";
					result[1]="0";
					return result;//returns a vector of the written formula and makes result 0 so it doesnt return an integral
				}
				else if(searchstrfirst(replacer2[0],0)=="arccsc" && n=="1")
				{
					//integral(arccsc(ax) dx)=1/a (cosh^(-1)(ax)+ax csc^(-1)(ax))+constant
					//or xarccsc(ax)+((a^2-1/x^2)^(1/2)xln(ax+(-1+a^2x^2)^(1/2)))/(a(-1+a^2x^2)^(1/2))
					result[0]=coeff+"x"+replacer2[0]+"+("+coeff+"/"+a+")(("+a+")("+a+")-x^(-2))^(1/2)xln("+a+"x+(("+a+")("+a+")x^(2)-1)^(1/2))((("+a+")("+a+")x^(2)-1)^(-1/2))";
					result[1]="0";
					return result;//returns a vector of the written formula and makes result 0 so it doesnt return an integral
				}
				else if(searchstrfirst(replacer2[0],0)=="arcsec" && n=="1")
				{
					//integral(arcsec(ax) dx)=1/a (cosh^(-1)(ax)+ax sec^(-1)(ax))+constant
					//or xarcsec(ax)-((a^2-1/x^2)^(1/2)xln(ax+(-1+a^2x^2)^(1/2)))/(a(-1+a^2x^2)^(1/2))
					result[0]=coeff+"x"+replacer2[0]+"-("+coeff+"/"+a+")(("+a+")("+a+")-x^(-2))^(1/2)xln("+a+"x+(("+a+")("+a+")x^(2)-1)^(1/2))((("+a+")("+a+")x^(2)-1)^(-1/2))";
					result[1]="0";
					return result;//returns a vector of the written formula and makes result 0 so it doesnt return an integral
				}
				else if(searchstrfirst(replacer2[0],0)=="arccot" && n=="1")
				{
					//integral(arccot(ax) dx)=xarccot(ax)+(1/2a)ln(a^(2)x^(2)-1)
					result[0]=coeff+"x"+replacer2[0]+"+("+coeff+"/"+simplify("(2)("+a+")")+")(ln(("+a+")("+a+")x^(2)+1))";
					result[1]="0";
					return result;//returns a vector of the written formula and makes result 0 so it doesnt return an integral
				}
				else if(searchstrfirst(replacer2[0],0)=="ln")
				{
					if(n=="1")
					{
						//intgeral(ln(ax^(m))^(n) dx)=xln(ax^(m))^(n)-(m*n)*intgeral(ln(ax^(m))^(n-1) dx)
						result[0]=coeff+"x"+replacer2[0]+"-("+simplify("("+coeff+")"+"("+m+")"+"("+n+")")+")";
						result[1]="0";
						return result;//returns a vector of the written formula and the function with power -2, can't use i_getdata() here so we implement it in redform()
					}
					else
					{
						//intgeral(ln(ax^(m))^(n) dx)=xln(ax^(m))^(n)-(m*n)xln(ax^(m))^(n-1)-(m*n)(m(n-1))*intgeral(ln(ax^(m))^(n-1) dx)
						string keep=replacer2[0];//makes a copy of the function
						string nminusone=keep;//makes another copy of the function
						nminusone.replace(nminusone.find(n,find),n.size(),simplify(n+"-1"));//gets the function with power -1 so we can use it in the formula
						replacer2[0].replace(replacer2[0].find(n,find),n.size(),simplify(n+"-2"));//gets the function with power -2 so we can use it in the formula
						result[0]=coeff+"x"+keep+"-("+simplify("("+coeff+")"+"("+m+")"+"("+n+")")+")x"+nminusone+"-("+simplify("("+coeff+")("+m+")("+n+")(("+m+")("+n+"-1))")+")";
						result[1]=replacer2[0];
						return result;//returns a vector of the written formula and the function with power -2, can't use i_getdata() here so we implement it in redform()
					}
				}
				else if(searchstrfirst(replacer2[0],0)=="log")
				{

				}
				else if(searchstrfirst(replacer2[0],0)=="exp")
				{

				}
			}
	}
	else if(replacer2.size()==2)
	{
		if(searchstrfirst(replacer2[0],0)=="poly")
		{
			if(searchstrfirst(replacer2[1],0)=="sin")
			{
				
			}
			else if(searchstrfirst(replacer2[1],0)=="cos")
			{
				
			}
			else if(searchstrfirst(replacer2[1],0)=="arcsin")
			{
				
			}
			else if(searchstrfirst(replacer2[1],0)=="arccos")
			{
				
			}
			else if(searchstrfirst(replacer2[1],0)=="arctan")
			{
				
			}
			else if(searchstrfirst(replacer2[1],0)=="arccsc")
			{
				
			}
			else if(searchstrfirst(replacer2[1],0)=="arcsec")
			{
				
			}
			else if(searchstrfirst(replacer2[1],0)=="arccot")
			{
				
			}
			else if(searchstrfirst(replacer2[1],0)=="ln")
			{
				
			}
			else if(searchstrfirst(replacer2[1],0)=="log")
			{
				
			}
			else if(searchstrfirst(replacer2[1],0)=="exp")
			{
				
			}
		}
		if(searchstrfirst(replacer2[0],0)=="exp")
		{
			if(searchstrfirst(replacer2[1],0)=="sin")
			{
				
			}
			else if(searchstrfirst(replacer2[1],0)=="cos")
			{
				
			}
		}
		if(searchstrfirst(replacer2[0],0)=="sin")
		{
			if(searchstrfirst(replacer2[1],0)=="cos")
			{
				
			}
		}
		if(searchstrfirst(replacer2[0],0)=="csc")
		{
			if(searchstrfirst(replacer2[1],0)=="sec")
			{

			}
		}
	}
	return result;
}

