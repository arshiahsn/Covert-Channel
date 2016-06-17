//Arshia Hosseini
#include<iostream>
#include<stdio.h>
#include <time.h>
#include <windows.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <bitset>

using namespace std;
//Define the default path using any desired path and folder name
#define PATH "C:\\import\\"
#define STOP "C:\\export\\"

bool dirExists(const string& dirName_in)	//A function to check whether the folder exists
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //Something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // This is a directory!

	return false;    // This is not a directory!
}


void CreateFolder(const char * path)	//A function to create a folder in desired path
{
	if (!CreateDirectory(path, NULL))
	{
		return;
	}
}
void DeleteFolder(const char* path)		//A function to delete a folder in desired path
{
	if (!RemoveDirectory(path) )
	{
		return;
	}

}
void sendBitMessage(char input)				//Sent a message bit by bit
{
	int code = int(input);
	cout << "Sending: " << input<<"(";
	string temp = bitset<8>(code).to_string();		//Converting input to bit-string
	while (temp.length() < 8)
		temp =  "0" + temp;
	string code_p = temp;
	reverse(temp.begin(), temp.end());				//Reversing the input to send
	//code = stoi(temp);
	cout << code_p << ")" << endl;
	bool zeroFlag = false;
	for (int i = 0; i < 8;i++) {
		if (dirExists(STOP))
			break;
		Sleep(1000);								//Inorder to sync both processes
		if (temp.back() == '1') {	//If the last bit is 1
			CreateFolder(PATH);
		}
		else {

			DeleteFolder(PATH);
		}
		//code = code/10;	//Consider next bit
		temp = temp.substr(0, temp.size() - 1);
	}
}

int main() {

	DeleteFolder(STOP);						//End of message correction
	DeleteFolder(PATH);
	string message;
	cout << "Write a message to send:\n";
	getline(cin, message);
	message.erase(remove_if(message.begin(), message.end(), isspace), message.end()); //Trimming the message
	int messageLen = message.length();
	while (!dirExists(STOP))				//While no STOP signals received
	{
		cout << "Signaling...\n";
		sendBitMessage('%');				//First preamble char indicating message starting
		sendBitMessage('$');				//Second preamble char indicating message starting
		for (int i = 0; i < messageLen; i++) {	//Sending the message
			sendBitMessage(message.at(i));
			if (dirExists(STOP))
				break;
		}
		sendBitMessage('$');				//First preamble char indicating message ending
		sendBitMessage('%');				//Second preamble char indicating message ending


	}

	return 0;
}