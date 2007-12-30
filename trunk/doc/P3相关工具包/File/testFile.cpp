/*
  testFile.cpp : test case for class File
  associated: File.h, File.cpp
  created: 12/21/2007, WANG Dong
*/
#include <iostream>
#include "File.h"

using namespace std;

void testFile() {
	#ifdef _WIN32
	File file("C:\\WINDOWS\\Resources\\Themes");
#else
	File file("/boot");
#endif
	vector<string> filelist = file.list();
	cout<<file.getPath()<<endl;
	vector<string>::const_iterator it;
	for(it = filelist.begin(); it != filelist.end(); it++) {
		cout<<"-" + *it<<endl;
	}
}

int main() {
	testFile();
	return 0;
}