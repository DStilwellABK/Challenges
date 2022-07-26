#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>

using namespace std;

constexpr char kCursor = '_';

constexpr char kTopRightBorder = 187;
constexpr char kTopLeftBorder = 201;
constexpr char kBottomRightBorder = 188;
constexpr char kBottomLeftBorder = 200;
constexpr char kHorizontalBorder = 205;
constexpr char kVerticalBorder = 186;

constexpr int kArrowInput = 224;
constexpr int kLeftArrowInput = 75;
constexpr int kRightArrowInput = 77;
constexpr int kDownArrowInput = 80;
constexpr int kUpArrowInput = 72;

constexpr int kEscapeKey = 27;
constexpr int kBackspace = 8;


void GetLevelDimensions(int& width, int& height);
void DisplayLevel(char* pLevel, int width, int height, int cursorX, int cursorY);

int GetIndexFromXY(int x, int y, int width);

void DisplayTopBorder(int width);
void DisplayLeftBorder();
void DisplayRightBorder();
void DisplayBottomBorder(int width);

bool EditLevel(char* levelData, int& cursorX, int& cursorY, int width, int height);

void SaveLevel(char* pLevel, int width, int height);

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

	bool doneEditing = false;
	while (!doneEditing) {
		ClearScreen();
		DisplayLevel(pLevel, levelWidth, levelHeight, cursorX, cursorY);
		DisplayLegend();
		doneEditing = EditLevel(pLevel, cursorX, cursorY, levelWidth, levelHeight);
	}
	ClearScreen();
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
}

bool EditLevel(char* levelData, int& cursorX, int& cursorY, int width, int heigh) {
	int newCursorX = cursorX;
	int newCursorY = cursorY;

	int intInput = _getch();

	if (intInput == kArrowInput) {
		int arrowInput = _getch();
		switch (arrowInput) {
			case kLeftArrowInput:
				newCursorX--;
				break;
			case kRightArrowInput:
				newCursorX++;
				break;
			case kUpArrowInput:
				newCursorY--;
				break;
			case kDownArrowInput:
				newCursorY++;
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
			return true;
		}
		else if (intInput == kBackspace) {
			// Ignore
		}
		else {
			int index = GetIndexFromXY(newCursorX, newCursorY, width);
			levelData[index] = (char)intInput;
		}
	}



	return false;
}

void GetLevelDimensions(int& width, int& height) {
	cout << "Please enter the width of your level: ";
	cin >> width;

	cout << "Please enter the height of your level: ";
	cin >> height;
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
