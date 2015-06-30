# Quadratic Programming Toolbox For Scilab
 
 A toolbox that provides quadratic programming in Scilab through Ipopt library.
 
## To Install ::
1. Follow [these](http://www.coin-or.org/Ipopt/documentation/node10.html " IPOPT documentation") instructions provided in IPOPT [documentation](http://www.coin-or.org/Ipopt/documentation/ " IPOPT Home page") to download and install.
2. Clone this repository on your computer or download this repository in .zip format and extract it.
3. Note the *path* to header files & libraries of IPOPT.
    In my computer :
    *header files* can be found in `/home/saikiran/Ipopt-3.12.3/include/coin` 
    *Libraries* can be found in `/home/saikiran/Ipopt-3.12.3/lib`
4. Go to extracted folder (of this toolbox), open `builder.sce`.
5. Set values of `INCLUDE_PATH`,`LIBRARIES_PATH` and `gpp` properly using step **3**.
6. Open **Scilab** software.
7. Change `pwd` (present working directory) to *toolbox folder*.
8. Execute `exec builer.sce` in **Scilab**.
9. If you got any *errors* ,please make sure that you followed step **3** and **4**.
10. Execute `exec loader.sce` in **Scilab**.
11. If you got any *errors* ,please make sure that you followed step **3** and **4**.
12. If you successfully completed this far, your installation is successful.

## To Use ::
1. Whenever you want to use this *toolbox*.
2. Just go to toolbox directory and run `exec loader.sce`.(No need to run `exec builder.sce`)


## Help ::

