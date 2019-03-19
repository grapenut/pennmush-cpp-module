
#include "modcommands.h"

MODULE_COMMAND_PROTO(version)
{
  if (args["switches"].find("VERSION") != string::npos) {
    MUSH.Notify(executor, MODULE.GetVersion());
  } else {
    MUSH.Notify(executor, "SWITCHES : %s", args["switches"].c_str());
    MUSH.Notify(executor, "ARGS_RAW : %s", args["args_raw"].c_str());
    MUSH.Notify(executor, "ARG_LEFT : %s", args["arg_left"].c_str());
    MUSH.Notify(executor, "ARG_RIGHT: %s", args["arg_right"].c_str());
  }
}

