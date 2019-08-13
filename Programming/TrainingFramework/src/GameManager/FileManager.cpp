// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <list>
using namespace std;


static std::list<int> readScore()
{
	std::list<int>	m_listScore;
    std::ifstream fileInput("..//score.txt");

	if (fileInput.fail())
		std::cout << "Failed to open this file!" << std::endl;

	while (!fileInput.eof())
	{
		int n;
		if (fileInput >> n)
			m_listScore.push_back(n);
	}

	fileInput.close();
	return m_listScore;
}
static void writeScore(int score)
{
	list<int> m_listScore = readScore();
	for (auto a : m_listScore)
	{
		if (a == score) return;
	}

	m_listScore.push_back(score);
	m_listScore.sort();
	m_listScore.pop_front();
	ofstream outfile("..//score.txt");
	for (auto a : m_listScore)
	{
		outfile << a << endl;
	}
	outfile.close();
}

