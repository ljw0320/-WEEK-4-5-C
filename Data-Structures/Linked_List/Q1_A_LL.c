//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

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

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
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

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			// removeAllItems(&ll); 임시 주석처리(pdf 테스트 케이스 따라가다보면 결과가 다르게 나타남)
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
// 정렬된 연결 리스트 //
// 연결리스트와 item이라는 값 입력 받으면 인덱스를 반환
// 연결리스트가 비어있으면 인덱스 0으로 해서 값 삽입
// 이미 연결리스트에 있는 값을 입력하면 삽입하지 않고 -1 반환
// 인덱스는 어떻게 알까? 
// 	=> 정렬하면서
// 	=> 어떻게? : 노드 순회하면서
int insertSortedLL(LinkedList *ll, int item)
{	
	// ll : LinkedList의 포인터(주소)	

	if (ll->head == NULL)	
	{
		return insertNode(ll, 0, item);
	}
	else 
	{
		// int arr_size = ll->size;
		// int arr[arr_size]; 배열에 값 넣고 다시 순회 하면서 비교해야하므로 X				
		bool finishFlag = false;

		ListNode *cur;
		cur = ll->head;

		// head 부터 순회하며 인덱스 찾기
		// 인덱스 카운트 변수 사용
		// 1. 인덱스가 현재 연결리스트의 마지막에 붙는 경우
		// 2. 인덱스가 중간에 있는 경우
		int index = 0;

		while (!finishFlag) 
		{			
			// 입력 값이 리스트에 이미 있는 경우 -1 반환(해시 집합 있으면 좋을 것 같음)
			if (cur->item == item) 
			{
				return -1;
			}

			// 현재 탐색 중인 노드의 값이 입력 값보다 작은 경우 
			if (cur->item < item)	
			{
				// 인덱스 카운트 증가
				index++;

				// 다음 노드가 없다면 마지막에 삽입.
				if (cur->next == NULL) 
				{
					insertNode(ll, index, item);				
					return index;
				}				
				// 아니면 현재 노드를 다음 노드에 연결
				cur = cur->next;					
				continue;
			}
			
			// 현재 탐색 중인 노드의 값이 입력 값보다 큰 경우  
			// 현재 노드의 인덱스 저장한 뒤 삽입 함수 호출.
			if (cur->item > item) 
			{
				insertNode(ll, index, item);				
				return index;
			}
		}		
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

	// 이전 노드, 현재 노드 선언
	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){		
		cur = ll->head;	// 현재 노드 = 연결리스트 헤드	
		ll->head = malloc(sizeof(ListNode)); // 리스트 헤드 = 동적 생성		
		ll->head->item = value; // 리스트 헤드의 값 적용		
		ll->head->next = cur; // 리스트 다음 노드 NULL포인터 연결		
		ll->size++;	// 리스트 사이즈 확장

		return 0;
	}

	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	// 노드 중간 삽입 과정
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;	// 현재 노드 저장 (이전 노드의 다음 노드로)
		pre->next = malloc(sizeof(ListNode));	// 이전 노드의 다음 노드 동적 생성
		pre->next->item = value;	// 이전 노드의 다음 노드의 값 대입
		pre->next->next = cur;	// 이전 노드의 다음 노드의 다음 노드 : 현재 노드
		ll->size++;	// 연결 리스트 크기 1칸 확장
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
