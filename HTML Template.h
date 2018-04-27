#include "Library.h"


void GetTemplate(string &HTML)
{
	ifstream f;
	f.open("HTML.txt");
	if (!f)
	{
		perror("Khong mo duoc file.\n\n");
	}
	string temp;
	while (!f.eof())
	{
		getline(f, temp);
		HTML += temp;
		HTML += "\n";
	}
	f.close();
}