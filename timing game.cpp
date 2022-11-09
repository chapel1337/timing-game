#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <random>

#ifdef __linux__
#include <unistd.h>
#elif _WIN32
#include <windows.h>

void sleep(int time)
{
	Sleep(time * 1000);
}
#endif

using std::cout; using std::cin; using std::string; using std::getline; using std::ws; using std::vector; using std::to_string;

/*
* written by chapel1337
* made on 10/25/2022

* returned on 11/6/2022 to finish this
* finally finished, currently 5:06pm
* i got a bit distracted, so this took longer than it should've to make
* i finally got loops with key input to work!!!
* i have no idea what made it not work last time still (i also used _kbit())
* inspired by a timing game that i played at dave & busters
* 
* came back on 11/8/2022 to fix restart
* also removed ccin because it was useless
*/

// ------- \\

vector<vector<char>> presetMap
{
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
};

vector<vector<char>> map{ presetMap };
vector<vector<char>> currentMap{ map };

int mapY{ (int) map.size() };
int mapX{ (int) map[0].size() };

int blockY{ mapY - 1 };
vector<int> blockX{ 0, 1, 2, 3, 4 };

int blocksPlaced{ 0 };
char block{ '#' };

double speed{ 0.4 };
// int random{};

bool stop{ false };
bool randomColorsEnabled{ false };
// bool startingFrom{ false }; // right = true, left = false
bool linux{ false };

#ifdef __linux__
	linux = true;
#endif

// ------- \\

void clear()
{
	if (linux)
	{
		system("clear");
	}
	else
	{
		system("cls");
	}
}

void sleep(auto time)
{
	Sleep(time * 1000);
}

/*
char ccin()
{
	string input{};
	std::getline(std::cin, input);

	return input[0];
}
*/

int getRandom(int min, int max)
{
	// i had to copy this from learncpp.com, i will not be memorizing this prng method anytime soon
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution random{ min, max };

	return random(mt);
}

void title(string title)
{
	if (linux) return;

	SetConsoleTitleA(("timing game - " + title).c_str());
}

void title()
{
	if (linux) return;

	SetConsoleTitleA("timing game");
}

void title(string title, int i)
{
	if (linux) return;

	SetConsoleTitleA(("timing game - " + title + to_string(i)).c_str()); // many paranthesis
}

