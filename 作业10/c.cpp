#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;
struct node
{
	int k;//记录当前结点编号 
	struct node *next;
}*v;
int ans = 0; int *ru;
int pocket[26];
char *coin;
bool *visit;
int *top_order;
int k=0;
int cmp(const void *a, const void *b) {
	return *(int*)b - *(int*)a;
}
int topsort(int n)
{
	int i;
	struct node *p;
	int *stack = (int*)malloc(sizeof(int)*n), top = -1;
	for (i = n - 1; i >= 0; i--)
		if (ru[i] == 0)stack[++top] = i;//入度为0的点入栈 
	int c = 0;
	while (top > -1)                  //栈非空时循环 
	{
		++c;
		p = &v[stack[top--]];        //取出栈顶元素 
		top_order[k++]=p->k;
		while (p->next != NULL)       //枚举该点所有后继 
		{
			p = p->next;
			if (--ru[p->k] == 0) {      //若去除一条边后入度为0则入栈 
				stack[++top] = p->k;
			}
		}
	}
	return c==n;
}
void check() {
	for (int i = 0; i < 26; i++) {
		if (pocket[i] > ans) {
			ans = pocket[i];
		}
	}
}
void search(node *v) {
	node *p = v->next;
	
	int c = coin[v->k];
	pocket[c]++;
	if (p == NULL) {
		check();
	}
	else while (p) {
		search(p);
		p = p->next;
	}
	pocket[c]--;
}


int main()
{
	int n, m;
	struct node *p, *pp;
	int i, a, b;
	scanf("%d%d", &n, &m);
	ru = (int*)malloc(sizeof(int)*n);
	v = (struct node*)malloc(sizeof(struct node)*n);
	visit = (bool*)malloc(sizeof(int)*n);
	top_order = (int*)malloc(sizeof(int)*n);
	coin = new char[n];
	cin >> coin;
	for (int i = 0; i < n; i++)
		coin[i] -= 'a';
	for (i = 0; i < n; i++)     //初始化：将所有点的入度置0，指针置空 
	{
		ru[i] = 0;
		v[i].k = i;
		v[i].next = NULL;
		visit[i]=false;
	}
	for (i = 0; i < m; i++)
	{
		scanf("%d%d", &a, &b);
		--a; --b;
		ru[b]++;
		p = &v[a];
		while (p->next != NULL)p = p->next;
		pp = (struct node*)malloc(sizeof(struct node));
		pp->next = NULL;
		pp->k = b;
		p->next = pp;
	}
	if (!topsort(n)) {
		printf("-1");
		return 0;
	}

	for (int i = 0; i < 26; i++)
		pocket[i] = 0;

	for (int i = 0; i < n; i++)
		search(v + i);

	printf("%d",ans);

	return 0;
}
/*
6 6
aacabc
1 2
1 3
3 5
3 6
4 2
4 1

3 3
abc
1 2
2 3
3 1
*/