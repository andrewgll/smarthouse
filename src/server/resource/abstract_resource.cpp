#include "server/resource/abstract_resource.h"

#include "Poco/JSON/Parser.h"
#include "Poco/Logger.h"
#include "Poco/Path.h"
#include "server/resource/utils/exception.h"
#include "server/resource/utils/json_error_builder.h"

namespace interface {
namespace resource {

AbstractResource::AbstractResource()
    : baseUrl(),
      requestURI(),
      requestHost(),
      dbService(Poco::Path(Poco::Path::current())
                    .append("db")
                    .append("devices.json")) {}

AbstractResource::~AbstractResource() {}

void AbstractResource::handleHttpHeaders(
    Poco::Net::HTTPServerRequest &request,
    Poco::Net::HTTPServerResponse &response) {
  response.setContentType("application/vnd.api+json; charset=utf-8");
  // if (request.getContentType() != "application/vnd.api+json" ||
  //     request.get("Accept") != "application/vnd.api+json") {
  //   throw resource::Exception(
  //       "Unsupported Media Type",
  //       "The only media type supported is application/vnd.api+json.", 415);
  // }

  if (request.getMethod() != Poco::Net::HTTPRequest::HTTP_GET &&
      request.getMethod() != Poco::Net::HTTPRequest::HTTP_PUT &&
      request.getMethod() != Poco::Net::HTTPRequest::HTTP_POST &&
      request.getMethod() != Poco::Net::HTTPRequest::HTTP_DELETE &&
      request.getMethod() != Poco::Net::HTTPRequest::HTTP_OPTIONS) {
    throw resource::Exception("Not Implemented",
                              "The request method is not supported by the "
                              "server and cannot be handled.",
                              501);
  }
}

void AbstractResource::handleRequest(Poco::Net::HTTPServerRequest &request,
                                     Poco::Net::HTTPServerResponse &response) {
  try {
    handleHttpHeaders(request, response);

    Poco::URI uri = Poco::URI(request.getURI());

    requestURI = request.getURI();
    requestHost = request.getHost();
    baseUrl = "http://" + requestHost + requestURI;
    queryStringParameters = uri.getQueryParameters();

    if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET) {
      this->handle_get(request, response);
    }

    if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_PUT) {
      this->handle_put(request, response);
    }

    if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST) {
      this->handle_post(request, response);
    }

    if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_DELETE) {
      this->handle_delete(request, response);
    }

    if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_OPTIONS) {
      this->handle_options(request, response);
    }
  } catch (resource::Exception &exception) {
    handleHttpStatusCode(exception.code(), response);

    handling::JsonErrorBuilder errorBuilder =
        handling::JsonErrorBuilder(request.getHost());
    Poco::Logger &logger = Poco::Logger::get("SmartHouseLogger");

    errorBuilder.sourceAt(request.getURI());
    errorBuilder.withType(exception.type());
    errorBuilder.withStatusCode(exception.code());
    errorBuilder.withDetails(exception.message());

    // TODO: Find out what is assertion violation
    response.send() << errorBuilder.build().toString();
    return;
  }
}

void AbstractResource::handle_get(Poco::Net::HTTPServerRequest &,
                                  Poco::Net::HTTPServerResponse &response) {
  handleHttpStatusCode(501, response);
  std::ostream &errorStream = response.send();
  errorStream.flush();
}

void AbstractResource::handle_put(Poco::Net::HTTPServerRequest &,
                                  Poco::Net::HTTPServerResponse &response) {
  handleHttpStatusCode(501, response);
  std::ostream &errorStream = response.send();
  errorStream.flush();
}

void AbstractResource::handle_post(Poco::Net::HTTPServerRequest &,
                                   Poco::Net::HTTPServerResponse &response) {
  handleHttpStatusCode(501, response);
  std::ostream &errorStream = response.send();
  errorStream.flush();
}

void AbstractResource::handle_delete(Poco::Net::HTTPServerRequest &,
                                     Poco::Net::HTTPServerResponse &response) {
  handleHttpStatusCode(501, response);
  std::ostream &errorStream = response.send();
  errorStream.flush();
}

