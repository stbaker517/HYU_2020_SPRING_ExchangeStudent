#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
void Insertminheap(int* minheap, int data);
void Insertmaxheap(int* maxheap, int data);
void printheap(int* heap);
int Deletemaxheap(int* heap);

int Prioritymax(int* heap, int i);
int Deleteminheap(int* heap);

int Prioritymin(int* heap, int i);
void initheap(int* heap);

int Retparent(int i);
int Retright(int i);
int Retleft(int i);


int main() {
	int n;
	int med;
	int* maxheap;
	int *minheap;
	int input;
	scanf("%d", &n);
	minheap = (int*)malloc(sizeof(int) * n);//0번 칸에 데이터 숫자 넣어줌
	maxheap = (int*)malloc(sizeof(int) *n);
	initheap(minheap);
	initheap(maxheap);
	//int a[100];
	/*scanf("%d", &med);
	printf("%d\n", med);*/
	for (int i = 0; i < n; i++) {
		scanf("%d", &input);//중간보다 작으면 max힙으로 중간보다 크면 min힙으로 대신 max개수<=min개수
		if (i == 0)
		{
			med = input;
		}
		else {
			if (input < med)
			{
				Insertmaxheap(maxheap, input);
			
				if (minheap[0] - maxheap[0] > 1)
				{
					
					Insertmaxheap(maxheap, med);
					med = Deleteminheap(minheap);
				
				}
				if (minheap[0] - maxheap[0] < 0)
				{
					Insertminheap(minheap, med);
					med = Deletemaxheap(maxheap);
				
				}
			}
			else
			{
				Insertminheap(minheap, input);
			
				if (minheap[0] - maxheap[0] > 1)
				{
					Insertmaxheap(maxheap, med);
					med = Deleteminheap(minheap);
					
				}
				if (minheap[0] - maxheap[0] < 0)
				{
					Insertminheap(minheap, med);
					med = Deletemaxheap(maxheap);
					
				}
			}
		
		}

		printf("%d\n", med);
		/*printf("좌측 힙 : ");
		printheap(maxheap);
		printf("  중간값:%d  ", med);
		printf("우측 힙 : ");
		printheap(minheap);
		printf("\n");
		a[i] = med;*/
	}
	/*printf("결과물 출력:");
	for (int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}*/

	


	return 0;
}
void initheap(int* heap) {
	heap[0] = 0;
}

void Insertmaxheap(int* maxheap, int data) {
	int last = ++maxheap[0];
	
	while (last != 1 && maxheap[Retparent(last)] < data) {

		maxheap[last] = maxheap[Retparent(last)];
		last = Retparent(last);

	}

	maxheap[last] = data; 
	return;
}
void Insertminheap(int* minheap, int data) {
	int last = ++minheap[0];
	
	
	while (last !=1 && minheap[Retparent(last)] > data) {

		minheap[last] = minheap[Retparent(last)];
		last = Retparent(last);

	}
	minheap[last] = data; 
	return;
}

int Deletemaxheap(int* heap) {
	int ret;
	int last;
	int target;
	if (heap[0] == 0)
		return;
	last = heap[0];
	ret = heap[1];
	target = 1;
	while (Retleft(target) < last)
	{
		if (heap[Prioritymax(heap, target)] <= heap[last])
		{
			break;
		}
		else
		{
			heap[target] = heap[Prioritymax(heap, target)];
			target = Prioritymax(heap, target);
		}
	}
	heap[target] = heap[last];
	heap[0]--;
	return ret;
}
int Deleteminheap(int* heap) {
	int ret;
	int last;
	int target;

	if (heap[0] == 0)
		return;
	last = heap[0];
	ret = heap[1];
	target = 1;
	while (Retleft(target) < last)
	{
		if (heap[Prioritymin(heap, target)] >= heap[last])
		{
			break;
		}
		else
		{
			heap[target] = heap[Prioritymin(heap, target)];
			target = Prioritymin(heap, target);
		}
	}
	heap[target] = heap[last];
	heap[0]--;
	return ret;
}


int Prioritymax(int* heap, int i) {
	if (heap[Retleft(i)] < heap[Retright(i)]) {
		return Retright(i);
	}
	else
	{
		return Retleft(i);
	}


}

int Prioritymin(int* heap, int i) {
	if (heap[Retleft(i)] > heap[Retright(i)]) {
		return Retright(i);
	}
	else
	{
		return Retleft(i);
	}


}

void printheap(int* heap) {
	for (int i = 1; i <= heap[0]; i++) {
		printf("%d ", heap[i]);
	}
	//printf("\n");
}






int Retparent(int i) {
	return i / 2;
}
int Retright(int i) {
	return 2 * i + 1;
}
int Retleft(int i) {
	return 2 * i;
}
