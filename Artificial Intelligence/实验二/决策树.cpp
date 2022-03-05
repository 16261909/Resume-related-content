#include<bits/stdc++.h>
using namespace std;
const int maxn=100;
const int maxele=4;
const double inf=1e9;
struct node
{
	double a[maxele];
	int type;
}p[maxn],o;
struct vec
{
	vector<int>v;
	int k,ch[2];
	double m;//ch[0]<=m ch[1]>m
	bool isleaf;
}a[maxn];
int n,root,tot,cnt;
int newnode(int fa)
{
	tot++;
//	for(int i=0;i<maxele;i++)a[tot].st[i]=a[fa].st[i];
	return tot;
}
double getent(vector<int>&v,int k,double val,int dir)
{
	cnt=0;
	int p1=0,p2=0,p3=0,sz=v.size();
	assert(sz>0);
	for(int i=0;i<v.size();i++)
	{
		if(dir==0&&p[v[i]].a[k]>val){sz--;continue;}
		if(dir==1&&p[v[i]].a[k]<=val){sz--;continue;}
		cnt++;
		if(p[v[i]].type==1)p1++;
		if(p[v[i]].type==2)p2++;
		if(p[v[i]].type==3)p3++;
	}
	double ret=0;
	if(p1)ret-=1.0*p1/sz*log2(1.0*p1/sz);
	if(p2)ret-=1.0*p2/sz*log2(1.0*p2/sz);
	if(p3)ret-=1.0*p3/sz*log2(1.0*p3/sz);
//	printf("getent:%d %lf %d %lf(%d %d %d %d)\n",k,val,dir,ret,p1,p2,p3,sz);
	return ret;
}
void dfs(int u)
{
	bool flag=1;
	assert(a[u].v.size()>0);
	for(int i=0;i<a[u].v.size();i++)flag&=p[a[u].v[i]].type==p[a[u].v[0]].type;
	if(flag)
	{
		a[u].isleaf=1;
		a[u].k=p[a[u].v[0]].type;
		return;
	}
	a[u].ch[0]=newnode(u);
	a[u].ch[1]=newnode(u);
	a[u].k=-1;
	double ent[maxele+1]={},mxt[maxele]={};
	ent[maxele]=getent(a[u].v,1,inf,0);
//	printf("%lf\n",ent[maxele]);
	for(int t=0;t<maxele;t++)
	{
//		puts("!");
//		if(a[u].st[t])continue;
		double mn=inf;
		vector<double>s;
		for(int i=0;i<a[u].v.size();i++)s.push_back(p[a[u].v[i]].a[t]);
		sort(s.begin(),s.end());
		s.erase(unique(s.begin(),s.end()),s.end());
		for(int i=0;i+1<s.size();i++)
		{
			double x=(s[i]+s[i+1])/2.0;
			double tmp=getent(a[u].v,t,x,0);
			ent[t]=1.0*cnt/a[u].v.size()*tmp;
			tmp=getent(a[u].v,t,x,1);
			ent[t]+=1.0*cnt/a[u].v.size()*tmp;
			if(mn>ent[t])
			{
				mn=ent[t];
				mxt[t]=x;
			}
		} 
		ent[t]=ent[maxele]-mn;
//		printf("%d %lf\n",t,ent[t]);
		if(a[u].k==-1||ent[t]>ent[a[u].k])a[u].k=t;
	}
	assert(a[u].k!=-1);
	a[u].m=mxt[a[u].k];
//	a[a[u].ch[0]].st[k]=1;
//	a[a[u].ch[1]].st[k]=1;
//	printf("%d %lf\n",a[u].k,a[u].m);
//	printf("%lf %lf %lf %lf %lf\n",ent[0],ent[1],ent[2],ent[3],ent[4]);
	for(int i=0;i<a[u].v.size();i++)
	{
//		printf("!%d %d %d\n",a[u].v[i],i,a[u].v.size());
//		printf("@%d %d %d\n",u,a[u].ch[0],a[u].ch[1]);
		if(p[a[u].v[i]].a[a[u].k]<=a[u].m)a[a[u].ch[0]].v.push_back(a[u].v[i]);
		if(p[a[u].v[i]].a[a[u].k]>a[u].m)a[a[u].ch[1]].v.push_back(a[u].v[i]);
//		printf("%d %d %d\n",a[a[u].ch[0]].v.size(),a[a[u].ch[1]].v.size(),a[u].v.size());
	}
	if(a[a[u].ch[0]].v.size()+a[a[u].ch[1]].v.size()!=a[u].v.size())printf("%d %d %d\n",a[a[u].ch[0]].v.size(),a[a[u].ch[1]].v.size(),a[u].v.size());
	assert(a[a[u].ch[0]].v.size()!=0);
	assert(a[a[u].ch[1]].v.size()!=0);
	assert(a[a[u].ch[0]].v.size()+a[a[u].ch[1]].v.size()==a[u].v.size());
	a[u].v.clear();
	dfs(a[u].ch[0]);
	dfs(a[u].ch[1]);
}
void init()
{
	freopen("traindata.txt","r",stdin);
	freopen("output.txt","w",stdout);
	do{n++;}while(scanf("%lf%lf%lf%lf%d",&p[n].a[0],&p[n].a[1],&p[n].a[2],&p[n].a[3],&p[n].type)!=EOF);
	n--;
	root=1;
	for(int i=1;i<=n;i++)a[root].v.push_back(i);
}
bool dfs1(int u)
{
	if(a[u].isleaf)
		return a[u].k==o.type;
	return dfs1(a[u].ch[o.a[a[u].k]>a[u].m]);
}
void check()
{
	freopen("testdata.txt","r",stdin);
	int sum=0,cnt1=0;
	while(scanf("%lf%lf%lf%lf%d",&o.a[0],&o.a[1],&o.a[2],&o.a[3],&o.type)!=EOF)
	{
		if(dfs1(root))cnt1++;
		sum++;
	}
	printf("\nsuccessful ratio:%.2lf%%\n",100.0*cnt1/sum);
}
void print(int u,int cur)
{
	if(!u)return;
	if(a[u].isleaf)
	{
		for(int i=1;i<=cur;i++)printf("\t");
		printf("'%d'\n",a[u].k);
		return;
	}
	for(int i=1;i<=cur;i++)printf("\t");
	printf("property%d:\n",a[u].k+1);
	for(int i=1;i<=cur;i++)printf("\t");
	puts("{");
	for(int i=1;i<=cur;i++)printf("\t");
	printf("'<=%.2f':\n",a[u].m);
	print(a[u].ch[0],cur+1);
	for(int i=1;i<=cur;i++)printf("\t");
	printf("'>%.2lf':\n",a[u].m);
	print(a[u].ch[1],cur+1);
	for(int i=1;i<=cur;i++)printf("\t");
	puts("}");
}
int main()
{
	init();
	dfs(root=newnode(0));
	print(root,0);
	check();
} 
/*
*/
