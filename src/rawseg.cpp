#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstring>

#include "Dict.h"
#include "HzSeg.h"

//#include "./ChiAnalyzer/Analyzer/Analyzer.h"
//#include "./ChiAnalyzer/Analyzer/Analyzer.cpp"

CDict iDict;

using namespace std;

//const unsigned int HEADER_BUF_SIZE = 1024;
//const unsigned int MAX_DOC_ID = 21312;
bool good_char(unsigned char c);
void clean(char *content,int len,string &out);
  
int main(int argc, char* argv[])
{
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
    if(tmp != "version:1.0"){
      cerr<<"[ERROR]:docid - offset wrong, cannot find \"version:1.0\" in that offset"<<endl;
    }
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
    CHzSeg iHzSeg;
    //string seged;
    tmp = iHzSeg.SegmentSentenceMM(iDict,tmp);
    //    if(seger.processString(tmp,seged)){
    fout<<hex<<setfill('0')<<setw(8)<<docid<<' '<< tmp<<endl;
    //}else{
    //cerr<<"[ERROR]:Seging file "<<docid<<" failed!"<<endl;
    //}
  }
  return 0;
}

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
