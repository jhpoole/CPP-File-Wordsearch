// CPPAssignment_SID1702281.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>

using namespace std;

class TextEntry
{	
    public:
		string text;
		int amount;
		bool repeat;
		TextEntry(string entry)
		{
			text = entry;
			amount = 1;
			repeat = false;
		}
		void IncreaseAmount()
		{
			amount++;
		}
		void isRepeat()
		{
			repeat = true;
		}
		string getText()
		{
			return text;
		}
		int getAmount()
		{
			return amount;
		}
		void getEntry()
		{			
			if (repeat == false) {
				cout << "\"" << getText() << "\"" << " occurs " << getAmount() << " time(s)."<< endl;
			}
		}
};

class File
{
    private:
		string fileContent;
		string path;
    public:
		ifstream file;
	void setPath(string address)
	{
		string userInput;
		cout << "Please enter the name of the text file (Do not include .txt): ";
		cin >> userInput; 
		address.erase(address.find_last_of("\\"), address.length() - address.find_last_of("\\"));
		address += "\\" + userInput + ".txt";
		path = address;
	}
	void searchString(string search, list<int>& searchPositions)
	{
		string content = fileContent;
		for (char &charLower : content)
			charLower = convertToLowercase(charLower);
		for (char &charLower : search)
			charLower = convertToLowercase(charLower);
		size_t position = content.find(search);
		while (position != std::string::npos)
		{
			searchPositions.push_back(position);
			position = content.find(search, position + search.size());
		}
	}
	char convertToLowercase(char character)
	{
		if (character >= 'A' && character <= 'Z')
			return character + 32;
		return character;
	}
	string findWholeWord(char characterBreak, size_t position)
	{
		string output = "";
		while (fileContent.at(position) != characterBreak || position == 1)
		{
			position--;
		}
		position++;
		do
		{
			output += fileContent.at(position);
			position++;
			if (position == fileContent.length()) { break; }
		} while (fileContent.at(position) != characterBreak);
		return output;
	}
	string getSearchedWord(char characterBreak, size_t position, vector<string> searchTerm, bool startsWithWildcard, bool endsWithWildcard, list<int> searchPositions)
	{
		if (startsWithWildcard && endsWithWildcard && searchTerm.size() == 3)
			return findWholeWord(characterBreak, position);
		else if (startsWithWildcard && endsWithWildcard && searchTerm.size() != 3)
		{
			//multiple wildcards with beginning and end
			for (int loop = 0; loop > searchTerm.size() - 1; )
			{
				searchTerm[loop];
				loop = loop + 2;
			}
		}
		else if (startsWithWildcard && !endsWithWildcard) 
		{ 
		   //ends with wildcard
		}
		else if (!startsWithWildcard && endsWithWildcard)
		{
			//starts with wildcard
		}
		else if (!startsWithWildcard && !endsWithWildcard)
		{
			//no wildcard at start or end
		}
		return "test"; // placeholder until this feature is developed
	}
	void appendFileContent(string content)
	{
		fileContent = fileContent + " " + content;
	}
	string getFileContent()
	{
		return fileContent;
	}
	string getPath()
	{
		return path;
	}
	bool openFile()
	{
		file.open(path, ios::in);
		if (file.is_open())
		{
			cout << "FILE FOUND AND OPENED" << endl;
			return true;
		}
		else
		{
			cout << "UNABLE TO FIND OR OPEN FILE" << endl;
			return false;
		}
	}
	void closeFile()
	{
		file.close();
		cout << "FILE CLOSED" << endl;
	}
	void createEntry(vector<TextEntry>& entriesFound, size_t pos, vector<string> searchTerm, bool startsWithWildcard, bool endsWithWildcard, list<int> searchPositions)
	{
		entriesFound.push_back(getSearchedWord(' ', pos, searchTerm, startsWithWildcard, endsWithWildcard, searchPositions));
		for (size_t loop = 0; loop != entriesFound.size() - 1; ++loop)
		{
			if (entriesFound[loop].getText() == entriesFound.back().getText())
			{
				entriesFound[loop].IncreaseAmount();
				entriesFound.back().isRepeat();
			}
		}
	}
};

class SearchWord
{
	private:
		string word;	
	public:
		vector<string> sections;
		bool startsWithWildcard;
		bool endsWithWildcard;
		SearchWord(string userInput)
		{
			    startsWithWildcard = true;
			    endsWithWildcard = true;
			    word = userInput;
				size_t position = userInput.find('*');
				if (position != 0)
				{
					sections.push_back(searchSection('*', 0));
					startsWithWildcard = false;
				} // first search term
				while (position != std::string::npos)
				{
					
					sections.push_back("*"); //current wildcard
					if (position != word.length()-1)
						sections.push_back(searchSection('*', position)); //current search term
					position = userInput.find('*', position + 1);
				}
				for (size_t loop = 0; loop != sections.size(); ++loop) {
					cout << "String section " << loop << ": " << sections[loop] << endl;
				}
				if (sections[sections.size() - 1] != "*")
					endsWithWildcard = false;
	    }
		void findWildcards()
		{

		}
		string searchSection(char characterBreak, size_t position)
		{
			string output = "";
			while (word.at(position) != characterBreak && position != 0)
			{
				position--;
			}
			if (word.at(position) == characterBreak)
				position++;
			do
			{				
					output += word.at(position);
					position++;
					if (position == word.length())
						break;
			} while (word.at(position) != characterBreak && position != word.length());
			return output;
		}
};



int main(int argc, char* argv[])
{
	File myFile;
	myFile.setPath(argv[0]);
	cout << "Searching: " << myFile.getPath() << endl;
	bool fileOpen = myFile.openFile();
	if (fileOpen)
	{
		string line;
		while (getline(myFile.file, line))
		{		
			myFile.appendFileContent(line);
		}
		cout << "File Content: " << myFile.getFileContent() << endl;
		myFile.closeFile();
		string userStringInput;
		cout << "Please enter the string you wish to search for: ";
		cin >> userStringInput;
		SearchWord search(userStringInput);
		list<int> searchPositions;
		list<int>::iterator pos;
		vector<TextEntry> entriesFound;
		if (search.startsWithWildcard == true)
			myFile.searchString(search.sections[1], searchPositions);
		else
			myFile.searchString(search.sections[0], searchPositions);
		//myFile.searchString(userStringInput, searchPositions);
		for (pos = searchPositions.begin(); pos != searchPositions.end(); ++pos) 
		{
			myFile.createEntry(entriesFound, *pos, search.sections, search.startsWithWildcard, search.endsWithWildcard, searchPositions);
		}
		cout << "The entries found in the text file:" << endl;
		for (size_t loop = 0; loop != entriesFound.size(); ++loop) {
			entriesFound[loop].getEntry();
		}
	}
	system("PAUSE");
	return 0;
}
