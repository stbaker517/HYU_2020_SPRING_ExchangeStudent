#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

typedef Student DATATYPE;

typedef struct {
	int ID;
	char* Name;
}Student;
typedef struct Node
{
	DATATYPE data;
	struct Node* next;
}Node;

typedef struct
{
	Node* Head;
	Node* Cur;
	Node* Tail;
	int NumofData;
	int (*Comp)(DATATYPE data1, DATATYPE data2);
}Linkedlist;

void InitList(Linkedlist* list);
void Insert(Linkedlist* list, DATATYPE data);
void HeadInsert(Linkedlist* list, DATATYPE data);
void SortInsert(Linkedlist* list, DATATYPE data);

int PosHead(Linkedlist* list, DATATYPE* data);
int PosNext(Linkedlist* list, DATATYPE* data);

DATATYPE Remove(Linkedlist* list);
int RetCount(Linkedlist* list);

void SetSortRule(Linkedlist* list, int(*Comp)(DATATYPE data1, DATATYPE data2));

int ComparePrecede(DATATYPE data1, DATATYPE data2);

int main(int argc, char* argv[])
{
	Linkedlist list;
	Student data;
	
	InitList(&list);

	DATATYPE* temp = (DATATYPE*)malloc(sizeof(DATATYPE));
	//save 5data

	temp->ID = 2020102501;
	temp->Name = "person1";
	Insert(&list, temp);
	temp->ID = 202014501;
	temp->Name = "person5";
	Insert(&list, temp);	
	temp->ID = 2020107501;
	temp->Name = "person2";
	Insert(&list, temp);
	temp->ID = 2020107401;
	temp->Name = "person4";
	Insert(&list, temp);
	temp->ID = 2020102501;
	temp->Name = "person3";
	Insert(&list, temp);

	free(temp);
	/*
	Insert(&list, 24);
	Insert(&list, 45);
	Insert(&list, 24);
	Insert(&list, 33);*/

	//print all
	printf("Num of datas %d\n", RetCount(&list));

	if (PosHead(&list, &data))
	{
		printf("ID : %d, Name : %s\n", data.ID,data.Name);


		while (PosNext(&list, &data))
		{
			printf("ID : %d, Name : %s\n", data.ID, data.Name);
		}
	}
	printf("\n");
	printf("\n");

	//search 24 and delete
	int target = 24;
	if (PosHead(&list, &data))
	{
		if (data.ID == target)
		{
			Remove(&list);
		}

		while (PosNext(&list, &data))
		{
			if (data.ID == target)
			{
				Remove(&list);
			}
		}
	}

	//print all
	printf("Num of datas %d\n", RetCount(&list));

	if (PosHead(&list, &data))
	{
		printf("ID : %d, Name : %s\n", data.ID, data.Name);

		while (PosNext(&list, &data))
		{
			printf("ID : %d, Name : %s\n", data.ID, data.Name);
		}
	}
	printf("\n");

	return 0;
}





int ComparePrecede(DATATYPE data1, DATATYPE data2)
{
	if (data1.ID < data2.ID)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void InitList(Linkedlist* list)
{
	list->Head = (Node*)malloc(sizeof(Node));
	list->Head->next = NULL;
	list->Comp = NULL;
	list->NumofData = 0;
}

void Insert(Linkedlist* list, DATATYPE data)
{
	if (list->Comp == NULL)
	{
		HeadInsert(list, data);
	}
	else
	{
		SortInsert(list, data);
	}
}

void HeadInsert(Linkedlist* list, DATATYPE data)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = data;

	temp->next = list->Head->next;
	list->Head->next = temp;

	list->NumofData++;
}

void SortInsert(Linkedlist* list, DATATYPE data)
{
	Node* new = (Node*)malloc(sizeof(Node));
	Node* pred = list->Head;
	new->data = data;

	//find pos
	while ((pred->next != NULL) && (list->Comp(data, pred->next->data) != 0))
	{
		pred = pred->next;
	}

	new->next = pred->next;
	pred->next = new;

	list->NumofData++;
}

int PosHead(Linkedlist* list, DATATYPE* data)
{
	if (list->Head->next == NULL)
	{
		return FALSE;
	}

	list->Tail = list->Head;
	list->Cur = list->Head->next;

	*data = list->Cur->data;
	return TRUE;
}

int PosNext(Linkedlist* list, DATATYPE* data)
{
	if (list->Cur->next == NULL)
	{
		return FALSE;
	}

	list->Tail = list->Cur;
	list->Cur = list->Cur->next;

	*data = list->Cur->data;
	return TRUE;
}

DATATYPE Remove(Linkedlist* list)
{
	Node* temp = list->Cur;
	DATATYPE tdata = temp->data;

	list->Tail->next = list->Cur->next;
	list->Cur = list->Tail;

	free(temp);
	list->NumofData--;
	return tdata;
}

int RetCount(Linkedlist* list)
{
	return list->NumofData;
}


void SetSortRule(Linkedlist* list, int(*Comp)(DATATYPE data1, DATATYPE data2))
{
	list->Comp = Comp;
}