#pragma once

#include <algorithm>

template<class Container, typename t_element>
bool find_some(const Container& cont, const t_element& elem) {
	if (std::find(cont.begin(), cont.end(), elem) != cont.end())
		return true;
	return false;
}