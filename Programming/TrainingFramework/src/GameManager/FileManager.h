#include <list>
class FileManager
{
public:
	static void writeScore(int score);
	static std::list<int> readScore();
};