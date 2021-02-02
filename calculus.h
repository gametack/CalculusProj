//header files
#include "global-variables.h"
#include "search string.h"
#include "simplify.h"
#include "evaluate.h"
#include "finaloutput.h"
#include "derivative.h"
#include "integral.h"
#include "graph-gnuplot.h"


using namespace std;

string start(string function,string type)
{
    ofstream fout("outputs\\output.txt");

    string derivative,integral;

    derivativesteps.close();
    integralsteps.close();
    derivativesteps.open("Formatted_Output\\Outputs\\derivative\\Solution.html");
    derivativesteps<<"<!DOCTYPE html>"<<endl;
    derivativesteps<<"<html>"<<endl;
    derivativesteps<<"<head>"<<endl;
    derivativesteps<<"<script type=\"text/javascript\" src=\"../../MathJax.js?config=TeX-AMS-MML_SVG-full\"></script>"<<endl;
    derivativesteps<<"<style>html,body{width:100%;margin-left:0px;margin-top:-8px;}</style>"<<endl;
    derivativesteps<<"</head>"<<endl;
    derivativesteps<<"<body><p style=\"BACKGROUND-COLOR: #0099FF\"><b><u>"<<endl;
	derivativesteps<<"Solution to `"<<function<<"`:<br><br>"<<endl<<endl;

    integralsteps.open("Formatted_Output\\Outputs\\integral\\Solution.html");
	integralsteps<<"<!DOCTYPE html>"<<endl;
	integralsteps<<"<html>"<<endl;
	integralsteps<<"<head>"<<endl;
    integralsteps<<"<script type=\"text/javascript\" src=\"../../MathJax.js?config=TeX-AMS-MML_SVG-full\"></script>"<<endl;
	integralsteps<<"<style>html,body{width:100%;margin-left:0px;margin-top:-8px;}</style>"<<endl;
	integralsteps<<"</head>"<<endl;
	integralsteps<<"<body><p style=\"BACKGROUND-COLOR: #0099FF\"><b><u>"<<endl;
	integralsteps<<"Solution to `"<<function<<"`:<br><br>"<<endl<<endl;

	function=simplify(function);

	derivativesteps<<"`d/dx("<<convert2ascii(function)<<")`";
	derivative =getdata(function);

    integralsteps<<"`int"<<convert2ascii(function)<<"`";
   // integral=i_getdata(function);
    if(integral.empty())
    {
        integral="NonElementary_Function";
    }

	derivativesteps<<"<p style=\"BACKGROUND-COLOR: #0099FF\">";
	derivativesteps<<endl<<"Results:"<<endl<<"`d/dx("+convert2ascii(function)+") = "+convert2ascii(derivative)<<"`"<<endl;
	integralsteps<<"<p style=\"BACKGROUND-COLOR: #0099FF\">";
	//integralsteps<<endl<<"Results:"<<endl<<"`d/dx("+convert2ascii(function)+") = "+convert2ascii(integral)<<"`"<<endl;

	fout<<function<<" "<<derivative<<" "<<integral<<endl;

	derivativesteps<<"</u></b></p></body>"<<endl;
	derivativesteps<<"</html>";
	integralsteps<<"</u></b></p></body>"<<endl;
	integralsteps<<"</html>";

	graph_gnuplot(function);
	finaloutput(function,derivative,integral);

	derivativesteps.close();
	integralsteps.close();

	if(type=="derivative")
	{
		return derivative;
	}
	else if(type=="integral")
	{
		return integral;
	}
}
