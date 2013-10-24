#ifndef LIST_H
#define LIST_H

class List
{
private:

	struct NODE
	{
		void *data;
		NODE *link;
	}*coreNode;

public:
	List();
	~List();
	void Add(void *value);
	void AddToTop(void *value);
	void Insert(int c, void *value);
	void Remove(void *value);
	void* RemoveAt(int index);
	void* Get(int index);
	int Count();
};

#endif
