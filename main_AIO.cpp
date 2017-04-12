//
//  main.cpp
//  BigNumber
//
//  Created by ChengAndy on 2017/2/14.
//  Copyright © 2017年 ChengAndy. All rights reserved.
//

// headers
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

class BigNumber{
	
private:
	
public:
	// number
	std::vector<int> value;	// contain digits (value[0] is the smallest digit)
	int num_of_digits;
	
	// constructor
	BigNumber();
	BigNumber(int length);
	BigNumber(std::string input);
	
	//overloaded arithmetic operators as member functions
	BigNumber operator+(BigNumber input);
	BigNumber operator-(BigNumber input);
	BigNumber operator*(BigNumber input);
	BigNumber operator/(BigNumber input);		//integer division: 3/2==1
	BigNumber operator%(BigNumber input);
	
	BigNumber scalar_mul(int scalar);
	bool isGreaterOrEqual(BigNumber input);
	
	// functions
	void show();
	void trim();
	
};

BigNumber::BigNumber()
{
	value = std::vector<int>(0);
}

int char_to_int(char ch)
{
	int output = 0;
	
	std::stringstream ss;
	ss << ch;
	ss >> std::hex >> output;
	
	return output;
}

BigNumber::BigNumber(int length)
{
	value = std::vector<int>(length);
}

BigNumber::BigNumber(std::string input)
{
	value = std::vector<int>((int)input.size());
	for (int i = 0; i < (int)input.size(); i++)
	{
		value[i] = char_to_int(input[i]);
	}
	std::reverse(value.begin(), value.end());
}

void BigNumber::trim()
{
	while (value.back() == 0 && value.size() > 1) {
		value.pop_back();
	}
}

bool BigNumber::isGreaterOrEqual(BigNumber input)
{
	if (value.size() > input.value.size())
	{
		return true;
	}
	else if (value.size() < input.value.size())
	{
		return false;
	}
	else
	{
		for (int i = (int)value.size() - 1; i >= 0; i--)
		{
			if (value[i] > input.value[i])
			{
				return true;
			}
			else if (value[i] < input.value[i])
			{
				return false;
			}
			else{ }		// if they are the same for the current digit, go on to the next iteration
		}
	}
	
	return 1;
}

BigNumber BigNumber::operator+(BigNumber input)
{
	BigNumber a, b;		// let length(a) > length(b)
	
	if ((int)this->value.size() >= input.value.size())
	{
		a = *this;
		b = input;
	}
	else
	{
		a = input;
		b = *this;
	}
	
	int total_length = (int)a.value.size() + 1;
	BigNumber output = BigNumber(total_length);
	
	// add zeros to the end to length "total_length"
	std::vector<int> zeros_a = std::vector<int>(1);
	std::vector<int> zeros_b = std::vector<int>(total_length - b.value.size());
	a.value.insert(a.value.end(), zeros_a.begin(), zeros_a.end());
	b.value.insert(b.value.end(), zeros_b.begin(), zeros_b.end());
	
	// addition
	for (int i = 0; i < total_length; i++)
	{
		int current = output.value[i] + a.value[i] + b.value[i];
		output.value[i] = current % 16 ;
		int carry = current / 16;
		output.value[i + 1] = carry;
	}
	output.trim();
	
	return output;
}

BigNumber BigNumber::operator*(BigNumber input)
{
	BigNumber output = BigNumber();
	
	for (int i = 0; i < (int)input.value.size(); i++)
	{
		BigNumber vec = this->scalar_mul(input.value[i]);
		
		BigNumber temp = BigNumber();
		temp.value = std::vector<int>(i);	// tailing zeros
		temp.value.insert(temp.value.end(), vec.value.begin(), vec.value.end());
		
		output = output.operator+(temp);
	}
	output.trim();
	return output;
}

