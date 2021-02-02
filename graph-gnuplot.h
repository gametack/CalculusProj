#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

#pragma comment(lib, "SHELL32.LIB")

using namespace std;


void graph_gnuplot(string x,string y);//Plots the function and it's derivative or integral on a graph and outputs as picture.
void gnuplotinteractive(string x,double xfrom, double xto);
void gnuplotsurfofrevolX_axis(string x, double revolve, double xfrom, double xto, double yfrom, double yto);
void gnuplotsurfofrevolY_axis(string x, double revolve, double xfrom, double xto, double yfrom, double yto);
void gnuplotrangeset(string x,double xfrom, double xto, double yfrom, double yto);
void gnuplotareaundercurve(string x, double xfrom, double xto);
void gnuplotareabetweencurves(string x, string y, double xfrom, double xto);


void graph_gnuplot(string x)//Plots the function and it's derivative or integral on a graph and outputs as picture.
{
	string newx;
	x=simplify(x);
	newx=rewritefunction(x);

	string newy;
    newy=rewritefunction(x);
	graphout<<newx<<"   "<<newy<<endl;;
	for(int i=0; i<2; i++)
	{
		string filename;

		if(i==0)
		{
			filename="graphs\\func";filename.append(".png");
		}
		if(i==1)
		{
            filename="graphs\\func1";filename.append(".png");
		}

		ofstream fout;//test.txt will have information for graphing

		if(i==0)
		{
			fout.open("test0.txt");
		}
		if(i==1)
		{
			fout.open("test1.txt");
		}

		fout<<"set term pngcairo enhanced size 300,260"<<endl;
		fout<<"set output '"<<filename<<"'"<<endl;//outputs to png image file
		fout<<"set border linewidth 1.5"<<endl;
		fout<<"set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2"<<endl;
        fout<<"set style line 2 linecolor rgb '#dd181f' linetype 1 linewidth 2"<<endl;
        if(i==0)
        {
            fout<<"set xrange [-10:10]"<<endl;
        }
        if(i==1)
        {
            fout<<"set xrange [-50:50]"<<endl;
        }
        fout<<"set yrange [*:*]"<<endl;
        fout<<"set samples 500"<<endl;
		fout<<"set xzeroaxis linetype -1 linewidth 2"<<endl;
		fout<<"set yzeroaxis linetype -1 linewidth 2"<<endl;
		fout<<"set xtics axis"<<endl;
		//fout<<"set xtics ('-2{/Symbol p}' -2*pi, '-{/Symbol p}' -pi, 0, '{/Symbol p}' pi, \
		//		'2{/Symbol p}' 2*pi)"<<endl;
		fout<<"set ytics axis"<<endl;
		fout<<"set style data lines"<<endl;
		fout<<"set style fill solid 0.4"<<endl;
		fout<<"set grid"<<endl;
		fout<<"sec(x)=1/cos(x)"<<endl;
		fout<<"csc(x)=1/sin(x)"<<endl;
        fout<<"cot(x)= 1/tan(x)"<<endl;
        fout<<"acsc(x)=asin(1/x)"<<endl;
        fout<<"asec(x)=acos(1/x)"<<endl;
        fout<<"acot(x)=atan(1/x)"<<endl;
        if(i==0)
		{
            fout<<"plot "<<newx<<" with lines linestyle 1 notitle\""<<endl;
			ShellExecute(NULL, "open", "wgnuplot\\wgnuplot.exe", \
				"test0.txt", NULL, SW_SHOW); //gnuplot is needed for graph to plot
		}
		if(i==1)
		{
            fout<<"plot "<<newy<<" with lines linestyle 1 notitle\""<<endl;
			ShellExecute(NULL, "open", "wgnuplot\\wgnuplot.exe", \
				"test1.txt", NULL, SW_SHOW); //gnuplot is needed for graph to plot
		}
		fout<<"quit"<<endl;

	}

}

