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
#include <vector>

/// Вариант парсера для файла с повторением базовых конструкций имеющие вложенные повторяемые конструкции
/// list

template<typename T>
struct Optional_simple {

	bool is_val() const { return is_val_; }
	const T& get_or(const T& alt_ret) const {
		if (is_val_)
			return value_;
		return alt_ret;
	};

	void set_value(const T& value) {
		value_ = value;
		is_val_ = true;
	}
	Optional_simple(): is_val_(false) {};
	explicit Optional_simple(const T& value): is_val_(true), value_(value) {}
	Optional_simple(const Optional_simple<T>& ref) = default;
	Optional_simple& operator=(const Optional_simple<T>& ref)  = default;
	virtual ~Optional_simple() {}
private:
	bool	is_val_;
	T			value_;
};

typedef Optional_simple<std::string> OptStr;

class ConfigParser {
public:
  class Section;
  ConfigParser(const std::string &config_name,
												const std::vector<std::string>& main_part_delim,
												const std::vector<std::string>& sub_part_delim,
												const std::vector<std::string>& sub_section_delim):
				  main_part_delim_(main_part_delim),
				  sub_part_delim_(sub_part_delim),
				  sub_section_delim_(sub_section_delim) {
		  std::ifstream ifs(config_name);
		  create_config(ifs);
  };
		const std::map<std::string, Section>& getVarietyOfSection(const size_t &section_count) const {
			auto find_res = all_sections.find(section_count);
			if (find_res == all_sections.end())
				throw std::out_of_range("Not found section");
			return find_res->second;
		};
	std::map<std::string, Section>& getVarietyOfSection(const size_t &section_count) {
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

	size_t getContentCount() const { return all_sections.size(); }

	class Section {
    friend ConfigParser;
		typedef std::map<std::string, Optional_simple<std::string> > t_section;
		typedef std::vector< t_section > t_list_section;

    t_list_section	content;
    void setContent(const std::string &key, const std::string &value, bool new_list = false) {
	    if (new_list || content.empty())
		    Section::content.emplace_back();
	    Section::content.back()[key] = Optional_simple<std::string>(value);
    };

		Optional_simple<std::string> throw_or_not(const std::string &Key, size_t num = 0) const {
			if (num > content.size())
				return Optional_simple<std::string>();
			auto find_res = content[num].find(Key);
			if (find_res == content[num].end())
				return Optional_simple<std::string>();
			return find_res->second;
		};
  public:
    Section() {}
    std::string	getStrValue(const std::string &Key, size_t num = 0, const std::string& or_val = "") const {
	    return throw_or_not(Key, num).get_or(or_val);
    };
    const t_section& getRawMap(size_t num = 0) { return content[num]; }
		size_t getContentSize() const { return content.size(); }
		t_section::const_iterator	getBeginSectIter(size_t num = 0) const {
			return t_section::const_iterator(content[num].begin());
		};
		t_section::const_iterator	getEndSectIter(size_t num = 0) const {
			return t_section::const_iterator(content[num].end());
		};
		t_section::iterator	getBeginSectIter(size_t num = 0) {
			return t_section::iterator(content[num].begin());
		};
		t_section::iterator	getEndSectIter(size_t num = 0) {
			return t_section::iterator(content[num].end());
		};
  };
private:
	std::string trim_str(const std::string &str_with) {
		auto pos_start = str_with.find_first_not_of(" \t");
		auto pos_end = str_with.find_last_not_of(" \t") + 1;
		if (pos_end > str_with.size())
			pos_end = str_with.size();
		if (pos_start > str_with.size() || str_with.empty())
			throw std::length_error("Empty value field!");
		return str_with.substr(pos_start, pos_end);
	}
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
	  std::string::iterator delimiter_iterator;
	  while (std::getline(ifs, line)) {
		  line = trim_str(line);
		  if (find_some(main_part_delim_, line)) {
		  	cur_section = line;
			  all_sections[main_part_counter].insert(std::pair<std::string, Section>(cur_section, Section()));
			  ++main_part_counter;
		  }
		  else if (find_some(sub_part_delim_, line)) {
			  cur_section = line;
			  all_sections[main_part_counter - 1].insert(std::pair<std::string, Section>(cur_section, Section()));
		  }
		  else if ( !line.empty() && (delimiter_iterator = std::find(line.begin(), line.end(), ':')) != line.end())
		  {
			  delimiter_iterator = std::find(line.begin(), line.end(), ':');
			  auto key = trim_str(std::string(line.begin(), delimiter_iterator));
			  auto value = std::string(delimiter_iterator + 1, line.end() );
			  value = trim_str(value);
			  value = value.substr(0, value.find(' '));
			  all_sections[main_part_counter - 1][cur_section].setContent(key, value, find_some(sub_section_delim_, key));
		  }
	  }
  };
};

#endif // HELLO_SFML_CONFIG_HPP
