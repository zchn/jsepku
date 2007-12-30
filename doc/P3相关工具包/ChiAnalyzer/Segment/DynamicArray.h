//此部分代码使用 计算所汉语词法分析系统 ICTCLAS
//
//此部分代码为免费使用 版权保护
//
//特在此特别申明
//
//
//Author:   Kevin Zhang (张华平); Qun Liu(刘群)
//
//Inst. of Computing Tech., Chinese Academy of Sciences
//
//Email:    zhanghp@software.ict.ac.cn 
//
//Tel:      +86-10-88455001/5/7 to 714

#if !defined(AFX_DYNAMICARRAY_H__C47E8C64_17A2_467F_8094_1DFDCC39A943__INCLUDED_)
#define AFX_DYNAMICARRAY_H__C47E8C64_17A2_467F_8094_1DFDCC39A943__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MIN_PROBLEM 1

#if MIN_PROBLEM == 1//The shortest path
	#define INFINITE_VALUE 10000.00//infinite value
#else//The longest path
	#define INFINITE_VALUE 0.00//infinite value
#endif

#define ELEMENT_TYPE double//the type of element

//#define ROW_FIRST 0//Row first in the array store

struct tagArrayChain{
	//row and column
	unsigned int col, row;
	//The value of the array
    ELEMENT_TYPE value;
	int nPOS;
	int nWordLen;
	char *sWord;
	//The possible POS of the word related to the segmentation graph
    struct tagArrayChain *next;
};
typedef struct tagArrayChain ARRAY_CHAIN, *PARRAY_CHAIN;

class CDynamicArray  
{
private:
    PARRAY_CHAIN m_pHead;//The head pointer of array chain

public:
	bool m_bRowFirst;
	unsigned int m_nCol,m_nRow;//The row and col of the array

public:
	//Constructor
	CDynamicArray(bool bRowFirst=false);
	//Destructor
	virtual ~CDynamicArray();

public://Methods
	void SetEmpty();
	bool SetRowFirst(bool RowFirst = true);
	//Get the tail Element buffer and return the count of elements
	unsigned int GetTail(PARRAY_CHAIN *pTailRet);
	//Get the head Element
	PARRAY_CHAIN GetHead();
	bool GetElement(int nRow, int nCol,ELEMENT_TYPE  *pRetValue,int *pRetPOS = 0,char *sRetWord = 0);
	ELEMENT_TYPE GetElement( int nRow, int nCol, PARRAY_CHAIN pStart = 0, PARRAY_CHAIN *pRet = 0);
	int SetElement(unsigned int nRow, unsigned int nCol, ELEMENT_TYPE fValue, int nPOS, char *sWord = 0);

public://Operators
	const CDynamicArray & operator =(const CDynamicArray &);
	bool operator ==(const CDynamicArray &array);
};

#endif // !defined(AFX_DYNAMICARRAY_H__C47E8C64_17A2_467F_8094_1DFDCC39A943__INCLUDED_)