void gnuplotinteractive(string x,double xfrom, double xto)
{

	string newx;
	x=simplify(x);
	newx=rewritefunction(x);

	ifstream graphin("outputs/output.txt");
    string testfunc,integral,derivative;
    graphin>>testfunc>>derivative>>integral;
	ofstream fout;//test.txt will have information for graphing
	fout.open("test.txt");

    fout<<"set terminal canvas size 800,630 enhanced standalone mousing jsdir \"\""<<endl;
    fout<<"set output 'graphs\\interactive\\intergraph.html'"<<endl;
	fout<<"set border linewidth 1.5"<<endl;
	fout<<"set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2"<<endl;
	fout<<"set style line 2 linecolor rgb '#dd181f' linetype 1 linewidth 2"<<endl;
    fout<<"set style line 3 linecolor rgb '#1fdd18' linetype 1 linewidth 2"<<endl;

    fout<<"set xrange ["<<xfrom<<":"<<xto<<"]"<<endl;
	fout<<"set yrange [*:*]"<<endl;
	fout<<"set samples 500"<<endl;
	fout<<"set xzeroaxis linetype -1 linewidth 2"<<endl;
	fout<<"set yzeroaxis linetype -1 linewidth 2"<<endl;
    fout<<"set xtics axis"<<endl;
	//fout<<"set xtics ('-2{/Symbol p}' -2*pi, '-{/Symbol p}' -pi, 0, '{/Symbol p}' pi, \
	//		'2{/Symbol p}' 2*pi)"<<endl;
	fout<<"set ytics axis"<<endl;
	fout<<"set style data lines"<<endl;
	fout<<"set style fill solid 0.4"<<endl;
	fout<<"set grid"<<endl;
	fout<<"sec(x)=1/cos(x)"<<endl;
	fout<<"csc(x)=1/sin(x)"<<endl;
	fout<<"cot(x)= 1/tan(x)"<<endl;
	fout<<"acsc(x)=asin(1/x)"<<endl;
	fout<<"asec(x)=acos(1/x)"<<endl;
	fout<<"acot(x)=atan(1/x)"<<endl;
    if(x==integral)
	{
        fout<<"plot "<<newx<<" with lines linestyle 3 notitle\""<<endl;
	}
    else if(x==derivative)
	{
        fout<<"plot "<<newx<<" with lines linestyle 2 notitle\""<<endl;
	}
    else
    {
         fout<<"plot "<<newx<<" with lines linestyle 1 notitle\""<<endl;
    }
	fout<<"quit"<<endl;
	ShellExecute(NULL, "open", "wgnuplot\\wgnuplot.exe", \
		"test.txt", NULL, SW_SHOW); //gnuplot is needed for graph to plot

}

void gnuplotsurfofrevolX_axis(string x, double revolve, double xfrom, double xto, double yfrom, double yto)
{
	string newx;
	x=simplify(x);

	newx=rewritefunction(x);

	string newy=newx;
	newy.insert(0,"-(");
	newy.append(")+");
	string strrevolve = boost::lexical_cast<string>(revolve);
	newy.append(strrevolve);

	graphout<<newx<<"   "<<newy<<endl;;

	ifstream graphin("outputs/output.txt");
	string testfunc;
	graphin>>testfunc>>testfunc;
	ofstream fout;//test.txt will have information for graphing
	fout.open("test.txt");

	fout<<"set terminal canvas size 800,630 enhanced standalone mousing jsdir \"\""<<endl;
	fout<<"set output 'graphs\\interactive\\intergraph.html'"<<endl;
	fout<<"set border linewidth 1.5"<<endl;
	fout<<"set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2"<<endl;
	fout<<"set style line 2 linecolor rgb '#dd181f' linetype 1 linewidth 2"<<endl;
	fout<<"set style line 3 linecolor rgb '#00bb00' linetype 1 linewidth 2"<<endl;

	fout<<"set xrange ["<<xfrom<<":"<<xto<<"]"<<endl;
	fout<<"set yrange ["<<0-yto<<":"<<yto<<"]"<<endl;
	fout<<"set samples 500"<<endl;
	fout<<"set xzeroaxis linetype -1 linewidth 2"<<endl;
	fout<<"set yzeroaxis linetype -1 linewidth 2"<<endl;
	if(xfrom>=-10 || xto <=10)
	{
		fout<<"set xtics axis 1"<<endl;
	}
	//fout<<"set xtics ('-2{/Symbol p}' -2*pi, '-{/Symbol p}' -pi, 0, '{/Symbol p}' pi, \
	//		'2{/Symbol p}' 2*pi)"<<endl;
	fout<<"set ytics axis"<<endl;
	fout<<"set style data lines"<<endl;
	fout<<"set style fill solid 0.4"<<endl;
	fout<<"set grid"<<endl;
	fout<<"sec(x)=1/cos(x)"<<endl;
	fout<<"csc(x)=1/sin(x)"<<endl;
	fout<<"cot(x)= 1/tan(x)"<<endl;
	fout<<"acsc(x)=asin(1/x)"<<endl;
	fout<<"asec(x)=acos(1/x)"<<endl;
	fout<<"acot(x)=atan(1/x)"<<endl;
	fout<<"f(x)="<<newx<<endl;
	fout<<"g(x)="<<newy<<endl;
    fout<<"plot '+' using 1:(f($1)):(g($1)) with filledcurves closed linestyle 3 ti\"Revolved about y="<<strrevolve<<"\""<<endl;

	fout<<"quit"<<endl;
	ShellExecute(NULL, "open", "wgnuplot\\wgnuplot.exe", \
		"test.txt", NULL, SW_SHOW); //gnuplot is needed for graph to plot
}

