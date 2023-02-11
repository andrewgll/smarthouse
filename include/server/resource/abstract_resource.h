#ifndef SMARTHOUSE_INTERFACE_RESOURCE_ABSTRACT_RESOURCE_INCLUDED
#define SMARTHOUSE_INTERFACE_RESOURCE_ABSTRACT_RESOURCE_INCLUDED

#include <functional>
#include <unordered_map>

#include "Poco/JSON/Object.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/URI.h"
#include "server/db/db_service.h"

namespace interface {
namespace resource {

using namespace Poco::Net;

class AbstractResource : public HTTPRequestHandler {
 public:
  AbstractResource();
  AbstractResource(Poco::Path &);
  virtual ~AbstractResource() override;

  void handleRequest(HTTPServerRequest &, HTTPServerResponse &) override;

 protected:
  void logRequest(HTTPServerRequest &);

  virtual void handle_get(HTTPServerRequest &, HTTPServerResponse &);

  virtual void handle_put(HTTPServerRequest &, HTTPServerResponse &);

  virtual void handle_post(HTTPServerRequest &, HTTPServerResponse &);

  virtual void handle_delete(HTTPServerRequest &, HTTPServerResponse &);

  virtual void handle_options(HTTPServerRequest &, HTTPServerResponse &);

  std::string getUrl(const std::string &fragment);

  std::string getQueryParameter(const std::string &, bool = true);

 protected:
  std::unordered_map<std::string,
                     std::function<void(AbstractResource &, HTTPServerRequest &,
                                        HTTPServerResponse &)>>
      handler_map = {
          {HTTPRequest::HTTP_GET, &AbstractResource::handle_get},
          {HTTPRequest::HTTP_PUT, &AbstractResource::handle_put},
          {HTTPRequest::HTTP_POST, &AbstractResource::handle_post},
          {HTTPRequest::HTTP_DELETE, &AbstractResource::handle_delete},
          {HTTPRequest::HTTP_OPTIONS, &AbstractResource::handle_options}};
  // TODO remove this field and make static method to get DBService instance
  std::unique_ptr<db::DBService> dbService;

  std::string baseUrl;
  std::string requestURI;
  std::string requestHost;
  Poco::URI::QueryParameters queryStringParameters;
};

}  // namespace resource
}  // namespace interface

#endif
