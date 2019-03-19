#ifndef __MODULE_MAIN_H
#define __MODULE_MAIN_H

#include <map>
#include <string>

using namespace std;

#include "module.h"
#include "mush.h"


#define MODULE_SOFTCODE_PROTO(fun)	string MODULE_SOFTCODE(fun)(objid executor, objid enactor, objid caller, vector<string> args)
#define MODULE_SOFTCODE_CALL(fun,argv)	(*fun)(executor, enactor, caller, argv)
typedef string (*MUSHFunction)(objid, objid, objid, vector<string>);

#define MODULE_COMMAND_PROTO(cmd)	void MODULE_COMMAND(cmd)(objid executor, objid enactor, objid caller, map<string,string> args)
#define MODULE_COMMAND_CALL(cmd,argmap)	(*cmd)(executor, enactor, caller, argmap)
typedef void (*MUSHCommand)(objid, objid, objid, map<string, string>);

class MODULE_CLASS
{
private:
  double version = MODULE_VERSION;
  
  map<string, MUSHCommand> commands;
  map<string, MUSHFunction> functions;

public:

  void Startup();
  void Dump();
  void Cycle();
  void Shutdown();
  void LoadCommands();
  void LoadFunctions();
  
  string GetVersion();

  bool RegisterCommand(const char *name, MUSHCommand cmd, const char *switches = NULL, const char *flags = NULL, const char *powers = NULL, int ctype = 0);
  bool DeleteCommand(string name);
  MUSHCommand FindCommand(string name);
  
  bool RegisterFunction(const char *name, MUSHFunction fun, int minargs = 0, int maxargs = 0, int ftype = 0);
  bool DeleteFunction(string name);
  MUSHFunction FindFunction(string name);
};

extern MODULE_CLASS MODULE;

#endif //__MODULE_MAIN_H
