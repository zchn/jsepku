#pragma warning(disable:4786)
#include<map>
#include<iostream>
#include<string>
#include<fstream>
#include<vector>

using namespace std;



class c_query
{
private:
	struct s_result
	{
		int docid;
		int weight;
	};
public:
	void query(const string words,vector<struct s_result> &res);

	string cut_words(const string words)
	{
		return string();
	}	

	void creat_map(const string path,map <string,int> &find_site)
	{
		string word;
		int site;
		ifstream file1;
		file1.open(path.c_str());
		if(!file1.is_open())
		{
			cerr<<"[ERROR]:file "<<path<<" can't be opened"<<endl;
		}
		while(!file1.eof())
		{
			file1>>word;
			site=file1.tellg();
			site-=word.length();
			find_site.insert(pair<string,int>(word,site));
			getline(file1,word);/*让指针跳到下一行*/
			word="";
		}
		file1.close();
	}

	string get_term(const string path,const string word,map <string,int> &find_site)
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

	void process_term(const string record, vector<struct s_result> &sub_result);

	void res_merge(vector<struct s_result> &final,const vector<struct s_result> &sub_result);
};

/*int main()
{
	string words,path;
	cin>>path;
	map <string,int>find_site;
	creat_map(path,find_site);
	cin>>words;
	string key_words;
	key_words=cut_words(words);
	string f_words;
	return 0;
	/*while(i<
	for(int i=0;i<key_words.length()&&key_words[i]!=' ';i++)
	{
		map item;
		item=
}*/
