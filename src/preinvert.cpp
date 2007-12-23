#include<iostream>

#include<fstream>
#include<string>
#include<iomanip>
using namespace std;
const int TERM_LEN=32;
int preinvert(string path)
{
	ifstream file1;
	file1.open(path.c_str());
	if(!file1.is_open())
	{
		cout<<"[ERROR]:file can't be opened"<<endl;
		return -1;
	}
	string file_name=path;
	/*������ļ�����.raw.segģʽ�ĳ�.piidxģʽ*/
	int len=file_name.length();
	len-=8;
	file_name.erase(len);/*ɾ������.raw.seg*/
	file_name+=".piidx";
	ofstream file2(file_name.c_str());
	while(!file1.eof())
	{
		string id;
		file1>>id;
		char temp;
		while(file1.peek()!='\n'&&!file1.eof())
		{
			string words;
			if(words.length()>(int)TERM_LEN) continue;
			file1>>words;
			while(file1.peek()==' ')
			{
				temp=file1.get();
			}
			file2<<setw(TERM_LEN)<<left<<words<<' '<<setw(8)<<left<<id<<endl;
		}
	}
	return 0;
}
int main(int argc,char *argv[])
{
	string file_name=argv[1];
	if(preinvert(file_name) != 0){
		return -1;
	}
	return 0;
}
