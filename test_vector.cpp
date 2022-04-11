#include "Vector.hpp"
#include <vector>

#include <string>
#include <iostream>

void print_Vectors(std::vector<int> std_vec, ft::Vector<int> ft_vec)
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

void print_str(std::vector<std::string> std_vec, ft::Vector<std::string> ft_vec)
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

int main()
{
	std::cout << "-------- Int Vector ----------" << std::endl;
	
	std::cout << std::endl << "- Constructors: " << std::endl;
	std::vector<int> std_vec0;
	ft::Vector<int> ft_vec0;
	print_Vectors(std_vec0, ft_vec0);

	std::vector<int> std_vec(10);
	ft::Vector<int> ft_vec(10);
	print_Vectors(std_vec, ft_vec);

	std::vector<int> std_vec1(10, 21);
	ft::Vector<int> ft_vec1(10, 21);
	print_Vectors(std_vec1, ft_vec1);

	std::cout << std::endl << "- Capacity: " << std::endl;
	std::cout << std::endl;
	std::cout << "size: " << std_vec.size() << std::endl;
	std::cout << "size: " << ft_vec.size() << std::endl;
	std::cout << "capacity: " << std_vec.capacity() << std::endl;
	std::cout << "capacity: " << ft_vec.capacity() << std::endl;
	std::cout << "empty: " << std_vec.empty() << std::endl;
	std::cout << "empty: " << ft_vec.empty() << std::endl;

	std::cout << "resize 20 " << std::endl;
	std_vec.resize(20);
	ft_vec.resize(20);
	std::cout << "now size: " << std_vec.size() << std::endl;
	std::cout << "now size: " << ft_vec.size() << std::endl;
	std::cout << "reserve 30 " << std::endl;
	std_vec.reserve(30);
	ft_vec.reserve(30);
	std::cout << "now capacity: " << std_vec.capacity() << std::endl;
	std::cout << "now capacity: " << ft_vec.capacity() << std::endl;
	

	std::cout << std::endl << "- Modifiers: " << std::endl;

	std::cout << std::endl << "assign: " << std::endl;
	std_vec.assign(7, 10);
	ft_vec.assign(7, 10);
	print_Vectors(std_vec, ft_vec);

	std::cout << "push_back: " << std::endl;
	std_vec.push_back(1);
	std_vec.push_back(2);
	std_vec.push_back(3);
	ft_vec.push_back(1);
	ft_vec.push_back(2);
	ft_vec.push_back(3);
	print_Vectors(std_vec, ft_vec);

	std::cout << "pop_back: " << std::endl;
	std_vec.pop_back();
	ft_vec.pop_back();
	print_Vectors(std_vec, ft_vec);

	std::cout << "insert: " << std::endl;
	std_vec.insert(std_vec.begin() + 1, 5);
	ft_vec.insert(ft_vec.begin() + 1, 5);
	print_Vectors(std_vec, ft_vec);
	
	std::cout << "insert: " << std::endl;
	std_vec.insert(std_vec.begin() + 5, 10, 5);
	ft_vec.insert(ft_vec.begin() + 5, 10, 5);
	print_Vectors(std_vec, ft_vec);

	std::cout << "erase: " << std::endl;
	std_vec.erase(std_vec.begin() + 2, std_vec.end() - 2);
	ft_vec.erase(ft_vec.begin() + 2, ft_vec.end() - 2);
	print_Vectors(std_vec, ft_vec);

	std::cout << std::endl << "- Iterators: " << std::endl;
	std::cout << "begin: " << *std_vec.begin() << std::endl;
	std::cout << "begin: " << *ft_vec.begin() << std::endl;
	std::cout << "end-1: " << *(--std_vec.end()) << std::endl;
	std::cout << "end-1: " << *(--ft_vec.end()) << std::endl;
	std::cout << "rbegin: " << *std_vec.rbegin() << std::endl;
	std::cout << "rbegin: " << *ft_vec.rbegin() << std::endl;
	std::cout << "rend-1: " << *(--std_vec.rend()) << std::endl;
	std::cout << "rend-1: " << *(--ft_vec.rend()) << std::endl;

	std::cout << std::endl << "swap with \"100\": " << std::endl;
	std_vec0.push_back(100);
	ft_vec0.push_back(100);
	std_vec.swap(std_vec0);
	ft_vec.swap(ft_vec0);
	print_Vectors(std_vec, ft_vec);

	std::cout << "clear: " << std::endl;
	std_vec.clear();
	ft_vec.clear();
	print_Vectors(std_vec, ft_vec);
	std_vec.swap(std_vec0);
	ft_vec.swap(ft_vec0);

	std::cout << std::endl << "- Element access: " << std::endl;
	print_Vectors(std_vec, ft_vec);
	std::cout << std::endl;
	std::cout << "Operator[1]: " << std_vec[1] << std::endl;
	std::cout << "Operator[1]: " << ft_vec[1] << std::endl;
	std::cout << "at[2]: " << std_vec.at(2) << std::endl;
	std::cout << "at[2]: " << ft_vec.at(2) << std::endl;
	std::cout << "front: " << std_vec.front() << std::endl;
	std::cout << "front: " << ft_vec.front() << std::endl;
	std::cout << "back: " << std_vec.back() << std::endl;
	std::cout << "back: " << ft_vec.back() << std::endl;


	std::cout << std::endl << "-------- String Vector ----------" << std::endl;
	
	std::cout << std::endl << "- Constructors: " << std::endl;
	std::vector<std::string> std_str0;
	ft::Vector<std::string> ft_str0;
	print_str(std_str0, ft_str0);

	std::vector<std::string> std_str(2);
	ft::Vector<std::string> ft_str(2);
	print_str(std_str, ft_str0);

	std::cout << std::endl << "- Capacity: " << std::endl;
	std::cout << std::endl;
	std::cout << "size: " << std_str.size() << std::endl;
	std::cout << "size: " << ft_str.size() << std::endl;
	std::cout << "capacity: " << std_str.capacity() << std::endl;
	std::cout << "capacity: " << ft_str.capacity() << std::endl;
	std::cout << "empty: " << std_str.empty() << std::endl;
	std::cout << "empty: " << ft_str.empty() << std::endl;

	std::cout << "resize 20 " << std::endl;
	std_vec.resize(20);
	ft_vec.resize(20);
	std::cout << "now size: " << std_vec.size() << std::endl;
	std::cout << "now size: " << ft_vec.size() << std::endl;
	std::cout << "reserve 30 " << std::endl;
	std_vec.reserve(30);
	ft_vec.reserve(30);
	std::cout << "now capacity: " << std_vec.capacity() << std::endl;
	std::cout << "now capacity: " << ft_vec.capacity() << std::endl;

	std::cout << std::endl << "- Modifiers: " << std::endl;
	
	std::cout << std::endl << "assign: " << std::endl;
	std_str.assign(3, "hi");
	ft_str.assign(3, "hi");
	print_str(std_str, ft_str);
	
	std::cout << "push_back: " << std::endl;
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

	std::cout << std::endl << "- Iterators: " << std::endl;
	std::cout << "begin: " << *std_str.begin() << std::endl;
	std::cout << "begin: " << *ft_str.begin() << std::endl;
	std::cout << "end-1: " << *(--std_str.end()) << std::endl;
	std::cout << "end-1: " << *(--ft_str.end()) << std::endl;
	std::cout << "rbegin: " << *std_str.rbegin() << std::endl;
	std::cout << "rbegin: " << *ft_str.rbegin() << std::endl;
	std::cout << "rend-1: " << *(--std_str.rend()) << std::endl;
	std::cout << "rend-1: " << *(--ft_str.rend()) << std::endl;
	
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

	std::cout << std::endl << "- Element access: " << std::endl;
	print_str(std_str, ft_str);
	std::cout << std::endl;
	std::cout << "Operator[1]: " << std_str[1] << std::endl;
	std::cout << "Operator[1]: " << ft_str[1] << std::endl;
	std::cout << "at[1]: " << std_str.at(1) << std::endl;
	std::cout << "at[1]: " << ft_str.at(1) << std::endl;
	std::cout << "front: " << std_str.front() << std::endl;
	std::cout << "front: " << ft_str.front() << std::endl;
	std::cout << "back: " << std_str.back() << std::endl;
	std::cout << "back: " << ft_str.back() << std::endl;
}
