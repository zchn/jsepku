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
#include<iomanip>
using namespace std;
const int TERM_LEN=32;
struct word_info
{
	string words;
	string id;
};
/**********************************************************************
��������invert
���ܣ���.piidx.sort���͵��ļ�ת��Ϊ.iidx���͵��ļ����й��ļ����͵�˵����ο����ⱨ�档
���������һ��string���͵��ļ�·����
����ֵ������ɹ��򷵻�0�����򷵻�-1��
***************************************************************************/
int invert(string path)
{
	ifstream in_piidx_sort(path.c_str());
	if(!in_piidx_sort.is_open())
	{
		cerr<<"[ERROR]:piidx file can't be opened"<<endl;
		return -1;
	}
	/*���ļ����е�.piidx.sortת��Ϊ.iidx*/
	word_info *words_info;
	words_info=new word_info[2];
	string out_name=path;
	int len=out_name.length();
	len-=11;
	out_name.erase(len);
	out_name+=".iidx";
	ofstream out_iidx(out_name.c_str());
	in_piidx_sort>>words_info[0].words;
	in_piidx_sort>>words_info[0].id;
	out_iidx<<setw(TERM_LEN)<<left<<words_info[0].words;
	out_iidx<<setw(8)<<left<<words_info[0].id<<' ';
	/*����.iidx��Ҫ�����ʼ���*/
	while(!in_piidx_sort.eof())
	{
		in_piidx_sort>>words_info[1].words;
		in_piidx_sort>>words_info[1].id;
		if(words_info[1].words==words_info[0].words) 
		{
			out_iidx<<setw(8)<<left<<words_info[1].id<<' ';
		}
		else
		{
			out_iidx<<endl<<setw(TERM_LEN)<<left<<words_info[1].words;
			out_iidx<<setw(8)<<left<<words_info[1].id<<' ';
		}
		words_info[0].words=words_info[1].words;
		words_info[0].id=words_info[1].id;
		words_info[1].words="";
		words_info[1].id="";
	}
	return 0;
}

int main(int argc,char *argv[])
{
	string file_name=argv[1];
	if(invert(file_name) != 0){
		return -1;
	}
	return 0;
}