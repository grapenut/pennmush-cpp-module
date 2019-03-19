
#include "module.h"
#include "main.h"
#include "mush.h"

#include "modfunctions.h"
#include "modcommands.h"

// Module on startup routine
void MODULE_CLASS::Startup()
{
  MUSH.Notify(3, "Module '" MODULE_NAME "' started.");
  MUSH.Notify(3, "       version %f", this->version);
}

// Save module data before dumping the game database
void MODULE_CLASS::Dump()
{

}

// Called once per second by the MUSH
void MODULE_CLASS::Cycle()
{
  int n;
  string s = MUSH.GetAttribute(3, "CYCLE");
  
  if (s.empty()) {
    n = 0;
  } else {
    n = stoi(s);
  }
  n++;

  MUSH.SetAttribute(3, "CYCLE", to_string(n));
  
  //if (n % 10 == 0) {
  //  map<string, MUSHCommand>::iterator it = this->commands.begin();
  //  MUSH.Notify(3, "DEBUG: cmds: %s", it->first.c_str());
  //}
}

// Called before the MUSH shuts down
void MODULE_CLASS::Shutdown()
{

}

// Register all module commands
void MODULE_CLASS::LoadCommands()
{
  this->RegisterCommand(MODULE_NAME, MODULE_COMMAND(version));
}

// Register all module softcode functions
void MODULE_CLASS::LoadFunctions()
{
  this->RegisterFunction("MODVERSION", MODULE_SOFTCODE(version));
}






