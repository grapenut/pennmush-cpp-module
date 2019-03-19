// MUSHInterface class implementation for PennMUSH servers
#include "module.h"
#ifdef PENNMUSH

#include <cstdarg>

#include "main.h"
#include "mush.h"

extern "C" {
/* pennmush headers */
#include "config.h"
//#include "conf.h"
//#include "flags.h"
//#include "externs.h"
//#include "match.h"
#include "dbdefs.h"
//#include "ansi.h"
#include "attrib.h"
//#include "lock.h"
//#include "function.h"
#include "command.h"
//#include "switches.h"
//#include "parse.h"
#include "notify.h"
//#include "strutil.h"

extern int mush_vsnprintf(char *, size_t, const char *, va_list);
extern int safe_str(const char *s, char *buff, char **bp);

#include "./externs.h"
}


MUSHInterface MUSH;


// Add a MUSH command
void MUSHInterface::AddCommand(const char *name, const char *switches, const char *flags, const char *powers, int ctype)
{
  //if (!MODULE.FindCommand(name)) {
  //  return;
  //}
  
  if (ctype == 0) {
    ctype = CMD_T_ANY;
  }
  
  command_add(name, ctype, flags, powers, switches, MODULE_FUNCTION(command_interface));
}


// Add a MUSH softcode function
void MUSHInterface::AddFunction(const char *name, int minargs, int maxargs, int ftype)
{
  //if (!MODULE.FindFunction(name)) {
  //  return;
  //}
  
  if (ftype == 0) {
    ftype = FN_REG;
  }
  
  function_add(name, MODULE_FUNCTION(softcode_interface), minargs, maxargs, ftype);
}


// Send message to player
//void MUSHInterface::Notify(objid player, string msg)
//{
//  notify(player, msg.c_str());
//}


// Send formatted message to player
void MUSHInterface::Notify(objid player, string fmt, ...)
{
  char buff[BUFFER_LEN];
  va_list args;

  va_start(args, fmt);
  mush_vsnprintf(buff, sizeof buff, fmt.c_str(), args);
  va_end(args);

  notify(player, buff);
}


// Add a string to a buffer
//void MUSHInterface::SafeString(char *buff, char **bp, char *msg)
//{
//  safe_str(msg, buff, bp);
//}


// Add formatted string to buffer
void MUSHInterface::SafeString(char *buff, char **bp, string fmt, ...)
{
  char sbuf[BUFFER_LEN];
  va_list args;

  va_start(args, fmt);
  mush_vsnprintf(sbuf, sizeof sbuf, fmt.c_str(), args);
  va_end(args);

  safe_str(sbuf, buff, bp);
}


// Get the object's type
int MUSHInterface::GetType(objid thing)
{
  return Type(thing);
}


// Get the object's name
string MUSHInterface::GetName(objid thing)
{
  return Name(thing);
}


// Check if the object is of a specific type
bool MUSHInterface::HasType(objid thing, int type)
{
  return (Type(thing) == type);
}


// Check if the object has a specific flag
bool MUSHInterface::HasFlag(objid thing, string name, int type = NOTYPE)
{
  return has_flag_by_name(thing, name.c_str(), type);
}


// Set a flag on an object
void MUSHInterface::SetFlag(objid thing, string name)
{
  set_flag(GOD, thing, name.c_str(), 0, 0, 0);
}


// Clear a flag from an object
void MUSHInterface::ClearFlag(objid thing, string name)
{
  set_flag(GOD, thing, name.c_str(), 1, 0, 0);
}


// Check if thing is in loc
bool MUSHInterface::HasContents(objid loc, objid thing)
{
  if (!RealGoodObject(loc) || !RealGoodObject(thing)) {
    return false;
  }
  
  return (loc == Location(thing));
}


// Return a list of the contents
vector<objid> MUSHInterface::ListContents(objid thing)
{
  vector<objid> list;
  objid id;
  
  if (!RealGoodObject(thing)) {
    return list;
  }
  
  id = Contents(thing);
  while (id != NOTHING) {
    list.push_back(id);
    id = Next(id);
  }
  
  return list;
}


// Return a vector of objids for the exits in a room
vector<objid> MUSHInterface::ListExits(objid room)
{
  vector<objid> list;
  objid exit;
  
  if (!RealGoodObject(room)) {
    return list;
  }
  
  if (!this->HasType(room, TYPE_ROOM)) {
    return list;
  }
  
  exit = Exits(room);
  while (exit != NOTHING) {
    list.push_back(exit);
    exit = Next(exit);
  }
  
  return list;
}


// Return the exits source room
objid MUSHInterface::GetSource(objid exit)
{
  if (!RealGoodObject(exit)) {
    return NOTHING;
  }
  
  if (!this->HasType(exit, TYPE_EXIT)) {
    return NOTHING;
  }
  
  return Source(exit);
}


// Return the exits destination room
objid MUSHInterface::GetDestination(objid exit)
{
  if (!RealGoodObject(exit)) {
    return NOTHING;
  }
  
  if (!this->HasType(exit, TYPE_EXIT)) {
    return NOTHING;
  }
  
  return Destination(exit);
}


// Return the things home
objid MUSHInterface::GetHome(objid thing)
{
  if (!RealGoodObject(thing)) {
    return NOTHING;
  }
  
  return Home(thing);
}


// Return the things home
objid MUSHInterface::GetLocation(objid thing)
{
  if (!RealGoodObject(thing)) {
    return NOTHING;
  }
  
  return Location(thing);
}


// Check if an attribute is present
bool MUSHInterface::HasAttribute(objid thing, string name)
{
  ATTR *a;
  
  a = atr_get(thing, name.c_str());
  if (!a) {
    return false;
  }
  
  return true;
}


// Get attribute value from thing
string MUSHInterface::GetAttribute(objid thing, string name)
{
  ATTR *a;
  const char *val;
  
  a = atr_get(thing, name.c_str());
  if (!a) {
    return "";
  }
  
  val = atr_value(a);
  return val;
}


// Set attribute on thing to value
void MUSHInterface::SetAttribute(objid thing, string name, string value)
{
  atr_add(thing, name.c_str(), value.c_str(), GOD, 0);
}


void MUSHInterface::ClearAttribute(objid thing, string name)
{

}

// Return a vector of objids for all objects with flag
vector<objid> MUSHInterface::ListObjectsByFlag(string flag, int type = NOTYPE)
{
  vector<objid> list;
  dbref obj;
  
  for (obj = 0; RealGoodObject(obj); obj++) {
    if (has_flag_by_name(obj, flag.c_str(), type)) {
      list.push_back(obj);
    }
  }
  
  return list;
}


#endif //PENNMUSH

