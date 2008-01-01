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
#include<cstring>

using namespace std;

#include<sys/types.h>
#include<dirent.h>

string RAWFILENAME;
/**********************************************************************
函数名：crawl
功能：将所有的文本合成一个内用的大文本，并且在文本之间添加固定格式的文本信息
输入参数：char类型的指针dir_name用来记录输入文件的路径
返回值：0表示添加无问题
***************************************************************************/
int crawl(ofstream &raw,const char *dir_name)
{
	/*检测是否成功打开文件*/
  DIR *dir;
  dir = opendir(dir_name);
  if(dir == NULL){
    cerr<<"[ERROR]:Error in opening dir "<<dir_name<<endl;
    return -1;
  }
  struct dirent *sub;
  for(sub = readdir(dir); sub != NULL; sub = readdir(dir)){
    if(strcmp(sub->d_name,".")==0
       ||strcmp(sub->d_name,"..")==0
       ||strcmp(sub->d_name,RAWFILENAME.c_str())==0) continue;
    if(sub->d_type == DT_DIR){
      //cerr<<"[DEBUG]:I'm a dir"<<endl;
      crawl(raw,(string(dir_name)+"/"+sub->d_name).c_str());
    }
    if(sub->d_type == DT_REG){
      //cerr<<"[DEBUG]:I'm a file "<<sub->d_name<<endl;
      ifstream in((string(dir_name)+"/"+sub->d_name).c_str());
      if(!in){
        cerr<<"[ERROR]:Fail to open file "<<dir_name<<'/'<<sub->d_name<<endl;
        continue;
      }
	  /*将文章信息等内容添加进去*/
      raw<<"version:1.0"<<endl;
      raw<<"url:"<<dir_name<<'/'<<sub->d_name<<endl;
      int length;
      in.seekg(0,ios_base::end);
      length = in.tellg();
      in.seekg(0,ios_base::beg);
      raw<<"length:"<<length<<endl;
      raw<<endl;
      while(!in.eof()){
        string tmp;
        getline(in,tmp);
        raw<<tmp<<endl;
      }
      raw<<endl;
    }
  }
  return 0;
}

int main(int argc, char **argv)
{
  if(argc < 3){
    cerr<<"USAGE: "<<argv[0]<<" dir_path proj_name"<<endl;
  }
  string path = argv[1];
  string proj_name = argv[2];

  while(path[path.length()-1] == '/'){
    path.erase(path.length()-1);
  }
  
  RAWFILENAME = proj_name+".raw";
      
  ofstream raw((path+"/"+RAWFILENAME).c_str());
  if(!raw){
    cerr<<"[ERROR]:Error when opening tianwang raw file "<<argv[1]<<"/"<<RAWFILENAME<<" to write!"<<endl;
    return -1;
  }

  if(crawl(raw,argv[1]) != 0){
    raw.close();
    return -1;
  }

  raw.close();
  return 0;
}
