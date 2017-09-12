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
	char ope;
	int x, y;
	while (!map.result()) {
		cout << "Please input the operation and the coordinate of block\n"
			 << "eg: (t 1 3 or m 3 9)\n"
			 << "-> ";
		cin >> ope >> x >> y;
		if (ope == 't') {
			map.touch(x, y);
		} else if (ope == 'm') {
			map.mark(x, y);
		}	
		map.print();
	}

	return 0;
}