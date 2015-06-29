//Made by Keyur Joshi
//Using cpp_example template provided with IPOPT

#include "QuadNLP.hpp"

using namespace Ipopt;

QuadNLP::~QuadNLP()
{}

//get NLP info such as number of variables and constraints
bool QuadNLP::get_nlp_info(Index& n, Index& m, Index& nnz_jac_g, Index& nnz_h_lag, IndexStyleEnum& index_style)
{
	n=numVars;
	m=numConstr;
	nnz_jac_g=n*m;
	/*TODO*/ //nnz_h_lag=;
	index_style=FORTRAN_STYLE;
	return true;
}

//get variable and constraint bound info
bool get_bounds_info(Index n, Number* x_l, Number* x_u, Index m, Number* g_l, Number* g_u)
{
	unsigned int i;
	for(i=0;i<n;i++)
	{
		x_l[i]=varLB[i];
		x_u[i]=varUB[i];
	}
	for(i=0;i<m;i++)
	{
		g_l[i]=conLB[i];
		g_u[i]=conUB[i];
	}
}

//get value of objective function at vector x
bool QuadNLP::eval_f(Index n, const Number* x, bool new_x, Number& obj_value)
{
	unsigned int i,j;
	Number temp;
	obj_value=0;
	for(i=0;i<n;i++)
	{
		//temp will contain product of x and ith column of qMatrix
		temp=0;
		for(j=0;j<n;j++)
			temp+=x[j]*qMatrix[n*j+i];
		//multiply temp/2 (as per definition) and linear component to x and add to objective value
		obj_value+=((temp/2)+lMatrix[i])*x[i];
	}
	return true;
}

//get value of gradient of objective function at vector x
bool QuadNLP::eval_grad_f(Index n, const Number* x, bool new_x, Number* grad_f)
{
	unsigned int i,j;
	for(i=0;i<n;i++)
	{
		grad_f[i]=lMatrix[i];
		for(j=0;j<n;j++)
			grad_f[i]+=(qMatrix[n*i+j]+qMatrix[n*j+i])*x[j];
	}
	return true;
}

bool QuadNLP::eval_g(Index n, const Number* x, bool new_x, Index m, Number* g)
{
	unsigned int i,j;
	for(i=0;i<m;i++)
	{
		g[i]=0;
		for(j=0;j<n;j++)
			g[i]+=x[j]*cMatrix[n*i+j];
	}
	return true;
}
