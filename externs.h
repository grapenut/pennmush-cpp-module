// External module interfaces that can be
// called from within PennMUSH code to access
// module objects and functions.
// Include with #include "<module>/externs.h"

#include "module.h"

void MODULE_FUN(init)(void);
void MODULE_FUN(dump)(void);
void MODULE_FUN(halt)(void);
void MODULE_FUN(cycle)(void);

