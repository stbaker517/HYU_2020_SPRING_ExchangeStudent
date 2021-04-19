#define _CRT_SECURE_NO_WARNINGS
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
int CompareOperatorPriority(char op1, char op2);
void ConvertExp(char exp[]);
void showme(char str[]);
int main(int argc, char* argv[])
{

	char* ex1 = "1+2*3";
	char* pex1 = (char*)malloc(sizeof(char) * (strlen(ex1) + 1));
	strcpy(pex1, ex1);
	printf("1: %s\n", pex1);
	ConvertExp(pex1);
	printf("1: %s\n", pex1);
	char* ex2 = "(1+2)*3";
	char* pex2 = (char*)malloc(sizeof(char) * (strlen(ex1) + 1));
	strcpy(pex2, ex2);
	printf("2: %s\n", pex2);
	ConvertExp(pex2);
	printf("2: %s\n", pex2);

	char* ex3 = "((1-2)+3)*(5-2)";
	char* pex3 = (char*)malloc(sizeof(char) * (strlen(ex3) + 1));
	strcpy(pex3, ex3);
	printf("3: %s\n", pex3);
	ConvertExp(pex3);
	printf("3: %s\n", pex3);
	int a = 1;
	printf("\n%d 번째 테스트", a);
	showme("2+3*4");

	a = 2;
	printf("\n%d 번째 테스트", a);
	showme("1*7+5");
	a = 3;
	printf("\n%d 번째 테스트", a);
	showme("(1+2)*7");
	a = 4;
	printf("\n%d 번째 테스트", a);
	showme("5*6/7");
	a = 5;
	printf("\n%d 번째 테스트", a);
	showme("((1/(2-3+4)))*(5-6)*7");
	a = 6;
	printf("\n%d 번째 테스트", a);
	showme("1/2-3+4*5-6*7");

	return 0;
}
void InitStack(ListStack* stack)
{
	stack->head = NULL;
}
int IsEmpty(ListStack* stack)
{
	if (stack->head == NULL)
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
	stack->head = temp;
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
	case '*':
		return 5;
	case '/':
		return 5;
	case '+':
		return 3;
	case '-':
		return 3;
	case '(':
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
void ConvertExp(char exp[])
{

	int i = 0, l = 0, len;
	len = strlen(exp);
	ListStack stack;
	InitStack(&stack);
	char* temp;
	temp = (char*)malloc(sizeof(char) * (len + 1));

	for (i; i < len;)
	{
		if (isdigit(exp[i]))
		{
			temp[l] = exp[i];
			i++;
			l++;
		}
		else//no digits
		{
			if (IsEmpty(&stack))//stack empty
			{
				Push(&stack, exp[i]);
				i++;
			}
			else//stack no empty
			{
				if (CompareOperatorPriority(exp[i], stack.head->data) != 1)//comming operator is low
				{
					if (GetOperatorPriority(exp[i]) == 1)// (
					{
						Push(&stack, exp[i]);
						i++;
					}
					else if (GetOperatorPriority(exp[i]) == -1)
					{
						while (!IsEmpty(&stack))
						{
							if (Peek(&stack) == '(')
							{
								Pop(&stack);
								break;
							}
							temp[l] = Pop(&stack);
							l++;
						}
						i++;
					}
					else//pop all before and push
					{
						while (!IsEmpty(&stack))
						{
							if (Peek(&stack) == '(')
							{

								break;
							}
							temp[l] = Pop(&stack);
							l++;
						}
						Push(&stack, exp[i]);
						i++;
					}
				}
				else//coming is high
				{
					Push(&stack, exp[i]);
					i++;
				}
			}
		}
	}
	while (!IsEmpty(&stack))
	{
		temp[l] = Pop(&stack);
		l++;
	}

	temp[l] = '\0';

	strcpy(exp, temp);
}
void showme(char str[])
{

	char* pex1 = (char*)malloc(sizeof(char) * (strlen(str) + 1));
	strcpy(pex1, str);
	printf("1: %s\n", pex1);
	ConvertExp(pex1);
	printf("1: %s\n", pex1);
}