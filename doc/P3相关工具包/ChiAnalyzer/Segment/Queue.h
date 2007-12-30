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
//////////////////////////////////////////////////////////////////////
//
// Queue.h: interface for the CQueue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUEUE_H__382C7319_66D8_4041_ABA2_EE25B9D15D9C__INCLUDED_)
#define AFX_QUEUE_H__382C7319_66D8_4041_ABA2_EE25B9D15D9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DynamicArray.h"

struct tagQueueElem{
	//the weight
    unsigned int nParent;
	//number of index in the parent node
	unsigned int nIndex;
	//the weight of last path
	ELEMENT_TYPE eWeight;
    struct tagQueueElem *next;
};
typedef struct tagQueueElem QUEUE_ELEMENT,*PQUEUE_ELEMENT;

class CQueue  
{
private:
	PQUEUE_ELEMENT m_pHead;//The chain sort according the weight of shortest path
	PQUEUE_ELEMENT m_pLastAccess;//The node last accessed
public:
	bool IsSingle();
	bool IsEmpty(bool bBrowsed = false);
	int Push(unsigned int nValue = 0,//The value for parent node
			 unsigned int nIndex = 0,//number of index in the parent node
             ELEMENT_TYPE eWeight = 0//the weight of last path 
			 );
	int Pop( unsigned int *npValue,//The value for node
			 unsigned int *npIndex,//number of index in the parent node
		     ELEMENT_TYPE *epWeight = 0,//the weight of last path 
			 bool  bModify = true,//false: not modify the data
			 bool bFirstGet = true//first get data,just for browse 
		   );
public:
	CQueue();
	virtual ~CQueue();
};

#endif // !defined(AFX_QUEUE_H__382C7319_66D8_4041_ABA2_EE25B9D15D9C__INCLUDED_)
