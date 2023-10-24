// Aveva_task2.cpp 
// Daniel Kiska
// 02.08.2023

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Solution {
private:
	//My custom data type to use 20-bit integers
	struct Int20 {
		unsigned int value : 20; // Use 20 bits to store the value
		Int20(unsigned int val) : value(val) {}
	};

	Int20 add20BitIntegers(Int20 a, Int20 b) {
		// Perform addition
		unsigned int sum = a.value + b.value;

		// Check if the sum exceeds 20 bits and throw an exception
		if (sum >= (1 << 20)) {
			throw runtime_error("Result exceeds 20-bit representation.");
		}

		return Int20(sum);
	}

	Int20 convertTo20Bit(int normalInt) {
		// Changing the value to 20 bits using a bitmask
		unsigned int truncatedValue = normalInt & ((1 << 20) - 1);

		return Int20(truncatedValue);
	}

	Int20 subtract20BitIntegers(Int20 a, Int20 b) {
		// Perform subtraction
		unsigned int difference = a.value - b.value;

		// Check if the result is negative
		if (b.value > a.value) {
			throw std::runtime_error("Negative result not allowed for 20-bit integers.");
		}

		return Int20(difference);
	}

	void print20BitStack(std::stack<Int20>& intStack) {
		cout << "Stack contents: ";

		// Create a temporary stack to preserve the original order
		stack<Int20> tempStack = intStack;

		// Pop and print the elements from the temporary stack
		while (!tempStack.empty()) {
			std::cout << tempStack.top().value << " ";
			tempStack.pop();
		}
		cout << "\n";
	}

	//Machine stack
	stack <Int20> mystack;

	//Methods to keep it more organized and for better error handling
	void POP() {
		if(mystack.size() >= 1) {
		mystack.pop();
		}
		else {
			throw invalid_argument("Stack is to small to perform remove operation");
		}
	}
	void DUP() {
		if (mystack.size() >= 1) {
		Int20 x = mystack.top();
		mystack.push(x);
		}
		else {
			throw invalid_argument("Stack is to small to perform duplication operation");
		}
	}
	void PLUS() {
		if (mystack.size() >= 2) {
			Int20 x = mystack.top();
			mystack.pop();
			Int20 y = mystack.top();
			mystack.pop();
			Int20 z = add20BitIntegers(x, y);
			mystack.push(z);
		}
		else {
			throw invalid_argument("Stack is to small to perform addition operation");
		}
	}
	void MINUS() {
		if (mystack.size() >= 2) {
			Int20 x = mystack.top();
			mystack.pop();
			Int20 y = mystack.top();
			mystack.pop();
			Int20 z = subtract20BitIntegers(x, y);
			mystack.push(z);
		}
		else {
			throw invalid_argument("Stack is to small to perform substraction operation");
		}
	}

public:
	int solution(string S) {
		//Clearing stack
		while (!mystack.empty()) {
			mystack.pop();
		}

		try {
			//Creating tokens from argument
			string token;
			vector<string> v;
			stringstream ss(S);
			while (getline(ss, token, ' ')) {
				v.push_back(token);
			}
			//Iterating commands
			for (auto&& item : v) {
				if (item == "POP") { POP(); }
				else if (item == "DUP") { DUP(); }
				else if (item == "+") { PLUS(); }
				else if (item == "-") { MINUS(); }
				else {
					//Change String to int
					int number = stoi(item);
					//Additional check for the argument
					if (number > 1048575 || number < 0) {
						throw invalid_argument("\n Number provided in argument is not in the 20-bit range");
					}
					mystack.push(number);
				}
				//For debug
				print20BitStack(mystack);
			}
			if (mystack.empty()) {
				throw invalid_argument("\n Provided arguments resulted in empty stack, please provide correct arguments\n");
			}
			else {
				//Result from the machine converted to int 
				Int20 num(mystack.top());
				unsigned int result = num.value;
				return result;
			}
		}
		catch (invalid_argument& e) {
			cerr << "Error: " << e.what() << endl;
			return -1;
		}
		catch (const runtime_error& e) {
			cerr << "Runtime error: " << e.what() << std::endl;
			return -1;
		}
		return -1;
	}
};

int main()
{
	static Solution machine;
	int result;

	//Provided test cases
	const string test1 = "4 5 6 - 7 +";//8
	const string test2 = "13 DUP 4 POP 5 DUP + DUP + -";//7
	const string test3 = "5 6 + -";//-1
	const string test4 = "3 DUP 5 - -";//-1
	const string test5 = "1048575 DUP +";//-1

	//Additional tests
	const string test6 = "4 5 6 - 7 + 32423 -63254";
	const string test7 = "13 DUP 4 POP 5 DUP + DUP + - 5 675657 234234 6786";
	const string test8 = "9999999 DUP +";
	const string test9 = "100 100 - -";
	const string test10 = "5 5 5 5 5 5 5 5 5 5 + + + + + + + + +";

	//Printing results
	cout << "\n ====== Test 1 ====== \n";
	result = machine.solution(test1);
	cout << "\n machine result is: " << result << "\n";

	cout << "\n ====== Test 2 ====== \n";
	result = machine.solution(test2);
	cout << "\n machine result is: " << result << "\n";

	cout << "\n ====== Test 3 ====== \n";
	result = machine.solution(test3);
	cout << "\n machine result is: " << result << "\n";

	cout << "\n ====== Test 4 ====== \n";
	result = machine.solution(test4);
	cout << "\n machine result is: " << result << "\n";

	cout << "\n ====== Test 5 ====== \n";
	result = machine.solution(test5);
	cout << "\n machine result is: " << result << "\n";

	//Additional tests
	cout << "\n ====== Test 6 ====== \n";
	result = machine.solution(test6);
	cout << "\n machine result is: " << result << "\n";

	cout << "\n ====== Test 7 ====== \n";
	result = machine.solution(test7);
	cout << "\n machine result is: " << result << "\n";

	cout << "\n ====== Test 8 ====== \n";
	result = machine.solution(test8);
	cout << "\n machine result is: " << result << "\n";

	cout << "\n ====== Test 9 ====== \n";
	result = machine.solution(test9);
	cout << "\n machine result is: " << result << "\n";

	cout << "\n ====== Test 10 ====== \n";
	result = machine.solution(test10);
	cout << "\n machine result is: " << result << "\n";

	return 0;
}
