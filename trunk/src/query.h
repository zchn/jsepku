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

  void query(const string words,vector<struct s_result> &res);

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

  void process_term(const string record,
                    vector<struct s_result> &sub_result);

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
