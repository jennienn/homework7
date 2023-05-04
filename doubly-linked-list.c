/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 *
 */


#include<stdio.h>
#include<stdlib.h>



typedef struct Node { /* 이중 연결 리스트의 노드를 정의 */
	int key; // 노드의 값
	struct Node* llink; // 왼쪽 링크 포인터
	struct Node* rlink; // 오른쪽 링크 포인터
} listNode;



typedef struct Head { /* 이중 연결 리스트의 헤드를 정의 */
	struct Node* first; // 첫 번째 노드를 가리키는 포인터
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
         - initialize와 왜 다른지 이해 할 것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command; // 입력받은 명령어를 저장하는 변수
    int key; // 입력받은 키 값을 저장하는 변수
    headNode* headnode=NULL; // linked list를 가리키는 head node를 NULL값으로 초기화

	printf("[----- [김예진]  [2022041035] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {

	/* headNode가 NULL이 아니면 freeList를 호출하여 메모리 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode 동적 메모리 할당 */
	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;  // 초기화된 headNode의 first 포인터를 NULL로 설정
	return 1;

}

int freeList(headNode* h){
	// 리스트의 노드들을 순회하기 위한 포인터 p 선언 및 초기화
	listNode* p = h->first;

	// 이전 노드를 가리키기 위한 포인터 prev 선언 및 NULL로 초기화
	listNode* prev = NULL;

	// p가 NULL이 될 때까지 반복
	while(p != NULL) {
		prev = p;       // prev 포인터에 현재 노드 p를 할당
		p = p->rlink;   // p 포인터를 오른쪽 링크로 이동
		free(prev);     // 이전 노드를 해제
	}

	free(h);            // 헤드 노드를 해제
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p; //현재 노드를 가리키는 포인터 p 선언

	printf("\n---PRINT\n");

	if(h == NULL) { // 헤드 노드가 NULL일 경우, 함수 종료
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; // p에 첫 번째 노드 주소 대입

	while(p != NULL) { // p가 NULL이 아닐 때까지 반복하여 출력
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i); // 전체 아이템 개수 출력
}




/**
 * list에 key에 대한 노드 하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로운 노드 생성
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	// 리스트가 비어있으면 새로운 노드를 첫 번째 노드로 설정
	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}
	// 리스트의 마지막 노드까지 이동하여 새로운 노드를 추가
	listNode* n = h->first;
	while(n->rlink != NULL) {
		n = n->rlink;
	}
	n->rlink = node;
	node->llink = n;
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	
	/* 리스트가 비어있는 경우 */
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* 리스트에 노드가 하나만 있는 경우 */
	if(n->rlink == NULL) {
		h->first = NULL; // 리스트의 첫 번째 노드를 NULL로 설정
		free(n); // 메모리 해제
	return 0;
	}

	/* 마지막 노드를 찾아서 삭제 */
	while(n->rlink != NULL) {
		trail = n; // 이전 노드를 가리키는 포인터
		n = n->rlink; // 다음 노드로 이동
	}

	/* n이 NULL인 경우 */
	trail->rlink = NULL; // 이전 노드의 rlink를 NULL로 설정
	free(n); // 메모리 해제

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	// 새로운 노드 생성 및 초기화
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = node->llink = NULL;

	// 리스트가 비어있는 경우
	if(h->first == NULL)
	{
		h->first = node; // 새로운 노드가 리스트의 첫 번째 노드가 됨
		return 1;
	}

	// 리스트가 비어있지 않은 경우
	node->rlink = h->first; // 새로운 노드의 오른쪽 링크를 리스트의 첫 번째 노드와 연결
	node->llink = NULL; // 새로운 노드의 왼쪽 링크는 NULL로 설정

	listNode *p = h->first; // 리스트의 첫 번째 노드를 가리키는 포인터 p 생성
	p->llink = node; // 첫 번째 노드의 왼쪽 링크를 새로운 노드와 연결
	h->first = node; // 리스트의 첫 번째 노드를 새로운 노드로 변경

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	// 리스트가 비어있는 경우
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	// 리스트의 첫번째 노드를 삭제
	listNode* n = h->first; // 삭제할 노드를 저장
	h->first = n->rlink; // 두번째 노드를 리스트의 첫번째 노드로 설정

	free(n); // 노드 삭제

	return 0;
}




/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	// 리스트가 비어있다면 함수종료
	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	// 리스트의 노드들을 역순으로 재배치하는 과정
	listNode *n = h->first; // 현재 노드를 가리키는 포인터
	listNode *trail = NULL; // 이전 노드를 가리키는 포인터
	listNode *middle = NULL; // 현재 노드를 저장하는 포인터

	while(n != NULL){
		trail = middle; // trail 포인터를 현재 노드로 이동
		middle = n; // middle 포인터를 다음 노드로 이동
		n = n->rlink; // 다음 노드로 이동
		middle->rlink = trail; // middle 노드의 rlink를 trail 노드로 설정
		middle->llink = n; // middle 노드의 llink를 다음 노드로 설정
	}

	h->first = middle; // 리스트의 헤드 노드를 역순으로 재배치한 리스트의 첫 번째 노드로 변경

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나우는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	/* 새 노드 생성 및 초기화 */
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	/* 리스트가 비어있는 경우, 첫 번째 노드로 삽입하고 함수 종료 */
	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	/* 리스트를 탐색하면서 삽입할 위치를 찾음 */
	listNode* n = h->first;
	while(n != NULL) {
		/* key보다 큰 값을 가진 노드를 찾은 경우 */
		if(n->key >= key) {
			/* 삽입할 위치가 첫 번째 노드인 경우 */
			if(n == h->first) {
				insertFirst(h, key);  // 첫 번째에 삽입하는 함수 호출
			} else { /* 중간에 삽입해야 하는 경우 */
				node->rlink = n;  // 삽입할 노드의 오른쪽 링크를 설정
				node->llink = n->llink;  // 삽입할 노드의 왼쪽 링크를 설정
				n->llink->rlink = node;  // 삽입할 위치의 왼쪽 노드의 오른쪽 링크를 삽입할 노드로 설정
			}
			return 0;
		}
		n = n->rlink;  // 다음 노드로 이동
	}

	/* 리스트의 끝에 삽입해야 하는 경우 */
	insertLast(h, key);  // 마지막에 삽입하는 함수 호출
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	// 리스트가 비어있는 경우
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 1;
	}

	// 리스트를 처음부터 탐색하며 key 값을 가진 노드를 찾는다
	listNode* n = h->first;
	while(n != NULL) {
		if(n->key == key) {
			// 삭제할 노드가 리스트의 첫 번째 노드인 경우
			if(n == h->first) {
				deleteFirst(h);
			} 
			// 삭제할 노드가 리스트의 마지막 노드인 경우
			else if (n->rlink == NULL){
				deleteLast(h);
			} 
			// 그 외의 경우 (리스트 중간에 위치한 노드를 삭제하는 경우)
			else {
				n->llink->rlink = n->rlink; // 삭제할 노드의 이전 노드의 rlink를 삭제할 노드의 다음 노드로 연결
				n->rlink->llink = n->llink; // 삭제할 노드의 다음 노드의 llink를 삭제할 노드의 이전 노드로 연결
				free(n); // 삭제할 노드의 메모리 해제
			}
			return 1;
		}
		n = n->rlink;
	}

	// 리스트에 해당 key 값을 가진 노드가 없는 경우
	printf("cannot find the node for key = %d\n", key);
	return 1;
}

