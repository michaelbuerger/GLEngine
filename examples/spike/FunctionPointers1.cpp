#include <iostream>

void callFunction(void (*functionPointer)(const char* param1), const char* param1)
{
	(*functionPointer)(param1);
}

void testFunction(const char* str)
{
	std::cout << str << std::endl;
}

int main() {
  callFunction(testFunction, "Hello, World");
}
