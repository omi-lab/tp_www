#ifndef tp_www_Request_h
#define tp_www_Request_h

#include "tp_www/Globals.h"

#include <iostream>
#include <vector>

namespace tp_www
{

//##################################################################################################
enum class RequestType
{
  GET,     //!< The GET method requests a representation of the specified resource. Requests using GET should only retrieve data.
  POST,    //!< The POST method is used to submit an entity to the specified resource, often causing a change in state or side effects on the server.
  HEAD,    //!< The HEAD method asks for a response identical to that of a GET request, but without the response body.
  PUT,     //!< The PUT method replaces all current representations of the target resource with the request payload.
  DELETE,  //!< The DELETE method deletes the specified resource.
  OPTIONS, //!< The OPTIONS method is used to describe the communication options for the target resource.
  CONNECT, //!< The CONNECT method establishes a tunnel to the server identified by the target resource.
  TRACE,   //!< The TRACE method performs a message loop-back test along the path to the target resource.
  PATCH    //!< The PATCH method is used to apply partial modifications to a resource.
};

//##################################################################################################
RequestType requestTypeFromString(const std::string& requestType);

//##################################################################################################
struct MultipartFormData
{
  std::unordered_map<std::string, std::string> headers;
  std::string data;
  std::string name;
  std::string filename;
  std::string contentType;
  std::string contentDisposition;
};

//##################################################################################################
class Request
{
  int m_httpStatus{0};

  std::ostream& m_out;
  std::ostream& m_err;
  const std::vector<std::string>& m_route;
  RequestType m_requestType;
  const std::string m_content;
  const std::unordered_map<std::string, std::string>& m_postParams;
  const std::unordered_map<std::string, std::string>& m_getParams;
  const std::unordered_map<std::string, MultipartFormData>& m_multipartFormData;
public:

  //################################################################################################
  Request(std::ostream& out,
          std::ostream& err,
          const std::vector<std::string>& route,
          RequestType requestType,
          const std::string& content,
          const std::unordered_map<std::string, std::string>& postParams,
          const std::unordered_map<std::string, std::string>& getParams,
          const std::unordered_map<std::string, MultipartFormData>& multipartFormData);

  //################################################################################################
  const std::vector<std::string>& route()const;

  //################################################################################################
  RequestType requestType()const;

  //################################################################################################
  //! The main body of the request
  const std::string& content()const;

  //################################################################################################
  const std::unordered_map<std::string, std::string>& postParams()const;

  //################################################################################################
  const std::unordered_map<std::string, std::string>& getParams()const;

  //################################################################################################
  const std::unordered_map<std::string, MultipartFormData>& multipartFormData()const;

  //################################################################################################
  //! Join the parts of the route after this part
  std::string subRoute(int routePart)const;

  //################################################################################################
  //! Extract a single part of the route
  std::string routePart(int routePart)const;

  //################################################################################################
  //! The route upto this routePart
  std::string routeBase(int routePart)const;

  //################################################################################################
  void sendHeader(int httpStatus, const char* contentType);

  //################################################################################################
  void sendBinary(int httpStatus, const char* contentType, const std::string& data);

  //################################################################################################
  int httpStatus() const;

  //################################################################################################
  std::ostream& out();

  //################################################################################################
  std::ostream& err();
};

}

#endif






