//
// Created by Gilberto Dougal on 7/3/21.
//
#include "config/Parser/ConfigParser.hpp"
#include "optional.hpp"

using Section = ConfigParser::Section;

void Section::setContent(const std::string &key, const std::string &value, bool new_list = false) {
	if (new_list || content.empty())
		Section::content.emplace_back();
	Section::content.back()[key] = ft::optional<std::string>(value);
};

ft::optional<std::string>	Section::throw_or_not(const std::string &Key, size_t num) const {
	if (num > content.size())
		return ft::optional<std::string>();
	auto find_res = content[num].find(Key);
	if (find_res == content[num].end())
		return ft::optional<std::string>();
	return find_res->second;
};

std::string	Section::getStrValue(const std::string &Key, size_t num,
																	 const std::string &or_val) const {
	return throw_or_not(Key, num).get_or(or_val);
};

const Section::t_section	&Section::getRawMap(size_t num) { return content[num]; };

size_t										Section::getContentSize() const { return content.size(); };

std::map<std::string, ft::optional<std::string>>::const_iterator
Section::getBeginSectIter(size_t num) const {
	return t_section::const_iterator(content[num].begin());
};

std::map<std::string, ft::optional<std::string>>::const_iterator
ConfigParser::Section::getEndSectIter(size_t num) const {
	return t_section::const_iterator(content[num].end());
};

std::map<std::string, ft::optional<std::string>>::iterator
ConfigParser::Section::getBeginSectIter(size_t num) {
	return t_section::iterator(content[num].begin());
};

std::map<std::string, ft::optional<std::string>>::iterator
ConfigParser::Section::getEndSectIter(size_t num) {
	return t_section::iterator(content[num].end());
};
