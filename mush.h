#ifndef __MUSH_H
#define __MUSH_H


#include <string>

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
  void Notify(objid player, string msg);
  
  string GetAttribute(objid thing, string name);
  void SetAttribute(objid thing, string name, string value);
};

extern MUSHInterface MUSH;


#endif //__MUSH_H

