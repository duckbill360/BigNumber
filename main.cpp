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
#include <algorithm>

#include "BigNumber.hpp"
//

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
