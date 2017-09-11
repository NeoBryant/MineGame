//
//	main.cpp
//	MineGame
//	
//	Created by Bryant on 2017/9/7.
//	Copyright @ 2017 Bryant. All rights reserved.
//

#include <iostream>
#include "Map.hpp"
using namespace std;

int main() {
	
	Map map(MIN_SIZE, MINES);
	map.print();

	map.mark(3,3);
	map.print();
	return 0;
}