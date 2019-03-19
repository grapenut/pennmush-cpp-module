
#include "_module.h"

// Main module class
#define MODULE_CLASS__(mod)		module_ ## mod
#define MODULE_CLASS_(mod)		MODULE_CLASS__(mod)
#define MODULE_CLASS			MODULE_CLASS_(MODULE)

// String version of the module name
#define MODULE_NAME__(mod)		#mod
#define MODULE_NAME_(mod)		MODULE_NAME__(mod)
#define MODULE_NAME			MODULE_NAME_(MODULE)

// Create token <module>_<fun>
#define MODULE_FUNCTION__(mod,fun)	mod ## _ ## fun
#define MODULE_FUNCTION_(mod,fun)	MODULE_FUNCTION__(mod,fun)
#define MODULE_FUNCTION(fun)		MODULE_FUNCTION_(MODULE,fun)

// Create token fun_<module>_<fun>
#define MODULE_SOFTCODE__(mod,fun)	fun_ ## mod ## _ ## fun
#define MODULE_SOFTCODE_(mod,fun)	MODULE_SOFTCODE__(mod,fun)
#define MODULE_SOFTCODE(fun)		MODULE_SOFTCODE_(MODULE,fun)

// Create token cmd_<module>_<cmd>
#define MODULE_COMMAND__(mod,cmd)	cmd_ ## mod ## _ ## cmd
#define MODULE_COMMAND_(mod,cmd)	MODULE_COMMAND__(mod,cmd)
#define MODULE_COMMAND(cmd)		MODULE_COMMAND_(MODULE,cmd)

// Some shortened aliases
#define MODCLASS			MODULE_CLASS
#define MODNAME				MODULE_NAME
#define MODFUN(fun)			MODULE_FUNCTION(fun)
#define MODSOFTCODE(fun)		MODULE_SOFTCODE(fun)
#define MODCOMMAND(cmd)			MODULE_COMMAND(cmd)

