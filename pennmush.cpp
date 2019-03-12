
#include "mush.h"

extern "C" {
/* pennmush headers */
#include "config.h"
//#include "conf.h"
//#include "flags.h"
//#include "externs.h"
//#include "match.h"
//#include "dbdefs.h"
//#include "ansi.h"
#include "attrib.h"
//#include "lock.h"
//#include "function.h"
//#include "command.h"
//#include "switches.h"
//#include "parse.h"
#include "notify.h"
//#include "strutil.h"

}


MUSHInterface MUSH;

void MUSHInterface::Notify(objid player, string msg)
{
  notify(player, msg.c_str());
}

string MUSHInterface::GetAttribute(objid thing, string name)
{
  ATTR *a;
  const char *val;
  
  a = atr_get(thing, name.c_str());
  if (!a) {
    return "";
  }
  
  val = atr_value(a);
  return string(val);
}

void MUSHInterface::SetAttribute(objid thing, string name, string value)
{

}




