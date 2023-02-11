#include "server/resource/abstract_resource.h"

#include <functional>
#include <memory>

#include "Poco/JSON/Parser.h"
#include "Poco/Logger.h"
#include "Poco/Path.h"
#include "server/db/db_service.h"
#include "server/resource/utils/exception.h"
#include "server/resource/utils/json_error_builder.h"

namespace interface {
namespace resource {

using namespace Poco::Net;
AbstractResource::AbstractResource() : baseUrl(), requestURI(), requestHost() {}
AbstractResource::AbstractResource(Poco::Path &path)
    : baseUrl(),
      requestURI(),
      requestHost(),
      dbService(std::unique_ptr<db::DBService>(new db::DBService(path))) {}

AbstractResource::~AbstractResource() {}

void AbstractResource::handleRequest(HTTPServerRequest &request,
                                     HTTPServerResponse &response) {
  try {
    Poco::URI uri = Poco::URI(request.getURI());

    requestURI = request.getURI();
    requestHost = request.getHost();
    baseUrl = "http://" + requestHost + requestURI;
    queryStringParameters = uri.getQueryParameters();

    if (handler_map.find(request.getMethod()) != handler_map.end()) {
      std::invoke(handler_map[request.getMethod()], *this, request, response);

    } else {
      response.setContentType("application/vnd.api+json; charset=utf-8");
      throw utils::HttpServerException(
          "Not Implemented",
          "The request method is not supported by the "
          "server and cannot be handled.",
          HTTPResponse::HTTP_NOT_IMPLEMENTED);
    }
  } catch (utils::HttpServerException &exception) {
    response.setStatusAndReason(exception.code());

    utils::JsonErrorBuilder errorBuilder =
        utils::JsonErrorBuilder(request.getHost());

    errorBuilder.sourceAt(request.getURI());
    errorBuilder.withType(exception.type());
    errorBuilder.withStatusCode(exception.code());
    errorBuilder.withDetails(exception.message());

    response.send() << errorBuilder.build().toString();
  }
}

void AbstractResource::handle_get(HTTPServerRequest &,
                                  HTTPServerResponse &response) {
  response.setStatusAndReason(HTTPResponse::HTTP_METHOD_NOT_ALLOWED);
  response.send();
}

void AbstractResource::handle_put(HTTPServerRequest &,
                                  HTTPServerResponse &response) {
  response.setStatusAndReason(HTTPResponse::HTTP_METHOD_NOT_ALLOWED);
  response.send();
}

void AbstractResource::handle_post(HTTPServerRequest &,
                                   HTTPServerResponse &response) {
  response.setStatusAndReason(HTTPResponse::HTTP_METHOD_NOT_ALLOWED);
  response.send();
}

void AbstractResource::handle_delete(HTTPServerRequest &,
                                     HTTPServerResponse &response) {
  response.setStatusAndReason(HTTPResponse::HTTP_METHOD_NOT_ALLOWED);
  response.send();
}

void AbstractResource::handle_options(HTTPServerRequest &,
                                      HTTPServerResponse &response) {
  response.setStatusAndReason(HTTPResponse::HTTP_METHOD_NOT_ALLOWED);
  response.send();
}

std::string AbstractResource::getUrl(const std::string &fragment) {
  return baseUrl + fragment;
}

std::string AbstractResource::getQueryParameter(const std::string &parameterKey,
                                                bool required) {
  auto iterator = std::find_if(
      queryStringParameters.begin(), queryStringParameters.end(),
      [&parameterKey](const std::pair<std::string, std::string> &item) {
        return item.first == parameterKey;
      });

  if (iterator == queryStringParameters.end()) {
    if (!required) {
      return "";
    }
    throw utils::HttpServerException(

        HTTPResponse::HTTP_REASON_BAD_REQUEST,
        "Attribute '" + parameterKey + "' is missing at URL.",
        HTTPResponse::HTTP_BAD_REQUEST);
  }

  return iterator->second;
}
}  // namespace resource
}  // namespace interface
