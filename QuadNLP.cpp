//Made by Keyur Joshi
//Using cpp_example template provided with IPOPT

#include "QuadNLP.hpp"

extern "C"{ 
#include <sciprint.h>
}
using namespace Ipopt;

QuadNLP::~QuadNLP()
{}

//get NLP info such as number of variables and constraints
bool QuadNLP::get_nlp_info(Index& n, Index& m, Index& nnz_jac_g, Index& nnz_h_lag, IndexStyleEnum& index_style)
{
	n=numVars;
	m=numConstr;
	nnz_jac_g = n*m;
	nnz_h_lag = n*(n+1)/2;
	index_style=C_STYLE;
	return true;
}

//get variable and constraint bound info
bool QuadNLP::get_bounds_info(Index n, Number* x_l, Number* x_u, Index m, Number* g_l, Number* g_u)
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
	return true;
}

//get value of objective function at vector x
bool QuadNLP::eval_f(Index n, const Number* x, bool new_x, Number& obj_value)
{
	unsigned int i,j;
	Number temp;
	obj_value=0;

	for (i=0;i<n;++i){
		for (j=0;j<n;++j){
			obj_value+=x[i]*x[j]*qMatrix[n*i+j];			
			}
		obj_value+=x[i]*lMatrix[i];
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
			g[i]+=x[j]*conMatrix[n*i+j];
	}
	return true;
}
bool QuadNLP::get_starting_point(Index n, bool init_x, Number* x,
										bool init_z, Number* z_L, Number* z_U,
										Index m, bool init_lambda,
										Number* lambda){

	for (int var=0;var<n;++var)
		x[var]=0.0;
	return true;
	}
bool QuadNLP::eval_jac_g(Index n, const Number* x, bool new_x,
								Index m, Index nele_jac, Index* iRow, Index *jCol,
								Number* values){
	if (values==NULL){ //Structure of jacobian (full structure)
		int index=0;
		for (int var=0;var<m;++var)//no. of constraints
			for (int flag=0;flag<n;++flag){//no. of variables
				iRow[index]=var;
				jCol[index]=flag;
				index++;
				}
		}
	else {
		int index=0;
		for (int var=0;var<m;++var)
			for (int flag=0;flag<n;++flag)
				values[index++]=conMatrix[n*var+flag];
		}
	return true;
	}

bool QuadNLP::eval_h(Index n, const Number* x, bool new_x,
							Number obj_factor, Index m, const Number* lambda,
							bool new_lambda, Index nele_hess, Index* iRow,
							Index* jCol, Number* values){
	if (values==NULL){
		Index idx=0;
		for (Index row = 0; row < n; row++) {
			for (Index col = 0; col <= row; col++) {
				iRow[idx] = row;
				jCol[idx] = col;
				idx++;
		  		}
			}
		}
	else {
		Index index=0;
		for (Index row=0;row < n;++row){
			for (Index col=0; col <= row; ++col){
				values[index++]=obj_factor*(qMatrix[n*row+col]+qMatrix[n*col+row]);
				}
			}
		}
	return true;
	}

void QuadNLP::finalize_solution(SolverReturn status,
									   Index n, const Number* x, const Number* z_L, const Number* z_U,
									   Index m, const Number* g, const Number* lambda, Number obj_value,
									   const IpoptData* ip_data,
									   IpoptCalculatedQuantities* ip_cq){

	sciprint("\nSolved::\n");
	for (int var=0;var<n;++var)sciprint("%f\n",x[var]);
	}

