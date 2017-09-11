//
//	Map.hpp
//	MineGame
//	
//	Created by Bryant on 2017/9/7.
//	Copyright @ 2017 Bryant. All rights reserved.
//

#ifndef SYMBOL
#define SYMBOL value

#include <iostream>
#include <cstdlib>
#include <ctime>

#define MIN_SIZE 9
#define MIDIUM_SIZE 16
#define MAX_SIZE 25
#define MINES 10
#define random(x) (rand()%x)
using namespace std;

struct Block
{
	bool isMine = false; //whether it is a mine or not
	bool isAppeared = false; //whether it is appeared
	bool isMarked = false; //whether it is marked
	int numOfAroundMines = 0; //the number of mines around the block
};


class Map
{
public:
	//constructor and destructor
	Map();
	Map(const int Size, const int Number);
	~Map();

	//operation fuctions

	//touch a block.-1->touch a mine,0->no touch,1->successful touch
	int touch(const int x, const int y); 
	bool mark(const int x, const int y); //mark a block as a mine
	void setMines(); //set mines on the map

	//appear the map
	void print();
	void tag(); //like a tag in Java

private:	
	Block **m_map; //the map
	int m_size; //the size of the map
	int m_mines; //the number of mines
	int m_marked; //the number of blocks that is marked
	int m_step; //the number of step that the user used
	bool isGG; //whether the game is over
};

Map::Map() {
	m_size = 0;
	m_mines = 0;
	m_map = NULL;
	isGG = false;
	m_step = 0;
	m_marked = 0;
}

Map::Map(const int Size, const int Number) {
	m_size = Size;
	m_mines = Number;
	isGG = false;
	m_step = 0;
	m_marked = 0;
	m_map = new Block*[m_size];
	for (int i = 0; i < m_size; ++i) {
		m_map[i] = new Block[m_size];
	}

	setMines();
}

Map::~Map() {
	for (int i = 0; i < m_size; ++i) {
		delete m_map[i];
		m_map[i] = NULL;
	}
	delete []m_map;
	m_map = NULL;
}

int Map::touch(const int x, const int y) {
	if (m_map[x-1][y-1].isAppeared || m_map[x-1][y-1].isMarked) {
		isGG = true;
		return 0;
	} else {
		if (m_map[x-1][y-1].isMine) { 
			return -1;
		} else {
			m_map[x-1][y-1].isAppeared = true;
		}
		++m_step;
	}
	// a important function 
	//.....

	return 1;
}

bool Map::mark(const int x, const int y) {
	if (m_map[x-1][y-1].isAppeared) {
		return false;
	} else {
		if (m_map[x-1][y-1].isMarked) {
			m_map[x-1][y-1].isMarked = false;
			--m_marked;
		} else {
			m_map[x-1][y-1].isMarked = true;
			++m_marked;
		}
		++m_step;
	}
	return true;
}

