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
// Queue.cpp: implementation of the CQueue class.
//
//////////////////////////////////////////////////////////////////////
//#include "stdafx.h"
#include "Queue.h"
#include "malloc.h"
#include "stdlib.h"
#include "memory.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQueue::CQueue()
{
	m_pHead=NULL;
	m_pLastAccess=NULL;
}

CQueue::~CQueue()
{
   PQUEUE_ELEMENT pCur=m_pHead,pTemp;//The pointer of queue chain
   while(pCur!=NULL)
   {
	   pTemp=pCur->next;
	   delete pCur;
	   pCur=pTemp;
   }
}

int CQueue::Push(unsigned int nValue,//The value for parent node
				 unsigned int nIndex,//number of index in the parent node
                 ELEMENT_TYPE eWeight//the weight of last path 
			     )
{//Sort it
   PQUEUE_ELEMENT pAdd,pCur=m_pHead,pPre=0;//The pointer of queue chain
   
   while(pCur!=NULL&&pCur->eWeight<eWeight)
   {//Get the proper posption,sort according the weight
	   pPre=pCur;
	   pCur=pCur->next;
   }
   pAdd=(PQUEUE_ELEMENT)new QUEUE_ELEMENT;
   pAdd->nParent=nValue;
   pAdd->nIndex=nIndex;
   pAdd->eWeight=eWeight;
   pAdd->next=pCur;
   if(pPre==0)
	   m_pHead=pAdd;
   else
	   pPre->next=pAdd;
   return 1;
}
int CQueue::Pop(unsigned int *npValue,//The value for parent node
				unsigned int *npIndex,//number of index in the parent node
                ELEMENT_TYPE *epWeight,//the weight of last path 
                bool  bModify,//not modify the data 
				bool  bFirstGet//first get data,just for browse 
			   )
{
	PQUEUE_ELEMENT pTemp;

	if(bModify) 
		pTemp=m_pHead;//The temp buffer
	else 
	{
	  if(bFirstGet)//First get the data
	 	   m_pLastAccess=m_pHead;//The temp buffer
	  pTemp=m_pLastAccess;
	}

	if(pTemp==NULL)
		return -1;//fail get the value
    if(npValue!=0)
	       *npValue=pTemp->nParent;
    if(npIndex!=0)
	       *npIndex=pTemp->nIndex;
    if(epWeight!=0)
		  *epWeight=pTemp->eWeight;

    if(bModify)//modify and get rid of the node
	{
 	   m_pHead=pTemp->next;
	   delete pTemp;//free the buffer
	}
	else
	{
       m_pLastAccess=pTemp->next;
    }
     return 1;
}

bool CQueue::IsEmpty(bool bBrowsed)//bBrowsed=true: judge whether the browse pointer got end.
{
	if(bBrowsed==true)
		return (m_pLastAccess==NULL);
   return (m_pHead==NULL);
}

bool CQueue::IsSingle()
{
   return (m_pHead!=NULL&&m_pHead->next==NULL);
}
