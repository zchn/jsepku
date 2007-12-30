#include<algorithm>
#include<map>
#include<string>
#include<fstream>
#include<vector>
#include<iterator>

#include "Dict.h"
#include "HzSeg.h"

using namespace std;

bool comp_weight(const struct s_result &a,const struct s_result &b){
  return a.weight < b.weight;
};

bool comp_docid(const struct s_result &a,const struct s_result &b){
  return a.docid < b.docid;
};

class c_query{
 private:
  struct s_result{
    int docid;
    int weight;
  };
  CDict iDict;
  CHzSeg iHzSeg;
  string cuted;
  map <string,int> find_site;
 public:
  c_query(){}
  
  void query(const string words,vector<struct s_result> &res);

  string cut_words(const string words){
    //string seged;
    cuted = iHzSeg.SegmentSentenceMM(iDict,words);
    return cuted;
  }

  void creat_map(const string path)
  {
    string word;
    int site;
    ifstream file1;
    file1.open(path.c_str());
    if(!file1.is_open()){
      cerr<<"[ERROR]:file "<<path<<" can't be opened"<<endl;
    }
    while(!file1.eof()){
      file1>>word;
      site=file1.tellg();
      site-=word.length();
      find_site.insert(pair<string,int>(word,site));
      getline(file1,word);/*让指针跳到下一行*/
      word="";
    }
    file1.close();
  }

  string get_term(const string path,const string word)
  {
    string words;
    map<string,int>::iterator item;
    item=find_site.find(word);
    int site=item->second;
    ifstream file1;
    file1.open(path.c_str());
    if(!file1.is_open())
      {
        cerr<<"[ERROR]:file "<<path<<" can't be opened"<<endl;
      }
    file1.seekg(site);
    getline(file1,words);
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
