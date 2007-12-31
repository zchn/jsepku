#include<vector>
#include<iostream>
#include<strstream>
#include<cstring>

#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_PORT 7891 // define the defualt connect port id
#define LENGTH_OF_LISTEN_QUEUE 10 //length of listen queue in server
#define BUFFER_SIZE 255
const char WELCOME_MESSAGE[] =
  "88888888888888888888888888888888888888888888888888888888888888888888888\n\r"
  "                                                                       \n\r"
  "   ####      ####   ######    ##    #####     ###   ##  ##             \n\r"
  "    ##      #    #  ##  ##   #  #   ##  ##   ## ##  ##  ##             \n\r"
  "    ##      #       ##      ##  ##  ##  #   ##      ##  ##             \n\r"
  "    ##  ##   ####   #####   ######  ####    ##      ######   Happy     \n\r"
  "    ##  ##       #  ##      ##  ##  ## ##   ##      ##  ##      New    \n\r"
  " ## ##      #    #  ##  ##  ##  ##  ##  ##   ## ##  ##  ##        Year!\n\r"
  "  ###        ####   ######  ##  ##  ##   #    ###   ##  ##             \n\r"
  "                                                    ----by Joyan     \n\r"
  "                                                          & Jiezhong \n\r"  
  "88888888888888888888888888888888888888888888888888888888888888888888888\n\r"
  "\n\r"
  "Just input your query then ENTER.(^@^)(input \"@bye\" to quit)\n\r";
  
 
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
int servfd,clifd;

void output(string str){
  send(clifd,str.c_str(),str.size(),0);
}

int docid2offset(int id)
{
  int iidx_off = id * 18;
  didx_file.seekg(iidx_off);
  string tmp;
  getline(didx_file,tmp);
  int t,ret;
  if(sscanf(tmp.c_str(),"%x %x",&t,&ret)!= 2){
    cerr<<"[ERROR]:docid to offset failed! "<<id<<endl;
  }
  return ret;
}

void get_content(int offset,string &content){
  cerr<<"[DEBUG]:Now I'm in get_content("<<offset<<",content)"<<endl;
  content.clear();
  rawfile.clear();
  rawfile.seekg(offset,ios_base::beg);
  string tmp;
  if(!rawfile){
    cerr<<"[ERROR]:RAW file broken!"<<endl;
  }
  getline(rawfile,tmp);
  cerr<<"[DEBUG]:read firstline from rawfile offset "<<tmp<<endl;
  if(tmp != "version:1.0"){
    cerr<<"[ERROR]:I read "<<tmp
        <<" first while expecting verson when getting the content acorrding to offset!"<<endl;
  }
  content += tmp+'\n';
  getline(rawfile,tmp);
  while(rawfile && tmp != "version:1.0"){
    content += tmp + '\n';
    //cerr<<"[DEBUG]:read from rawfile offset "<<tmp<<endl;
    //cerr<<"[DEBUG]:CONTENT:"<<tmp<<endl;
    getline(rawfile,tmp);
  }
  content += tmp + '\n';

  cerr<<"[DEBUG]:Now I'm leaving get_content"<<endl;
}

void get_title_url(istrstream &cont,c_raw_record &rec){
  string tmp;
  cerr<<"[DEBUG]:Now I'm in get_title_url()"<<endl;
  getline(cont,tmp);
  cerr<<"[DEBUG]:first str: "<<tmp<<endl;
  while(tmp.substr(0,4) != "url:")
    getline(cont,tmp);

  rec.url = tmp;
  unsigned int pos = tmp.rfind('/');
  if(pos == string::npos){
    pos = tmp.rfind(':');
  }
  rec.title = tmp.substr(pos+1);
  cerr<<"[DEBUG]:Now I'm leaving get_title_url(). Got "<<rec.title<<'-'<<rec.url<<endl;
}

