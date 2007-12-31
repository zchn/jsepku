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
#ifndef _QUERY_H_
#define _QUERY_H_

#include<algorithm>
#include<map>
#include<string>
#include<fstream>
#include<vector>
#include<iterator>

#include "Dict.h"
#include "HzSeg.h"

using namespace std;

struct s_result{
  int docid;
  int weight;
};


bool comp_weight(const struct s_result &a,const struct s_result &b){
  return a.weight < b.weight;
}

bool comp_docid(const struct s_result &a,const struct s_result &b){
  return a.docid < b.docid;
}

class c_query{
private:
  CDict iDict;
  CHzSeg iHzSeg;
  string cuted;
  map<string,int> map_word;
  ifstream iidx_file;
public:
  c_query(const string path)
  {
    iidx_file.open(path.c_str());
    if(!iidx_file){
      cerr<<"[ERROR]:file "<<path<<" can't be opened"<<endl;
    }
    creat_map();
  }
  
  ~c_query(){
    iidx_file.close();
  }

  void out_debug(string out){
    cerr<<"[DEBUG]:"<<out<<endl;
  }
  
  void query(const string words,vector<struct s_result> &res)
  {
    res.clear();
    string m_words;
    m_words=cut_words(words);
    out_debug("words cuted :"+cuted);
    string keywords;
    unsigned int i=0;
    while(i<m_words.length()){
      keywords = "";
      for(;i<m_words.length();i++){
        if(m_words[i]==' ') break;
        keywords+=m_words[i];
      }
      string record=get_term(keywords);
      if(record == ""){
        return;
      }
      vector<s_result> temp_vector;/*this temp is what i will give to your function*/
      process_term(record,temp_vector);
      res_merge(res,temp_vector);/*this maybe wrong*/
      while(i < m_words.length() && m_words[i] == ' ') i++;
    }
    sort(res.begin(),res.end(),comp_weight);
  }
 
  string get_cuted(){
    return cuted;
  }

  string cut_words(const string words){
    //string seged;
    cuted = iHzSeg.SegmentSentenceMM(iDict,words);
    return cuted;
  }
/**********************************************************************
函数名：creat_map
功能：将文本中每个词和它们的地址建立联系，便于以后对其进行查找。
输入参数：无
返回值：无
***************************************************************************/
  void creat_map()
  {
    string word;
    int site;
    out_debug("begin create_map");
    while(!iidx_file.eof()){
      site=iidx_file.tellg();
      iidx_file>>word;
      map_word.insert(pair<string,int>(word,site));
      getline(iidx_file,word);
    }
    iidx_file.clear();
    out_debug("map created!");
    // map<string,int>::iterator it;
    // for(it = map_word.begin(); it != map_word.end(); it++){
    //   cerr<<"[DEBUG]:map has "<<it->first<<' '<<it->second<<endl;
    // }

  }
/**********************************************************************
函数名：get_term
功能：将所要查询的记录的地址读出，并从文件中读取相应的内容
输入参数：一个string类型的字符串,也就是所要查找的字符串。
返回值：所找到相应的内容，也是一个string类型的字符串。
***************************************************************************/
  string get_term(const string word)
  {
    string words;
    map<string,int>::iterator item;
    item=map_word.find(word);
    if(item == map_word.end())
      return string("");
    int site=item->second;
    iidx_file.seekg(site,ios_base::beg);
    if(!iidx_file){
      cerr<<"[ERROR]:iidx file broken when seeking word term!"<<endl;
    }
    getline(iidx_file,words);
    cerr<<"[DEBUG]:find word "<<words<<" for "<<word<<" at "<<site<< " !"<<endl;
    return words;
  }
/**********************************************************************
函数名：process_term
功能：将所找的记录的内容，通过算法转化为权值，储存在vector的结构体数组中
输入参数：string类型的记录以及用来储存的vector数组
返回值：无
***************************************************************************/
  void process_term(const string record,
                    vector<struct s_result> &sub_result)
  {
    cerr<<"[DEBUG]:Extracting docids from "<<record<<endl;
    istrstream rec(record.c_str());
    s_result tmp_res;
    string head;
    int tmp;
    sub_result.clear();
    if(rec){
      rec>>head;
      cout<<"[DEBUG]:head has "<<head<<endl;
    }else{
      cerr<<"[ERROR]:record "<<record<<" invalid"<<endl;
      return;
    }
    rec>>hex>>tmp_res.docid;
    tmp_res.weight = 1;
    while(rec){
      rec>>hex>>tmp;
      if(tmp_res.docid == tmp){
        tmp_res.weight++;
      }else{
        cerr<<"[DEBUG]:Get a doc "<<tmp_res.docid<<'-'<<tmp_res.weight<<endl;
        sub_result.push_back(tmp_res);
        tmp_res.docid = tmp;
        tmp_res.weight = 1;
      }
    }
    cerr<<"[DEBUG]:Get a doc "<<tmp_res.docid<<'-'<<tmp_res.weight<<endl;
    sub_result.push_back(tmp_res);
  }    
    // int len;
    // len=record.length();
    // string words;
    // s_result temp;
    // string c_num1,c_num2;
    // int num1=-1,num2=-1;
    // int i=0;
    // while(i<record.length() && record[i]==' ')i++;
    // for(;i<len;i++){
    //   if(record[i]==' ') break;
    //   words+=record[i];
    // }
    // while(record[i]==' ') i++;
    // while(i<len){
    //   for(int a=0;a<8;a++,i++){
    //     c_num1+=record[i];
    //   }
    //   sscanf(c_num1.c_str(),"%x",&num2);
    //   c_num1="";
    //   if(num1==-1)
    //     {
    //         num1=num2;
    //         temp.docid=num1;
    //         temp.weight=0;
    //         while(record[i]==' ') i++;
    //         continue;
    //       }
    //     else if(num1==num2)
    //       {
    //         temp.weight++;
    //       }
    //     else
    //       {
    //         sub_result.push_back(temp);
    //         num1=num2;
    //         temp.docid=num1;
    //         temp.weight=0;
    //       }
    //     while(record[i]==' ') i++;
    //   }
 /**********************************************************************
函数名：res_merge
功能：将上个函数得到的每个关键词的vector转化为一个每个文档的最后权值。
输入参数：用于储存最后权值的final的vector，一个用于计算权值的sub_result
返回值：无
***************************************************************************/
  void res_merge(vector<struct s_result> &final,
                 vector<struct s_result> &sub_result)
  {
    out_debug("Now I'm in res_merge()");
    sort(sub_result.begin(),sub_result.end(),comp_docid);
    if(final.size() == 0){
      final = sub_result;
      out_debug("Now I'm leaving res_merge()");
      return;
    }else{
      vector<struct s_result>::iterator it_final,it_sub;
      it_sub = sub_result.begin();
      for(it_final = final.begin(); it_final != final.end();){
        for( ;(*it_final).docid > (*it_sub).docid;it_sub++);
        if((*it_final).docid == (*it_sub).docid){
          (*it_final).weight += (*it_sub).weight;
          it_final++;
          it_sub++;
        }else{
          it_final = final.erase(it_final);
        }
      }
    }
    out_debug("Now I'm leaving res_merge()");
  }
};

#endif
