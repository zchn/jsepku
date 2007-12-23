// Dict handling

#include "Dict.h"

CDict::CDict()
{
	OpenDict();
}

CDict::~CDict()
{
	mapDict.clear();
}

void CDict::OpenDict()
{
	FILE *fpDict;
	if ((fpDict = fopen(DICTFILENAME.c_str(), "r")) == NULL) {
		cout << "Can not open the Dictionary file!";
		exit(1);
	}
  
	int id, freq;
	char word[16];
	while (fscanf(fpDict, "%d %s %d", &id, word, &freq) != EOF) {
		//fscanf(fpDict, "%d %s %d", &id, word, &freq);
		mapDict.insert(map<string,int>::value_type (word, 0));
	}
  
	fclose(fpDict);
  
}

bool CDict::IsWord(string& str) const
{
	if (mapDict.find(str) != mapDict.end())
		return true;
	return false;
}