void get_digest(const string cuted,const string &content,istrstream &cont,c_raw_record &rec){
  cerr<<"[DEBUG]:Now I'm in get_digest()."<<endl;
  int *beg = new int[content.size()];
  int *end = new int[content.size()];
  memset(beg,0,sizeof(int)*content.size());
  memset(end,0,sizeof(int)*content.size());
  rec.digest = "";
  istrstream cuted_s(cuted.c_str());
  string tmp;
  while(cuted_s){
    cuted_s>>tmp;
    unsigned int pos = 0;
    while((pos = content.find(tmp,pos)) != string::npos){
      unsigned int i;
      for(i = pos-1; pos-i < 10; i--){
        if((unsigned char)content[i] >= 128)
          i--;
      }
      i++;
      beg[i]++;

      for(i = pos; i-pos < 15 && i < content.size(); i++){
        if((unsigned char)content[i] >= 128)
          i++;
      }
      end[i]++;
      pos++;
    }
  }
  unsigned int j;
  int print = 0;
  for(j = 0; j < content.size(); j++){
    print += beg[j];
    print -= end[j];
    if(print){ 
      if((unsigned char)content[j] < ' ')
        rec.digest += ' ';
      else
        rec.digest += content[j];
    }
  }
  cerr<<"[DEBUG]:Now I'm leaving get_digest()."<<endl;
}
  


void make_rec(string cuted, s_result res,c_raw_record &rec)
{
  cerr<<"[DEBUG]:Now I'm in make_rec("<<cuted<<")"<<endl;
  int offset = docid2offset(res.docid);
  string content;
  get_content(offset,content);
  istrstream cont(content.c_str());
  if(!cont){
    cerr<<"[ERROR]:Cannot init istrstream~"<<endl;
  }
  get_title_url(cont,rec);
  get_digest(cuted,content,cont,rec);
  cerr<<"[DEBUG]:Now I'm leaving make_rec()"<<endl;
}


void get_telnet_result(string words)
{
  output("\n\rThe files including words : "+words+"\n\r");
  cerr<<"[DEBUG]Now I'm in get_telnet_result"<<endl;
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
    output("\n\r++++++TITLE:"+record.title+"\n\r");
    output("-----------------------------------------------\n\r");
    output(record.digest+"\n\r");
    output("-----------------------------------------------\n\r");
    output("++++++"+record.url+"\n\r\n\r");
  }
  char buf[10];
  sprintf(buf,"%d",result.size());
  output("Find files containing "+words+" In total : "+buf+"\n\r");
}

void start_serv()
{
  struct sockaddr_in servaddr,cliaddr;
 
  if ((servfd = socket(AF_INET,SOCK_STREAM,0)) < 0){
    cerr<<"[ERROR]:Create socket error"<<endl;
    return;
  }
  
  memset(&servaddr,0,sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(SERVER_PORT);
  servaddr.sin_addr.s_addr = htons(INADDR_ANY); 

  if(bind(servfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
    cerr<<"[ERROR]:Fail to bind~"<<endl;
    return;
  }

  if (listen(servfd,LENGTH_OF_LISTEN_QUEUE) < 0){
    cerr<<"[ERROR]:Fail to listen~"<<endl;
    return;
  }
  
  while (1){
    char buf[BUFFER_SIZE];
    socklen_t length = sizeof(cliaddr);
    cerr<<"[LOG]: Start listening on port 7891...."<<endl;
    clifd = accept(servfd,(struct sockaddr*)&cliaddr,&length);

    if(clifd < 0){
      cerr<<"[ERROR]:Fail to accept~! continuing"<<endl;
      continue;
    }
    strcpy(buf,WELCOME_MESSAGE);
    cerr<<"[LOG]:Receive conn from IP:("<<inet_ntoa(cliaddr.sin_addr)<<":"<<ntohs(cliaddr.sin_port)<<')'<<endl;
    send(clifd,buf,strlen(buf)+1,0);
    int size = recv(clifd,buf,BUFFER_SIZE,0);
    buf[size] = 0;
    while(string(buf).substr(0,4) != "@bye"){
      get_telnet_result(buf);
      size = recv(clifd,buf,BUFFER_SIZE,0);
      buf[size] = 0;
    }
    close(clifd);
  }//exit
  close(servfd);
}


int main(int argc,char **argv){
  if(argc != 4){
    cout<<argv[0]<<" raw iidx didx"<<endl;
    return 1;
  }
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
  start_serv();
  return 0;
}
