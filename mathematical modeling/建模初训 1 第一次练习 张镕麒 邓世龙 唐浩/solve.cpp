#include<bits/stdc++.h>
using namespace std;
const int maxn=70;
const int maxm=200;
const int maxd=30;
const int maxw=250;
const int maxf=250;
int debug=0,idi,idj;
int w[5],f[5],type[maxn],wt[maxd+2];
int dp[maxn][maxd+2][maxw+2][maxf+2];
bool book[maxn][maxd+2][maxw+2][maxf+2];
//int last[maxn][maxd+2][maxw+2][maxf+2];
//map<int,map<int,map<int,map<int,int> > > >b;//[maxn][maxd+2][maxw+2][maxf+2];
//map<int,map<int,map<int,map<int,bool> > > >book;
int d,n,m,mxwei,mon0,Wwei,Fwei,a0,st,ed,tmp,ans;//[maxd];
bool final;
vector<int>v[maxn];
int dfs(int pos,int day,int W,int F,int pre,int tm)
{
//	assert(pre>100000&&tm!=0); 
	if(W<0||F<0||pre<0||day>d)return 0xc0c0c0c0;
	if(book[pos][day][W][F]==1)return dp[pos][day][W][F];
	else
	{
		if(debug==1)printf("[%d %d %d %d %d\n",pos,day,W,F,pre);
		book[pos][day][W][F]=1;
		int ret=0xc0c0c0c0;
		if(pos==ed)
		{
//			printf("%d %d %d %d\n",day,W,F,pre);
			if(debug==1)puts("!");
			if(pre+W*(w[0]>>1)+F*(f[0]>>1)>ans)
			{
				ans=pre+W*(w[0]>>1)+F*(f[0]>>1);
				if(ans==20250)// 20250
				{
					final=1;
					return 0;
				}
				printf("%d %d %d %d %d %d %d %d\n",idi,idj,day,W,F,ans,tm,pre);
			}
			return dp[pos][day][W][F]=W*(w[0]>>1)+F*(f[0]>>1);
		}
		if(type[pos]==3)//trans 2
		{
			if(debug==1)puts("@");
			int J=min((mxwei-W*Wwei-F*Fwei)/(Wwei+Fwei),pre/(2*(w[0]+f[0])));
			for(int j=J;j>=1;j-=5)
			{
				int i=j;
				int tmp1=dfs(pos,day,W+i,F+j,pre-(2*i*w[0]+2*j*f[0]),tm);
				if(final)
				{
					printf("(%d %d %d %d %d)\n",W+i,F+j,(mxwei-W*Wwei-F*Fwei)/(Wwei+Fwei),pre/(2*(w[0]+f[0])),J);
					printf("(%d %d %d)\n",W,F,mxwei);
				}
				if(final)
				{
					printf("%d %d %d %d %d\n",pos,day,W,F,pre);
					return 0;
				}
				if(tmp1>ret)
				{
//					last[pos][day][W][F]=2;
//					b[pos][day][W][F]=j;
					ret=tmp1;
				}
			}
		}
		if(wt[day]!=3)//trans 3
		{
			if(debug==1)puts("$");
			for(int i=0;i<v[pos].size();i++)
			{
				int tmp1=dfs(v[pos][i],day+1,W-2*w[wt[day]],F-2*f[wt[day]],pre,tm);
				if(final)
				{
					printf("%d %d %d %d %d\n",pos,day,W,F,pre);
					return 0;
				}
				if(tmp1>ret)
				{
//					last[pos][day][W][F]=3+10*i;
					ret=tmp1;
				}
			}
		}
		if(type[pos]==2)//trans 4
		{
			if(debug==1)puts("^");
			int tmp1=dfs(pos,day+1,W-3*w[wt[day]],F-3*f[wt[day]],pre+a0,tm+1);
			if(final)
				{
					printf("%d %d %d %d %d\n",pos,day,W,F,pre);
					return 0;
				}
			if(tmp1>ret)
			{
//				last[pos][day][W][F]=4;
				ret=tmp1;
			}
		}
		if(debug==1)puts("#");
		//trans 5 
		int tmp1=dfs(pos,day+1,W-w[wt[day]],F-f[wt[day]],pre,tm);
		if(final)
				{
					printf("%d %d %d %d %d\n",pos,day,W,F,pre);
					return 0;
				}
		if(tmp1>ret)
		{
			ret=tmp1;
//			last[pos][day][W][F]=5;
		}
		if(debug==1)puts("]");
		return dp[pos][day][W][F]=ret;
	}
}
/*
void dfs1(int pos,int day,int W,int F,int pre)
{
	printf("!%d:%d %d %d %d %d\n",last[pos][day][W][F],pos,day,W,F,pre);
	if(pos==ed)
	{
		return;
	}
	if(last[pos][day][W][F]%10==3)
	{
		int j=last[pos][day][W][F]/10;
		dfs1(v[pos][j],day+1,W-2*w[wt[day]],F-2*f[wt[day]],pre);
	}
	if(last[pos][day][W][F]%10==4)
	{
		dfs1(pos,day+1,W-3*w[wt[day]],F-3*f[wt[day]],pre+a0);
	}
	if(last[pos][day][W][F]%10==5)
	{
		dfs1(pos,day+1,W-w[wt[day]],F-f[wt[day]],pre);
	}
	if(last[pos][day][W][F]%10==2)
	{
		int j=b[pos][day][W][F];
		dfs1(pos,day,W+j,F+j,pre-(2*j*w[0]+2*j*f[0]));
	}
	return;
}
*/
int main()
{
//	freopen("123.txt","r",stdin);
//	freopen("1234.txt","r",stdin);

	scanf("%d%d%d%d",&d,&mxwei,&mon0,&a0);
	mon0<<=1;
	a0<<=1;
	scanf("%d%d%d%d%d",&Wwei,&w[0],&w[1],&w[2],&w[3]);
	scanf("%d%d%d%d%d",&Fwei,&f[0],&f[1],&f[2],&f[3]);
	w[0]<<=1;
	f[0]<<=1;
	for(int i=1;i<=d;i++)scanf("%d",&wt[i]);
	scanf("%d%d",&st,&ed);
	scanf("%d",&tmp);for(int i=1,tmp1;i<=tmp;i++)scanf("%d",&tmp1),type[tmp1]=2;
	scanf("%d",&tmp);for(int i=1,tmp1;i<=tmp;i++)scanf("%d",&tmp1),type[tmp1]=3;
	scanf("%d%d",&n,&m);
	for(int i=1,tmp1,tmp2;i<=m;i++)
	{
		scanf("%d%d",&tmp1,&tmp2);
		v[tmp1].push_back(tmp2);
		v[tmp2].push_back(tmp1);
	}
	/*
	for(int j=5;j*Wwei+j*Fwei<=mxwei;j+=5)
	{
//		puts("!");
		int i=j;idi=j,idj=j;
		memset(book,0,sizeof book);
		memset(dp,0xc0,sizeof dp);
		dfs(st,1,i,j,mon0-i*w[0]-j*f[0],0);
//		if(i>=90&&j>=90&&tmp>0)printf("%d %d %d\n",i,j,tmp);
//		if(tmp>0)printf("%d %d %d\n",i,j,tmp);
//		if(i>=89&&tmp>0)printf("%d %d %d\n",i,j,tmp);
	}
	*/
	if(debug>=0)
	{
		memset(book,0,sizeof book);
		memset(dp,0xc0,sizeof dp);
//		memset(ans,0xc0,sizeof ans);
		int i,j=240;i=j;
		tmp=dfs(st,1,i,j,mon0-i*w[0]-j*f[0],0);
//		dfs1(st,1,i,j,mon0-i*w[0]-j*f[0]);
	}
}
