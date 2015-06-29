mode(-1)
lines(0)

WITHOUT_AUTO_PUTLHSVAR = %t;
toolbox_title = "qptoolbox"


tbx_build_gateway(toolbox_title, ..
	[
	 "loadQpprob","loadProblem";
	],..
	[
	"sci_iofunc.hpp";
	"QuadNLP.hpp";
	"QuadNLP.cpp";
	"sci_ipopt.cpp";
	"sci_iofunc.cpp";
	],..
	get_absolute_file_path("builder.sce"), [], ["-lipopt"], ["-w -fpermissive -I/home/saikiran/Ipopt-3.12.3/include/coin -L/home/saikiran/Ipopt-3.12.3/lib -Wl,-rpath=/home/saikiran/Ipopt-3.12.3/lib -lipopt -lm -ldl"], [], "g++");


clear WITHOUT_AUTO_PUTLHSVAR toolbox_title LINKER_FLAGS;
