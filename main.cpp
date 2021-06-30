#include "Server.hpp"
#include <csignal>
#include <iostream>


string configFileName = "config.wsc";

string trimKey(string &line) {
    return line.substr(line.find_first_of(':') + 1, line.size());
}

string trimFrontSpaces(string &line) {
    if (line[0] != ' ') {
        return(line);
    }
    return line.substr(line.find_first_not_of(' '), line.size());
}

string trimBackSpaces(string &line) {
    return line.substr(0, line.find_last_not_of(' ') + 1);
}

string trimSpaces(string &line) {
    string trimmedFront = trimFrontSpaces(line);
    return trimBackSpaces(trimmedFront);
}

string getValue(string &line) {
    string untrimmedSpaces = trimKey(line);
    return trimSpaces(untrimmedSpaces);
}

string getKey(string &line) {
    string buf = trimFrontSpaces(line);
    return buf.substr(0, buf.find_first_of(':'));
}

string getHost(string &line) {
    return getValue(line);
}

string getPort(string &line) {
    return getValue(line);
}

string getErrorPagePath(string &line) {
    string buf = trimBackSpaces(line).substr();
    return buf.substr(buf.find_last_of(' ') + 1, buf.size());
}

int getErrorNumber(string &line) {
    return stoi(trimKey(line));
}

std::list<methods> getAvailableMethods(string line) {
    std::list<methods> methodsList;
    if ((line.find("GET")) != string::npos) {
        methodsList.push_back(GET);
    }
    if ((line.find("DELETE")) != string::npos) {
        methodsList.push_back(DELETE);
    }
    if ((line.find("POST")) != string::npos) {
        methodsList.push_back(POST);
    }
    if ((line.find("HEAD")) != string::npos) {
        methodsList.push_back(HEAD);
    }
    return methodsList;
}

std::list<route> parseRoutes(std::ifstream &configFile) {
    string line;
    std::getline(configFile, line);
    std::list<route> result;
    while (!configFile.eof() || getKey(line) == "route") {
        route current;
        current.location = getValue(line);
        while (!configFile.eof()) {
            std::getline(configFile, line);
            if (line == "" || getKey(line) == "route") {
                result.push_back(current);
                break ;
            }
            else if (getKey(line) == "directory") {
                current.directory = getValue(line);
            }
            else if (getKey(line) == "redirection") {
                    current.redirect_path = getValue(line);
            }
            else if (getKey(line) == "autoindex") {
                current.autoindex = getValue(line) == "on";
            }
            else if (getKey(line) == "index_file") {
                current.index_file = getValue(line);
            }
            else if (getKey(line) == "cgi_path") {
                current.cgi_path = getValue(line);
            }
            else if (getKey(line) == "methods_allowed") {
                current.methods_allowed = getAvailableMethods(line);
            }
            else {
                return result;
            }
        }
    }
    return result;
}

server_config parseServer(std::ifstream &configFile) {
    server_config parsed;
    string line;
    std::getline(configFile, line);
    parsed.host = getHost(line);
    std::getline(configFile, line);
    parsed.port = getPort(line);
    while (!configFile.eof() && trimSpaces(line) != "routes:") {
        std::getline(configFile, line);
        if (getKey(line) == "server_name")
            parsed.server_name = getValue(line);
        else if (getKey(line) == "limit_body_size")
            parsed.client_body_size = stoi(getValue(line));
        else if (getKey(line) == "error_page")
            parsed.error_pages_paths.emplace(getErrorNumber(line), getErrorPagePath(line));
        else if (getKey(line) == "routes") {
            parsed.routes = parseRoutes(configFile);
            return parsed;
        }
        else {
            std::cout << "Unexpected field in configuration file\n" << getKey(line) << std::endl;
            return parsed;
        }
        std::getline(configFile, line);
    }
    return parsed;
}

list<server_config> parseConfigFile(void) {
    list<server_config> servers;
    server_config parsed;
    string line;

    std::ifstream configFile(configFileName);
    if (!configFile) {
        std::cout << "Can't open configuration file" << std::endl;
        return servers;
    }

    std::getline(configFile, line);
    while (!configFile.eof()) {
        if (line == "server:") {
            parsed = parseServer(configFile);
            if (parsed.server_name == "err") {
                std::cout << "Shit" << std::endl;
            }
            servers.push_back(parsed);
        }
        else {
            std::cout << "Shit 1" << line <<std::endl;
            return servers;
        }
    }
    configFile.close();
    return servers;
}

// main for test parser
//int main() {
//    string line = "     methods_allowed: GET POST     ";
//    std::cout << trimKey(line) << std::endl;
//    std::cout << trimKey(line) << std::endl;
//    std::cout << getErrorPagePath(line) << std::endl;
//    list<server_config> parsed = parseConfigFile();
//    return 228;
//}

void pipe(int l) { sigignore(l); }
int main() {
  signal(SIGPIPE, pipe);
  // TODO: Thies piece of data should filling by parsing part
  parseConfigFile();
  std::list<route> routes;
  std::list<methods> allowed_methods;
  allowed_methods.push_back(methods(GET));
  allowed_methods.push_back(methods(HEAD));
  routes.push_back(route("/", "direction", false, "/pages/simple.html",
                         "/pages/lyubaya.html", "/pages/lyubaya.html",
                         allowed_methods));
  std::map<int, std::string> error_page;
  error_page.insert(std::make_pair(1, "/pages/simple"));
  server_config serverConfig("127.0.0.1", "8000", "lol", 21, error_page,
                             routes);
  // TODO: Thies piece of data should filling by parsing part

  std::list<server_config> cfgs;
  cfgs.emplace_back(serverConfig);

  Server<http::types> serv(cfgs);
  serv.run_server();
  return 0;
}
