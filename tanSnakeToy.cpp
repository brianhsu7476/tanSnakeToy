#include <bits/stdc++.h>
#define rep(i,n) for(int i=0; i<(int)(n); ++i)
#define fup(i,a,b) for(int i=(a); i<(int)(b); ++i)
#define fdn(i,a,b) for(int i=(a); i>(int)(b); --i)
using namespace std;
#define kN 12

struct P{
	int x, y, z;
	P(){}
	P(int x, int y, int z):x(x), y(y), z(z){}
}ans[kN*kN*kN];

int n, n0, n1, n2;
bool shape[kN*kN*kN], used[kN][kN][kN];

int dis(P a, P b){return abs(a.x-b.x)+abs(a.y-b.y)+abs(a.z-b.z);}
int shp(P a, P b){return dis(a, b)==2?abs(a.x-b.x)==2||abs(a.y-b.y)==2||abs(a.z-b.z)==2:-1;}

bool dfs1(int x){
	if(x>=n)return 1;
	rep(i, n0)rep(j, n1)rep(k, n2)if(i+j+k&1&&!used[i][j][k]){
		if(dis(ans[x-1], P(i, j, k))!=1||x!=n-1&&dis(ans[x+1], P(i, j, k))!=1)continue;
		if(x>1&&shp(ans[x-2], P(i, j, k))!=shape[x-1])continue;
		used[i][j][k]=1, ans[x]=P(i, j, k);
		if(dfs1(x+2))return 1;
		used[i][j][k]=0;
	}
	return 0;
}

bool dfs0(int x){
	if(x>=n)return dfs1(1);
	rep(i, n0)rep(j, n1)rep(k, n2)if((i+j+k&1)==0&&!used[i][j][k]){
		if(x&&shp(ans[x-2], P(i, j, k))!=shape[x-1])continue;
		used[i][j][k]=1, ans[x]=P(i, j, k);
		if(dfs0(x+2))return 1;
		used[i][j][k]=0;
	}
	return 0;
}

signed main(){
	ios::sync_with_stdio(0), cin.tie(0);
	cout<<"Enter the length of eash side: ";
	cin>>n0>>n1>>n2, n=n0*n1*n2;
	cout<<"Enter the shape of the tan snake: (0 for 90-degree turn, 1 for straight line) ";
	string s; cin>>s, assert(s.size()==n-2);
	fup(i, 1, n-1)shape[i]=s[i-1]-48;
	if(!dfs0(0))cout<<"Answer not found.\n";
	else rep(i, n)cout<<ans[i].x<<' '<<ans[i].y<<' '<<ans[i].z<<endl;

}
