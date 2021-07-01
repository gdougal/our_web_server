//
// Created by Gilberto Dougal on 4/26/21.
//

#ifndef HELLO_SFML_CONFIG_HPP
#define HELLO_SFML_CONFIG_HPP

#include <arpa/inet.h>
#include <exception>
#include <fstream>
#include <istream>
#include <map>
#include <list>
#include <algorithm>

/// Вариант парсера для файла с повторением базовых конструкций имеющие вложенные повторяемые конструкции
/// list

class ConfigParser {
public:
  class Section;
  explicit ConfigParser(const std::string &config_name,
												const std::vector<std::string>& main_part_delim,
												const std::vector<std::string>& sub_part_delim,
												const std::vector<std::string>& sub_section_delim):
				  main_part_delim_(main_part_delim),
				  sub_part_delim_(sub_part_delim),
				  sub_section_delim_(sub_section_delim) {
		  std::ifstream ifs(config_name);
		  create_config(ifs);
  };
		const std::map<std::string, Section> &getVarietyOfSection(const size_t &section_count) const {
			auto find_res = all_sections.find(section_count);
			if (find_res == all_sections.end())
				throw std::out_of_range("Not found section");
			return find_res->second;
		};
  const Section &getConcreteSection(const size_t &section_count, const std::string &section_name) const {
	  auto part = (getVarietyOfSection(section_count));
	  auto find_res = part.find(section_name);
	  if (find_res == part.end())
		  throw std::out_of_range("Not found section");
	  return find_res->second;
  };

	std::string jewMaker(const std::string &str_with) {
		auto pos_start = str_with.find_first_not_of(" \t");
		auto pos_end = str_with.find_last_not_of(" \t") + 1;
		if (pos_end > str_with.size())
			pos_end = str_with.size();
		if (pos_start > str_with.size() || str_with.empty())
			throw std::length_error("Empty value field!");
		return str_with.substr(pos_start, pos_end);
	}

  class Section {
    friend ConfigParser;
		typedef std::vector< std::map<std::string, std::string> > t_list_section;

    t_list_section content;
    void setContent(const std::string &key, const std::string &value, bool new_list = false) {
	    if (new_list || content.empty())
		    Section::content.emplace_back();
	    Section::content.back()[key] = value;
    };
    const std::string &throw_or_not(const std::string &Key, size_t num = 0) const {
			  auto find_res = content[num].find(Key);
			  if (find_res == content[num].end())
				  throw std::out_of_range("Not found parameter");
			  std::string a(find_res->second);
			  return find_res->second;
		  };

  public:
    Section() {}
    const std::string getStringVal(const std::string &Key, size_t num = 0) const {
	    return throw_or_not(Key);
    };
    int               getIntVal(const std::string &Key, size_t num = 0) const {
	    return std::stoi(throw_or_not(Key));
    };
    bool              getBoolVal(const std::string &Key, size_t num = 0) const {
	    std::string str(throw_or_not(Key));
	    bool ret;
	    if (str.size() != 1 || str.at(0) < '0' || str.at(0) > '1')
		    throw std::length_error("Empty value field!");
	    ret = (str.at(0) == '1');
	    return ret;
    };
  };
private:
		template<class Container, typename t_element>
		bool find_some(const Container& cont, const t_element& elem) {
			if (std::find(cont.begin(), cont.end(), elem) != cont.end())
				return true;
			return false;
		}

		const std::vector<std::string>& main_part_delim_;
		const std::vector<std::string>& sub_part_delim_;
		const std::vector<std::string>& sub_section_delim_;
		std::map<size_t, std::map<std::string, Section> >	all_sections;
  void create_config(std::ifstream &ifs) {
	  std::string line;
	  std::string cur_section;
		size_t main_part_counter = 0;
	  while (std::getline(ifs, line)) {
		  line = jewMaker(line);
		  if (find_some(main_part_delim_, line)) {
		  	cur_section = line;
			  all_sections[main_part_counter].insert(std::pair<std::string, Section>(cur_section, Section()));
			  ++main_part_counter;
		  }
		  else if (find_some(sub_part_delim_, line)) {
			  cur_section = line;
			  all_sections[main_part_counter - 1].insert(std::pair<std::string, Section>(cur_section, Section()));
		  }
		  else
		  {
			  auto delimiter_iterator = std::find(line.begin(), line.end(), ':');
			  if (delimiter_iterator == line.end() && !line.empty())
				  throw(std::invalid_argument("Wrong config!"));
			  else if (delimiter_iterator == line.end())
				  continue;
			  auto key = jewMaker(std::string(line.begin(), delimiter_iterator));
			  auto value = std::string(delimiter_iterator + 1, line.end() );
			  value = jewMaker(value);
			  value = value.substr(0, value.find(' '));
			  all_sections[main_part_counter - 1][cur_section].setContent(key, value, find_some(sub_section_delim_, key));
		  }
	  }
  };
};

#endif // HELLO_SFML_CONFIG_HPP
