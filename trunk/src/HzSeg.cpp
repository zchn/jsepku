// HzSeg handling

#include "HzSeg.h"
#include "Dict.h"

const unsigned int MAX_WORD_LENGTH = 8;
const string SEPARATOR(" ");		// delimiter between words

CHzSeg::CHzSeg()
{
}

CHzSeg::~CHzSeg()
{
}

// Using Max Matching method to segment a character string.
string CHzSeg::SegmentHzStrMM (CDict &dict, string s1) const
{
	string s2="";				// store segment result
	while (!s1.empty()) { 
		unsigned int len=s1.size();
		if (len>MAX_WORD_LENGTH) len=MAX_WORD_LENGTH;

		string w=s1.substr(0, len);// the candidate word
		bool isw=dict.IsWord(w);

		while (len>2 && isw==false) {	// if not a word
			len-=2;		// cut a word
			w=w.substr(0, len);
			isw=dict.IsWord(w);
		}
		s2 += w + SEPARATOR;

		s1 = s1.substr(w.size());
	}

	return s2;
}


bool CHzSeg::good_char(unsigned char c) const
{
  if((c >= '0' && c <= '9')
     || (c >= 'A' && c <= 'Z')
     || (c >= 'a' && c <= 'z')
     || (c == '\'')
     || c >= 128)
    return true;
  else
    return false;
}


// process a sentence before segmentation
string CHzSeg::SegmentSentenceMM (CDict &dict, string s1) const
{
	string s2="";
	unsigned int i,len;

	while (!s1.empty()) {
		unsigned char ch=(unsigned char) s1[0];
                len = s1.size();
                if(!good_char(ch)){//add by chenzhijie
                  unsigned int j = 1;
                  while(j < len && !good_char(s1[j])) j++;
                  s1 = s1.substr(j);
                  continue;
                }
                
		if(ch<128) { // deal with ASCII
			i=1;
			
			while (i<len && ((unsigned char)s1[i]<128) 
                               && good_char(s1[i])) { // LF, CR
				i++;
			}
                        
                        s2 += s1.substr(0, i) + SEPARATOR;

			if (i <= s1.size())	// added by yhf
				s1=s1.substr(i);
			else break;		// yhf

			continue;

		} else { 
			if (ch<176) { // 中文标点等非汉字字符
				i = 0;
				len = s1.length();

				while(i<len && ((unsigned char)s1[i]<176) && ((unsigned char)s1[i]>=161)
              && (!((unsigned char)s1[i]==161 && ((unsigned char)s1[i+1]>=162 && (unsigned char)s1[i+1]<=168)))
              && (!((unsigned char)s1[i]==161 && ((unsigned char)s1[i+1]>=171 && (unsigned char)s1[i+1]<=191)))
              && (!((unsigned char)s1[i]==163 && ((unsigned char)s1[i+1]==172 || (unsigned char)s1[i+1]==161) 
              || (unsigned char)s1[i+1]==168 || (unsigned char)s1[i+1]==169 || (unsigned char)s1[i+1]==186
              || (unsigned char)s1[i+1]==187 || (unsigned char)s1[i+1]==191))) { 
					i=i+2; // 假定没有半个汉字
				}

				if (i==0) i=i+2;

				// 不处理中文空格
				if (!(ch==161 && (unsigned char)s1[1]==161)) { 
					if (i <= s1.size())	// yhf
						// 其他的非汉字双字节字符可能连续输出
						s2 += s1.substr(0, i) + SEPARATOR; 
					else break; // yhf
				}

				if (i <= s1.size())	// yhf
					s1=s1.substr(i);
				else break;		//yhf

				continue;
			}
		}
    

    // 以下处理汉字串

		i = 2;
		len = s1.length();

		while(i<len && (unsigned char)s1[i]>=176) 
//    while(i<len && (unsigned char)s1[i]>=128 && (unsigned char)s1[i]!=161)
			i+=2;

		s2+=SegmentHzStrMM(dict, s1.substr(0,i));

		if (i <= len)	// yhf
			s1=s1.substr(i);
		else break;	// yhf
	}

	return s2;
}

// translate the encoded URL(%xx) to actual chars
void CHzSeg::Translate(char* SourceStr) const
{
	int i=0;
	int j=0;
	char *tempstr,tempchar1,tempchar2;

	tempstr = (char*)malloc(strlen(SourceStr) + 1);
	if(tempstr == NULL){
		return;
	}

	while (SourceStr[j])
	{
		if ((tempstr[i]=SourceStr[j])=='%'){
			if (SourceStr[j+1]>='A')
				tempchar1=((SourceStr[j+1]&0xdf)-'A')+10;
			else
				tempchar1=(SourceStr[j+1]-'0');
			if (SourceStr[j+2]>='A')
				tempchar2=((SourceStr[j+2]&0xdf)-'A')+10;
			else
				tempchar2=(SourceStr[j+2]-'0');
				tempstr[i]=tempchar1*16+tempchar2;
			j=j+2;
		}
		i++;
		j++;
	}
	tempstr[i]='\0';
	strcpy(SourceStr,tempstr);

	if(tempstr) free(tempstr);
}

/*
 * segment the image URL by '/'
 * omit the domain name
 */
string CHzSeg::SegmentURL(CDict &dict, string url) const
{
	string::size_type idx, nidx;
	char *curl = (char *)url.c_str();
	this->Translate(curl);
	url = curl;
	if((idx = url.find("http://", 0)) != string::npos)
	{
		if((nidx = url.find("/", 7)) != string::npos)
		{
			url = url.substr(nidx + 1);	// cut the part of sitename
		}
	}
	idx = 0;
	while((idx = url.find("/", idx)) != string::npos)
	{
		url.replace(idx, 1, SEPARATOR);	// replace "/" with SEPARATOR "/  "
		idx += 3;
	}
	if((idx = url.rfind(".")) != string::npos)
	{
		url = url.erase(idx);	// erase the file extension
	}

	url += "/  ";
	
	// segment the string whose length is greater than 8 (4 HZ_chars)
	idx = 0; nidx = 0;
	bool isover = false;
	string stmp;
	while(!isover)
	{
		if((nidx = url.find(SEPARATOR, idx)) == string::npos)
			isover = true;
		if(nidx - idx > 0)
		{
			stmp = url.substr(idx, nidx-idx);
			stmp = SegmentSentenceMM(dict, stmp);
			if ( stmp.size() >= 3)
				stmp.erase(stmp.length() - 3);	// erase the tail "/  "
			url = url.replace(idx, nidx-idx, stmp);
			idx += stmp.length() + 3;
		}
		else if(nidx == string::npos && idx < url.length())
		{
			stmp = url.substr(idx);
			stmp = SegmentSentenceMM(dict, stmp);
			stmp.erase(stmp.length() - 3);
			url = url.substr(0, idx) + stmp;
		}
		else
			idx = nidx + 3;
	}
	
	return url;
	
}


