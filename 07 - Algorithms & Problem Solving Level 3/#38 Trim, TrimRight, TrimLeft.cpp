// #38 Trim, TrimRight, TrimLeft
// https://programmingadvices.com/courses/1869980/lectures/42697291/comments/25851153

#include <iostream>
#include <string>

using namespace std;

enum enTrimTypes { All, Right, Left };

string TrimString(string text, enTrimTypes type = enTrimTypes::All)
{
	switch (type)
	{
	case All:
		text = TrimString(text, enTrimTypes::Right);
		text = TrimString(text, enTrimTypes::Left);
		break;
	case Right:
		while (text[text.length() - 1] == ' ')
			text.erase(text.length() - 2, text.length() - 1);
		break;
	case Left:
		while (text[0] == ' ') text.erase(0, 1);
		break;
	}

	return text;
}

int main()
{
	string text;
	cout << "String     = ";
	getline(cin, text);
	cout << "\nTrim       = " << TrimString(text);
	cout << "\nTrim Right = " << TrimString(text, enTrimTypes::Right);
	cout << "\nTrim Left  = " << TrimString(text, enTrimTypes::Left);
	cout << endl;
	return 0;
}

/* Instructor Solution:
string TrimLeft(string S1)
{
	for (short i = 0; i < S1.length(); i++)
	{
		if (S1[i] != ' ')
		{
			return S1.substr(i, S1.length() - i);
		}
	}
	return "";
}
string TrimRight(string S1)
{
	for (short i = S1.length() - 1; i >= 0; i--)
	{
		if (S1[i] != ' ')
		{
			return S1.substr(0, i + 1);
		}
	}
	return "";
}
string Trim(string S1)
{
	return (TrimLeft(TrimRight(S1)));
}
*/
