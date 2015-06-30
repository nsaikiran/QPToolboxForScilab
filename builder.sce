// Quadratic Programming Toolbox for Scailab.
// Authors ::
//			Sai Kiran
//			Keyur Joshi
//			Iswarya


// Location of header files of IPOPT
INCLUDE_PATH = "/home/saikiran/Ipopt-3.12.3/include/coin"
// Location of libraries
LIBRARIES_PATH = "/home/saikiran/Ipopt-3.12.3/lib"
//g++ compiler (you can specify the version)
gpp = "g++"


mode(-1)
lines(0)

WITHOUT_AUTO_PUTLHSVAR = %t;
toolbox_title = "qptoolbox"


tbx_build_gateway(toolbox_title, ..
	[
	 "solveQpprob","loadProblem";
	],..
	[
	"sci_iofunc.hpp";
	"QuadNLP.hpp";
	"QuadNLP.cpp";
	"sci_ipopt.cpp";
	"sci_iofunc.cpp";
	],..
	get_absolute_file_path("builder.sce"), [], ["-lipopt"], ["-w -fpermissive -I"+INCLUDE_PATH+" -L"+LIBRARIES_PATH+" -Wl,-rpath="+LIBRARIES_PATH+" -lipopt"], [], gpp);


clear WITHOUT_AUTO_PUTLHSVAR toolbox_title INCLUDE_PATH LIBRARIES_PATH gpp;


