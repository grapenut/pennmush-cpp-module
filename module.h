
#define MODULE mymod

#define MODULE_VERSION 0.1

#define PENNMUSH
//#define RHOSTMUSH
//#define TM3

#define MODULE_NAME__(mod) #mod
#define MODULE_NAME_(mod) MODULE_NAME__(mod)
#define MODULE_NAME MODULE_NAME_(MODULE)

#define MODULE_FUNCTION__(mod,fun) mod ##_## fun
#define MODULE_FUNCTION_(mod,fun) MODULE_FUNCTION__(mod,fun)
#define MODULE_FUNCTION(fun) MODULE_FUNCTION_(MODULE,fun)







