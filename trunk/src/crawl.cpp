// ����ϵر�֤��
    
// ���Լ��������������������ӷ�������Ƶ���������й�����
// ��������������У���������ʲô���Ѷ�������ˣ���ô���ҽ��ڳ���ʵϰ������
// ��ϸ���о��������������⣬�Լ����˸��ҵ���ʾ��

// �ڴˣ��Ҹ�л XXX, ��, XXX���ҵ������Ͱ���������ı����У��һ��������ᵽ
// �����ڸ����������ҵİ�����

// �ҵĳ������з������õ�����������ĵ�֮����
// ����̲ġ����ñʼǡ����ϵ�Դ�����Լ������ο����ϵĴ����,
// �Ҷ��Ѿ��ڳ����ע����������ע�������õĳ�����
// �Ҵ�δû��Ϯ�����˵ĳ���Ҳû�е��ñ��˵ĳ���
// �������޸�ʽ�ĳ�Ϯ����ԭ�ⲻ���ĳ�Ϯ��

// �ұ�д������򣬴���û�����Ҫȥ�ƻ���������������ϵͳ��������ת��
    
// ��־�� ����
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>

using namespace std;

#include<sys/types.h>
#include<dirent.h>

string RAWFILENAME;
/**********************************************************************
��������crawl
���ܣ������е��ı��ϳ�һ�����õĴ��ı����������ı�֮����ӹ̶���ʽ���ı���Ϣ
���������char���͵�ָ��dir_name������¼�����ļ���·��
����ֵ��0��ʾ���������
***************************************************************************/
int crawl(ofstream &raw,const char *dir_name)
{
	/*����Ƿ�ɹ����ļ�*/
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
	  /*��������Ϣ��������ӽ�ȥ*/
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
