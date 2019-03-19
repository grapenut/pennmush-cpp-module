
#include "module.h"
#include "main.h"
#include "mush.h"

extern "C" {
#include "./externs.h"
#include "parse.h"
#include "command.h"
}

// initialize module
void MODULE_FUNCTION(startup)(void)
{
  MODULE.Startup();
}

// save module to database
void MODULE_FUNCTION(dump)(void)
{
  MODULE.Dump();
}

// shutdown module
void MODULE_FUNCTION(shutdown)(void)
{
  MODULE.Shutdown();
}

// module heartbeat
void MODULE_FUNCTION(cycle)(void)
{
  MODULE.Cycle();
}

// add player commands
void MODULE_FUNCTION(load_commands)(void)
{
  MODULE.LoadCommands();
}

// add softcode functions
void MODULE_FUNCTION(load_functions)(void)
{
  MODULE.LoadFunctions();
}

// common interface for all softcode functions
FUNCTION(MODULE_FUNCTION(softcode_interface))
{
  string val;
  vector<string> argv;
  MUSHFunction f = MODULE.FindFunction(called_as);
  
  if (!f) {
    MUSH.SafeString(buff, bp, "#-1 Function not registered.");
    return;
  }
  
  // store the arguments in a vector<string>
  for (int i = 0; i < nargs; ++i) {
    argv.push_back(args[i]);
  }
  
  // execute the function
  val = MODULE_SOFTCODE_CALL(f, argv);
  
  // copy the results into the return buffer
  MUSH.SafeString(buff, bp, val);
  return;
}

#define cstring(str)	(str != NULL ? str : "")

// common interface for all commands
COMMAND(MODULE_FUNCTION(command_interface))
{
  map<string,string> argmap;
  map<string,string>::iterator it;
  MUSHCommand c = MODULE.FindCommand(cmd->name);
  
  if (!c) {
    MUSH.Notify(executor, "Command '%s' disabled.", cmd->name);
    return;
  }
  
  MUSH.Notify(3, "DEBUG: SWITCHES = %s", switches);
  MUSH.Notify(3, "DEBUG: ARGS_RAW = %s", args_raw);
  MUSH.Notify(3, "DEBUG: ARG_LEFT = %s", arg_left);
  MUSH.Notify(3, "DEBUG: ARG_RIGHT = %s", arg_right);
  

  argmap.insert(make_pair("switches", cstring(switches)));
  argmap.insert(make_pair("args_raw", cstring(args_raw)));
  argmap.insert(make_pair("arg_left", cstring(arg_left)));
  argmap.insert(make_pair("arg_right", cstring(arg_right)));
  
  for (it = argmap.begin(); it != argmap.end(); ++it)
  {
    MUSH.Notify(3, "DEBUG: %s = %s", it->first.c_str(), it->second.c_str());
  }
  
  // call the command function
  MODULE_COMMAND_CALL(c, argmap);
  return;
}




