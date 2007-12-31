#include<vector>
#include<iostream>
#include<strstream>


using namespace std;

#include"query.h"

class c_raw_record{
public:
  string title;
  string digest;
  string url;
};

c_query *query;
ifstream rawfile;
ifstream didx_file;

void output(string str){
  cout<<str;
}

int docid2offset(int id)
{
  int iidx_off = id * 18;
  didx_file.seekg(iidx_off);
  string tmp;
  getline(didx_file,tmp);
  int t,ret;
  sscanf(tmp.c_str(),"%x %x",&t,&ret);
  return ret;
}

void get_content(int offset,string &content){
  content.clear();
  rawfile.seekg(offset,ios_base::beg);
  string tmp;
  getline(rawfile,tmp);
  if(tmp != "version:1.0"){
    cerr<<"[ERROR]:I read "<<tmp
        <<" first while expecting verson when getting the content acorrding to offset!"<<endl;
  }
  content += tmp;
  getline(rawfile,tmp);
  while(tmp != "verson:1.0"){
    content += tmp;
    getline(rawfile,tmp);
  }
}

void get_title_url(istrstream &cont,c_raw_record &rec){
  string tmp;
  
  getline(cont,tmp);
  while(tmp.substr(0,4) != "url:")
    getline(cont,tmp);

  rec.url = tmp;
  unsigned int pos = tmp.rfind('/');
  if(pos == string::npos){
    pos = tmp.rfind(':');
  }
  rec.title = tmp.substr(pos+1);
}

void get_digest(const string cuted,const string &content,istrstream &cont,c_raw_record &rec){
  int *beg = new int[content.size()];
  int *end = new int[content.size()];
  memset(beg,0,sizeof(int)*content.size());
  memset(end,0,sizeof(int)*content.size());
  rec.digest = "";
  string tmp;
  while(cont){
    cont>>tmp;
    if(cuted.find(tmp) != string::npos){
      unsigned int i,pos = cont.tellg();
      for(i = pos-1; pos-i < 15; i--){
        if((unsigned char)content[i] >= 128)
          i--;
      }
      i++;
      beg[i]++;

      for(i = pos; i-pos < 10 && i < content.size(); i++){
        if((unsigned char)content[i] >= 128)
          i++;
      }
      i--;
      end[i]++;
    }
  }
  unsigned int j;
  int print = 0;
  for(j = 0; j < content.size(); j++){
    print += beg[j];
    print -= end[j];
    if(print){
      rec.digest += content[j];
    }
  }
}
  


void make_rec(string cuted, s_result res,c_raw_record &rec)
{
  int offset = docid2offset(res.docid);
  string content;
  istrstream cont(content.c_str());
  get_content(offset,content);
  get_title_url(cont,rec);
  get_digest(cuted,content,cont,rec);
}


void get_telnet_result(string words)
{
  vector<s_result> result;
  query->query(words,result);
  if(result.size() == 0){
    output("No files found!\n");
    return;
  }
  string cuted = query->get_cuted();
  vector<s_result>::iterator it;
  for(it = result.begin(); it != result.end(); it++){
    c_raw_record record;
    make_rec(cuted,*it,record);
    output(record.title+'\n');
    output(record.digest+'\n');
    output(record.url+"\n\n");
  }
}

int main(int argc,char **argv){
  
  string rawfile_name(argv[1]);
  string iidx_file_name(argv[2]);
  string didx_file_name(argv[3]);
  rawfile.open(rawfile_name.c_str());
  if(!rawfile){
    cerr<<"[ERROR]:raw file "<<rawfile_name<<" cannot be opened!"<<endl;
    return -1;
  }
  didx_file.open(didx_file_name.c_str());
  if(!didx_file){
    cerr<<"[ERROR]:raw file "<<didx_file_name<<" cannot be opened!"<<endl;
    return -1;
  }
  query = new c_query(iidx_file_name);

  string tmp;
  cin>>tmp;
  while(tmp != "@!"){
    get_telnet_result(tmp);
  }
  return 0;
}