void Map::setMines() {
	int *randomNumber = new int[m_mines];
	bool isExisted = false;
//	cout << "**";

	//get (Number) index of mines which are totally different
	srand((unsigned)time(NULL));
	for (int count = 0; count < m_mines; ) {
		int num = random(m_size*m_size/2)+random(m_size*m_size/2);
		isExisted = false;

		//check if num has existed
		for (int i = 0; i < count; ++i) {
			if (randomNumber[i] == num) {
				isExisted = true;
				break;
			}
		}

		//if num is a new one, sign it
		if (!isExisted) {
			randomNumber[count++] = num;
		}
	}

	for (int i = 0; i < m_mines; ++i) {
		int x = randomNumber[i] % m_size;
		int y = randomNumber[i] / m_size;
		m_map[x][y].isMine = true;
	}
	

	//mark the block with the number of mines around them
	if (m_map[0][1].isMine) ++m_map[0][0].numOfAroundMines;
	if (m_map[1][0].isMine) ++m_map[0][0].numOfAroundMines;

	if (m_map[0][m_size-2].isMine) ++m_map[0][m_size-1].numOfAroundMines;
	if (m_map[1][m_size-1].isMine) ++m_map[0][m_size-1].numOfAroundMines;

	if (m_map[m_size-2][0].isMine) ++m_map[m_size-1][0].numOfAroundMines;
	if (m_map[m_size-1][1].isMine) ++m_map[m_size-1][0].numOfAroundMines;

	if (m_map[m_size-2][m_size-1].isMine) ++m_map[m_size-1][m_size-1].numOfAroundMines;
	if (m_map[m_size-1][m_size-2].isMine) ++m_map[m_size-1][m_size-1].numOfAroundMines;


	for (int i = 1; i < m_size-1; ++i) {
		if (m_map[0][i-1].isMine) ++m_map[0][i].numOfAroundMines;
		if (m_map[0][i+1].isMine) ++m_map[0][i].numOfAroundMines;

		if (m_map[m_size-1][i-1].isMine) ++m_map[m_size-1][i].numOfAroundMines;
		if (m_map[m_size-1][i+1].isMine) ++m_map[m_size-1][i].numOfAroundMines;

		if (m_map[i-1][0].isMine) ++m_map[i][0].numOfAroundMines;	
		if (m_map[i+1][0].isMine) ++m_map[i][0].numOfAroundMines;	

		if (m_map[i-1][m_size-1].isMine) ++m_map[i][m_size-1].numOfAroundMines;	
		if (m_map[i+1][m_size-1].isMine) ++m_map[i][m_size-1].numOfAroundMines;		
	}

	for (int x = 1; x < m_size-1; ++x) {
		for (int y = 1; y < m_size-1; ++y) {
			if (!m_map[x][y].isMine) {
				if (m_map[x+1][y].isMine) ++m_map[x][y].numOfAroundMines;
				if (m_map[x-1][y].isMine) ++m_map[x][y].numOfAroundMines;
				if (m_map[x][y+1].isMine) ++m_map[x][y].numOfAroundMines;
				if (m_map[x][y-1].isMine) ++m_map[x][y].numOfAroundMines;
				if (m_map[x+1][y+1].isMine) ++m_map[x][y].numOfAroundMines;
				if (m_map[x+1][y-1].isMine) ++m_map[x][y].numOfAroundMines;
				if (m_map[x-1][y+1].isMine) ++m_map[x][y].numOfAroundMines;
				if (m_map[x-1][y-1].isMine) ++m_map[x][y].numOfAroundMines;
			}
		}
	}
	delete []randomNumber;
	randomNumber = NULL;
}

//+->block @->mine $->mark !->touch mine
void Map::print() {

	tag();
		cout << "\t  ";
		for (int i = 0; i < m_size; ++i) cout << i+1 << " ";
		cout << "\n\t ";	
		for (int i = 0; i < m_size+1; ++i) cout << "- ";	
		cout << "\n";
	if (!isGG) {	
		for (int i = 0; i < m_size; ++i) {
			cout << "\t" << i+1 << "|";
			for (int j = 0; j < m_size; ++j) {
				if (m_map[i][j].isMarked) {
					cout << "$ ";
				} else if (m_map[i][j].isAppeared) {
					if (m_map[i][j].numOfAroundMines == 0) cout << "  ";
					else cout << m_map[i][j].numOfAroundMines << " ";
				} else {
					cout << "+ ";
				}
			}
			cout << "|\n";
		}
	} else {
		for (int i = 0; i < m_size; ++i) {
			cout << "\t" << i+1 << "|";
			for (int j = 0; j < m_size; ++j) {
				if (m_map[i][j].isMine) {
					cout << "@ ";
				}
			}
			cout << "|\n";
		}
	}
	cout << "\t ";
	for (int i = 0; i < m_size+1; ++i) cout << "- ";
	cout << "\n";
}
void Map::tag() {
	cout << "--------------------------------\n"
		 << "|          Mine Game           \n"
		 << "| Marked: " << m_marked << "  "
		 << isGG ? ":)" : ":(" ;
	cout << "  "
		 << "Step: " << m_step << "\n"
		 << "---------------------------------\n\n" << endl;
}




#endif