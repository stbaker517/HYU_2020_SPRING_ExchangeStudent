#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define EMPTY -1

typedef char DATATYPE;

typedef struct NODE
{
	DATATYPE data;
	struct NODE* next;
}NODE;

typedef struct
{
	NODE* head;
}ListStack;

void InitStack(ListStack* stack);
int IsEmpty(ListStack* stack);

void Push(ListStack* stack, DATATYPE data);
DATATYPE Pop(ListStack* stack);
DATATYPE Peek(ListStack* stack);
int GetOperatorPriority(char op);
char postfix(char* Eq);

int main(int argc, char*argv[])
{
	ListStack stack;

	InitStack(&stack);

	char* ex1 = "1+2*3";
	char* ex2 = "(1+2)*3";
	char* ex3 = "((1-2)+3)*(5-2)";

	


	//make 1 dynamicallocation for postfit 
	char* converted1 = postfix(ex1);
	printf("check1\n");
	



	/* no use
	//save 5 data in stack
	Push(&stack, 1);
	Push(&stack, 2);
	Push(&stack, 3);
	Push(&stack, 4);
	Push(&stack, 5);

	//peek final data
	printf("Final data : %d\n", Peek(&stack));

	//pop data
	while (!IsEmpty(&stack))
	{
		printf("%d ", Pop(&stack));
	}
	printf("\n");
	/*
	char op = '/';
	printf("%d\n", GetOperatorPriority(op));
	*/



	return 0;
}

void InitStack(ListStack* stack)
{
	stack->head = NULL;
}

int IsEmpty(ListStack* stack)
{
	if (stack-> head == NULL)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void Push(ListStack* stack, DATATYPE data)
{
	NODE* temp = (NODE*)malloc(sizeof(NODE));

	temp->data = data;
	temp->next = stack->head;

	stack->head=temp;
}

DATATYPE Pop(ListStack* stack)
{
	DATATYPE tempData;
	NODE* temp;

	if (IsEmpty(stack))
	{
		printf("Stack is empty\n");
		exit(1);
	}

	tempData = stack->head->data;
	temp = stack->head;

	stack->head = stack->head->next;
	free(temp);

	return tempData;
}

DATATYPE Peek(ListStack* stack)
{
	if (IsEmpty(stack))
	{
		printf("Stack is empty\n");
		exit(1);
	}

	return stack->head->data;
}

/*converter*/

int GetOperatorPriority(char op)
{
	switch (op)
	{
	case 42:
		return 5; 
	case 47:
		return 5; 
	case 43:
		return 3; 
	case 45:
		return 3; 
	case 40:
		return 1; 
	default:
		return -1; 
	}
}

int CompareOperatorPriority(char op1, char op2)
{
	int Pop1, Pop2;
	Pop1 = GetOperatorPriority(op1);
	Pop2 = GetOperatorPriority(op2);

	if (Pop1 > Pop2)
	{
		return 1;
	}
	else if (Pop1 < Pop2)
	{
		return -1;
	}
	else//same
	{
		return 0;
	}

}

char postfix(char* Eq)
{
	int i = 0;
	int len = strlen(Eq);
	ListStack stack;
	InitStack(&stack);

	printf("check postfix1\n");
	char* temp = (char*)malloc(sizeof(len + 1));
	for (i; i <= len; i++)
	{
		if (isdigit(Eq[i]))
		{
			temp[i] = Eq[i];
		
		}
			
		else
		{

			if (IsEmpty(&stack))
			{
				
				Push(&stack, Eq[i]);
			
			}
			else {
				if (CompareOperatorPriority(Eq[i], stack.head->data)||Eq[i]==')')
				{
				
					
					while (IsEmpty(&stack)&&!(Peek(&stack)==')'))
					{
						temp[i] = Pop(&stack);
						i++;
						
					
						
					}
					if (IsEmpty(&stack))
						i--;
					
				}
				else {
					Push(&stack, Eq[i]);
					
				}
			}
		}

		printf("%dȸ\n", i);

	}
	while (IsEmpty(&stack))
	{
		temp[i] = Pop(&stack);
		i++;


	}
	temp[i] = '\0';
	for (int i = 0; i < len; i++)
	{
		printf("%c ", temp[i]);
	}
}