#ifndef SmartHouse_Interface_Resource_Abstract_Resource_INCLUDED
#define SmartHouse_Interface_Resource_Abstract_Resource_INCLUDED

#include "Poco/JSON/Object.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/URI.h"

#include "server/resource/utils/exception.h"

namespace interface {
namespace resource {

class AbstractResource : public Poco::Net::HTTPRequestHandler {
 public:
  // Default User-defined Constructor
  AbstractResource();

  // Default Destructor
  ~AbstractResource() override;

  void handleRequest(Poco::Net::HTTPServerRequest &,
                     Poco::Net::HTTPServerResponse &) override;

 protected:
  /// It handles to Http verb GET.
  virtual void handle_get(Poco::Net::HTTPServerRequest &,
                          Poco::Net::HTTPServerResponse &);

  /// It handles to Http verb PUT.
  virtual void handle_put(Poco::Net::HTTPServerRequest &,
                          Poco::Net::HTTPServerResponse &);

  /// It handles to Http verb POST.
  virtual void handle_post(Poco::Net::HTTPServerRequest &,
                           Poco::Net::HTTPServerResponse &);

  /// It handles to Http verb DELETE.
  virtual void handle_delete(Poco::Net::HTTPServerRequest &,
                             Poco::Net::HTTPServerResponse &);

  /// It handles to Http VERB OPTIONS.
  virtual void handle_options(Poco::Net::HTTPServerRequest &,
                              Poco::Net::HTTPServerResponse &);

  /// It validates required information into the Http headers.
  virtual void handleHttpHeaders(Poco::Net::HTTPServerRequest &,
                                 Poco::Net::HTTPServerResponse &);

  /**
   * @param payload The string containing the Json data.
   * @return Only part of the payload with attributes in Poco Json Object
   * format.
   */
  Poco::JSON::Object::Ptr getJsonAttributesSectionObject(const std::string &);

  /*!
   * It validates a set of parameters have been set in a Json payload.
   *
   * @param jsonObject        Poco Json Object that contains payload data.
   * @param attributesNames   Attributes list to be validated.
   */
  void assertPayloadAttributes(const Poco::JSON::Object::Ptr &,
                               const std::list<std::string> &);

  /*!
   * It sets all the HTTP Response information based on the HTTP Code.
   *
   * @param statusCode    The HTTP Status Code.
   * @param response      Response to be handled.
   */
  void handleHttpStatusCode(int statusCode, Poco::Net::HTTPServerResponse &);

  /*!
   * @param fragment Part that it wishes to add to a URL.
   * @return A complete URL with a fragment added to its end.
   */
  std::string getUrl(const std::string &fragment);

  /*!
   * @param name The parameter name.
   * @return The parameter value.
   */
  std::string getQueryParameter(const std::string &);

  /*!
   * It converts an exception to Json API format.
   *
   * @param exception The exception thrown.
   * @return The exception Json API formatted.
   */
  std::string toJson(const Exception &);

 private:
  std::string baseUrl;
  std::string requestURI;
  std::string requestHost;
  Poco::URI::QueryParameters queryStringParameters;
};

}  // namespace resource
}  // namespace interface

#endif
