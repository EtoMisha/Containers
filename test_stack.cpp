#include "Stack.hpp"
#include <stack>
#include <string>
#include <iostream>

void print_stack_int(std::stack<int> std_stack, ft::Stack<int> ft_stack)
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

int main()
{
	std::cout << std::endl << "-------- Stack ----------" << std::endl;

	std::cout << "Constructors: " << std::endl;
	std::stack<int> std_stack;
	ft::Stack<int> ft_stack;
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

}