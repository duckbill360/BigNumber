//
//  BigNumber.hpp
//  BigNumber
//
//  Created by ChengAndy on 2017/2/14.
//  Copyright © 2017年 ChengAndy. All rights reserved.
//

#ifndef BigNumber_hpp
#define BigNumber_hpp

#include <vector>

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

#endif /* BigNumber_hpp */
