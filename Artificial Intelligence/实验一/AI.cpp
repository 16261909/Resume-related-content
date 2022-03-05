#include<bits/stdc++.h>
using namespace std;
char s[2];
long long st,ed;
int ans;
map<long long,bool>vis[2];
map<long long,long long>fa;
map<long long,int>h,f,g;//f=g+h<=g+h'(true)
priority_queue<pair<int,long long>,vector<pair<int,long long>>,greater<pair<int,long long>>>q;
int geth(long long s)
{
	int ret=-1;
	for(int i=1;i<=9;i++)
		ret+=(s>>(4*(i-1))&15)!=(ed>>(4*(i-1))&15);//count different digits
	return max(ret,0);//special judge
}
void update(long long s,long long ss)
{
	if(vis[1][ss])
	{
		if(f[ss]>f[s]+1)
		{
			fa[ss]=s;
			g[ss]=g[s]+1;
			f[ss]=g[ss]+h[ss];
			vis[0][ss]=1;
			vis[1][ss]=0;
			q.push(make_pair(f[ss],ss));
			//close->open 
		}
	}
	else if(vis[0][ss])
	{
		if(f[ss]>f[s]+1)
		{
			fa[ss]=s;
			g[ss]=g[s]+1;
			f[ss]=g[ss]+h[ss];
			q.push(make_pair(f[ss],ss));
			//open->open(update priority_queue)
		}
	}
	else
	{
		vis[0][ss]=1;
		fa[ss]=s;
		h[ss]=geth(ss);
		g[ss]=g[s]+1;
		f[ss]=g[ss]+h[ss];
		q.push(make_pair(f[ss],ss));
		//unvis->open
	}
}
void solve()
{
	if(st==ed)
	{
		ans=0;
		return;
	}
	h[st]=geth(st);
	g[st]=0;
	f[st]=h[st]+g[st];
	vis[0][st]=1;
	q.push(make_pair(f[st],st));
	while(!q.empty())
	{
		pair<int,long long>u=q.top();q.pop();
		if(f[u.second]!=u.first)continue;//redundancy
		if(u.second==ed)
		{
			ans=u.first;
			return;
		}
		long long s=u.second,ss=0;
		/*
		//print search process for debug
		printf("----------------------\nf:%d g:%d h:%d\n",f[s],g[s],h[s]);
		for(int i=1;i<=9;i++)
		{
			printf("%d ",(s>>(4*(i-1)))&15);
			if(i%3==0)puts("");
		}
		*/
		vis[1][st]=1;
		vis[0][st]=0;
		int pos=0;
		for(int i=1;i<=9;i++)if((s>>(4*(i-1))&15)==0)pos=i;
		assert(pos!=0);
		if(pos%3!=0)//right
		{
			long long d=((s>>4*(pos-1+1))&15);
			ss=s&(~(15ll<<(4*(pos-1+1))));
			ss&=(~(15ll<<(4*(pos-1))));
			ss|=((d<<(4*(pos-1))));
			update(s,ss);
		}
		if(pos%3!=1)//left
		{
			long long d=((s>>4*(pos-1-1))&15);
			ss=s&(~(15ll<<(4*(pos-1))));
			ss&=(~(15ll<<(4*(pos-1-1))));
			ss|=((d<<(4*(pos-1))));
			update(s,ss);
		}
		if(pos>=4)//down
		{
			long long d=((s>>4*(pos-1-3))&15);
			ss=s&(~(15ll<<(4*(pos-1))));
			ss&=(~(15ll<<(4*(pos-1-3))));
			ss|=((d<<(4*(pos-1))));
			update(s,ss);
		}
		if(pos<=6)//up
		{
			long long d=((s>>4*(pos-1+3))&15);
			ss=s&(~(15ll<<(4*(pos-1))));
			ss&=(~(15ll<<(4*(pos-1+3))));
			ss|=((d<<(4*(pos-1))));
			update(s,ss);
		}
	}
}
int check(long long s)//O(n^2) count inverted pair 
{
	int ret=0;
	for(int i=1;i<=9;i++)
	{
		int x=(s>>(4*(9-i)))&15;
		for(int j=i+1;j<=9;j++)
		{
			int y=(s>>(4*(9-j)))&15;
			if(x>y&&y!=0)ret++;
		}
	}
	return ret;
}
void init()
{
	//memset
	vis[0].clear();
	vis[1].clear();
	h.clear();
	f.clear();
	g.clear();
	fa.clear();
	ans=1e9;
	while(!q.empty())q.pop();
	//read
	for(int i=1;i<=9;i++)
	{
		scanf("%s",s+1);
		st=st|((1ll*s[1]-'0')<<(4*(i-1)));
	}
//	printf("%lld\n",st);
	for(int i=1;i<=9;i++)
	{
		scanf("%s",s+1);
		ed=ed|((1ll*s[1]-'0')<<(4*(i-1)));
	}
	if(check(st)%2!=check(ed)%2)ans=-1;//special judge
//	printf("%d %d\n",check(st),check(ed));
}
void print()
{
	if(ans==-1)
	{
		puts("Unreachable");
		return;
	}
	printf("Total step is %d\n",ans);
	long long s=ed;
	vector<long long>v;
	while(s!=st)
	{
		v.push_back(s);
		s=fa[s];
	}
	v.push_back(st);
	while(v.size()>=1)
	{
		long long s=v.back();v.pop_back();
		for(int i=1;i<=9;i++)
		{
			if(i==4)printf("Step:%03d |",g[s]);
			if(i==1||i==7)printf("         |");
			printf("%d ",(s>>(4*(i-1)))&15);
			if(i%3==0)putchar('|');
			if(i==6)printf("f:%d g:%d h:%d",f[s],g[s],h[s]);
			if(i%3==0)puts("");
		}
		if(v.size()>=1)puts("-----------------");
	}
}
int main()
{
	while(1)
	{
		init();
		if(ans!=-1)solve();
		print();
	}
}
/*

1 2 3
4 0 5
6 7 8
1 2 3
4 0 5
6 8 7


2 3 5
1 0 6
4 8 7
1 2 3
4 0 5
6 7 8
*/
