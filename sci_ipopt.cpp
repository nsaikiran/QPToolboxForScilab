#include "sci_iofunc.hpp"
#include "IpIpoptApplication.hpp"
#include "QuadNLP.hpp"
#include <iostream>

extern "C"{
#include <api_scilab.h>
#include <Scierror.h>
#include <BOOL.h>
#include <localization.h>
#include <sciprint.h>

bool readSparse(int arg,int *iRows,int *iCols,int *iNbItem,int** piNbItemRow, int** piColPos, double** pdblReal){
	SciErr sciErr;
	int* piAddr = NULL;
	int iType   = 0;
	int iRet    = 0;
	sciErr = getVarAddressFromPosition(pvApiCtx, arg, &piAddr);
	if(sciErr.iErr)	{
		printError(&sciErr, 0);
		return false;
		}
	sciprint("\ndone\n");
	if(isSparseType(pvApiCtx, piAddr)){
		sciprint("done\n");
		sciErr =getSparseMatrix(pvApiCtx, piAddr, iRows, iCols, iNbItem, piNbItemRow, piColPos, pdblReal);
		if(sciErr.iErr)	{
			printError(&sciErr, 0);
			return false;
			}
		}

	else {
		sciprint("\nSparse matrix required\n");
		return false;
		}
	return true;
	}

int loadProblem(char *fname,unsigned long len ){
	SciErr sciErr;
	int* piAddr = NULL;
	int iType   = 0;
	int iRet    = 0;
	CheckInputArgument(pvApiCtx, 9, 9);
	CheckOutputArgument(pvApiCtx, 1, 1);
	//bool status;
	/*int nQRows,nQCols,nQItems,*nQItemsPerRow=NULL,*QItemColPosition=NULL,
		*conMatrix=NULL,*conUB=NULL,*conLB=NULL,*varUB=NULL,*varLB=NULL;*/

	double *QItems=NULL,*PItems=NULL,*ConItems=NULL,*conUB=NULL,
			*conLB=NULL,*varUB=NULL,*varLB=NULL;
	int nVars,nCons;	
	//status=readSparse(1,&nQRows,&nQCols,&nQItems,&nQItemsPerRow,&QItemColPosition,&QItems);	
	getIntFromScilab(1,&nVars);
	getIntFromScilab(2,&nCons);
	
	QItems = new double[nVars*nVars];
	/*ConItems = new double[nCons*nVars];
	PItems = new double[nVars];
	conUB = new double[nCons];
	conLB = new double[nCons];
	varUB = new double[nVars];
	varLB = new double[nVars];*/

//	double *ConItems=NULL;
	int temp1,temp2;
	getDoubleMatrixFromScilab(3,&temp1,&temp2,&QItems);
	if (temp1 != nVars && temp2 != nVars){
		sciprint("Error:: Argument 3\n");
		returnDoubleToScilab(1.0);return 1;
		}
	getDoubleMatrixFromScilab(4,&temp1,&temp2,&PItems);
	if (temp2 != nVars){
		sciprint("Error:: Argument 4\n");
		returnDoubleToScilab(1.0);return 1;
		}
	getDoubleMatrixFromScilab(5,&temp1,&temp2,&ConItems);
	if (temp1 != nCons && temp2 != nCons){
		sciprint("Error:: Argument 5\n");
		returnDoubleToScilab(1.0);return 1;
		}
	getDoubleMatrixFromScilab(6,&temp1,&temp2,&conLB);
	if ( temp2 != nCons){
		sciprint("Error:: Argument 6\n");
		returnDoubleToScilab(1.0);return 1;
		}
	getDoubleMatrixFromScilab(7,&temp1,&temp2,&conUB);
	if ( temp2 != nCons){
		sciprint("Error:: Argument 7\n");
		returnDoubleToScilab(1.0);return 1;
		}
	getDoubleMatrixFromScilab(8,&temp1,&temp2,&varLB);
	if ( temp2 != nVars){
		sciprint("Error:: Argument 8\n");
		returnDoubleToScilab(1.0);return 1;
		}
	getDoubleMatrixFromScilab(9,&temp1,&temp2,&varUB);
	if ( temp2 != nVars){
		sciprint("Error:: Argument 9\n");
		returnDoubleToScilab(1.0);return 1;
		}
	
	for (int var=0;var < nVars;++var){
		sciprint("%f\n",ConItems[var]);
		}
		
	using namespace Ipopt;
	SmartPtr<TNLP> Prob = new QuadNLP(nVars,nCons,QItems,PItems,ConItems,conUB,conLB,varUB,varLB);

	SmartPtr<IpoptApplication> app = IpoptApplicationFactory();

  	app->RethrowNonIpoptException(true);

  // Change some options
  // Note: The following choices are only examples, they might not be
  //       suitable for your optimization problem.
  app->Options()->SetNumericValue("tol", 1e-7);
  app->Options()->SetStringValue("mu_strategy", "adaptive");
  app->Options()->SetStringValue("output_file", "ipopt.out");
  // The following overwrites the default name (ipopt.opt) of the
  // options file
  // app->Options()->SetStringValue("option_file_name", "hs071.opt");

  // Initialize the IpoptApplication and process the options
  ApplicationReturnStatus status;
  status = app->Initialize();
  if (status != Solve_Succeeded) {
    sciprint("*** Error during initialization!");
	return0toScilab();
    return (int) status;
  }

  // Ask Ipopt to solve the problem
  status = app->OptimizeTNLP(Prob);

  if (status == Solve_Succeeded) {
    sciprint("*** The problem solved!\n");
  }
  else {
    sciprint( "*** The problem FAILED!\n");
  }

  // As the SmartPtrs go out of scope, the reference count
  // will be decremented and the objects will automatically
  // be deleted.
	return0toScilab();
	}

}
