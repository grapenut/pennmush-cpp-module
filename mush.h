#ifndef __MUSH_H
#define __MUSH_H


#include <string>
#include <vector>

using namespace std;

#include "module.h"


extern "C" {
#ifdef PENNMUSH
#include "mushtype.h"
#endif
}


// object id type
typedef dbref objid;

// MUSH Interface class
class MUSHInterface
{
public:
  //void Notify(objid player, string msg);
  void Notify(objid player, string fmt, ...);
  
  //void SafeString(char *buff, char **bp, string msg);
  void SafeString(char *buff, char **bp, string fmt, ...);
  
  string GetName(objid thing);
  
  int GetType(objid thing);
  bool HasType(objid thing, int type);
  
  bool HasFlag(objid thing, string name, int type);
  void SetFlag(objid thing, string name);
  void ClearFlag(objid thing, string name);
  
  bool HasContents(objid loc, objid thing);
  
  vector<objid> ListContents(objid thing);
  vector<objid> ListExits(objid room);
  
  objid GetSource(objid exit);
  objid GetDestination(objid exit);
  
  objid GetHome(objid thing);
  objid GetLocation(objid thing);
  
  bool HasAttribute(objid thing, string name);
  string GetAttribute(objid thing, string name);
  void SetAttribute(objid thing, string name, string value);
  void ClearAttribute(objid thing, string name);
  
  vector<objid> ListObjectsByFlag(string flag, int type);
  
  void AddCommand(const char *name, const char *switches, const char *flags, const char *powers, int ctype);
  void AddFunction(const char *name, int minargs, int maxargs, int ftype);
};

extern MUSHInterface MUSH;


#endif //__MUSH_H

