//
// Created by Gilberto Dougal on 4/26/21.
//

#pragma once


#include <exception>
#include <vector>
#include "manual_types.h"
#include "optional.hpp"

class ConfigParser {
public:
  class Section;
  ConfigParser(const std::string &config_name,
												const std::vector<std::string>& main_part_delim,
												const std::vector<std::string>& sub_part_delim,
												const std::vector<std::string>& sub_section_delim);

	const std::map<std::string, Section>&	getVarietyOfSection(const size_t &section_count) const;
	std::map<std::string, Section>&				getVarietyOfSection(const size_t &section_count);
  const Section&												getConcreteSection(const size_t &section_count, const std::string &section_name) const;
	size_t																getContentCount() const;

	class Section {
    friend ConfigParser;
		typedef std::map<std::string, ft::optional<std::string> > t_section;
		typedef std::vector< t_section > t_list_section;
    void setContent(const std::string &key, const std::string &value, bool new_list);
    ft::optional<std::string> throw_or_not(const std::string &Key, size_t num = 0) const;
	public:
		Section() = default;
		std::string	getStrValue(const std::string &Key, size_t num = 0, const std::string& or_val = "") const;
		const t_section& getRawMap(size_t num = 0);
		size_t getContentSize() const;
		t_section::const_iterator	getBeginSectIter(size_t num = 0) const;
		t_section::const_iterator	getEndSectIter(size_t num = 0) const;
		t_section::iterator	getBeginSectIter(size_t num = 0);
		t_section::iterator	getEndSectIter(size_t num = 0);
		private:
			t_list_section	content;
  };
private:
	std::string trim_str(const std::string &str_with);
	void create_config(std::ifstream &ifs);
  typedef std::map<size_t, std::map<std::string, Section> > big_data;

	const std::vector<std::string>& main_part_delim_;
	const std::vector<std::string>& sub_part_delim_;
	const std::vector<std::string>& sub_section_delim_;
	big_data                        all_sections;
};
