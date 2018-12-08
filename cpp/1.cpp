#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
using namespace std;
const int N=50010,P_2=10000;
const int LOG=30;
inline int read(){
	int x=0,f=1;char ch;
	do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
	do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
	return x*f;
}
inline void write(ll x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
int n,m,p,c,a[N];
inline ll mo(ll a,ll b){
	return a>b?a%b+b:a;
}
int getphi(int p){
	int t=p;
	for (int i=2;i*i<=p;++i){
		if (p%i==0){
			t-=t/i;
			while(p%i==0) p/=i;
		}
	}
	if (p>1) t-=t/p;
	return t;
}
ll phi[LOG],t1[LOG][P_2+1],t2[LOG][P_2+1];
int lp;
inline ll Pow(int tip,int k){
	return mo(1ll*t1[tip][k%P_2]*t2[tip][k/P_2],phi[tip]);
}
inline ll calc(int k,int x,int tip){
	if (tip>lp||x<=0) return k;
	return Pow(tip,calc(k,x-1,tip+1));
}
struct node{
	ll sum;
	int now;
	bool is;
}data[N<<2];
inline void pushup(int o){
	data[o].sum=data[o<<1].sum+data[o<<1|1].sum,data[o].sum%=p;
//	if (data[o].sum>=p) data[o].sum-=p;
	data[o].is=data[o<<1].is&&data[o<<1|1].is;
}
void create(int o,int l,int r){
	if (l==r){
		data[o].is=data[o].now=0,data[o].sum=a[l];
		return;
	}
	int mid=(l+r)>>1;
	create(o<<1,l,mid);
	create(o<<1|1,mid+1,r);
	pushup(o);
}
void add(int o,int l,int r,int x,int y){
	if (data[o].is) return;
	if (l==r){
		++data[o].now;
		data[o].sum=calc(a[l],data[o].now,0);
		if (data[o].now>lp) data[o].is=1;
		return;
	}
	int mid=(l+r)>>1;
	if (x<=mid) add(o<<1,l,mid,x,y);
	if (y>mid) add(o<<1|1,mid+1,r,x,y);
	pushup(o);
}
int ask(int o,int l,int r,int x,int y){
	if (x<=l&&r<=y) return data[o].sum%p;
	int mid=(l+r)>>1,ans=0;
	if (x<=mid){
		ans+=ask(o<<1,l,mid,x,y);
		if (ans>=p) ans%=p;
	}
	if (y>mid){
		ans+=ask(o<<1|1,mid+1,r,x,y);
		if (ans>=p) ans%=p;
	}
	return ans;
}
int main(){
//	fread(ch,1,ch_top,stdin);
	n=read(),m=read(),p=read(),c=read();
	lp=0;phi[0]=p;
	while (phi[lp]!=1)
	phi[lp+1]=getphi(phi[lp]),++lp;
	for (int i=0;i<=lp;++i){
		t1[i][0]=t2[i][0]=1;
		for (int j=1;j<=P_2;++j) t1[i][j]=mo(1ll*t1[i][j-1]*c,phi[i]);
		for (int j=1;j<=P_2;++j) t2[i][j]=mo(1ll*t2[i][j-1]*t1[i][P_2],phi[i]);
	}
	for (int i=1;i<=n;++i) a[i]=read();
	create(1,1,n);
	for (int i=1;i<=m;++i){
		int opt=read(),l=read(),r=read();
		if (!opt) add(1,1,n,l,r);
		else write(ask(1,1,n,l,r)),putchar('\n');
	}
//	fwrite(ch,1,now_w-ch,stdout);
	return 0;
}
