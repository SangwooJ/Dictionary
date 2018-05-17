#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//sub시 xxx존재 yyy존재하면 yyy값을 xxx값으로 대체??


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
	Header *arrp; //헤더가르킴
	Node *head; //리스트의 노드를 가르키는 헤더
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

void initList(List *plist, Header header[]) { //리스트 초기화
	initHeader(header);
	plist->arrp = header;
	plist->head = NULL;

}

Header *findHeader(List *plist, char* str) { //단어의 첫글자로 헤더의 주소를 반환
	int i = 0;
	for (i = 0; i < 53; i++) {
		if (plist->arrp[i].data == str[0]) {
			//printf("r값 %c \n", plist->arrp[i].data);
			return &(plist->arrp[i]);
		}
	}
	return NULL;
}

Node* new_node(char *str, int val) { //노드생성

	Node *p = (Node*)malloc(sizeof(Node));
	p->pkey = str;
	p->val = val;
	p->next = NULL;
	return p;
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

void addNode(List *plist, char *str, int val) {
	Node* p = new_node(str, val);
	Header *hp = findHeader(plist, str);
	if (existNode(plist, str) == 1) { //중복일경우
		return;
	}
	if (hp->next == NULL) { //헤더 다음 첫번째노드를 추가할때
		hp->next = p;
	}
	else { //2번쨰 노드부터
		plist->head = hp->next;
		while (plist->head->next != NULL)
		{
			plist->head = plist->head->next;
		}
		plist->head->next = p;
	}
}

void searchNode(List *plist, char *str) { //검색
	Header *hp = findHeader(plist, str);
	if (hp->next == NULL) { //하나도 없을경우
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
			if (plist->head->next != NULL) //마지막 노드가아니면 공백추가
				printf(" ");
		}
		plist->head = plist->head->next;
	} while (plist->head != NULL);
	if (existNode(plist, str) == 0) { //못찾을경우 newline
		printf("\n");
	}
}

void deleteNode(List *plist, char *str, int *val) { //검색
	Header *hp = findHeader(plist, str);
	Node* bef;
	if (hp->next == NULL) { //하나도 없을경우
		return;
	}
	plist->head = hp->next; //헤드가 첫번째노드를 가르킴
	if (strcmp(plist->head->pkey, str) == 0) { //첫번째 노드의 삭제일경우
		hp->next = plist->head->next; //삭제
		*val = plist->head->val;
		free(plist->head);
		return;
	}
	bef = plist->head;
	plist->head = plist->head->next;
	while (plist->head != NULL) {
		if (strcmp(plist->head->pkey, str) == 0) {
			bef->next = plist->head->next;
			*val = plist->head->val;
			free(plist->head);
			return;
		}
		bef = plist->head;
		plist->head = plist->head->next;
	}
	if (existNode(plist, str) == 0) { //못찾을경우 newline
		return;
	}
}

void sub(List *plist, char* x, char* y) { //x를 삭제하고 y를 추가
	int val=0;
	if (existNode(plist, x) == 0) { //x가 존재하지 않으면
		return;
	}
	if (strcmp(x, y) == 0) { //x와 y가 같으면
		return;
	}
	deleteNode(plist, x,&val);
	addNode(plist, y,val);
}


char* input() {
	const static char* end = "\n";
	char tmp[10];
	char* rtn = NULL;

	while (fgets(tmp, 10, stdin), 1) {
		if (!rtn) {
			rtn = (char*)malloc(strlen(tmp) + 1);
			strcpy(rtn, tmp);
		}
		else {
			rtn = (char*)realloc(rtn, strlen(rtn) + strlen(tmp) + 1);
			strcat(rtn, tmp);
		}
		if (strstr(rtn, end) != NULL) {
			char* endstr = strstr(rtn, end);
			*endstr = '\0';
			break;
		}
	}
	return rtn;
}

char* getWord(char *sen,int *point) { //get word from sentence ( sen[point]부터 )
	int i = 0;
	int j = 0;
	int start = -1;
	int	end = -2; //문자의 시작과 끝
	char* word;
	for (i = *point; i < (int)strlen(sen); i++) { //단어의 시작
		if (sen[i] == '\0') {
			return NULL;
		}
		if (sen[i] != ' ') {
			start = i;
			break;
		}
	}
	for (j = start; j < (int)strlen(sen)+1; j++) {
		if (j == -1)
			break;
		if ((sen[j] == ' ')|| (sen[j] == '\0')) {
			end = j-1;
			*point = j;
			break;
		}
	}
	if (end - start < 0) {
		return NULL;
	}
	word = (char*)malloc(sizeof(char) * (end-start+1+1));
	for (i = 0; i < end - start + 1; i++) {
		word[i] = sen[start + i];
	}
	word[i] = '\0';
	return word;
}

void allocateWord(List *plist) {
	char *sen;
	char *word;
	int point = 0;
	int i = 0;
	int val = 0;
	//printf("input string : ");
	sen = input();
	while (point != strlen(sen))
	{
		word = getWord(sen, &point);
		if (word == NULL)
			break;
		if (existNode(plist, word) == 1) //이미 존재할경우
			continue;
		addNode(plist, word, val);
		val++;
		//printf("%s ", word);
		
	}

	//printf("\n");
	//printf("%s \n", m);
	free(sen);

}

void runCommand(List* plist) {
	char* com;
	int point = 0;
	int temp=0;
	char* comType;
	char* x;
	char* y;

	com = input();
	comType=getWord(com, &point);
	if (strcmp(comType, "0")==0)
		exit(0);
	x=getWord(com, &point);
	if (strcmp(comType, "sch")==0)
		searchNode(plist, x);
	if (strcmp(comType, "del")==0)
		deleteNode(plist, x, &temp);
	if (strcmp(comType, "sub")==0) {
		y=getWord(com, &point);
		sub(plist, x, y);
		free(y);
	}

	free(com);
	free(x);

}

int main(void) {

	int point = 0;
	int i = 0;
	int temp=0;
	
	List list;
	Header header[53];
	initList(&list, header);
	allocateWord(&list);

	while (1) {
		runCommand(&list);
	}
	
	return 0;
}