void gnuplotsurfofrevolY_axis(string x, double revolve, double xfrom, double xto, double yfrom, double yto)
{
	string toreplace="(-x+"+ boost::lexical_cast<string>(revolve)+")";
	string newx;
	x=simplify(x);

	newx=rewritefunction(x);

	string newy=newx;
	for(int i=0; i<newy.size(); i++)
	{
		if(newy[i]=='x')
		{
			newy.replace(i,1,toreplace);
		}
		i+=3;
	}
	newy.insert(0,"-(");
	newy.append(")+");
	string strrevolve = boost::lexical_cast<string>(revolve);
	newy.append(strrevolve);

	graphout<<newx<<"   "<<newy<<endl;;

	ifstream graphin("outputs/output.txt");
	string testfunc;
	graphin>>testfunc>>testfunc;
	ofstream fout;//test.txt will have information for graphing
	fout.open("test.txt");

	fout<<"set terminal canvas size 800,630 enhanced standalone mousing jsdir \"\""<<endl;
	fout<<"set output 'graphs\\interactive\\intergraph.html'"<<endl;
	fout<<"set border linewidth 1.5"<<endl;
	fout<<"set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2"<<endl;
	fout<<"set style line 2 linecolor rgb '#dd181f' linetype 1 linewidth 2"<<endl;
	fout<<"set style line 3 linecolor rgb '#00bb00' linetype 1 linewidth 2"<<endl;

	fout<<"set xrange ["<<0-xto<<":"<<xto<<"]"<<endl;
	fout<<"set yrange ["<<yfrom<<":"<<yto<<"]"<<endl;
	fout<<"set samples 500"<<endl;
	fout<<"set xzeroaxis linetype -1 linewidth 2"<<endl;
	fout<<"set yzeroaxis linetype -1 linewidth 2"<<endl;
	if(xto <=10)
	{
		fout<<"set xtics axis 1"<<endl;
	}
	//fout<<"set xtics ('-2{/Symbol p}' -2*pi, '-{/Symbol p}' -pi, 0, '{/Symbol p}' pi, \
	//		'2{/Symbol p}' 2*pi)"<<endl;
	fout<<"set ytics axis"<<endl;
	fout<<"set style data lines"<<endl;
	fout<<"set style fill solid 0.4"<<endl;
	fout<<"set grid"<<endl;
	fout<<"sec(x)=1/cos(x)"<<endl;
	fout<<"csc(x)=1/sin(x)"<<endl;
	fout<<"cot(x)= 1/tan(x)"<<endl;
	fout<<"acsc(x)=asin(1/x)"<<endl;
	fout<<"asec(x)=acos(1/x)"<<endl;
	fout<<"acot(x)=atan(1/x)"<<endl;
	fout<<"f(x)="<<newx<<endl;
	fout<<"g(x)="<<newy<<endl;
    fout<<"plot '+' using 1:(f($1)):(g($1)) with filledcurves closed linestyle 3 ti\"Revolved about x="<<strrevolve<<"\""<<endl;

	fout<<"quit"<<endl;
	ShellExecute(NULL, "open", "wgnuplot\\wgnuplot.exe", \
		"test.txt", NULL, SW_SHOW); //gnuplot is needed for graph to plot
}