BigNumber BigNumber::operator-(BigNumber input)
{
	BigNumber a, b;
	
	// let "a" be the greater number
	if (this->isGreaterOrEqual(input))
	{
		a = *this;
		b = input;
		
		int num = (int)a.value.size() - (int)b.value.size();
		
		// append zeros to "b" to match the length of "a"
		for (int i = 0; i < num; i++)
		{
			b.value.push_back(0);
		}
	}
	else
	{
		a = input;
		b = *this;
		
		// append zeros to "b" to match the length of "a"
		for (int i = 0; i < (int)(a.value.size() - b.value.size()); i++)
		{
			b.value.push_back(0);
		}
	}
	BigNumber output = BigNumber((int)(a.value.size()));
	
	// substraction
	for (int i = 0; i < (int)a.value.size(); i++)
	{
		if (a.value[i] >= b.value[i])
		{
			output.value[i] = a.value[i] - b.value[i];
		}
		else
		{
			int j = i;
			
			// find the closest non-zero digit
			do
			{
				j++;
			} while (a.value[j] == 0);
			
			// borrow 1 from the highest available digit and add to the lower digits
			a.value[j]--;
			
			for (int k = j - 1; k > i; k--)
			{
				a.value[k] += 15;
			}
			a.value[i] += 16;
			
			output.value[i] = a.value[i] - b.value[i];
		}
	}
	
	output.trim();
	return output;
}

BigNumber BigNumber::operator/(BigNumber input)
{
	BigNumber output;
	
	if (!this->isGreaterOrEqual(input))
	{
		return BigNumber("0");
	}
	else
	{
		BigNumber a, b;
		a = *this;
		b = input;
		int max_len = (int)a.value.size() - (int)b.value.size() + 1;
		
		// insert tailing zeros = push in the "front"
		for (int i = 0; i < max_len - 1; i++)
		{
			b.value.insert(b.value.begin(), 0);
		}
		
		std::vector<int> quotient = std::vector<int>(max_len);
		
		// long division
		for (int i = max_len - 1; i >= 0; i--)
		{
			int flag = 0;
			
			for (int j = 0; j < 16; j++)
			{
				if (a.isGreaterOrEqual(b.scalar_mul(j)) && !a.isGreaterOrEqual(b.scalar_mul(j + 1)))
				{
					flag = j;
				}
			}
			
			quotient[i] = flag;
			a = a.operator-(b.scalar_mul(flag));
			
			// delete 1 tailing zero after each iteration (pop front)
			std::reverse(b.value.begin(), b.value.end());
			b.value.pop_back();
			std::reverse(b.value.begin(), b.value.end());
			
		}
		
		output.value = quotient;
		output.trim();
		return output;
	}
}

BigNumber BigNumber::operator%(BigNumber input)
{
	BigNumber quotient = this->operator/(input);
	BigNumber output = this->operator-(input.operator*(quotient));
	
	return output;
}

BigNumber BigNumber::scalar_mul(int scalar)
{
	int total_length = (int)value.size() + 1;
	BigNumber output = BigNumber(total_length);
	
	// multiply each digit and add
	for (int i = 0; i < total_length - 1; i++)
	{
		int current = output.value[i] + scalar * value[i];
		output.value[i] = current % 16;
		output.value[i + 1] = current / 16;		// carry
	}
	output.trim();
	
	return output;
}

void BigNumber::show()
{
	for (int i = (int)value.size() - 1; i >= 0; i--)
	{
		std::cout << std::hex << value[i];
	}
}


using namespace std;

// functions definition
void string_pop_front(string &input);

//

