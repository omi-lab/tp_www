#ifndef tp_www_Route_h
#define tp_www_Route_h

#include "tp_www/Globals.h"

namespace tp_www
{
class Request;

//##################################################################################################
class Route
{
public:

  //################################################################################################
  Route(const std::string& name);

  //################################################################################################
  virtual ~Route();

  //################################################################################################
  const std::string& name()const;

  //################################################################################################
  virtual bool handleRequest(Request& request, int routePart);

  //################################################################################################
  void addRoute(Route* route);

private:
  struct Private;
  Private* d;
  friend struct Private;
};

}

#endif






