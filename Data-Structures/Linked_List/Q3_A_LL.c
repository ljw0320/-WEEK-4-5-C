//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 3 */

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
void moveOddItemsToBack(LinkedList *ll);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move all odd integers to the back of the linked list:\n");
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
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveOddItemsToBack(&ll); // You need to code this function
			printf("The resulting linked list after moving odd integers to the back of the linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
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
1) 리스트 순회
2) 각 노드의 값이 짝수인지 홀수인지 확인
- 새로운 연결리스트 생성
- 짝수면 기존 리스트에서 꺼내서 헤드부터 연결
- 홀수면 그대로 둠
- 반복 횟수가 리스트 크기에 도달하면 새 리스트 마지막 노드에 기존 리스트 헤드 연결
- 기존 리스트를 새 리스트로 초기화
*/
void moveOddItemsToBack(LinkedList *ll)
{	
	const int iter_count = ll->size;
	ListNode *cur, *tail;
	cur = ll->head;

	// tailnode 얻기
	for (int i = 0; i < iter_count; i++)
	{
		if (cur->next == NULL)
		{
			tail = cur;
		}

		cur = cur->next;
	}

	// 현재 노드를 입력된 리스트의 헤드로 초기화	

	ListNode *temp, *prev;
	cur = ll->head;		

	// 홀수를 tail노드 뒤로 이동
	for (int i = 0; i < iter_count; i++)
	{		
		temp = cur->next;		

		if (cur->item%2 != 0)
		{
			if (cur == ll->head) 
			{
				ll->head = cur->next;
			}
			else
			{
				prev->next = cur->next;
			}

			tail->next = cur;
			tail = tail->next;
		}		
		prev = cur;
		cur = temp;
	}


	// const int iter_count = ll->size;
	// // LinkedList *newll;
	// LinkedList newll;
	// ListNode *prev, *cur;
	// ListNode *prev_new, *cur_new;

	// // 입력된 연결 리스트 노드
	// prev = NULL;
	// cur = ll->head;	

	// // 새로 정의한 연결 리스트 노드
	// newll.head = NULL;
	// newll.size = 0;
	// prev_new = NULL;
	// cur_new = newll.head;

	// // 반복문
	// // 반복 횟수 = 입력된 연결리스트 크기
	// // 매 반복 마다 아래는 반드시 수행
	// // - 현재 노드를 이전 노드에 저장
	// // - 현재 노드를 다음 노드로 변경
	// for (int i=0; i < iter_count; i++) 
	// {		
	// 	if (cur == NULL) break;

	// 	ListNode *temp;
	// 	temp = cur->next;

	// 	prev = cur;

	// 	if (cur->item % 2 == 0)	 // 현재 노드의 값이 짝수인 경우
	// 	{
	// 		ll->size--;

	// 		if (cur == ll->head) // 현재 노드가 '헤드'라면 다음 노드를 헤드로 초기화.
	// 		{
	// 			ll->head = cur->next;
	// 		}
	// 		else // 중간 노드라면 이전 노드를 현재 노드에 연결
	// 		{
	// 			prev->next = cur->next;
	// 		}

	// 		if (newll.head == NULL) // 짝수 연결리스트 헤드 비어있을 경우 초기화
	// 		{
	// 			newll.head = cur;	
	// 			cur_new = newll.head; // 왜 초기화해야하지?						
	// 		}
	// 		else // 이미 있다면 현재 노드 뒤에 붙임
	// 		{
	// 			cur_new = cur;
	// 		}

	// 		cur_new->next = NULL;	// 다음 노드 NULL로 초기화
	// 		cur_new = cur_new->next; // 현재 짝수 노드를 다음 짝수 노드로 초기화
	// 	}		
				
	// 	cur = temp;
	// }



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
