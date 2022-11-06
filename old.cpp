/*

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using std::cout; using std::cin; using std::string; using std::vector;

// written by chapel1337
// made on 10/25/2022

// ------- \\

int platformLength{ 5 };
int spaces{ 0 };
int test{ 5 };

const int maxSpaces{ 10 };
const int minSpaces{ 0 };

vector<string> previousPlatforms{};

// ------- \\

void clear()
{
	system("cls");
}

template <typename T>
void sleep(T time)
{
	Sleep(time * 1000);
}

// ------- \\

void returnTo(string returnFunction);

bool stopMoving{ false };

void reverseMovingPlatform()
{
	if (stopMoving == true)
	{
		exit(1);
	}
	else
	{
		clear();

		cout << spaces << '\n';

		if (spaces == minSpaces && stopMoving != true)
		{
			returnTo("movingPlatform");
		}

		for (int i{ spaces }; i > 0; --i)
		{
			cout << ' ';
		}

		for (int i{ 0 }; i < platformLength; ++i)
		{
			cout << '#';
		}

		--spaces;

		sleep(0.50);
		reverseMovingPlatform();
	}
}

void movingPlatform()
{
	if (stopMoving == true)
	{
		exit(1);
	}
	else
	{
		clear();

		cout << spaces << '\n';

		for (int i{ 0 }; i < spaces; ++i)
		{
			if (spaces == maxSpaces && stopMoving != true)
			{
				reverseMovingPlatform();
				break;
			}

			cout << ' ';
		}

		for (int i{ 0 }; i < platformLength; ++i)
		{
			cout << '#';
		}

		++spaces;

		sleep(0.50);
		movingPlatform();
	}
}

void displayPreviousPlatforms()
{
	for (int i{ 0 }; i < test; ++i)
	{
		cout << '\n';
	}

	for (int i{ 0 }; i < previousPlatforms.size(); ++i)
	{
		cout << previousPlatforms.at(i) << '\n';
	}
}

void placePlatform()
{
	string platform{};

	for (int i{ 0 }; i < platformLength; ++i)
	{
		platform += '#';
	}

	previousPlatforms.insert(previousPlatforms.begin(), platform);

	--platformLength;

	returnTo("start");
}

void youWin()
{
	clear();

	cout << "you win!\n";

	cin.ignore();
}

void stopMovement()
{
	clear();
	stopMoving = true;
}

// ------- \\

void start()
{
	if (platformLength <= 0)
	{
		youWin();
	}

	displayPreviousPlatforms();
	movingPlatform();

	stopMovement();

	placePlatform();
}

// ------- \\

void returnTo(string returnFunction)
{
	if (returnFunction == "start")
	{
		start();
	}
	else if (returnFunction == "movingPlatform")
	{
		movingPlatform();
	}
}

int main()
{
	start();
}

// ------- \\

*/