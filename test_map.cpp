#include "map.hpp"
#include <map>

#include <string>
#include <iostream>

void print_map(std::map<char, std::string>std_map, ft::map<char, std::string>ft_map)
{
	std::map<char,std::string>::iterator iter;
	ft::map<char,std::string>::iterator ft_iter;

	for (iter = std_map.begin(); iter != std_map.end(); iter++)
	{
		std::cout << "    " << iter->first << " - " << iter->second << std::endl;
	}
	std::cout << std::endl;
	for (ft_iter = ft_map.begin(); ft_iter != ft_map.end(); ft_iter++)
	{
		std::cout << "    " << ft_iter->first << " - " << ft_iter->second << '\n';
	}

	std::cout << std::endl;
}

int main()
{
	std::cout << std::endl << "-------- Map ----------" << std::endl;

	std::map<char, std::string> std_map;
	ft::map<char, std::string> ft_map;

	std_map['a'] = "alpha";
	std_map['b'] = "bravo";
	std_map['c'] = "charlie";
	std_map['d'] = "delta";

	ft_map['a'] = "alpha";
	ft_map['b'] = "bravo";
	ft_map['c'] = "charlie";
	ft_map['d'] = "delta";

	print_map(std_map, ft_map);

	std::cout << std::endl << "- Iterators: " << std::endl;
	std::cout << "begin: " << std_map.begin()->first << " - ";
	std::cout << std_map.begin()->second << std::endl;
	std::cout << "begin: " << ft_map.begin()->first << " - ";
	std::cout << ft_map.begin()->second << std::endl;
	std::cout << "end-1: " << (--std_map.end())->first << " - ";
	std::cout << (--std_map.end())->second << std::endl;
	std::cout << "end-1: " << (--ft_map.end())->first << " - ";
	std::cout << (--ft_map.end())->second << std::endl;
	std::cout << "rbegin: " << std_map.rbegin()->first << " - ";
	std::cout << std_map.rbegin()->second << std::endl;
	std::cout << "rbegin: " << ft_map.rbegin()->first << " - ";
	std::cout << ft_map.rbegin()->second << std::endl;
	std::cout << "rend-1: " << (--std_map.rend())->first << " - ";
	std::cout << (--std_map.rend())->second << std::endl;
	std::cout << "rend-1: " << (--ft_map.rend())->first << " - ";
	std::cout << (--ft_map.rend())->second << std::endl;

	std::cout  << std::endl << "- Capacity: " << std::endl;
	std::cout << "size: " << std_map.size() << std::endl;
	std::cout << "size: " << ft_map.size() << std::endl;
	std::cout << "max_size: " << std_map.max_size() << std::endl;
	std::cout << "max_size: " << ft_map.max_size() << std::endl;
	std::cout << "empty: " << std_map.empty() << std::endl;
	std::cout << "empty: " << ft_map.empty() << std::endl;

	std::cout << std::endl << "- Element access: " << std::endl << std::endl;
	std::cout << "map[c]: " << std_map['c'] << std::endl;
	std::cout << "map[c]: " << ft_map['c'] << std::endl;

	std::cout << std::endl << "- Modifiers: " << std::endl;
	std::cout << std::endl << "insert: " << std::endl;
	std_map.insert(std::pair<char, std::string>('e', "echo"));
	ft_map.insert(ft::pair<char, std::string>('e', "echo"));
	print_map(std_map, ft_map);

	std::cout << "erase begin+1: " << std::endl;
	std_map.erase(++std_map.begin());
	ft_map.erase(++ft_map.begin());
	print_map(std_map, ft_map);

	std::cout << "swap: " << std::endl;
	std::map<char, std::string> std_map2;
	ft::map<char, std::string> ft_map2;
	std_map2['f'] = "foxtrot";
	ft_map2['f'] = "foxtrot";
	std_map.swap(std_map2);
	ft_map.swap(ft_map2);
	print_map(std_map, ft_map);

	std::cout << "clear: " << std::endl;
	std_map.clear();
	ft_map.clear();
	print_map(std_map, ft_map);
	std_map.swap(std_map2);
	ft_map.swap(ft_map2);


	std::cout << std::endl << "- Observers: " << std::endl << std::endl;

	char std_first = std_map.begin()->first;
	char ft_first = ft_map.begin()->first;

	std::cout << "key compare 'a': " << std_map.key_comp()(std_first, 'a') << std::endl;
	std::cout << "key compare 'a': " << ft_map.key_comp()(ft_first, 'a') << std::endl;
	std::cout << "key compare 'b': " << std_map.key_comp()(std_first, 'b') << std::endl;
	std::cout << "key compare 'b': " << ft_map.key_comp()(ft_first, 'b') << std::endl;

	std::pair<char, std::string> std_p1 ('a', "alpha");
	std::pair<char, std::string> std_p2 = *std_map.begin();
	std::pair<char, std::string> std_p3 = *std_map.rbegin();

	ft::pair<char, std::string> ft_p1 ('a', "alpha");
	ft::pair<char, std::string> ft_p2 = *ft_map.begin();
	ft::pair<char, std::string> ft_p3 = *ft_map.rbegin();
	
	std::cout << "value compare: " << std_map.value_comp()(std_p1, std_p2) << std::endl;
	std::cout << "value compare: " << ft_map.value_comp()(ft_p1, ft_p2) << std::endl;
	std::cout << "value compare: " << std_map.value_comp()(std_p1, std_p3) << std::endl;
	std::cout << "value compare: " << ft_map.value_comp()(ft_p1, ft_p3) << std::endl;

	std::cout << std::endl << "- Operations: " << std::endl << std::endl;

	print_map(std_map, ft_map);

	std::cout << "find c: " << std_map.find('c')->second << std::endl;
	std::cout << "find c: " << ft_map.find('c')->second << std::endl;

	std::cout << "count d: " << std_map.count('d') << std::endl;
	std::cout << "count d: " << ft_map.count('d') << std::endl;

	std::cout << "lower bound c: " << std_map.lower_bound('c')->second << std::endl;
	std::cout << "lower bound c: " << ft_map.lower_bound('c')->second << std::endl;
	std::cout << "upper bound c: " << std_map.upper_bound('c')->second << std::endl;
	std::cout << "upper bound c: " << ft_map.upper_bound('c')->second << std::endl;

	std::cout << "equal_range e: " << std_map.equal_range('e').first->second << std::endl;
	std::cout << "equal_range e: " << ft_map.equal_range('e').first->second << std::endl;

}