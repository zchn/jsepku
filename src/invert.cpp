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
struct word_info
{
	string words;
	string id;
};
/**********************************************************************
函数名：invert
功能：将.piidx.sort类型的文件转化为.iidx类型的文件，有关文件类型的说明请参考解题报告。
输入参数：一个string类型的文件路径。
返回值：如果成功则返回0，否则返回-1。
***************************************************************************/
int invert(string path)
{
	ifstream in_piidx_sort(path.c_str());
	if(!in_piidx_sort.is_open())
	{
		cerr<<"[ERROR]:piidx file can't be opened"<<endl;
		return -1;
	}
	/*将文件名中的.piidx.sort转化为.iidx*/
	word_info *words_info;
	words_info=new word_info[2];
	string out_name=path;
	int len=out_name.length();
	len-=11;
	out_name.erase(len);
	out_name+=".iidx";
	ofstream out_iidx(out_name.c_str());
	in_piidx_sort>>words_info[0].words;
	in_piidx_sort>>words_info[0].id;
	out_iidx<<setw(TERM_LEN)<<left<<words_info[0].words;
	out_iidx<<setw(8)<<left<<words_info[0].id<<' ';
	/*按照.iidx的要求从左开始输出*/
	while(!in_piidx_sort.eof())
	{
		in_piidx_sort>>words_info[1].words;
		in_piidx_sort>>words_info[1].id;
		if(words_info[1].words==words_info[0].words) 
		{
			out_iidx<<setw(8)<<left<<words_info[1].id<<' ';
		}
		else
		{
			out_iidx<<endl<<setw(TERM_LEN)<<left<<words_info[1].words;
			out_iidx<<setw(8)<<left<<words_info[1].id<<' ';
		}
		words_info[0].words=words_info[1].words;
		words_info[0].id=words_info[1].id;
		words_info[1].words="";
		words_info[1].id="";
	}
	return 0;
}

int main(int argc,char *argv[])
{
	string file_name=argv[1];
	if(invert(file_name) != 0){
		return -1;
	}
	return 0;
}
