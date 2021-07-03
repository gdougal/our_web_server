//
// Created by Lonmouth Mallador on 6/19/21.
//

#include "ResponseBuilder.hpp"
#include "RoutingUtils.hpp"

ResponseBuilder::ResponseBuilder(const server_config &serverConfig,
																 const t_request_data &data)
				: serverConfig(serverConfig), request_data(data) {}

string ResponseBuilder::search_file(const route &r) const {
	string path_res;
	path_res = r.directory + r.location +
						 request_data.path.substr(r.location.length(),
																			request_data.path.length() -
																			r.location.length());

	if (ResponseUtils::is_directory(path_res))
		path_res += r.index_file;
	return path_res;
}

string ResponseBuilder::build_response(methods qurey_type) {
	string path_res = search_file(request_data.request_route);
	std::string body;

	switch (qurey_type) {
		case methods::GET: {
			if (ResponseUtils::is_directory(path_res) &&
					request_data.request_route.autoindex)
				body = AutoindexResonseBuilder().build(
								serverConfig, PATH_TO_ROOT + path_res,
								request_data.path);
			else {
				body = ResponseUtils::read_from_file(path_res);
				if (body.empty())
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
															 body.length()) +
				 body;
}

string ResponseBuilder::build_headers() { return std::string(); }


ResponseBuilder::~ResponseBuilder() {}
