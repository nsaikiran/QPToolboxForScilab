// Make sure that you have executed exec loader.sce before run this.

// Problem 1:
//	Ref : u.math.biu.ac.il/~krasnov/369/NLP.doc
//
//
//			 	  2							 2					  2
// 	min. (5/2)* x1  - 2*x1*x2 - x1 * x3 + 2*x2 + 3*x1*x2+(5/2) * x3 + 2*x1-35*x2-47*x3
//	No constraints
//

solveQpprob(3,0,[2.50,-2,-1;0,2,3;0,0,2.50],[2,-35,-47],[],[],[],[0,0,0],[2e19,2e19,2e19])

// Problem 2:
//			
//	Ref : example 14 :
// 
//		https://www.me.utexas.edu/~jensen/ORMM/supplements/methods/nlpmethod/S2_quadratic.pdf
//
//
//			 2		 2
// min. -8*x1 -16*x2 + x1 + 4* x2
// such that
//	x1 + x2 <= 5,
//	x1 <= 3,
//	x1 >= 0,
//	x2 >= 0
//	
// We load this problem as
solveQpprob(2,1,[1,0;0,4],[-8,-16],[1,1],[-2e19],[5],[0,0],[3,2e19])


//	Problem 3:
//	Ref :http://cvxopt.org/examples/tutorial/qp.html
//
//
//	min. 2*x1+x2+x1*x2+x1+x2
//	such that
//	x1+x2=1
//	x1>=0,x2>=0

solveQpprob(2,1,[2,1;0,1],[1,1],[1,1],[1],[1],[0,0],[2e19,2e19])

//	Problem 4:
//	Ref :

//			  2		 2
// min . 26*x1 + 5*x2 + 10*x1*x2 - 14*x1 - 4*x2
// such that
// 0.9 <= 3*x1+2*x2 <= 1.1
// x1>=0 , x2>=0

solveQpprob(2,1,[26,10;0,5],[-14,-4],[3,2],[0.9],[1.1],[0,0],[2e19,2e19])
