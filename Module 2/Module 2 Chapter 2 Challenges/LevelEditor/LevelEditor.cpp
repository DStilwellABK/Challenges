#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;

constexpr char kCursor = '_';

constexpr char kTopRightBorder = 187;
constexpr char kTopLeftBorder = 201;
constexpr char kBottomRightBorder = 188;
constexpr char kBottomLeftBorder = 200;
constexpr char kHorizontalBorder = 205;
constexpr char kVerticalBorder = 186;



enum class ArrowInput {
	Regular = 224,
	LeftArrow = 75,
	RightArrow = 77,
	DownArrow = 80,
	UpArrow = 72,
};

enum class States {
	EDITING,
	REDO,
	DONE,
};

constexpr int kEscapeKey = 27;
constexpr int kBackspace = 8;
constexpr int kSpace = 32;

ArrowInput lastInput = ArrowInput::Regular;

void GetLevelDimensions(int& width, int& height);
void DisplayLevel(char* pLevel, int width, int height, int cursorX, int cursorY);

int GetIndexFromXY(int x, int y, int width);

void DisplayTopBorder(int width);
void DisplayLeftBorder();
void DisplayRightBorder();
void DisplayBottomBorder(int width);

States EditLevel(char* levelData, int& cursorX, int& cursorY, int width, int height);

void SaveLevel(char* pLevel, int width, int height);

void AddBordersToFinalLevel(char* levelData, int width, int height);

void DisplayLegend();
void ClearScreen();


int main()
{
	int levelWidth;
	int levelHeight;

	GetLevelDimensions(levelWidth, levelHeight);

	char* pLevel = new char[levelWidth * levelHeight];

	for (int i = 0; i < levelWidth * levelHeight; i++)
	{
		pLevel[i] = ' ';
	}

	int cursorX = 0;
	int cursorY = 0;

	// 1 = Finished editing, 2 = Redo
	States doneEditing = States::EDITING;
	while (doneEditing != States::DONE) {
		ClearScreen();

	
		if (doneEditing == States::REDO) {
			// Start over

			system("cls");
			GetLevelDimensions(levelWidth, levelHeight);


			pLevel = new char[levelWidth * levelHeight];

			for (int i = 0; i < levelWidth * levelHeight; i++)
			{
				pLevel[i] = ' ';
			}
			
			cursorX = 0;
			cursorY = 0;

			doneEditing = States::EDITING;

			system("cls");

		}
		DisplayLevel(pLevel, levelWidth, levelHeight, cursorX, cursorY);
		
		DisplayLegend();
		doneEditing = EditLevel(pLevel, cursorX, cursorY, levelWidth, levelHeight);


	}

	// Display final screen here and save the level
	system("cls");
	DisplayLevel(pLevel, levelWidth, levelHeight, cursorX, cursorY);

	SaveLevel(pLevel, levelWidth, levelHeight);

	delete[] pLevel;
	pLevel = nullptr;
}

