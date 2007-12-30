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
  c_query(const string path){
    iidx_file.open(path.c_str());
    if(!iidx_file.is_open())
      {
        cerr<<"[ERROR]:file "<<path<<" can't be opened"<<endl;
      }
  }
  ~c_query(){
    iidx_file.close();
  }

  void query(const string words,vector<struct s_result> &res)
  {
    string m_words;
    m_words=cut_words(words);
    creat_map();
    string keywords;
    unsigned int i=0;
    while(i<m_words.length())
      {
        for(;i<m_words.length();i++)/*cut words by space,and search one word each time*/
          {
            if(m_words[i]==' ') break;
            keywords+=m_words[i];
          }
        string record=get_term(keywords);
        vector<s_result> temp_vector;/*this temp is what i will give to your function*/
        process_term(record,temp_vector);
        res_merge(temp_vector,res);/*this maybe wrong*/
      }
  }
 
  string get_cuted(){
    return cuted;
  }

  string cut_words(const string words){
    //string seged;
    cuted = iHzSeg.SegmentSentenceMM(iDict,words);
    return cuted;
  }

  void creat_map()
  {
    string word;
    int site;
    while(!iidx_file.eof()){
      iidx_file>>word;
      site=iidx_file.tellg();
      site-=word.length();
      map_word.insert(pair<string,int>(word,site));
      getline(iidx_file,word);
      word="";
    }
     
  }

  string get_term(const string word)
  {
    string words;
    map<string,int>::iterator item;
    item=map_word.find(word);
    int site=item->second;
    iidx_file.seekg(site);
    getline(iidx_file,words);
    cout<<words<<endl;
    return words;
  }

  void process_term(const string record,vector<struct s_result> &sub_result)
  {
    int len;
    len=record.length();
    string words;
    s_result temp;
    string c_num1,c_num2;
    int num1=-1,num2=-1;
    int i=0;
    while(record[i]==' ')i++;
    for(;i<len;i++)
      {
        if(record[i]==' ') break;
        words+=record[i];
      }
    while(record[i]==' ') i++;
    while(i<len)
      {
        for(int a=0;a<8;a++,i++)
          {
            c_num1+=record[i];
          }
        cout<<c_num1;
        sscanf(c_num1.c_str(),"%x",&num2);
        c_num1="";
        if(num1==-1)
          {
            num1=num2;
            temp.docid=num1;
            temp.weight=0;
            while(record[i]==' ') i++;
            continue;
          }
        else if(num1==num2)
          {
            temp.weight++;
          }
        else
          {
            sub_result.push_back(temp);
            num1=num2;
            temp.docid=num1;
            temp.weight=0;
          }
        while(record[i]==' ') i++;
      }
  }

 
  void res_merge(vector<struct s_result> &final,
                 vector<struct s_result> &sub_result){
    sort(sub_result.begin(),sub_result.end(),comp_docid);
    if(final.size() == 0){
      final = sub_result;
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
  }    
};

#endif
