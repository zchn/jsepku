#include<iostream>
#include<fstream>
#include<string>

using namespace std;

#include<sys/types.h>
#include<dirent.h>

const char RAWFILENAME[] = "tianwang.raw";

int crawl(ofstream &raw,const char *dir_name)
{
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
       ||strcmp(sub->d_name,RAWFILENAME)==0) continue;
    if(sub->d_type == DT_DIR){
      //cerr<<"[DEBUG]:I'm a dir"<<endl;
      crawl(raw,(string(dir_name)+"/"+sub->d_name).c_str());
    }
    if(sub->d_type == DT_REG){
      //cerr<<"[DEBUG]:I'm a file "<<sub->d_name<<endl;
      ifstream in((string(dir_name)+"/"+sub->d_name).c_str());
      if(!in){
        cerr<<"[ERROR]:Fail to open file "<<dir_name<<'/'<<sub->d_name<<endl;
        c!mountontinue;
      }
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
  ofstream raw((string(argv[1])+"/"+RAWFILENAME).c_str());
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