void ClearScreen()
{
	COORD cursorPosition;	
	cursorPosition.X = 0;	
	cursorPosition.Y = 0;	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void DisplayLegend() {
	cout << "Arrows to move cursor" << endl;
	cout << "Esc to finish editing" << endl;
	cout << "+ | - for walls" << endl;
	cout << "@ for player start" << endl;
	cout << "r g b for key to doors" << endl;
	cout << "R G B for door" << endl;
	cout << "$ for money" << endl;
	cout << "v for Vertical moving enemy" << endl;
	cout << "h for horiontal moving enemy" << endl;
	cout << "e for non-moving enemy" << endl;
	cout << "X for end" << endl;
	cout << "^ for starting over with new parameters (new width and height" << endl;
}

States EditLevel(char* levelData, int& cursorX, int& cursorY, int width, int heigh) {
	int newCursorX = cursorX;
	int newCursorY = cursorY;

	int intInput = _getch();
	ArrowInput arrowInput = (ArrowInput)intInput;

	if (arrowInput == ArrowInput::Regular) {
		arrowInput = (ArrowInput)_getch();
		switch (arrowInput) {
			case ArrowInput::LeftArrow:
				newCursorX--;
				lastInput = arrowInput;
				break;
			case ArrowInput::RightArrow:
				newCursorX++;
				lastInput = arrowInput;
				break;
			case ArrowInput::UpArrow:
				newCursorY--;
				lastInput = arrowInput;
				break;
			case ArrowInput::DownArrow:
				newCursorY++;
				lastInput = arrowInput;
				break;
			default:
				break;

		}

		if (newCursorX < 0)
			newCursorX = 0;
		else if (newCursorX == width)
			newCursorX = width - 1;

		if (newCursorY < 0)
			newCursorY = 0;
		else if (newCursorY == width)
			newCursorY = width - 1;

		cursorX = newCursorX;
		cursorY = newCursorY;
	}
	else {
		if (intInput == kEscapeKey) {
			return States::DONE;
		}
		else if (intInput == kBackspace) {
			// Ignore
		}
		if (intInput == '^') {
			return States::REDO;
		}
		// Else the user is implementing something like a wall, door, goal, key, etc...
		else {
			int index = GetIndexFromXY(newCursorX, newCursorY, width);
			levelData[index] = (char)intInput;
			if (intInput != kSpace) {

				if (lastInput == ArrowInput::LeftArrow) {
					newCursorX--;
					if (newCursorX < 0)
						newCursorX = 0;
					
					cursorX = newCursorX;

				}
				else if (lastInput == ArrowInput::RightArrow) {
					newCursorX++;
					if (newCursorX == width)
						newCursorX = width - 1;

					cursorX = newCursorX;

				}
				else if (lastInput == ArrowInput::UpArrow) {
					newCursorY--;
					if (newCursorY < 0)
						newCursorY = 0;
					cursorY = newCursorY;
				}
				else if (lastInput == ArrowInput::DownArrow) {
					newCursorY++;

					if (newCursorY == width)
						newCursorY = width - 1;

					cursorY = newCursorY;


				}
				else {
					newCursorX++;
					if (newCursorX == width)
						newCursorX = width - 1;

					cursorX = newCursorX;
				}


			}
		}
	}



	return States::EDITING;
}

void GetLevelDimensions(int& width, int& height) {
	cout << "Please enter the width and height of your level: ";
	cin >> width >> height;

}

void DisplayLevel(char* pLevel, int width, int height, int cursorX, int cursorY) {
	DisplayTopBorder(width);

	for (int y = 0; y < height; y++)
	{
		DisplayLeftBorder();
		for (int x = 0; x < width; x++)
		{

			if (cursorX == x && cursorY == y) {
				cout << kCursor;
			}
			else {
				int index = GetIndexFromXY(x, y, width);
				cout << pLevel[index];
			}
		}
		DisplayRightBorder();
	}
	DisplayBottomBorder(width);
}

int GetIndexFromXY(int x, int y, int width) {
	return x + y * width;
}


void AddBordersToFinalLevel(char* levelData, int width, int height){
	//Top Left border
	int index = GetIndexFromXY(0, 0, width);
	levelData[index] = '+';

	//Top Right Border
	index = GetIndexFromXY(width, 0, width);
	levelData[index] = '+';

	//Bottom Left border
	index = GetIndexFromXY(0, height, width);
	levelData[index] = '+';

	//Bottom Right border
	index = GetIndexFromXY(width, height, width);
	levelData[index] = '+';

	// Top Border
	for (int i = 0; i < width; i++)
	{
		index = GetIndexFromXY(i, 0, width);
		levelData[index] = '-';
	}

	// Bottom Border
	for (int i = 0; i < width; i++)
	{
		index = GetIndexFromXY(i, height, width);
		levelData[index] = '-';
	}

	//Left Border 
	for (int i = 0; i < width; i++)
	{
		index = GetIndexFromXY(0, i, width);
		levelData[index] = '|';
	}

	//Right Border
	for (int i = 0; i < width; i++)
	{
		index = GetIndexFromXY(width, i, width);
		levelData[index] = '|';
	}
}

void DisplayTopBorder(int width) {
	cout << kTopLeftBorder;
	for (int i = 0; i < width; i++)
	{
		cout << kHorizontalBorder;
	}
	cout << kTopRightBorder << endl;
}

void DisplayBottomBorder(int width) {
	cout << kBottomLeftBorder;
	for (int i = 0; i < width; i++)
	{
		cout << kHorizontalBorder;
	}
	cout << kBottomRightBorder << endl;
}


void DisplayLeftBorder() {
	cout << kVerticalBorder;
}

void DisplayRightBorder() {
	cout << kVerticalBorder << endl;
}

void SaveLevel(char* pLevel, int width, int height) {
	AddBordersToFinalLevel(pLevel, width, height);
	
	cout << "Please enter a name for the level (eg: level1.txt): ";
	
	string levelName;
	cin >> levelName;

	levelName.insert(0, "../");

	ofstream levelFile;
	levelFile.open(levelName);
	if (!levelFile) {
		cout << "Opening file failed!" << endl;
	}
	else {
		levelFile << width << endl;
		levelFile << height << endl;
		levelFile.write(pLevel, width * height);

		if (!levelFile) {
			cout << "Write failed!" << endl;
		}

		levelFile.close();
	}
}
