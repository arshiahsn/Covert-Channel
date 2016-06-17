//Arshia Hosseini
#include<iostream>
#include<stdio.h>
#include <time.h>
#include <windows.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;
//Define the default path using any desired path and folder name
#define PATH "C:\\import\\"
#define STOP "C:\\export\\"

void resetArray(int arr[])				//A function to reset 8 bit array
{
	for (int i = 0; i < 8; i++)
		arr[i] = 0;
}
int binaryToDecimal(int input)			//Converting a binary integer to the relevant decimal value
{
	int in = input;
	int multiplier = 1;
	int temp = 0;
	for (int i = 0; i < 8; i++)
	{
		temp = (in % 10)*multiplier + temp;
		multiplier *= 2;
		in = in / 10;
	}
	return temp;
}

void shiftAndAppend(int arr[], int element)			//Creating a window to read stream of bits
{													//Window indicates the receiving character (8bits)
	for (int i = 1; i <= 7; i++) {
		arr[i-1] = arr[i];
	}
	arr[7] = element;
}
int arrToChar(int arr[]) {							//Converts an 8bit array of integers to a character

	int temp = 0;
	int multiplier = 1;
	for (int i = 7; i >= 0; i--) {
		temp = (arr[i] * multiplier) + temp;
		multiplier = multiplier*10;
		//cout << arr[i] << endl;
	}
//	cout << setfill('0') << setw(8) << temp << endl;				//For Tracing (uncomment for Debugging)
	temp = binaryToDecimal(temp);
	return char(temp);
}

bool dirExists(const string& dirName_in)							//A function to check whether the folder exists
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //Something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // This is a directory!

	return false;    // This is not a directory!
}

void CreateFolder(const char * path)		//A function to create a folder
{
	if (!CreateDirectory(path, NULL))
	{
		return;
	}
}
void DeleteFolder(const char* path)			//A function to delete a folder
{
	if (!RemoveDirectory(path))
	{
		return;
	}

}
int recBitMessage()							//Function to recieve a bit of message
{
	Sleep(1000);
	if (!dirExists(PATH))					//If the folder exists, bit is 0, else it's 1
		return 0;
	else
		return 1;
}

char readMessage()							//A function to read a character bit by bit
{
	int msgChar = 0;
	int multiplier = 1;
	for (int i = 0; i < 8; i++)
	{
		msgChar = msgChar * multiplier + recBitMessage();
		multiplier *= 10;
		//Sleep(100);
	}
	msgChar = binaryToDecimal(msgChar);
	return char(msgChar);
}

/*char readWithArr()
{
	int msgArray[8];
	int msgChar = 0;
	for (int i = 0; i < 8; i++)
	{
		shiftAndAppend(msgArray, recBitMessage());
	}
	msgChar = arrToInt(msgArray);
	return char(msgChar);
}
*/
int main() {
	int count = 0;
	char restart;
//	int cnt = 0;
	int msgArray[8] = {0,0,0,0,0,0,0,0};		//Instantiating the character window
	char msgChar;
//	bool startFlag = false;
//	bool endFlag = false;
	bool firstSign = false;
	bool secondSign = false;
	bool firstOff = false;
	bool secondOff = false;
	int cnt = 0;
	bool exit = true;
	cout << "Waiting to capture...\n";
//	cout << "If any problem happened during receiving, press R to restart.\n";
	while (exit) {					//Trying to find beggining
		if (!firstSign && !secondSign)				//Finding first preamble
		{
			shiftAndAppend(msgArray, recBitMessage());
			msgChar = arrToChar(msgArray);
			cnt++;
//			cout << msgChar << endl;
			if (msgChar == '%')
			{
				cout << "Probable signaling...\n";
				resetArray(msgArray);
				cnt = 0;
				firstSign = true;
			}


		}
		if (firstSign && !secondSign)			//Finding second preamble
		{
			shiftAndAppend(msgArray, recBitMessage());
			msgChar = arrToChar(msgArray);
			cnt++;
			if (cnt == 8)
			{
				resetArray(msgArray);
				cnt = 0;
				cout << endl << "Message started:\n";
				if (msgChar == '$')
					secondSign = true;
			}

		}
		if (firstSign && secondSign)		//Receiving message unlti first preamble for end receives
		{
			shiftAndAppend(msgArray, recBitMessage());
			msgChar = arrToChar(msgArray);
			cnt++;
			if (cnt == 8)
			{
				resetArray(msgArray);
				cnt = 0;
				cout <<"Received:" <<msgChar << endl;
				if (msgChar == '$')
				{
					firstOff = true;
					firstSign = false;
				}
					
			}

		}
		if (firstOff && !secondOff)			//Second preamble for end
		{
			shiftAndAppend(msgArray, recBitMessage());
			msgChar = arrToChar(msgArray);
			cnt++;
			if (cnt == 8)
			{
				resetArray(msgArray);
				cnt = 0;
				cout << msgChar << endl;
				if (msgChar == '%')
					secondOff = true;
			}

		}
		if (firstOff && secondOff)			//Message received
		{
			resetArray(msgArray);
			cout << "Message fully received!\n";
			cout << "Quiting...\n";
			CreateFolder(STOP);
			Sleep(5000);
			DeleteFolder(STOP);
			DeleteFolder(PATH);
			exit = false;
		}

		

		//Sleep(10);
	}
//	msgChar = readMessage();
//	if (msgChar != '%')
//		goto again;
/*	while (count < 2) {
		cout << "Waiting to capture...\n";
		msgChar = readMessage();
		if (msgChar != '%')
			count = 0;
		if (msgChar == '%')
			count++;
	}

	msgChar = 0;
	while (char(msgChar) != '%') {
		msgChar = readMessage();
		cout << "Reading: " << char(msgChar) << endl;
	}
	msgChar = readMessage();									//Second %
	if (char(msgChar) == '%')
		CreateFolder(STOP);
	else
		goto again;*/


	return 0;
}