void AbstractResource::handle_options(Poco::Net::HTTPServerRequest &,
                                      Poco::Net::HTTPServerResponse &response) {
  response.setStatusAndReason(
      Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED,
      Poco::Net::HTTPResponse::HTTP_REASON_NOT_IMPLEMENTED);

  std::ostream &errorStream = response.send();
  errorStream.flush();
}

Poco::JSON::Object::Ptr AbstractResource::getJsonAttributesSectionObject(
    const std::string &payload) {
  Poco::JSON::Parser jsonParser;
  Poco::Dynamic::Var parsingResult = jsonParser.parse(payload);
  auto jsonObject = parsingResult.extract<Poco::JSON::Object::Ptr>();

  if (jsonObject->isArray("data")) {
    throw resource::Exception(
        Poco::Net::HTTPResponse::HTTP_REASON_BAD_REQUEST,
        "This payload can not be represented as a collection.",
        Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
  }

  //
  Poco::JSON::Object::Ptr dataObject = jsonObject->getObject("data");

  if (!dataObject->has("attributes")) {
    throw resource::Exception(Poco::Net::HTTPResponse::HTTP_REASON_BAD_REQUEST,
                              "The payload has no an 'attributes' section.",
                              Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
  }

  return dataObject->getObject("attributes");
}

// `

void AbstractResource::handleHttpStatusCode(
    int statusCode, Poco::Net::HTTPServerResponse &response) {
  switch (statusCode) {
    case 200:
      response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_OK);
      break;

    case 201:
      response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_CREATED);
      break;

    case 202:
      response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_ACCEPTED);
      break;

    case 204:
      response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NO_CONTENT);
      break;

    case 205:
      response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_RESET_CONTENT);
      break;

    case 206:
      response.setStatusAndReason(
          Poco::Net::HTTPResponse::HTTP_PARTIAL_CONTENT);
      break;

    case 400:
      response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
      break;

    case 401:
      response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
      break;

    case 403:
      response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_FORBIDDEN);
      break;

    case 404:
      response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
      break;

    case 405:
      response.setStatusAndReason(
          Poco::Net::HTTPResponse::HTTP_METHOD_NOT_ALLOWED);
      break;

    case 406:
      response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_ACCEPTABLE);
      break;

    case 409:
      response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_CONFLICT);
      break;

    case 410:
      response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_GONE);
      break;

    case 415:
      response.setStatusAndReason(
          Poco::Net::HTTPResponse::HTTP_UNSUPPORTEDMEDIATYPE);

    case 500:
      response.setStatusAndReason(
          Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);

    case 501:
      response.setStatusAndReason(
          Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);

    case 503:
      response.setStatusAndReason(
          Poco::Net::HTTPResponse::HTTP_SERVICE_UNAVAILABLE);

    // Validating routines throw exceptions all over the program, but are not
    // able to specify an exception code compatible with HTTP. So, the code is
    // left zero. This routine can catch this.
    default:
      response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
  }
}

std::string AbstractResource::getUrl(const std::string &fragment) {
  return baseUrl + fragment;
}

std::string AbstractResource::getQueryParameter(
    const std::string &parameterKey) {
  auto iterator = std::find_if(
      queryStringParameters.begin(), queryStringParameters.end(),
      [&parameterKey](const std::pair<std::string, std::string> &item) {
        return item.first == parameterKey;
      });

  if (iterator == queryStringParameters.end()) {
    throw resource::Exception(
        Poco::Net::HTTPResponse::HTTP_REASON_BAD_REQUEST,
        "Attribute '" + parameterKey + "' is missing at URL.",
        Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
  }

  return iterator->second;
}
std::string AbstractResource::toJson(const Exception &exception) {
  handling::JsonErrorBuilder errorBuilder(requestHost);
  errorBuilder.withType(exception.type());
  errorBuilder.sourceAt(requestURI);
  errorBuilder.withStatusCode(exception.code());
  errorBuilder.withDetails(exception.message());
  return errorBuilder.build().toString();
}

}  // namespace resource
}  // namespace interface
