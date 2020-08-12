#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <time.h>
#include <cstddef>

int width  {120};
int height {50};

char tile[]{"#"};
char air[]{"~"};

int tileChance {50};

const size_t tilesLength = width*height;

HANDLE stdOut { GetStdHandle(STD_OUTPUT_HANDLE) };

// --------------------------------
void goToxy(int column, int line);

void write(char *message);

void writeAt(int column, int line, char *character);
// --------------------------------




int main()
{
	system("color 4");
	system("cls");

	std::cout << "++===================================================++" << "\n";
	std::cout << "+ Hermitao's Cellular Automata Landmass Generator 1.0 +" << "\n";
	std::cout << "++===================================================++" << "\n";

	std::cout << "Map dimensions (values larger than the terminal will cause errors, try again with smaller values if that happens)" << "\n";
	std::cout << "Map width: " << "\n";
	std::cin >> width;
	std::cout << "Map height: " << "\n";
	std::cin >> height;

	std::size_t length{};
	length = width * height;
	char *tiles{ new char[length]{*air} };

	std::cout << "Chance for a cell to be land at the start of the simulation (higher numbers will produce smaller continents):" << "\n";
	std::cin >> tileChance;

	int maxIterations{}; 
	std::cout << "Number of iterations (higher numbers will result in smoother land masses and less small islands):" << "\n";
	std::cin >> maxIterations;
	std::cout << "Iteration time in seconds: " << "\n";
	float timeInput {};
	std::cin >> timeInput; 
	int sleepTimeMilliseconds = timeInput * 1000;


	srand(time(NULL));	


	system("cls");

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x) 
		{
			SetConsoleTextAttribute(stdOut, 4);
			if (rand() % 100 < tileChance)
			{
				writeAt(x, y, tile);
				tiles[x + (y * width)] = *tile;
			}
		}

	}

	std::cout << "\nNumber of iterations: 0";


	Sleep(sleepTimeMilliseconds);
	
	for (int i {0}; i < maxIterations; ++i)
	{
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x) 
			{
				int numOfNeighbours{0};

				if (tiles[x + (y * width)] == *tile)
				{
					++numOfNeighbours;
				}

				if ((x > -1 && y > -1) && (x < width && y < height))
				{
					for (int j = 0; j < 3; ++j)
					{
						if (tiles[x + ((y-1) * width) + j] == *tile)
						{
							++numOfNeighbours;
						}
					}

					if (tiles[(x + (y * width)) - 1] == *tile)
					{
						++numOfNeighbours;
					}

					if (tiles[(x + (y * width)) + 1] == *tile)
					{
						++numOfNeighbours;
					}

					for (int j = 0; j < 3; ++j)
					{
						if (tiles[x + ((y+1) * width) + j] == *tile)
						{
							++numOfNeighbours;
						}
					}

					if (numOfNeighbours >= 5)
					{
						SetConsoleTextAttribute(stdOut, 10);
						writeAt(x, y, tile);
						tiles[x + (y * width)] = *tile;
					}
					else
					{
						SetConsoleTextAttribute(stdOut, 1);
						writeAt(x, y, air);
						tiles[x + (y * width)] = *air;
					}
				}
			}
		}

		SetConsoleTextAttribute(stdOut, 4);
		std::cout << "\nNumber of iterations: " << i+1 << "\n";

		Sleep(sleepTimeMilliseconds);
	}

	std::cout << "Generation finished. Press any key to exit." << "\n";
	system("pause");

	return 0;
}






/// <summary>Go to position.</summary>
void goToxy(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	
	if (!SetConsoleCursorPosition(stdOut, coord))
	{
		std::cout << "SetConsoleCursorPosition() failed - (" << GetLastError() << ")" << "\n";
	}
}

/// <summary>Write text at cursor.</summary>
void write(char *message)
{
	DWORD written{0};
	WriteConsole(stdOut, message, strlen(message), &written, NULL);
}

/// <summary>Combines goToxy and write.</summary>
void writeAt(int column, int line, char *character)
{
	goToxy(column, line);
	write(character);
}	
