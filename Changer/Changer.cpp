#include "stdafx.h"


#include <iostream>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<filesystem>
#include <vector>
#include"windows.h"


using namespace std;
using namespace std::experimental::filesystem;

FILE *newFile;
using namespace System;

vector<string> find_all_files(path pathOfDirectoris, vector<string> directorisName,string tempAdress)
{
	for (const auto &p : directory_iterator(pathOfDirectoris))
	{
		 string newAdress=tempAdress + "\\"+p.path().filename().string();
		if (is_directory(p))
		{
			directorisName.push_back(newAdress);
			//cout << newAdress << endl;
			directorisName=find_all_files(p, directorisName, newAdress);
		}
	}
		return directorisName;
}

int main()
{
	vector<string> directorisName;
	vector<string> filesName;
	int f = 0;
	path pathOfDirectoris(".\\Concepts");

	directorisName=find_all_files(pathOfDirectoris, directorisName, ".\\Concepts");


	//cout << directorisName.size();
	for (int i = 0; i < directorisName.size(); i++)
	{
		path pathOfFile = directorisName[i];
		
		for (const auto &p : directory_iterator(pathOfFile))
		{
			string filenameStr = directorisName[i]+"\\";
			filenameStr += p.path().filename().string();
			
			if(p.path().extension().string()==".scs"|| p.path().extension().string() == ".scsi")
				filesName.push_back(filenameStr);

			//cout << filenameStr << endl;
		}
	}

	string changeWord, newWord;
	cin >> changeWord;
	cin >> newWord;

	for (int i = 0; i < filesName.size(); i++)
	{
		ifstream file(filesName[i]);
		string workString="";

		cout << filesName[i]<<endl;

		while (file)
		{
			string tempString;
			getline(file, tempString);
			workString += tempString+"\n";
		}

		string:: size_type ind=0;
		while (workString.find(changeWord, ind) != string::npos)
		{
			ind = workString.find(changeWord, ind);
			cout << ind<<endl;
			workString.replace(ind, changeWord.size(), newWord);
			ind += newWord.size();
			/*if (ind > 2000)
				Sleep(30000);*/
		}

		file.close();

		ofstream newFile;
		newFile.open(filesName[i]);
		newFile << workString;
	}
	system("pause");
}
