#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <cassert>
#include <ctime>
using namespace std;
typedef long long LL;
#define For(i,a,b) for (int i = (a); i <= (b); i++)
#define Cor(i,a,b) for (int i = (a); i >= (b); i--)
#define rep(i,a) for (int i = 0; i < a; i++)
#define Fill(a,b) memset(a,b,sizeof(a))

#define maxn 1000
#define maxm 8000
struct EDGE {
	int y, z, id;
};

vector<EDGE> e[maxn];
int Link[maxn][maxn];
bool vise[maxm];
int ans[maxn];
bool visit[maxn];
int source,destination,m,n;

int main(int argc, char *argv[]) {
	freopen(argv[1], "r", stdin);
	int w, x, y, z;
	char ch;
	while(scanf("%d,%d,%d,%d", &w, &x, &y, &z) != EOF) {
		++m;
		if(Link[x][y] == 0) {
			Link[x][y] = z;
			e[x].push_back(EDGE{y, z, w});
		}
		else {
			Link[x][y] = min(Link[x][y], z);
			for(int i = 0; i < e[x].size(); i++) 
				if(e[x][i].y == y) {
				e[x][i].z = z;
				e[x][i].id = w;
			}
		}
		n = max(n, x);
		n = max(n, y);
	}
	n++;
	freopen(argv[2], "r", stdin);
	scanf("%d,%d,", &source, &destination);
	while(scanf("%d", &x) != EOF) {
		visit[x] = 1;
		scanf("%c", &ch);
	}
	freopen(argv[3], "r", stdin);
	while(scanf("%d", &x) != EOF) {
		vise[x] = 1;
		scanf("%c", &ch);
	}
	int cost = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < e[i].size(); j++)
			if (vise[e[i][j].id])
			{
				cost += e[i][j].z;
				if (visit[i])
					visit[i] = 0;
				if (visit[e[i][j].y])
					visit[e[i][j].y] = 0;
			}
	for (int i = 0; i < n; i++)
		if (visit[i])
			cost = 0;
	printf("%d\n", cost);
	return 0;
}

