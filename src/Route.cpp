#include "tp_www/Route.h"
#include "tp_www/Request.h"

#include "tp_utils/DebugUtils.h"

#include <unordered_map>

namespace tp_www
{
//##################################################################################################
struct Route::Private
{
  const std::string name;
  std::unordered_map<std::string, Route*> routes;
  Route* starRoute{nullptr};

  //################################################################################################
  Private(const std::string& name_):
    name(name_)
  {

  }
};

//##################################################################################################
Route::Route(const std::string& name):
  d(new Private(name))
{

}

//##################################################################################################
Route::~Route()
{
  delete d;
}

//##################################################################################################
const std::string& Route::name()const
{
  return d->name;
}

//##################################################################################################
bool Route::handleRequest(Request& request, int routePart)
{
  bool dbg=false;
  const std::vector<std::string>& route = request.route();

  if(routePart<0 || routePart>=int(route.size()))
    return false;

  const std::string& name = route.at(size_t(routePart));
  Route* child = tpGetMapValue(d->routes, name, nullptr);

  if(dbg)
    tpWarning() << "Route::handleRequest name: " << name;

  if(child)
  {
    if(dbg)
      tpWarning() << "  call child: " << name;
    return child->handleRequest(request, routePart+1);
  }
  else if(d->starRoute)
  {
    if(dbg)
      tpWarning() << "  start route: " << name;
    return d->starRoute->handleRequest(request, routePart+1);
  }

  return false;
}

//##################################################################################################
void Route::addRoute(Route* route)
{
  if(d->routes.find(route->name()) != d->routes.end())
    tpWarning() << "Error! Route::addRoute Adding a route that already exists!";

  d->routes[route->name()] = route;
  if(route->name() == "*")
    d->starRoute = route;
}

}
