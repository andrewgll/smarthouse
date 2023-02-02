#ifndef SmartHouse_Interface_Resource_Abstract_Resource_INCLUDED
#define SmartHouse_Interface_Resource_Abstract_Resource_INCLUDED
#include <memory>

#include "Poco/JSON/Object.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/URI.h"
#include "server/db/db_service.h"
#include "server/resource/utils/exception.h"

namespace interface {
namespace resource {

class AbstractResource : public Poco::Net::HTTPRequestHandler {
 public:
  AbstractResource();
  AbstractResource(Poco::Path &);
  virtual ~AbstractResource() override;

  void handleRequest(Poco::Net::HTTPServerRequest &,
                     Poco::Net::HTTPServerResponse &) override;

 protected:
  void logRequest(Poco::Net::HTTPServerRequest &);

  virtual void handle_get(Poco::Net::HTTPServerRequest &,
                          Poco::Net::HTTPServerResponse &);

  virtual void handle_put(Poco::Net::HTTPServerRequest &,
                          Poco::Net::HTTPServerResponse &);

  virtual void handle_post(Poco::Net::HTTPServerRequest &,
                           Poco::Net::HTTPServerResponse &);

  virtual void handle_delete(Poco::Net::HTTPServerRequest &,
                             Poco::Net::HTTPServerResponse &);

  virtual void handle_options(Poco::Net::HTTPServerRequest &,
                              Poco::Net::HTTPServerResponse &);

  /// It validates required information into the Http headers.
  virtual void handleHttpHeaders(Poco::Net::HTTPServerRequest &,
                                 Poco::Net::HTTPServerResponse &);

  /*!
   * @param fragment Part that it wishes to add to a URL.
   * @return A complete URL with a fragment added to its end.
   */
  std::string getUrl(const std::string &fragment);

  /*!
   * @param name The parameter name.
   * @return The parameter value.
   */
  std::string getQueryParameter(const std::string &, bool = true);

 protected:
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
