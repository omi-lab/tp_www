#include "tp_www/Request.h"

namespace tp_www
{

//##################################################################################################
RequestType requestTypeFromString(const std::string& requestType)
{
  if(requestType == "GET"    ) return RequestType::GET;
  if(requestType == "POST"   ) return RequestType::POST;
  if(requestType == "HEAD"   ) return RequestType::HEAD;
  if(requestType == "PUT"    ) return RequestType::PUT;
  if(requestType == "DELETE" ) return RequestType::DELETE;
  if(requestType == "OPTIONS") return RequestType::OPTIONS;
  if(requestType == "CONNECT") return RequestType::CONNECT;
  if(requestType == "TRACE"  ) return RequestType::TRACE;
  if(requestType == "PATCH"  ) return RequestType::PATCH;

  return RequestType::GET;
}

//##################################################################################################
Request::Request(std::ostream& out,
                 std::ostream& err,
                 const std::vector<std::string>& route,
                 RequestType requestType,
                 const std::unordered_map<std::string, std::string>& postParams,
                 const std::unordered_map<std::string, std::string>& getParams,
                 const std::unordered_map<std::string, MultipartFormData>& multipartFormData):
  m_out(out),
  m_err(err),
  m_route(route),
  m_requestType(requestType),
  m_postParams(postParams),
  m_getParams(getParams),
  m_multipartFormData(multipartFormData)
{

}

//##################################################################################################
const std::vector<std::string>& Request::route()const
{
  return m_route;
}

//##################################################################################################
RequestType Request::requestType()const
{
  return m_requestType;
}

//##################################################################################################
const std::unordered_map<std::string, std::string>& Request::postParams()const
{
  return m_postParams;
}

//##################################################################################################
const std::unordered_map<std::string, std::string>& Request::getParams()const
{
  return m_getParams;
}

//##################################################################################################
const std::unordered_map<std::string, MultipartFormData>& Request::multipartFormData()const
{
  return m_multipartFormData;
}

//##################################################################################################
std::string Request::subRoute(int routePart)const
{
  std::string result;
  size_t iMax = m_route.size();
  for(size_t i=size_t(tpMax(0, routePart)); i<iMax; i++)
    result += "/" + m_route.at(i);
  return result;
}

//##################################################################################################
std::string Request::routePart(int routePart)const
{
  return (routePart>=0 && routePart<int(m_route.size()))?m_route.at(size_t(routePart)):std::string();
}

//##################################################################################################
std::string Request::routeBase(int routePart)const
{
  std::string result;
  int iMax = tpMin(int(m_route.size()), routePart);
  for(int i=0; i<iMax; i++)
    result += "/" + m_route.at(size_t(i));
  return result;
}

//##################################################################################################
void Request::sendHeader(int htmlStatus, const char* contentType)
{
  m_out << "Status: "
        << htmlStatus
        << "\r\n"
           "Content-type: "
        << contentType
        << "\r\n"
           "\r\n";
}


//################################################################################################
void Request::sendBinary(int htmlStatus, const char* contentType, const std::string& data)
{
  m_out << "Status: "
        << htmlStatus
        << "\r\n"
           "Content-type: "
        << contentType
        << "\r\n"
           "Content-Length: "
        << data.size()
        << "\r\n"
           "\r\n"
        << data;
}

//##################################################################################################
std::ostream& Request::out()
{
  return m_out;
}

//##################################################################################################
std::ostream& Request::err()
{
  return m_err;
}

}
