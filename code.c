#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char *pkey; //key
	int val; //value
	struct node *next;
}Node;

typedef struct headerArr {
	char data;
	Node *next;
}Header;

typedef struct list {
	Header *arrp; //일차원리스트르 가리킴
	Node *head;
}List;

void initHeader(Header header[]) { //헤더 데이터 초기화
	int i = 0;
	char initData[53] = { 'a','b','c','d','e','f','g','h','i','j',
		'k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
		'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
		'Q','R','S','T','U','V','W','X','Y','Z','.' };
	for (i = 0; i < 53; i++) {
		header[i].data = initData[i];
		header[i].next = NULL;
	}
}

void initList(List *plist, Header header[]) {
	initHeader(header); 
	plist->arrp = header;
	plist->head = NULL;
	
}

Header *findHeader(List *plist,char* str) {
	int i = 0;
	for (i = 0; i < 53; i++) {
		if (plist->arrp[i].data == str[0]) {
			//printf("r값 %c \n", plist->arrp[i].data);
			return &(plist->arrp[i]);
		}
	}
	return NULL;
}

Node* new_node(char *str,int val) {

	Node *p = (Node*)malloc(sizeof(Node));
	p->pkey = str;
	p->val = val;
	p->next = NULL;
	return p;
}

void addNode(List *plist,char *str, int val) {
	Node* p = new_node(str, val);
	Header *hp = findHeader(plist, str);
	if (hp->next == NULL) { //헤더 다음 첫번째노드를 추가할때
		hp->next = p;
	}
	else { //2번쨰 노드부터
		plist->head = hp->next;
		while (plist->head->next!=NULL)
		{
			plist->head = plist->head->next;
		}
		plist->head->next = p;
	}
}

void searchNode(List *plist, char *str) { //검색
	Header *hp = findHeader(plist, str);
	if (hp->next==NULL) { //하나도 없을경우
		printf("\n");
		return;
	}
	plist->head = hp->next; //헤드가 첫번째노드를 가르킴
	do {
		if (strcmp(plist->head->pkey, str) == 0) {
			printf("%d\n", plist->head->val);
			break;
		}
		else {
			printf("%d", plist->head->val);
			if (plist->head->next != NULL)
				printf(" ");
		}
		plist->head = plist->head->next;
	} while (plist->head != NULL);
	if (existNode(plist, str) == 0) { //못찾을경우 newline
		printf("\n");
	}
}

int existNode(List *plist, char *str) { //검색후 존재하는지여부
	Header *hp = findHeader(plist, str);
	if (hp->next == NULL) { //하나도 없을경우
		return 0;
	}
	plist->head = hp->next; //헤드가 첫번째노드를 가르킴
	do {
		if (strcmp(plist->head->pkey, str) == 0) {
			return 1;
		}
		plist->head = plist->head->next;
	} while (plist->head != NULL);
	return 0;
}

char* input()
{
	const static char* end = ".";
	char tmp[10];
	char* rtn = NULL;

	while (fgets(tmp, 10, stdin), 1)
	{
		if (!rtn)
		{
			rtn = (char*)malloc(strlen(tmp) + 1);
			strcpy(rtn, tmp);
		}
		else
		{
			rtn = (char*)realloc(rtn, strlen(rtn) + strlen(tmp) + 1);
			strcat(rtn, tmp);
		}
		if (strstr(rtn, end) != NULL)
		{
			char* endpoint = strstr(rtn, end);
			*(endpoint + strlen(end)) = '\0';
			break;
		}
	}
	return rtn;
}
char* input2() {
	const static char* end = "\n";
	char tmp[10];
	char* rtn = NULL;

	while (fgets(tmp, 10, stdin), 1) {
		if (!rtn) {
			rtn = (char*)malloc(strlen(tmp) + 1);
			strcpy(rtn, tmp);
		}
		else{
			rtn = (char*)realloc(rtn, strlen(rtn) + strlen(tmp) + 1);
			strcat(rtn, tmp);
		}
		if (strstr(rtn, end) != NULL){
			char* endstr = strstr(rtn, end);
			*endstr = '\0';
			break;
		}
	}
	return rtn;
}

int main(void) {
	char *m;
	int i = 0;
	char *test = "can";
	char *test2 = "apple";
	char *test3 = "ball";
	char *test4 = "count";
	char *test5 = "cccd";
	
	List list;
	
	printf("input string : ");
	m = input();
	printf("%s \n", m);

	free(m);
	
	Header header[53];

	initList(&list,header);
	addNode(&list, test, 3);
	addNode(&list, test2, 5);
	addNode(&list, test4, 2);
	
	searchNode(&list, test4);
	printf("존재여부 :%d \n", existNode(&list, test4));
	searchNode(&list, test3);
	printf("존재여부 :%d \n", existNode(&list, test3));
	searchNode(&list, test2);
	printf("존재여부 :%d \n", existNode(&list, test2));
	searchNode(&list, test5);
	printf("존재여부 :%d \n", existNode(&list, test5));
	//printf("하이 %d", findHeader(&list,test));

	/*
	for (i = 0; i < 53; i++) {
		printf("%d 번째 헤더 : %c \n",i,header[i].data );
	}
	*/
	
	return 0;
}
