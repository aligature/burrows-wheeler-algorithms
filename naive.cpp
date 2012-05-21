// Unbelievably naîve implementation of the Burrows-Wheeler transform.

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

//algorithm to find the occurence count of a given element starting from
//the beginning.  I.e. given "abraca" and an iterator pointing to the second
//"a" the algorithm will return 2.  If the element iterator points to the last
//character, the algorithm will return 3 because the last character is the third
//"a".  Walking all the characters in the string, the algorithm will return
//1, 1, 1, 2, 1 and 3.  The element must be in the range between the first and
//last iterators.
template<typename ForwardIter>
unsigned int find_element_occurance(ForwardIter first, ForwardIter last,
	ForwardIter element);
	
std::pair<std::string,unsigned int> burrows_wheeler_copy(const std::string & s);
std::string inverse_burrows_wheeler_copy(const std::string & s, unsigned int original_index);

int main()
{
	std::string	s = "abraca";
	std::pair<std::string,unsigned int>	xform = burrows_wheeler_copy(s);
	std::string	t = xform.first;
	unsigned int original_string_index = xform.second;
	
	std::cout << "Transform results:\n" << s << '\n' << t << std::endl;
	std::cout << "Original string index is " << original_string_index << '\n';
	std::string i = inverse_burrows_wheeler_copy(t, original_string_index);
	std::cout << "Inverse transform results:\n" << i << std::endl;
	
	return 0;
}

std::pair<std::string,unsigned int> burrows_wheeler_copy(const std::string & s)
{
	std::string	l;
	unsigned int original_string_index;
	std::pair<std::string,unsigned int>	result_pair;
	
	l.reserve(s.size());
	
	std::vector<std::string>	m(s.size(), s);
	for (unsigned int i = 0; i < s.size(); i++) {
		std::rotate(m[i].begin(), m[i].begin() + i, m[i].end());
		std::cout << m[i] << '\n';
	}
	std::cout << '\n';
	std::stable_sort(m.begin(), m.end());
	for (unsigned int i = 0; i < s.size(); i++) {
		l.push_back(*--m[i].end());
		if (s == m[i]) {
			original_string_index = i;
			std::cout << "Original index found at " << i << '\n';
		}
		std::cout << m[i] << '\n';
	}
	std::cout << '\n' << l << '\n';
	result_pair.first = l;
	result_pair.second = original_string_index;

	return result_pair;
}

std::string inverse_burrows_wheeler_copy(const std::string & l, unsigned int original_index)
{
	std::string	s;
	
	std::string	f(l);
	std::stable_sort(f.begin(), f.end());
	std::cout << "L is " << l << '\n';
	std::cout << "F is " << f << '\n';
	
	std::vector<unsigned int>	t(l.size());
	unsigned int i;
	unsigned int j;
	unsigned int k = 1;
	std::string::value_type	ch = 0;
	for (j = 0; j < l.size(); j++) {
		if (ch != l[j]) {
			ch = l[j];
			k = 1;
		}
		std::string::iterator	nth_iter
			= std::search_n(f.begin(), f.end(), k++, ch);
		i = nth_iter - f.begin();
		t[j] = i;
		std::cout << "i = " << i << '\n';
		std::cout << "k = " << k << '\n';
		std::cout << "ch = " << ch << '\n';
		std::cout << "T[" << j << "] = " << t[j] << '\n';
	}
	
	return s;
}

template<typename ForwardIter>
unsigned int find_element_occurance(ForwardIter first, ForwardIter last,
	ForwardIter element)
{
	unsigned int count = 0;
	typename ForwardIter::value_type	element_value = *element;
	while (first != last) {
		if (*first == element_value) count++;
		if (first == element) break;
	}
	assert(count > 0);
	
	return count;
}
