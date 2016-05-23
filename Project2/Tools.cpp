#include "Tools.h"

unsigned int getConsoleWidth()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	unsigned int CONSOLE_WIDTH = (csbi.srWindow.Right - csbi.srWindow.Left) / 2;

	return CONSOLE_WIDTH;
}
const unsigned int CONSOLE_WIDTH = getConsoleWidth();
void c(const string s)
{
	cout << setw(CONSOLE_WIDTH + s.length() / 2) << s << endl;
}
string validFile(string fileType)
{
	string fileName;
	while (true)
	{
		cout << "\nWhat's the name of your " << fileType << " file? ";
		getline(cin, fileName);
		ifstream file(fileName);
		if (file.is_open())
		{
			cout << "File found!\n";
			file.close();
			break;
		}
		else cout << "File not found!\n";
	}
	return fileName;
}
bool yesNoAnswer()
{
	string answer;
	while (true)
	{
		cout << "Answer: ";
		getline(cin, answer);
		transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
		if (answer == "y" || answer == "yes")
			return true;
		else if (answer == "n" || answer == "no")
			return false;
		else cerr << "Invalid Answer!\n";
		cin.clear();
	}
}