#include "Server.hpp"
#include <csignal>
#include <iostream>
#include "Post.hpp"
#include "ConfigParser.hpp"

using std::string;
using std::list;

string configFileName = "config.wsc";

// main for test parser
int main() {
		std::list<server_config> parsed;
		ConfigParser hehe(configFileName, {"server"}, {"error_pages", "routes"}, {"route"});
	for (size_t idx = 0; idx < hehe.getContentCount(); ++ idx) {
		server_config cur( hehe.getVarietyOfSection(idx) );
		parsed.push_back(cur);
	}
    return 228;
}

//void pipe(int l) { sigignore(l); }
//int main() {
//  signal(SIGPIPE, pipe);
//
//  std::list<route> routes;
//  std::list<methods> allowed_methods;
//  allowed_methods.push_back(methods(GET));
//  allowed_methods.push_back(methods(HEAD));
//  std::map<int, string> error_pages;
////  error_pages.insert(pair<int, string>(404, "/pages_root/error_pages/404_error"
////                                            ".html"));
//  error_pages.insert(pair<int, string>(403, "/pages_root/error_pages/403_error"
//                                            ".html"));
//  routes.push_back(route("/pages/some/", "/data/www", false, "simple.html",
//                         "/pages/lyubaya.html", "/pages/lyubaya.html",
//                         allowed_methods));
//  routes.push_back(route("/", "/pages_root", true, "", "/pages/lyubaya.html",
//                         "/pages/lyubaya.html", allowed_methods));
//
//  routes.push_back(route("/data/www/html/", "/pages_root", false,
//                         "simple.html"
//                         ".html",
//                         "/pages/lyubaya.html", "/pages/lyubaya.html",
//                         allowed_methods));
//
//  std::list<server_config>  serverConfig;
//  serverConfig.emplace_back("127.0.0.1", "8000", "lol", 21, error_pages, routes);
//
//  Server<http::types> serv(serverConfig);
//  serv.run_server();
//  return 0;
//}
