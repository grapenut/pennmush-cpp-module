// External module interfaces that can be
// called from within PennMUSH code to access
// module objects and functions.
// Include with #include "<module>/externs.h"

#include "module.h"

#include "command.h"
#include "function.h"

// MUSH callbacks
void MODULE_FUNCTION(startup)(void);
void MODULE_FUNCTION(dump)(void);
void MODULE_FUNCTION(shutdown)(void);
void MODULE_FUNCTION(cycle)(void);

// Module version string
const char *MODULE_FUNCTION(version)(void);

// Load commands and functions
void MODULE_FUNCTION(load_commands)(void);
void MODULE_FUNCTION(load_functions)(void);

// Interface to module softcode functions
FUNCTION_PROTO(MODULE_FUNCTION(softcode_interface));

// Prototypes for @commands
COMMAND_PROTO(MODULE_FUNCTION(command_interface));