void gnuplotrangeset(string x,double xfrom, double xto, double yfrom, double yto)
{

	string newx;
	x=simplify(x);
	newx=rewritefunction(x);

	ifstream graphin("outputs/output.txt");
	string testfunc;
	graphin>>testfunc>>testfunc;
	ofstream fout;//test.txt will have information for graphing
	fout.open("test.txt");

	fout<<"set terminal canvas size 800,630 enhanced standalone mousing jsdir \"\""<<endl;
	fout<<"set output 'graphs\\interactive\\intergraph.html'"<<endl;
	fout<<"set border linewidth 1.5"<<endl;
	fout<<"set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2"<<endl;
	fout<<"set style line 2 linecolor rgb '#dd181f' linetype 1 linewidth 2"<<endl;
	fout<<"set xrange ["<<xfrom<<":"<<xto<<"]"<<endl;
	fout<<"set yrange ["<<yfrom<<":"<<yto<<"]"<<endl;
	fout<<"set samples 500"<<endl;
	fout<<"set xzeroaxis linetype -1 linewidth 2"<<endl;
	fout<<"set yzeroaxis linetype -1 linewidth 2"<<endl;
	if(xfrom>=-10 || xto <=10)
	{
		fout<<"set xtics axis 1"<<endl;
	}
	else
	{
		fout<<"set xtics axis"<<endl;
	}
	//fout<<"set xtics ('-2{/Symbol p}' -2*pi, '-{/Symbol p}' -pi, 0, '{/Symbol p}' pi, \
	//		'2{/Symbol p}' 2*pi)"<<endl;
	fout<<"set ytics axis"<<endl;
	fout<<"set style data lines"<<endl;
	fout<<"set style fill solid 0.4"<<endl;
	fout<<"set grid"<<endl;
	fout<<"sec(x)=1/cos(x)"<<endl;
	fout<<"csc(x)=1/sin(x)"<<endl;
	fout<<"cot(x)= 1/tan(x)"<<endl;
	fout<<"acsc(x)=asin(1/x)"<<endl;
	fout<<"asec(x)=acos(1/x)"<<endl;
	fout<<"acot(x)=atan(1/x)"<<endl;
	if(x==testfunc)
	{
		fout<<"plot "<<newx<<" with lines linestyle 2 ti\"y="<<x<<"\""<<endl;
	}
	else
	{
		fout<<"plot "<<newx<<" with lines linestyle 1 ti\"y="<<x<<"\""<<endl;
	}
	fout<<"quit"<<endl;
	ShellExecute(NULL, "open", "wgnuplot\\wgnuplot.exe", \
		"test.txt", NULL, SW_SHOW); //gnuplot is needed for graph to plot

}

