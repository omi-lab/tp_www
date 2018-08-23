#include "tp_www/routes/DebugRoute.h"
#include "tp_www/Request.h"

#include "tp_utils/DebugUtils.h"

namespace tp_www
{

//##################################################################################################
DebugRoute::DebugRoute(const std::string& name):
  Route(name)
{

}

//##################################################################################################
bool DebugRoute::handleRequest(Request& request, int routePart)
{
  TP_UNUSED(routePart);
  tpWarning() << "DebugRoute::handleRequest: " << tpGetMapValue(request.getParams(), "message");
  request.sendHeader(200, "text/plain");
  return true;
}

}