// main()
int main(void) {
	
	// declaration
	string a, b;
	bool a_sign, b_sign;	// "0" for +, "1" for -
	BigNumber A, B;
	
	// get inputs
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	
	// initialize objects with inputs
	// A
	if (a[0] == '-')
	{
		string_pop_front(a);
		A = BigNumber(a);
		a_sign = 1;
	}
	else
	{
		A = BigNumber(a);
		a_sign = 0;
	}
	
	// B
	if (b[0] == '-')
	{
		string_pop_front(b);
		B = BigNumber(b);
		b_sign = 1;
	}
	else
	{
		B = BigNumber(b);
		b_sign = 0;
	}
	//
	
	
	// SHOW RESULTS
	cout << "---------------------------------------------" << endl;
	BigNumber result;
	
	if (a_sign == 0 && b_sign == 0)
	{
		if (A.isGreaterOrEqual(B))
		{
			//		+
			result = A.operator+(B);
			cout << "a + b = "; result.show(); cout << endl;
			//		-
			result = A.operator-(B);
			cout << "a - b = "; result.show(); cout << endl;
			//		*
			result = A.operator*(B);
			cout << "a * b = "; result.show(); cout << endl;
			//		/
			result = A.operator/(B);
			cout << "a / b = "; result.show(); cout << endl;
			//		%
			result = A.operator%(B);
			cout << "a % b = "; result.show(); cout << endl;
		}
		else
		{
			//		+
			result = A.operator+(B);
			cout << "a + b = "; result.show(); cout << endl;
			//		-
			result = A.operator-(B);
			cout << "a - b = -"; result.show(); cout << endl;
			//		*
			result = A.operator*(B);
			cout << "a * b = "; result.show(); cout << endl;
			//		/
			result = A.operator/(B);
			cout << "a / b = "; result.show(); cout << endl;
			//		%
			result = A.operator%(B);
			cout << "a % b = "; result.show(); cout << endl;
		}
	}
	else if (a_sign == 0 && b_sign == 1)
	{
		if (A.isGreaterOrEqual(B))
		{
			//		+
			result = A.operator-(B);
			cout << "a + b = "; result.show(); cout << endl;
			//		-
			result = A.operator+(B);
			cout << "a - b = "; result.show(); cout << endl;
			//		*
			result = A.operator*(B);
			cout << "a * b = -"; result.show(); cout << endl;
			//		/
			result = A.operator/(B);
			cout << "a / b = -"; result.show(); cout << endl;
			//		%
			result = A.operator%(B);
			cout << "a % b = "; result.show(); cout << endl;
		}
		else
		{
			//		+
			result = A.operator-(B);
			cout << "a + b = -"; result.show(); cout << endl;
			//		-
			result = A.operator+(B);
			cout << "a - b = "; result.show(); cout << endl;
			//		*
			result = A.operator*(B);
			cout << "a * b = -"; result.show(); cout << endl;
			//		/
			result = A.operator/(B);
			cout << "a / b = "; result.show(); cout << endl;
			//		%
			result = A.operator%(B);
			cout << "a % b = "; result.show(); cout << endl;
		}
	}
	else if (a_sign == 1 && b_sign == 0)
	{
		if (A.isGreaterOrEqual(B))
		{
			//		+
			result = A.operator-(B);
			cout << "a + b = -"; result.show(); cout << endl;
			//		-
			result = A.operator+(B);
			cout << "a - b = -"; result.show(); cout << endl;
			//		*
			result = A.operator*(B);
			cout << "a * b = -"; result.show(); cout << endl;
			//		/
			result = A.operator/(B);
			cout << "a / b = -"; result.show(); cout << endl;
			//		%
			result = A.operator%(B);
			cout << "a % b = -"; result.show(); cout << endl;
		}
		else
		{
			//		+
			result = A.operator-(B);
			cout << "a + b = "; result.show(); cout << endl;
			//		-
			result = A.operator+(B);
			cout << "a - b = -"; result.show(); cout << endl;
			//		*
			result = A.operator*(B);
			cout << "a * b = -"; result.show(); cout << endl;
			//		/
			result = A.operator/(B);
			cout << "a / b = -"; result.show(); cout << endl;
			//		%
			result = A.operator%(B);
			cout << "a % b = -"; result.show(); cout << endl;
		}
	}
	else if (a_sign == 1 && b_sign == 1)
	{
		if (A.isGreaterOrEqual(B))
		{
			//		+
			result = A.operator+(B);
			cout << "a + b = -"; result.show(); cout << endl;
			//		-
			result = A.operator-(B);
			cout << "a - b = -"; result.show(); cout << endl;
			//		*
			result = A.operator*(B);
			cout << "a * b = "; result.show(); cout << endl;
			//		/
			result = A.operator/(B);
			cout << "a / b = "; result.show(); cout << endl;
			//		%
			result = A.operator%(B);
			cout << "a % b = -"; result.show(); cout << endl;
		}
		else
		{
			//		+
			result = A.operator+(B);
			cout << "a + b = -"; result.show(); cout << endl;
			//		-
			result = A.operator-(B);
			cout << "a - b = "; result.show(); cout << endl;
			//		*
			result = A.operator*(B);
			cout << "a * b = "; result.show(); cout << endl;
			//		/
			result = A.operator/(B);
			cout << "a / b = "; result.show(); cout << endl;
			//		%
			result = A.operator%(B);
			cout << "a % b = -"; result.show(); cout << endl;
		}
	}
	
	return 0;
}
//

// function implementation
void string_pop_front(string &input)
{
	reverse(input.begin(), input.end());
	input.pop_back();
	reverse(input.begin(), input.end());
}

//
