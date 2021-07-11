//
// Created by Gilberto Dougal on 4/26/21.
//

#include "config/Parser/ConfigParser.hpp"
#include "CommonUtils.hpp"
#include <fstream>

ConfigParser::ConfigParser(const std::string &config_name,
													 const std::vector<std::string> &main_part_delim,
													 const std::vector<std::string> &sub_part_delim,
													 const std::vector<std::string> &sub_section_delim) :
				main_part_delim_(main_part_delim),
				sub_part_delim_(sub_part_delim),
				sub_section_delim_(sub_section_delim) {
	std::ifstream ifs(config_name);
	create_config(ifs);
};

const std::map<std::string, ConfigParser::Section> &ConfigParser::getVarietyOfSection(const size_t &section_count) const {
	big_data::const_iterator find_res = all_sections.find(section_count);
	if (find_res == all_sections.end())
		throw std::out_of_range("Not found section");
	return find_res->second;
};

std::map<std::string, ConfigParser::Section> &ConfigParser::getVarietyOfSection(const size_t &section_count) {
  big_data::iterator find_res = all_sections.find(section_count);
	if (find_res == all_sections.end())
		throw std::out_of_range("Not found section");
	return find_res->second;
};

const ConfigParser::Section &ConfigParser::getConcreteSection(const size_t &section_count, const std::string &section_name) const {
  std::map<std::string, ConfigParser::Section> part = (getVarietyOfSection(section_count));
  std::map<std::string, ConfigParser::Section>::iterator find_res = part.find(section_name);
	if (find_res == part.end())
		throw std::out_of_range("Not found section");
	return find_res->second;
};

size_t ConfigParser::getContentCount() const { return all_sections.size(); };

std::string ConfigParser::trim_str(const std::string &str_with) {
	size_t pos_start = str_with.find_first_not_of(" \t");
  size_t pos_end = str_with.find_last_not_of(" \t") + 1;
	if (pos_end > str_with.size())
		pos_end = str_with.size();
	if (pos_start > str_with.size() || str_with.empty())
		throw std::length_error("Empty value field!");
	return str_with.substr(pos_start, pos_end);
}

void ConfigParser::create_config(std::ifstream &ifs) {
	std::string line;
	std::string cur_section;
	size_t main_part_counter = 0;
	std::string::iterator delimiter_iterator;
	while (std::getline(ifs, line)) {
		line = trim_str(line);
		if (find_some(main_part_delim_, line)) {
			cur_section = line;
			all_sections[main_part_counter].insert(
							std::pair<std::string, Section>(cur_section, Section()));
			++main_part_counter;
		} else if (find_some(sub_part_delim_, line)) {
			cur_section = line;
			all_sections[main_part_counter - 1].insert(
							std::pair<std::string, Section>(cur_section, Section()));
		} else if (!line.empty() && (delimiter_iterator = std::find(line.begin(), line.end(), ':')) != line.end()) {
			delimiter_iterator = std::find(line.begin(), line.end(), ':');
			std::string key = trim_str(std::string(line.begin(), delimiter_iterator));
      std::string value = std::string(delimiter_iterator + 1, line.end());
			value = trim_str(value);
			value = value.substr(0, value.find(' '));
			all_sections[main_part_counter - 1][cur_section].setContent(key, value,
																																	find_some(
																																					sub_section_delim_,
																																					key));
		}
	}
};
