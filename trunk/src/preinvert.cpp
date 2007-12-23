#include<iostream>

#include<fstream>
#include<string>
#include<iomanip>
using namespace std;
const int TERM_LEN=16;
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
	/*将输出文件名由.raw.seg模式改成.piidx模式*/
	int len=file_name.length();
	len-=8;
	file_name.erase(len);/*删除最后的.raw.seg*/
	file_name+=".piidx";
	ofstream file2(file_name.c_str());
	while(!file1.eof())
	{
		string id;
		file1>>id;
		while(file1.peek()!='/n'&&!file1.eof())
		{
			string words;
			if(words.length()>TERM_LEN) continue;
			else if(words.length()<TERM_LEN&&words.length()!=0) 
			{
				for(int i=words.length();i<TERM_LEN;i++)
				{
					words[i]=' ';
				}
			}
			file1>>words;
			file2<<setw(TERM_LEN)<<left<<words<<' '<<setw(TERM_LEN)<<left<<id<<' ';
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