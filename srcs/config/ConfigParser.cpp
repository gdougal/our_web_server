//
// Created by Gilberto Dougal on 4/26/21.
//

#include "ConfigParser.hpp"
#include <algorithm>

ConfigParser::ConfigParser(const std::string &config_name) {
  std::ifstream ifs(config_name);
  create_config(ifs);
}

void ConfigParser::create_config(std::ifstream &ifs) {
  std::string line, section_name;

  while (std::getline(ifs, line)) {
    if (line[0] == '#') {
      section_name = std::string(line.c_str() + 1);
    } else {
      auto delimiter_iterator = std::find(line.begin(), line.end(), ':');
      if (delimiter_iterator == line.end() && !line.empty())
        throw(std::invalid_argument("Wrong config!"));
      else if (delimiter_iterator == line.end())
        continue;
      auto key = std::string(line.begin(), delimiter_iterator);
      auto value = std::string(delimiter_iterator + 1, line.end());
      sections[section_name].setContent(key, value);
    }
  }
}

const ConfigParser::Section &
ConfigParser::getSection(const std::string &section_name) const {
  auto find_res = sections.find(section_name);
  if (find_res == sections.end())
    throw std::out_of_range("Not found section");
  return find_res->second;
}

void ConfigParser::Section::setContent(const std::string &key,
                                 const std::string &value) {
  auto pos = value.find_first_not_of(" \t");
  auto str = value.substr(pos);
  if (pos > value.size() || str.empty())
    throw std::length_error("Empty value field!");
  Section::content[key] = str;
}

const std::string &
ConfigParser::Section::throw_or_not(const std::string &Key) const {
  auto find_res = content.find(Key);
  if (find_res == content.end())
    throw std::out_of_range("Not found parameter");
  std::string a(find_res->second);
  return find_res->second;
}

bool ConfigParser::Section::getBoolVal(const std::string &Key) const {
  std::string str(throw_or_not(Key));
  bool ret;
  if (str.size() != 1 || str.at(0) < '0' || str.at(0) > '1')
    throw std::length_error("Empty value field!");
  ret = (str.at(0) == '1');
  return ret;
}
int ConfigParser::Section::getIntVal(const std::string &Key) const {
  return std::stoi(throw_or_not(Key));
}
float ConfigParser::Section::getFloatVal(const std::string &Key) const {
  return std::stof(throw_or_not(Key));
}
const std::string
ConfigParser::Section::getStringVal(const std::string &Key) const {
  return throw_or_not(Key);
}
uint32_t ConfigParser::Section::getAddrVal(const std::string &Key) const {
  return inet_addr(throw_or_not(Key).c_str());
}
uint16_t ConfigParser::Section::getPortVal(const std::string &Key) const {
  return htons(static_cast<uint16_t>(std::stoul(throw_or_not(Key))));
}
