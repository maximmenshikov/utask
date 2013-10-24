#include "stdafx.h"
#include "List.h"

List::List()
{
	coreNode = NULL;
};

void List::Add(void *value)
{
	NODE *tempNode;

	if( coreNode == NULL )
	{
		coreNode = new NODE;
		coreNode->data = value;
		coreNode->link = NULL;
	}
	else
	{
		tempNode = coreNode;
		while( tempNode->link != NULL )
			tempNode = tempNode->link;

		NODE *newNode = new NODE;
		newNode->data = value;
		newNode->link = NULL;
		tempNode->link = newNode;
	}
};

void List::AddToTop(void *value)
{
	NODE *q;

	q = new NODE;
	q->data = value;
	q->link = coreNode;
	coreNode = q;
};

void List::Insert(int c, void *value)
{
	NODE *q,*t;
	int i;
	for(i=0,q=coreNode;i<c;i++)
	{
		q = q->link;
		if( q == NULL )
		{
			return;
		}
	}

	t = new NODE;
	t->data = value;
	t->link = q->link;
	q->link = t;
};

void List::Remove(void *value)
{
	NODE *q,*r;
	q = coreNode;
	if ( q->data == value )
	{
		coreNode = coreNode->link;
		delete(q);
		return;
	}

	r = q;
	while( q!=NULL )
	{
		if( q->data == value )
		{
			r->link = q->link;
			delete(q);
			return;
		}

		r = q;
		q = q->link;
	}
};

void* List::RemoveAt(int index)
{
	void *result = NULL;
	NODE *lastNode, *tempNode;
	if (index == 0)
	{
		result = coreNode->data;
		coreNode = coreNode->link;
		delete(coreNode);
		return result;
	}
	else
	{
		lastNode = coreNode->link;
		tempNode = coreNode;
		int currentIndex = 1;
		while (lastNode != NULL)
		{
			if (currentIndex == index)
			{
				tempNode->link = lastNode->link;
				result = lastNode->data;
				delete(lastNode);
				return result;
			}
			tempNode = lastNode;
			lastNode = lastNode->link;
			currentIndex++;
		}
	}
	return result;
};

void* List::Get(int index)
{
	if (index == 0)
	{
		return coreNode->data;
	}
	else if (coreNode)
	{
		NODE *lastNode = coreNode->link;
		int currentIndex = 1;
		while( lastNode != NULL )
		{
			if( currentIndex == index )
			{
				return lastNode->data;
			}
			
			lastNode = lastNode->link;
			currentIndex++;
		}
	}
	return NULL;
};

int List::Count()
{
	NODE *q;
	int c=0;
	for( q = coreNode ; q != NULL ; q = q->link )
		c++;

	return c;
};


List::~List()
{
	
	if( coreNode == NULL )
		return;

	NODE *tempNode;
	while( coreNode != NULL )
	{
		tempNode = coreNode->link;
		delete(coreNode);
		coreNode = tempNode;
	}
};
