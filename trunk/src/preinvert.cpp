// 我真诚地保证：
    
// 我自己独立地完成了整个程序从分析、设计到编码的所有工作。
// 如果在上述过程中，我遇到了什么困难而求教于人，那么，我将在程序实习报告中
// 详细地列举我所遇到的问题，以及别人给我的提示。

// 在此，我感谢 XXX, …, XXX对我的启发和帮助。下面的报告中，我还会具体地提到
// 他们在各个方法对我的帮助。
 
// 我的程序里中凡是引用到其他程序或文档之处，
// 例如教材、课堂笔记、网上的源代码以及其他参考书上的代码段,
// 我都已经在程序的注释里很清楚地注明了引用的出处。

// 我从未没抄袭过别人的程序，也没有盗用别人的程序，
// 不管是修改式的抄袭还是原封不动的抄袭。

// 我编写这个程序，从来没有想过要去破坏或妨碍其他计算机系统的正常运转。
    
// 陈志杰 揭忠
#include<iostream>

#include<fstream>
#include<string>
#include<iomanip>
using namespace std;
const int TERM_LEN=32;
/**********************************************************************
函数名：preinvert
功能：将.raw.seg模式的文件转化为.piidx模式的文件。
输入参数：文件路径
返回值：当转化成功时，返回0，否则返回-1.
***************************************************************************/
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
