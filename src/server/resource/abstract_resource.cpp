#include "server/resource/abstract_resource.h"

#include "Poco/JSON/Parser.h"
#include "Poco/Logger.h"
#include "Poco/Message.h"
#include "Poco/Path.h"
#include "Poco/StreamCopier.h"
#include "server/resource/utils/exception.h"
#include "server/resource/utils/json_error_builder.h"

namespace interface {
namespace resource {

using namespace Poco::Net;

AbstractResource::AbstractResource()
    : baseUrl(),
      requestURI(),
      requestHost(),
      dbService(Poco::Path(Poco::Path::current())
                    .append("db")
                    .append("devices.json")) {}

AbstractResource::~AbstractResource() {}

void AbstractResource::handleHttpHeaders(HTTPServerRequest &request,
                                         HTTPServerResponse &response) {
  response.setContentType("application/vnd.api+json; charset=utf-8");

  if (request.getMethod() != HTTPRequest::HTTP_GET &&
      request.getMethod() != HTTPRequest::HTTP_PUT &&
      request.getMethod() != HTTPRequest::HTTP_POST &&
      request.getMethod() != HTTPRequest::HTTP_DELETE &&
      request.getMethod() != HTTPRequest::HTTP_OPTIONS) {
    throw utils::HttpServerException(
        "Not Implemented",
        "The request method is not supported by the "
        "server and cannot be handled.",
        HTTPResponse::HTTP_NOT_IMPLEMENTED);
  }
}

void AbstractResource::handleRequest(HTTPServerRequest &request,
                                     HTTPServerResponse &response) {
  try {
    handleHttpHeaders(request, response);

    Poco::Logger &logger = Poco::Logger::get("SmartHouseLogger");
    std::string requestData;
    // TODO: find better way to get data from istream
    Poco::StreamCopier::copyToString(request.stream(), requestData);
    logger.information("%s from %s to %s Content-Type: %s Received: %s",
                       request.getMethod(), request.clientAddress().toString(),
                       request.getHost(), request.getContentType(),
                       requestData);
    Poco::URI uri = Poco::URI(request.getURI());

    requestURI = request.getURI();
    requestHost = request.getHost();
    baseUrl = "http://" + requestHost + requestURI;
    queryStringParameters = uri.getQueryParameters();

    if (request.getMethod() == HTTPRequest::HTTP_GET) {
      this->handle_get(request, response);
    }

    if (request.getMethod() == HTTPRequest::HTTP_PUT) {
      this->handle_put(request, response);
    }

    if (request.getMethod() == HTTPRequest::HTTP_POST) {
      this->handle_post(request, response);
    }

    if (request.getMethod() == HTTPRequest::HTTP_DELETE) {
      this->handle_delete(request, response);
    }

    if (request.getMethod() == HTTPRequest::HTTP_OPTIONS) {
      this->handle_options(request, response);
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
  Poco::Logger &logger = Poco::Logger::get("SmartHouseLogger");
  response.setStatusAndReason(HTTPResponse::HTTP_METHOD_NOT_ALLOWED);
  std::ostream &errorStream = response.send();
  errorStream.flush();
}

void AbstractResource::handle_put(HTTPServerRequest &,
                                  HTTPServerResponse &response) {
  response.setStatusAndReason(HTTPResponse::HTTP_METHOD_NOT_ALLOWED);
  std::ostream &errorStream = response.send();
  errorStream.flush();
}

void AbstractResource::handle_post(HTTPServerRequest &,
                                   HTTPServerResponse &response) {
  response.setStatusAndReason(HTTPResponse::HTTP_METHOD_NOT_ALLOWED);
  std::ostream &errorStream = response.send();
  errorStream.flush();
}

void AbstractResource::handle_delete(HTTPServerRequest &,
                                     HTTPServerResponse &response) {
  response.setStatusAndReason(HTTPResponse::HTTP_METHOD_NOT_ALLOWED);
  std::ostream &errorStream = response.send();
  errorStream.flush();
}

void AbstractResource::handle_options(HTTPServerRequest &,
                                      HTTPServerResponse &response) {
  response.setStatusAndReason(HTTPResponse::HTTP_METHOD_NOT_ALLOWED);
  std::ostream &errorStream = response.send();
  errorStream.flush();
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
