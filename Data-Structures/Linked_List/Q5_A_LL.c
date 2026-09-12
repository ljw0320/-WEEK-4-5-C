//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 5 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototype of this function
void frontBackSplitLinkedList(LinkedList* ll, LinkedList *resultFrontList, LinkedList *resultBackList);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *l);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	LinkedList ll;
	LinkedList resultFrontList, resultBackList;

	//Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	//Initialize the front linked list as an empty linked list
	resultFrontList.head = NULL;
	resultFrontList.size = 0;

	// Initialize the back linked list as an empty linked list
	resultBackList.head = NULL;
	resultBackList.size = 0;

	printf("1: Insert an integer to the linked list:\n");
	printf("2: Split the linked list into two linked lists, frontList and backList:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
	    printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The resulting linked lists after splitting the given linked list are:\n");
			frontBackSplitLinkedList(&ll, &resultFrontList, &resultBackList); // You need to code this function
			printf("Front linked list: ");
			printList(&resultFrontList);
			printf("Back linked list: ");
			printList(&resultBackList);
			printf("\n");
			removeAllItems(&ll);
			removeAllItems(&resultFrontList);
			removeAllItems(&resultBackList);
			break;
		case 0:
			removeAllItems(&ll);
			removeAllItems(&resultFrontList);
			removeAllItems(&resultBackList);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
// 리스트 절반으로 쪼개는 함수
// 앞 리스트에는 앞쪽 절반, 뒤 리스트에는 뒤쪽 절반
// 크기가 홀수이면 앞쪽에 하나 더 붙임 (2 3 5 6 7)이면 2 3 5 / 6 7
// C언어에서는 타입이 int인 변수는 소수점을 버림
// 따라서 리스트 size가 홀수라면 앞쪽 리스트를 +1해줌
// 앞쪽 절반 리스트는 헤드부터 절반 크기만큼 순회해서 붙여줌
// 뒤쪽 절반 리스트는 남은것 부터 붙여줌.
void frontBackSplitLinkedList(LinkedList *ll, LinkedList *resultFrontList, LinkedList *resultBackList)
{
	if (ll == NULL || ll->head == NULL) 
	{	
		printf("List is empty!");
		return;
	}
	
	int halfSize = (ll->size)/2;
	int frontSize, backSize;	

	frontSize = ((ll->size)%2 == 0)? halfSize : halfSize+1;
	backSize = halfSize;

	resultFrontList->head = malloc(sizeof(ListNode));	
	resultFrontList->size = frontSize;	

	ListNode *curLL, *curFL, *tempLL;
	curLL = ll->head;		
	curFL = resultFrontList->head;	

	for (int i=0; i < frontSize; i++)
	{
		tempLL = curLL->next;
		curFL->item = curLL->item;	

		if (i <= (frontSize-2))
		{
			curFL->next = malloc(sizeof(ListNode));
			curFL = curFL->next;
		}

		ll->head = tempLL;		
		ll->size--; 
		curLL = tempLL;		
	}	

	curFL->next = NULL;
	
	if (ll->size == 0) 
	{
		printf("LL Number is: %d\n", ll->size); 
		printf("LL size(Byte) is: %zu\n", sizeof(ll)); 
		return;
	}

	resultBackList->head = malloc(sizeof(ListNode));	
	resultBackList->size = backSize;

	ListNode *curBL;
	curBL = resultBackList->head;

	for (int i=0; i < backSize; i++)
	{
		if (curLL == NULL)
		{
			break;
		}
		tempLL = curLL->next;

		curBL->item = curLL->item;

		if (curLL->next != NULL)		
		{
			curBL->next = malloc(sizeof(ListNode));
			curBL = curBL->next;
		}		

		ll->head = tempLL;	
		ll->size--; 
		curLL = tempLL;
	}		
	curBL->next = NULL;

	printf("LL Number is: %d\n", ll->size); 
	printf("LL size(Byte) is: %zu\n", sizeof(ll)); 
}
//
///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;
	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}

	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
