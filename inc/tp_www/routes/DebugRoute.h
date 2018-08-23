#ifndef tp_www_DebugRoute_h
#define tp_www_DebugRoute_h

#include "tp_www/Route.h"

namespace tp_www
{

//##################################################################################################
class DebugRoute: public Route
{
public:

  //################################################################################################
  DebugRoute(const std::string& name);

  //################################################################################################
  bool handleRequest(Request& request, int routePart) override;
};

}

#endif






