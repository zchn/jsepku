#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;
int docoff(string path)
/**********************************************************************
��������docoff.
���ܣ���.raw���͵��ļ�ת��Ϊ.didx���͵��ļ����й��ļ����͵�˵����ο����ⱨ�档
���������һ��string���͵��ļ�·����
����ֵ������ɹ��򷵻�0�����򷵻�-1��
***************************************************************************/
{
	ifstream in_raw;
	string out_name=path;
	/*���ļ�����.raw��Ϊ.didx*/
	int len=out_name.length();
	len-=4;
	out_name.erase(len);
	out_name+=".didx";
	ofstream out_didx(out_name.c_str());
	if(!out_didx.is_open())
	{
		cerr<<"[ERROR]:out-file can't be opened"<<endl;
		return -1;
	}
	in_raw.open(path.c_str());
	if(!in_raw.is_open())
	{
		cerr<<"[ERROR]:in-file can't be opened"<<endl;
		return -1;
	}
	string words;
	int id=0;
	while(!in_raw.eof())
	{
		unsigned int offset;			
		offset=in_raw.tellg();
		getline(in_raw,words);
		/*version:1.0���ж����¼�������ݣ���16��������ļ��ı��*/
		if(words=="version:1.0")
		{
			out_didx<<setfill('0')<<hex<<setw(8)<<id<<' '<<setfill('0')<<hex<<setw(8)<<offset<<endl;
			id++;
		}
	}
	return 0;
}
int main(int argc,char *argv[])
{
	string filename=argv[1];
	if(docoff(filename)!=0){
		return -1;
	}
	return 0;
}

