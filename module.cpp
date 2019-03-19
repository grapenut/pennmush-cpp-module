#include "main.h"

// The main module object
MODULE_CLASS MODULE;

// Return a string representation of the module name and version
string MODULE_CLASS::GetVersion()
{
  return string(MODULE_NAME " v") + to_string(MODULE_VERSION);
}

// Register a MUSH command
bool MODULE_CLASS::RegisterCommand(const char *name, MUSHCommand cmd, const char *switches, const char *flags, const char *powers, int ctype)
{
  if (!name || !*name || !cmd) {
    return false;
  }
  
  this->commands.insert(make_pair(name, cmd));
  MUSH.AddCommand(name, switches, flags, powers, ctype);
  
  return true;
}

// Delete a registered MUSH command
bool MODULE_CLASS::DeleteCommand(string name)
{
  if (!this->FindCommand(name)) {
    return false;
  }
  
  this->commands.erase(name);
  return true;
}

// Find a registered MUSH command
MUSHCommand MODULE_CLASS::FindCommand(string name)
{
  map<string, MUSHCommand>::iterator it = this->commands.find(name);
  
  if (it != this->commands.end()) {
    return it->second;
  }
  
  return NULL;
}

// Register a MUSH function
bool MODULE_CLASS::RegisterFunction(const char *name, MUSHFunction fun, int minargs, int maxargs, int ftype)
{
  if (!name || !*name || !fun) {
    return false;
  }
  
  if (maxargs < minargs) {
    maxargs = minargs;
  }
  
  this->functions.insert(make_pair(name, fun));
  MUSH.AddFunction(name, minargs, maxargs, ftype);

  return true;
}

// Delete a registered MUSH function
bool MODULE_CLASS::DeleteFunction(string name)
{
  if (!this->FindFunction(name)) {
    return false;
  }
  
  this->functions.erase(name);
  return true;
}

// Find a registered MUSH function
MUSHFunction MODULE_CLASS::FindFunction(string name)
{
  map<string, MUSHFunction>::iterator it = this->functions.find(name);
  
  if (it != this->functions.end()) {
    return it->second;
  }
  
  return NULL;
}



