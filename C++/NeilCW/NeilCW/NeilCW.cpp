// NeilCW.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS
#define R 6371
#define TO_RAD (3.1415926536 / 180)

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

void getCoords(string line, string splitOn, vector<double> &results)
{
	auto cString = const_cast<char*>(line.c_str());
	char * token;

	token = strtok(cString, splitOn.c_str());
	while(token != nullptr)
	{
		results.push_back(stod(token));
		token = strtok(nullptr, splitOn.c_str());
	}
}

auto calculateDistance(double th1, double ph1, double th2, double ph2)
{
	double dx, dy, dz;
	ph1 -= ph2;	ph1 *= TO_RAD;	th1 *= TO_RAD;	th2 *= TO_RAD;	dz = sin(th1) - sin(th2);	dx = cos(ph1) * cos(th1) - cos(th2);	dy = sin(ph1) * cos(th1);	return (asin(sqrt(dx*dx + dy*dy + dz*dz) / 2) * 2 * R);
}

auto distBetweenCoords(vector<double> coords)
{
	double totalDistance = 0;
	for (auto i = 0; i + 3 < coords.size(); i += 2)
	{
		totalDistance += calculateDistance(coords[i], coords[i + 1], coords[i+2], coords[i+3]);
	}
	return totalDistance;
}


int main()
{
	string fileLine;
	vector<double> coordinates;
	auto firstLine = true;
	double totalDistance;
	ifstream coordinatesFile;
	coordinatesFile.open("coords.txt");
	if(!coordinatesFile)
	{
		cout << "File not found." << endl << endl;
		return -1;
	}
	while (getline(coordinatesFile, fileLine))
	{
		if (firstLine)
		{
			cout << "Journey Description: " << fileLine << endl;
			firstLine = false;
		}
		else
		{
			getCoords(fileLine,", " , coordinates);
		}
	}
	if (coordinates.size() % 2 != 0)
	{
		cout << "Coordinates number uneven, please check the format of the input file." << endl;
		return -1;
	}

	totalDistance = distBetweenCoords(coordinates);
	cout << "The total distance for the journey is: " << totalDistance << "KMs" << endl;

	coordinatesFile.close();
	return 0;
}

