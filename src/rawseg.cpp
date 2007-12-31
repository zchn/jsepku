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
#include<iomanip>
#include<cstdio>
#include<cstring>

#include "Dict.h"
#include "HzSeg.h"

//#include "./ChiAnalyzer/Analyzer/Analyzer.h"
//#include "./ChiAnalyzer/Analyzer/Analyzer.cpp"

CDict iDict;
CHzSeg iHzSeg;

using namespace std;

//const unsigned int HEADER_BUF_SIZE = 1024;
//const unsigned int MAX_DOC_ID = 21312;
bool good_char(unsigned char c);
void clean(char *content,int len,string &out);
  
int main(int argc, char* argv[])
{
	/*打开文件，并检查文件是否能被打开*/
  string terms,in_file_name=argv[1],in_idx_name=argv[2],out_file_name=in_file_name+".seg";


  ifstream fin(in_file_name.c_str());
  if (!fin) {
    cerr << "[ERROR]:Cannot open "<<in_file_name<<" for input"<<endl;
    return -1;
  }

  
  ifstream fidx(in_idx_name.c_str());
  if (!fidx) {
    cerr << "[ERROR]:Cannot open "<<in_idx_name<<" for input"<<endl;
    return -1;
  }

  
  ofstream fout(out_file_name.c_str());
  if(!fout){
    cerr<<"[ERROR]:Cannot open "<<out_file_name<<" for output"<<endl;
    return -1;
  }

  //Analyzer seger;

  //if(!seger.init()){
  //cerr<<"[ERROR]:Seger init() failed!"<<endl;
  //return -1;
  //}
  
  while (!fidx.eof()){
    string idx_line;
    getline(fidx,idx_line);
    if(idx_line.length() < 4)
      continue;
    unsigned int docid = 0,offset = 0;
    if(sscanf(idx_line.c_str(),"%x %x",&docid,&offset) != 2){
      cerr<<"[ERROR]:Irregular format found when reading "<<in_idx_name<<endl;
      continue;
    }
    
    string tmp = "";
    fin.seekg(offset,ios_base::beg);
    getline(fin,tmp);
	/*检查格式，分别对version:1.0,url等格式进行检查*/
    if(tmp != "version:1.0"){
      cerr<<"[ERROR]:docid - offset wrong, cannot find \"version:1.0\" in that offset"<<endl;
    }
    

    while(tmp.substr(0,4) != "url:"){
      if(fin.eof()){
        cerr<<"[ERROR]:EOF found when finding the string \"url:\""<<endl;
        return -1;
      }
      getline(fin,tmp);
    }

    cerr<<"[MESSAGE]Processing file "<<tmp<<" ...";
    
    while(tmp.substr(0,7) != "length:"){
      if(fin.eof()){
        cerr<<"[ERROR]:EOF found when finding the string \"length:\""<<endl;
        return -1;
      }
      getline(fin,tmp);
    }

    unsigned int length;
    if(sscanf(tmp.c_str(),"length:%d",&length) != 1){
      cerr<<"[ERROR]:error when reading the file length"<<endl;
      continue;
    }
    getline(fin,tmp);
    
    char *content = new char[length+1];
    memset(content, 0, length+1);
    fin.read(content, length);

    clean(content,length,tmp);

    delete [] content;
    
    // segment the document

    //string seged;
    tmp = iHzSeg.SegmentSentenceMM(iDict,tmp);
    //    if(seger.processString(tmp,seged)){
    fout<<hex<<setfill('0')<<setw(8)<<docid<<' '<< tmp<<endl;
    //}else{
    //cerr<<"[ERROR]:Seging file "<<docid<<" failed!"<<endl;
    //}
    cerr<<"Done!"<<endl;
  }
  return 0;
}
/**********************************************************************
函数名：clean
功能：判断字符串中的内容是否符合要求，并做相应的处理
输入参数：char类型的指针content，字符串的长度len以及string类型的字符串
返回值：无
***************************************************************************/
void clean(char *content,int len,string &out)
{
  char *curr = content;
  out = "";
  for(;curr <= content+len;curr++){
    if(good_char(*curr))
      out += *curr;
    else if(good_char(*(curr+1)))
      out += ' ';
  }
}

bool good_char(unsigned char c)
{
  if((c >= '0' && c <= '9')
     || (c >= 'A' && c <= 'Z')
     || (c >= 'a' && c <= 'z')
     || (c == '\'')
     || c >= 128)
    return true;
  else
    return false;
}