void gnuplotareaundercurve(string x, double xfrom, double xto)
{
	string newx;
	x=simplify(x);
	newx=rewritefunction(x);

	ifstream graphin("outputs/output.txt");
	string testfunc;
	graphin>>testfunc>>testfunc;
	ofstream fout;//test.txt will have information for graphing
	fout.open("test.txt");

	fout<<"set terminal canvas size 800,630 enhanced standalone mousing jsdir \"\""<<endl;
	fout<<"set output 'graphs\\interactive\\intergraph.html'"<<endl;
	fout<<"set border linewidth 1.5"<<endl;
	fout<<"set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2"<<endl;
	fout<<"set style line 2 linecolor rgb '#dd181f' linetype 1 linewidth 2"<<endl;

	fout<<"set xrange ["<<xfrom<<":"<<xto<<"]"<<endl;
	fout<<"set yrange [*:*]"<<endl;
	fout<<"set samples 500"<<endl;
	fout<<"set xzeroaxis linetype -1 linewidth 2"<<endl;
	fout<<"set yzeroaxis linetype -1 linewidth 2"<<endl;
	if(xfrom>=-10 || xto <=10)
	{
		fout<<"set xtics axis 1"<<endl;
	}
	//fout<<"set xtics ('-2{/Symbol p}' -2*pi, '-{/Symbol p}' -pi, 0, '{/Symbol p}' pi, \
	//		'2{/Symbol p}' 2*pi)"<<endl;
	fout<<"set ytics axis"<<endl;
	fout<<"set style data lines"<<endl;
	fout<<"set style fill solid 0.4"<<endl;
	fout<<"set grid"<<endl;
	fout<<"sec(x)=1/cos(x)"<<endl;
	fout<<"csc(x)=1/sin(x)"<<endl;
	fout<<"cot(x)= 1/tan(x)"<<endl;
	fout<<"acsc(x)=asin(1/x)"<<endl;
	fout<<"asec(x)=acos(1/x)"<<endl;
	fout<<"acot(x)=atan(1/x)"<<endl;
	if(x==testfunc)
	{
        fout<<"plot "<<newx<<" with filledcurves y1=0 linestyle 2 notitle\""<<endl;
	}
	else
	{
        fout<<"plot "<<newx<<" with filledcurves y1=0 linestyle 1 notitle\""<<endl;
	}
	fout<<"quit"<<endl;
	ShellExecute(NULL, "open", "wgnuplot\\wgnuplot.exe", \
		"test.txt", NULL, SW_SHOW); //gnuplot is needed for graph to plot
}

void gnuplotareabetweencurves(string x, string y, double xfrom, double xto)
{
	string newx;
	x=simplify(x);
	newx=rewritefunction(x);

	string newy;
	newy=rewritefunction(y);
	graphout<<newx<<"   "<<newy<<endl;;

	ifstream graphin("outputs/output.txt");
	string testfunc;
	graphin>>testfunc>>testfunc;
	ofstream fout;//test.txt will have information for graphing
	fout.open("test.txt");

	fout<<"set terminal canvas size 800,630 enhanced standalone mousing jsdir \"\""<<endl;
	fout<<"set output 'graphs\\interactive\\intergraph.html'"<<endl;
	fout<<"set border linewidth 1.5"<<endl;
	fout<<"set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2"<<endl;
	fout<<"set style line 2 linecolor rgb '#dd181f' linetype 1 linewidth 2"<<endl;
	fout<<"set style line 3 linecolor rgb '#00bb00' linetype 1 linewidth 2"<<endl;

	fout<<"set xrange ["<<xfrom<<":"<<xto<<"]"<<endl;
	fout<<"set yrange [*:*]"<<endl;
	fout<<"set samples 500"<<endl;
	fout<<"set xzeroaxis linetype -1 linewidth 2"<<endl;
	fout<<"set yzeroaxis linetype -1 linewidth 2"<<endl;
	if(xfrom>=-10 || xto <=10)
	{
		fout<<"set xtics axis 1"<<endl;
	}
	//fout<<"set xtics ('-2{/Symbol p}' -2*pi, '-{/Symbol p}' -pi, 0, '{/Symbol p}' pi, \
	//		'2{/Symbol p}' 2*pi)"<<endl;
	fout<<"set ytics axis"<<endl;
	fout<<"set style data lines"<<endl;
	fout<<"set style fill solid 0.4"<<endl;
	fout<<"set grid"<<endl;
	fout<<"sec(x)=1/cos(x)"<<endl;
	fout<<"csc(x)=1/sin(x)"<<endl;
	fout<<"cot(x)= 1/tan(x)"<<endl;
	fout<<"acsc(x)=asin(1/x)"<<endl;
	fout<<"asec(x)=acos(1/x)"<<endl;
	fout<<"acot(x)=atan(1/x)"<<endl;
	fout<<"f(x)="<<newx<<endl;
	fout<<"g(x)="<<newy<<endl;
    fout<<"plot '+' using 1:(f($1)):(g($1)) with filledcurves closed linestyle 3 notitle\""<<endl;

	fout<<"quit"<<endl;
	ShellExecute(NULL, "open", "wgnuplot\\wgnuplot.exe", \
		"test.txt", NULL, SW_SHOW); //gnuplot is needed for graph to plot
}