void setTextColor(int color)
{
	if (linux) return;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetTextColor()
{
	if (linux) return;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

// ------- \\

void goTo(string function);

void winLoseHandler(bool outcome) // win = true, loss = false
{
	string response{};

	blocksPlaced = 0;
	speed = 0.4;
	stop = false;

	blockY = mapY - 1;

	blockX.clear();
	for (int i{}; i < 5; ++i)
	{
		blockX.push_back(i);
	}

	map.clear();
	map = presetMap;
	currentMap.clear();
	currentMap = map;

	cout << "would you like to play again?\n\n";

	cout << "> ";
	getline(cin >> ws, response);

	if (response == "yes" || response == "y")
	{
		goTo("start");
	}
	else if (response == "no" || response == "n")
	{
		goTo("menu");
	}
	else
	{
		if (outcome)
		{
			goTo("youWin");
		}
		else
		{
			goTo("youLose");
		}
	}

}

void youWin()
{
	clear();

	setTextColor(10);
	cout << "you win!\n\n";
	resetTextColor();

	Beep(500, 200);
	Beep(500, 200);
	Beep(500, 500);
	Beep(500, 200);
	Beep(500, 200);

	winLoseHandler(true);
}

void youLose()
{
	clear();

	setTextColor(4);
	cout << "you lose!\n\n";
	resetTextColor();

	Beep(200, 700);
	Beep(200, 700);
	Beep(200, 700);
	Beep(200, 1250);

	winLoseHandler(false);
}

// ------- \\

void displayStatistics()
{
	cout << "y: " << blockY << '\n';

	cout << "x: ";
	for (int i{ 0 }; i < blockX.size(); ++i)
	{
		cout << blockX[i] << ", ";
	}
	cout << '\n';

	cout << "map y: " << mapY << '\n';
	cout << "map x: " << mapX << "\n\n";
	cout << "blocks placed: " << blocksPlaced << '\n';

	cout << '\n';
}

void positionBlock()
{
	currentMap.clear();
	currentMap = map;

	for (int i{ 0 }; i < blockX.size(); ++i)
	{
		currentMap[blockY][blockX[i]] = block;
	}
}

void refresh()
{
	clear();
	positionBlock();
	displayStatistics();

	cout << '|';
	for (int i{ 0 }; i < mapX; ++i)
	{
		cout << '-';
	}
	cout << "|\n";

	for (int i{ 0 }; i < currentMap.size(); ++i)
	{
		cout << '|';
		for (int o{ 0 }; o < currentMap[0].size(); ++o)
		{
			if (randomColorsEnabled)
			{
				setTextColor(getRandom(1, 10));

				cout << currentMap[i][o];
			}
			else
			{
				if (currentMap[i][o] == block)
				{
					setTextColor(9);
					cout << currentMap[i][o];
					resetTextColor();
				}
				else
				{
					cout << currentMap[i][o];
				}
			}
		}

		cout << "|\n";
	}

	cout << '|';
	for (int i{ 0 }; i < mapX; ++i)
	{
		cout << '-';
	}
	cout << "|\n";
}

// ------- \\

void placeBlock();

void getInput()
{
	if (_kbhit())
	{
		stop = true;
		_getch(); // resets _kbhit()

		placeBlock(); // i have no idea why goTo() doesn't work with this
	}
}

// ------- \\

void moveBackward()
{
	for (int i{ 0 }; i < mapX; ++i)
	{
		if (stop)
		{
			return;
		}

		getInput();

		if (blockX[0] == 0)
		{
			break;
		}

		for (int i{ 0 }; i < blockX.size(); ++i)
		{
			blockX[i]--;
		}

		sleep(speed);

		refresh();
	}

	if (stop)
	{
		return;
	}

	getInput();
	goTo("moveForward");
}

void moveForward()
{
	for (int i{ 0 }; i < mapX; ++i)
	{
		if (stop)
		{
			return;
		}

		getInput();

		if (blockX[blockX.size() - 1] == mapX - 1)
		{
			break;
		}

		for (int i{ 0 }; i < blockX.size(); ++i)
		{
			blockX[i]++;
		}

		sleep(speed);

		refresh();
	}

	// mutiple stop checks for accuracy
	if (stop)
	{
		return;
	}

	// mutiple getInput() checks for accuracy (2)
	getInput();
	moveBackward();
}

// ------- \\

void placeBlock()
{
	// probably the largest function i have ever written

	int hashtagCount{ 0 };

	if (blockY == 0)
	{
		youWin();
	}

	for (int i{ 0 }; i < blockX.size(); ++i)
	{
		map[blockY][blockX[i]] = block;
	}

	if (blocksPlaced != 0)
	{
		for (int i{ 0 }; i < blockX.size(); ++i)
		{
			if (currentMap[blockY + 1][blockX[i]] == block)
			{
				hashtagCount++;
			}
			else
			{
				if (blockX.size() == 1)
				{
					youLose();
				}
				else
				{
					blockX.erase(blockX.begin() + i);
				}
			}
		}
	}

	for (int i{ 0 }; i < blockX.size(); ++i)
	{
		blockX[i] = i;
	}

	// if my biggest issue right now is trying to get the block to start from either side, i'm pretty well off
	/*
	int test{};
	
	if (blockX.size() % 2 == 0)
	{
		test = blockX.size() - 1 / 2;
	}
	else
	{
		test = blockX.size() / 2;
	}

	if (mapX / 2 > test)
	{
		startingFrom = false;
	}
	else
	{
		startingFrom = true;
	}

	for (int i{ 0 }; i < blockX.size(); ++i)
	{
		blockX[i] = test;

		test++;
	}
	*/

	if (blocksPlaced == 1)
	{
		if (hashtagCount != 0 && blockX.size() != 1) blockX.pop_back(); // terror

		speed = 0.25;
	}
	else if (blocksPlaced == 3)
	{
		if (hashtagCount != 0 && blockX.size() != 1) blockX.pop_back();

		speed = 0.15;
	}
	else if (blocksPlaced == 5)
	{
		if (hashtagCount != 0 && blockX.size() != 1) blockX.pop_back();

		speed = 0.10;
	}
	else if (blocksPlaced == 8)
	{
		if (hashtagCount != 0 && blockX.size() != 1) blockX.pop_back();

		speed = 0.05;
	}

	blocksPlaced++;
	blockY--;

	hashtagCount = 0;
	stop = false;
	// random = getRandom(0, 1);
	
	refresh();

	/*
	if (random == 1)
	{
		moveForward();
	}
	else
	{
		moveBackward();
	}
	*/

	moveForward();
}

// ------- \\

void toggleRandomColors()
{
	clear();

	if (randomColorsEnabled)
	{
		randomColorsEnabled = false;
		cout << "disabled random colors\n\n";
	}
	else
	{
		randomColorsEnabled = true;
		cout << "enabled random colors\n\n";
	}

	cout << "> ";

	sleep(2);
	goTo("menu");
}

char inputBlock{ '#' };
int inputBlockSize{ (int) blockX.size() };

int inputMapY{ mapY };
int inputMapX{ mapX };

void displayBlockMapStatistics(bool comingFrom) // true = changeBlock(), false = changeMapSize()
{
	if (comingFrom)
	{
		cout << "block: " << inputBlock << '\n';

		cout << "block size: ";
		for (int i{ 0 }; i < inputBlockSize; ++i)
		{
			cout << i << ", ";
		}
		cout << "\n\n";
	}
	else
	{
		cout << "map x: " << inputMapX << "\n\n";
		cout << "map y: " << inputMapY << '\n';
	}
}

void changeBlock()
{
	clear();
	title("change block");

	string response{};

	displayBlockMapStatistics(true);

	cout << "input block: \n\n";

	cout << "> ";
	cin >> inputBlock;

	clear();

	displayBlockMapStatistics(true);

	cout << "input block size: \n\n";

	cout << "> ";
	cin >> inputBlockSize;

	clear();

	displayBlockMapStatistics(true);

	cout << "are you sure you want to preform this action? \n\n";

	cout << "> ";
	getline(cin >> ws, response);

	if (response == "yes" || response == "y")
	{
		clear();

		displayBlockMapStatistics(true);

		blockX.clear();
		for (int i{ 0 }; i < inputBlockSize; ++i)
		{
			blockX[i] = i;
		}
		block = inputBlock;

		inputBlockSize = blockX.size();
		inputBlock = block;

		cout << "successfully changed block and block size\n\n";
		cout << "> ";

		sleep(2);
		goTo("settings");
	}
	else if (response == "no" || response == "n")
	{
		inputBlock = '#';
		inputBlockSize = blockX.size();

		goTo("settings");
	}
}

void changeMapSize()
{
	clear();
	title("change map size");

	string response{};

	displayBlockMapStatistics(false);

	cout << "input map y: \n\n";

	cout << "> ";
	cin >> inputMapY;

	clear();

	displayBlockMapStatistics(false);

	cout << "input map x: \n\n";

	cout << "> ";
	cin >> inputMapX;

	clear();

	displayBlockMapStatistics(false);

	cout << "are you sure you want to preform this action? \n\n";

	cout << "> ";
	getline(cin >> ws, response);

	if (response == "yes" || response == "y")
	{
		clear();

		displayBlockMapStatistics(false);

		mapX = inputMapX;
		mapY = inputMapY;

		cout << "successfully changed map size\n\n";
		cout << "> ";

		sleep(2);
		goTo("settings");
	}
	else if (response == "no" || response == "n")
	{
		inputMapX = mapX;
		inputMapY = mapY;

		goTo("settings");
	}
}

// ------- \\

void start()
{
	refresh();
	moveForward();
}

void settings()
{
	clear();

	char response{};

	cout << "settings\n\n";

	if (linux)
	{
		cout << "1. change block/block size\n";
		cout << "2. change map size\n";
		cout << "3. back\n\n";
	}
	else
	{
		cout << "1. toggle random colors\n";
		cout << "2. change block/block size\n";
		cout << "3. change map size\n";
		cout << "4. back\n\n";
	}

	cout << "> ";
	cin >> response;

	if (linux)
	{
		switch (response)
		{
		case '1':
			changeBlock();
			break;

		case '2':
			changeMapSize();
			break;

		case '3':
			goTo("menu");
			break;

			settings();
		}
	}
	else
	{
		switch (response)
		{
		case '1':
			toggleRandomColors();
			break;

		case '2':
			changeBlock();
			break;

		case '3':
			changeMapSize();
			break;

		case '4':
			goTo("menu");
			break;
		}

		settings();
	}
}

void quit()
{
	clear();

	for (int i{ 3 }; i > 0; --i)
	{
		title("okay, quitting in ", i);
		cout << "okay, exiting in " << i;

		sleep(1);
		clear();
	}

	Beep(200, 325);
	exit(1);
}

void menu()
{
	clear();
	title("menu");

	char response{};

	cout << "timing game\n\n";

	cout << "1. start\n";
	cout << "2. settings\n";
	cout << "3. quit\n\n";

	cout << "> ";
	cin >> response;

	switch (response)
	{
	case '1':
		start();
		break;

	case '2':
		settings();
		break;

	case '3':
		quit();
		break;
	}

	menu();
}

// ------- \\

void goTo(string function)
{
	if (function == "start")
	{
		start();
	}
	else if (function == "menu")
	{
		menu();
	}

	else if ("moveForward")
	{
		moveForward();
	}
	else if ("placeBlock")
	{
		placeBlock();
	}
}

int main()
{
	setTextColor(6);
	cout << "written by chapel1337\n";
	cout << "made on 11/6/2022\n";
	resetTextColor();

	sleep(2);

	Beep(200, 325);
	menu();
}

// ------- \\
