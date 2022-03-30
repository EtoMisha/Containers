#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include <vector>
#include <stack>
#include <map>

#include <string>
#include <iostream>

void print_vectors(std::vector<int> std_vec, ft::vector<int> ft_vec)
{
	std::cout << "    ";
	for (int i = 0; i < (int)std_vec.size(); i++)
	{
		std::cout << std_vec[i] << " ";
	}
	std::cout << std::endl << "    ";
	for (int i = 0; i < (int)ft_vec.size(); i++)
	{
		std::cout << ft_vec[i] << " ";
	}
	std::cout << std::endl;
}

void print_str(std::vector<std::string> std_vec, ft::vector<std::string> ft_vec)
{
	std::cout << "    ";
	for (int i = 0; i < (int)std_vec.size(); i++)
	{
		std::cout << std_vec[i] << " ";
	}
	std::cout << std::endl << "    ";
	for (int i = 0; i < (int)ft_vec.size(); i++)
	{
		std::cout << ft_vec[i] << " ";
	}
	std::cout << std::endl;
}

void print_stack_int(std::stack<int> std_stack, ft::stack<int> ft_stack)
{
	std::cout << "    ";
	while (std_stack.size() > 0)
	{
		std::cout << std_stack.top() << " ";
		std_stack.pop();
	}
	std::cout << std::endl << "    ";
	while (ft_stack.size() > 0)
	{
		std::cout << ft_stack.top() << " ";
		ft_stack.pop();
	}
	std::cout << std::endl;
}

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
	std::cout << "-------- Int vector ----------" << std::endl;
	
	//	Constructors
	std::cout << "Constructors: " << std::endl;
	std::vector<int> std_vec0;
	ft::vector<int> ft_vec0;
	print_vectors(std_vec0, ft_vec0);

	std::vector<int> std_vec(10);
	ft::vector<int> ft_vec(10);
	print_vectors(std_vec, ft_vec);

	std::vector<int> std_vec1(10, 21);
	ft::vector<int> ft_vec1(10, 21);
	print_vectors(std_vec1, ft_vec1);

	//	Capacity
	std::cout << std::endl;
	std::cout << "size: " << std_vec.size() << std::endl;
	std::cout << "size: " << ft_vec.size() << std::endl;

	std::cout << "max_size: " << std_vec.max_size() << std::endl;
	std::cout << "max_size: " << ft_vec.max_size() << std::endl;

	std::cout << "capacity: " << std_vec.capacity() << std::endl;
	std::cout << "capacity: " << ft_vec.capacity() << std::endl;

	std::cout << "empty: " << std_vec.empty() << std::endl;
	std::cout << "empty: " << ft_vec.empty() << std::endl;

	//	Modifiers
	std::cout << std::endl << "push_back: " << std::endl;
	std_vec.push_back(1);
	std_vec.push_back(2);
	std_vec.push_back(3);
	ft_vec.push_back(1);
	ft_vec.push_back(2);
	ft_vec.push_back(3);
	print_vectors(std_vec, ft_vec);

	std::cout << "pop_back: " << std::endl;
	std_vec.pop_back();
	ft_vec.pop_back();
	print_vectors(std_vec, ft_vec);

	std::cout << "insert: " << std::endl;
	std_vec.insert(std_vec.begin() + 1, 5);
	ft_vec.insert(ft_vec.begin() + 1, 5);
	print_vectors(std_vec, ft_vec);
	
	std::cout << "insert: " << std::endl;
	std_vec.insert(std_vec.begin() + 5, 10, 5);
	ft_vec.insert(ft_vec.begin() + 5, 10, 5);
	print_vectors(std_vec, ft_vec);

	std::cout << "erase: " << std::endl;
	std_vec.erase(std_vec.begin() + 2, std_vec.end() - 2);
	ft_vec.erase(ft_vec.begin() + 2, ft_vec.end() - 2);
	print_vectors(std_vec, ft_vec);

	std::cout << "swap with \"100\": " << std::endl;
	std_vec0.push_back(100);
	ft_vec0.push_back(100);
	std_vec.swap(std_vec0);
	ft_vec.swap(ft_vec0);
	print_vectors(std_vec, ft_vec);

	std::cout << "clear: " << std::endl;
	std_vec.clear();
	ft_vec.clear();
	print_vectors(std_vec, ft_vec);
	std_vec.swap(std_vec0);
	ft_vec.swap(ft_vec0);

	// Element access
	std::cout << std::endl;
	std::cout << "Operator[1]: " << std_vec[1] << std::endl;
	std::cout << "Operator[1]: " << ft_vec[1] << std::endl;

	std::cout << "at[2]: " << std_vec.at(2) << std::endl;
	std::cout << "at[2]: " << ft_vec.at(2) << std::endl;

	std::cout << "front: " << std_vec.front() << std::endl;
	std::cout << "front: " << ft_vec.front() << std::endl;

	std::cout << "back: " << std_vec.back() << std::endl;
	std::cout << "back: " << ft_vec.back() << std::endl;



	std::cout << std::endl << "-------- String vector ----------" << std::endl;
	//	Constructors
	std::cout << "Constructors: " << std::endl;
	std::vector<std::string> std_str0;
	ft::vector<std::string> ft_str0;
	print_str(std_str0, ft_str0);

	std::vector<std::string> std_str(2);
	ft::vector<std::string> ft_str(2);
	print_str(std_str, ft_str0);

	//	Capacity
	std::cout << std::endl;
	std::cout << "size: " << std_str.size() << std::endl;
	std::cout << "size: " << ft_str.size() << std::endl;

	std::cout << "max_size: " << std_str.max_size() << std::endl;
	std::cout << "max_size: " << ft_str.max_size() << std::endl;

	std::cout << "capacity: " << std_str.capacity() << std::endl;
	std::cout << "capacity: " << ft_str.capacity() << std::endl;

	std::cout << "empty: " << std_str.empty() << std::endl;
	std::cout << "empty: " << ft_str.empty() << std::endl;

	// Modifiers
	std::cout << std::endl << "push_back: " << std::endl;
	std_str.push_back("hello");
	std_str.push_back("lol");
	ft_str.push_back("hello");
	ft_str.push_back("lol");
	print_str(std_str, ft_str);

	std::cout << "pop_back: " << std::endl;
	std_str.pop_back();
	ft_str.pop_back();
	print_str(std_str, ft_str);

	std::cout << "insert: " << std::endl;
	std_str.insert(std_str.begin(), "kek");
	ft_str.insert(ft_str.begin(), "kek");
	print_str(std_str, ft_str);
	
	std::cout << "insert: " << std::endl;
	std_str.insert(std_str.begin() + 1, 4, "lol");
	ft_str.insert(ft_str.begin() + 1, 4, "lol");
	print_str(std_str, ft_str);

	std::cout << "erase: " << std::endl;
	std_str.erase(std_str.begin() + 1, std_str.end() - 1);
	ft_str.erase(ft_str.begin() + 1, ft_str.end() - 1);
	print_str(std_str, ft_str);

	std::cout << "swap with \"hi\": " << std::endl;
	std_str0.push_back("hi");
	ft_str0.push_back("hi");
	std_str.swap(std_str0);
	ft_str.swap(ft_str0);
	print_str(std_str, ft_str);

	std::cout << "clear: " << std::endl;
	std_str.clear();
	ft_str.clear();
	print_str(std_str, ft_str);
	std_str.swap(std_str0);
	ft_str.swap(ft_str0);

	// Element access
	std::cout << std::endl;
	std::cout << "Operator[0]: " << std_str[0] << std::endl;
	std::cout << "Operator[0]: " << ft_str[0] << std::endl;

	std::cout << "at[1]: " << std_str.at(1) << std::endl;
	std::cout << "at[1]: " << ft_str.at(1) << std::endl;

	std::cout << "front: " << std_str.front() << std::endl;
	std::cout << "front: " << ft_str.front() << std::endl;

	std::cout << "back: " << std_str.back() << std::endl;
	std::cout << "back: " << ft_str.back() << std::endl;


	std::cout << std::endl << "-------- Stack ----------" << std::endl;

	//	Constructors
	std::cout << "Constructors: " << std::endl;
	std::stack<int> std_stack;
	ft::stack<int> ft_stack;
	print_stack_int(std_stack, ft_stack);

	std::cout << "push: " << std::endl;
	std_stack.push(2);
	std_stack.push(4);
	std_stack.push(6);
	std_stack.push(8);
	std_stack.push(10);
	ft_stack.push(2);
	ft_stack.push(4);
	ft_stack.push(6);
	ft_stack.push(8);
	ft_stack.push(10);
	print_stack_int(std_stack, ft_stack);

	std::cout << "pop: " << std::endl;
	std_stack.pop();
	ft_stack.pop();
	print_stack_int(std_stack, ft_stack);

	std::cout << "size: " << std_stack.size() << std::endl;
	std::cout << "size: " << ft_stack.size() << std::endl;

	std::cout << "empty: " << std_stack.empty() << std::endl;
	std::cout << "empty: " << ft_stack.empty() << std::endl;

	std::cout << "top: " << std_stack.top() << std::endl;
	std::cout << "top: " << ft_stack.top() << std::endl;



	std::cout << std::endl << "-------- Map ----------" << std::endl;

	std::map<char, std::string> std_map;
	ft::map<char, std::string> ft_map;

	std_map['a'] = "alpha";
	std_map['b'] = "beta";
	std_map['c'] = "charly";

	ft_map['a'] = "alpha";
	ft_map['b'] = "beta";
	ft_map['c'] = "charly";

	print_map(std_map, ft_map);

	std::cout << "begin: " << std_map.begin()->first << " - ";
	std::cout << std_map.begin()->second << std::endl;
	std::cout << "begin: " << ft_map.begin()->first << " - ";
	std::cout << ft_map.begin()->second << std::endl;

	std::cout << "end - 1: " << (--std_map.end())->first << " - ";
	std::cout << (--std_map.end())->second << std::endl;
	std::cout << "end - 1: " << (--ft_map.end())->first << " - ";
	std::cout << (--ft_map.end())->second << std::endl;

		std::cout << "size: " << std_map.size() << std::endl;
	std::cout << "size: " << ft_map.size() << std::endl;

	std::cout << "empty: " << std_map.empty() << std::endl;
	std::cout << "empty: " << ft_map.empty() << std::endl;

	std::cout << "map[c]: " << std_map['c'] << std::endl;
	std::cout << "map[c]: " << ft_map['c'] << std::endl;

	std::cout << std::endl << "insert: " << std::endl;
	std_map.insert(std::pair<char, std::string>('d', "delta"));
	ft_map.insert(ft::pair<char, std::string>('d', "delta"));
	print_map(std_map, ft_map);

	std::cout << "erase begin+1: " << std::endl;
	std_map.erase(++std_map.begin());
	ft_map.erase(++ft_map.begin());
	print_map(std_map, ft_map);

	std::cout << "clear: " << std::endl;
	std_map.clear();
	ft_map.clear();
	print_map(std_map, ft_map);

}

