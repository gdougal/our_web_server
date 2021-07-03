//
// Created by Lonmouth Mallador on 6/19/21.
//

#include "ResponseBuilder.hpp"
#include "RoutingUtils.hpp"
#include "CommonUtils.hpp"

ResponseBuilder::ResponseBuilder(const server_config &serverConfig,
																 const t_request_data &data)
				: serverConfig(serverConfig), request_data(data) {}


string ResponseBuilder::build_response(methods qurey_type) {
	std::string response_body;

	switch (qurey_type) {
		case methods::GET: {
			if (is_directory(request_data.path) &&
					request_data.request_route.autoindex)
				response_body = AutoindexResonseBuilder().build(
								serverConfig, PATH_TO_ROOT + request_data.path,
								request_data.path);
			else {
				response_body = ResponseUtils::read_from_file(request_data.path);
				if (response_body.empty())
					return ErrorBuilder::build(404, serverConfig);
			}
			break;
		}
		case methods::HEAD: {

			break;
		}
		case methods::PUT: {

			break;
		}
		case methods::POST: {
//    if (!r->cgi_path.empty()) {
//     // run cgi post
//    } else {
//      // run post
//    }
			break;
		}
		case methods::DELETE: {
//    if (!r->cgi_path.empty()) {
//      // run cgi delete
//    } else {
//      // run delete
//    }
			break;
		}
	}

	return HeadersBuilder::build(200, connection(KEEP_ALIVE), content_type(HTML),
															 response_body.length()) +
				 response_body;
}

ResponseBuilder::~ResponseBuilder() {}
