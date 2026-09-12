//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 2 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll1, ll2;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll1.head = NULL;
	ll1.size = 0;

	//Initialize the linked list 2 as an empty linked list
	ll2.head = NULL;
	ll2.size = 0;

	printf("1: Insert an integer to the linked list 1:\n");
	printf("2: Insert an integer to the linked list 2:\n");
	printf("3: Create the alternate merged linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list 1: ");
			scanf("%d", &i);
			j = insertNode(&ll1, ll1.size, i);
			printf("Linked list 1: ");
			printList(&ll1);
			break;
		case 2:
			printf("Input an integer that you want to add to the linked list 2: ");
			scanf("%d", &i);
			j = insertNode(&ll2, ll2.size, i);
			printf("Linked list 2: ");
			printList(&ll2);
			break;
		case 3:
		    printf("The resulting linked lists after merging the given linked list are:\n");
			alternateMergeLinkedList(&ll1, &ll2); // You need to code this function
			printf("The resulting linked list 1: ");
			printList(&ll1);
			printf("The resulting linked list 2: ");
			printList(&ll2);
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		case 0:
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
/*
첫번째 리스트와 두번째 리스트 합치는 함수
예시 1)
LinkedList1: 1, 2, 3
LinkedList2: 4, 5, 6, 7
=>alternateMergeLinkedList(LinkedList1, LinkedList2)
LinkedList1: 1, 4, 2, 5, 3, 6
LinkedList2: 7

예시 2)
LinkedList1: 1, 5, 7, 3, 9, 11
LinkedList2: 6, 10, 2, 4
=>alternateMergeLinkedList(LinkedList1, LinkedList2)
LinkedList1: 1, 6, 5, 10, 7, 2, 3, 4, 9, 11
LinkedList2: empty

첫번째 리스트 원소들 사이에 두번째 리스트를 사이에 끼워 넣는 형식->끼워 넣는 기준 표현 필요
#1 LL1이 LL2보다 작거나 같은 경우
LL2의 노드는 LL1의 크기 만큼만 넣는다.

#2 LL1이 LL2보다 큰 경우 
LL2의 노드를 전부 LL1에 넣는다.

아이디어)
각 리스트의 노드를 순회하며 연결.
L1의 현재 노드에 L2의 현재 노드 연결.
1) 현재노드를 L1, L2의 헤드로 초기화
2) L1 다음 노드 임시 저장
3) 현재 노드 다음 노드를 L2의 현재 노드로 연결
4) 현재 노드 = 현재노드의 다음노드로 초기화
5) 현재 노드에 기존 L1의 다음 노드 연결
6) 현재 노드 = 현재노드의 다음노드로 초기화

#1 순회 횟수: LL1->size
cur_1 = LL1->head
cur_2 = LL2->head

루프
temp_1 = cur_1->next
cur_1->next = cur_2
cur_1 = cur_1->next

cur_1->next = temp_1
cur_1 = cur_1->next

*/

void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2)
{
	// 현재 노드 초기화
    ListNode *cur1, *cur2;
	// ListNode *temp1, *temp2;	
	cur1 = ll1->head;
	cur2 = ll2->head;

	// 현재 리스트1 또는 리스트2의 노드가 비어있으면 종료(둘다 NULL이 아니어야함)
	while (cur1 != NULL && cur2 != NULL) 
	{		
		ListNode *temp1, *temp2;		
		
		temp1 = cur1->next;	// 현재 L1 노드의 다음 노드 저장
		temp2 = cur2->next; // 현재 L2 노드의 다음 노드 저장

		cur1->next = cur2; // 다음 L1 노드에 현재 L2 노드 연결(L1 cur->L2 cur)				
		cur2 = temp2; // 현재 L2 노드를 temp2로 초기화(L2 cur = temp 2)
		ll1->size++; // L1 사이즈 1 증가

		ll2->head = cur2;	// 리스트2의 헤드를 초기화(L2 head = cur2)
		cur1 = cur1->next; // 현재 L1 노드를 다음노드로 초기화
		ll2->size--; // L2 사이즈 1 감소

		cur1->next = temp1;
		cur1 = cur1->next;		
	}
}

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


ListNode *findNode(LinkedList *ll, int index){

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
