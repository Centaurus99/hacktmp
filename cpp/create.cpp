#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include <iomanip>
#define ll long long
#define ull unsigned long long
using namespace std;
const int JUDGE_type=0;
/* JUDGE_type:
0-->number
1-->string(无法使用)
......*/
const int Line=50010;
/* N:
输出最大行数
......*/
inline ll read(){
	ll x=0,f=1;char ch;
	do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
	do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
	return x*f;
}
inline void write(ull x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
int TL,Maxn,Maxm,Maxp,type;
/* 数据生成相关参数
Maxn-->基本参数
Maxm-->基本参数
Maxp-->基本参数
type-->生成数据类型
......*/
/*	注意！ 
数据生成值域为 [0,n)
......*/
ull Pow[64];
struct Slow_create_node{
	/* 
	2的次方模数生成
	自适应数据大小 
	分布均匀，速度较慢
	......*/
	inline int get_short(){
		return rand();
	}
	inline int get_int(){
		int x=(rand()<<15);
		x+=rand();
		return x;
	}
	inline ll get_ll(){
		ll x=((ll)get_int()<<30);
		x+=get_int();
		return x;
	}
	inline ull get_ull(){
		ull x=rand();
		x<<=60;
		x+=get_ll();
		return x;
	}
	inline ull get_num(ull n){
		ll mod=upper_bound(Pow,Pow+64,n)-Pow;
		mod=Pow[mod];
		ll x=mod;
		if (n<((ull)1<<15)){
			while (x>n) x=get_short();
			return x;
		}
		if (n<((ull)1<<30)){
			while (x>n) x=get_int();
			return x;
		}
		if (n<((ull)1<<60)){
			while (x>n) x=get_ll();
			return x;
		}
		while (x>n) x=get_ull();
		return x;
	}
}Slow_create;
struct Quick_create_node{
	/* 
	分布不大均匀，速度较快
	需自行选择生成类型 
	......*/
	inline int get_short(int n){
		return rand()%n;
	}
	inline int get_int(int n){
		int x=(rand()<<15);
		x+=rand();
		return x%n;
	}
	inline ll get_ll(ll n){
		ll x=((ll)Slow_create.get_int()<<30);
		x+=Slow_create.get_int();
		return x%n;
	}
	inline ull get_ull(ull n){
		ull x=rand();
		x<<=60;
		x+=Slow_create.get_ll();
		return x%n;
	}
}Quick_create;
/*---*/void start(){
	srand((unsigned long long)new char);
	for(int i=0;i<=63;++i) Pow[i]=((ull)1<<i);
	freopen("..\\..\\create.in","r",stdin);
	TL=read();
	Maxn=read(),Maxm=read(),Maxp=read();
	fclose(stdin);
}
/*---*/void data_create(){
	int n=Quick_create.get_int(Maxn)+1;
	int m=Quick_create.get_int(Maxm)+1,p=Quick_create.get_int(Maxp)+2;
	freopen("input","w",stdout);
	printf("%d %d %d %d\n",n,m,p,Quick_create.get_int(p-1)+1);
	for (int i=1;i<=n;++i) printf("%d ",Quick_create.get_int(p));
	printf("\n");
	for (int i=1;i<=m;++i){
		int opt=Quick_create.get_int(2),l=Quick_create.get_int(n)+1,r=Quick_create.get_int(n)+1;
		if (l>r) swap(l,r);
		printf("%d %d %d\n",opt,l,r);
	}
	fclose(stdout);
}
/*judge
0-->AC
1-->WA
......*/
/*---*/bool judge(){
	if (JUDGE_type==0){
		int ans1[Line+1],ans2[Line+1];
		int tmp;
		freopen("output1","r",stdin);
		int t1=0;
		while (~scanf("%d",&tmp)) ans1[++t1]=tmp;
		fclose(stdin);
		freopen("output2","r",stdin);
		int t2=0;
		while (~scanf("%d",&tmp)) ans2[++t2]=tmp;
		fclose(stdin);
		bool issame=1;
		for (int i=1;i<=t1;++i){
			if (ans1[i]!=ans2[i]){
				issame=0;
				cout<<"line "<<i<<':'<<endl;
				cout<<'\t'<<"1'ans:"<<ans1[i]<<endl;
				cout<<'\t'<<"2'ans:"<<ans2[i]<<endl;
			}
		}
		if (t1!=t2||!issame){
			cout<<"WA----------------------\n";
			return 1;
		}
		return 0;
	}
	//'JUDGE_type==1'存在bug
	/*if (JUDGE_type==1){
		string ans1[N+1],ans2[N+1];
		string tmp;
		freopen("output1","r",stdin);
		int t1=0;
		while (cin>>tmp) ans1[++t1]=tmp;
		fclose(stdin);
		freopen("output2","r",stdin);
		int t2=0;
		while (cin>>tmp) ans2[++t2]=tmp;
		fclose(stdin);
		bool issame=1;
		for (int i=1;i<=max(t1,t2);++i){
			if (ans1[i]!=ans2[i]){
				issame=0;
				cout<<"line "<<i<<':'<<endl;
				cout<<'\t'<<"1'ans:"<<ans1[i]<<endl;
				cout<<'\t'<<"2'ans:"<<ans2[i]<<endl;
			}
		}
		if (t1!=t2||!issame){
			cout<<"WA----------------------\n";
			return 1;
		}
		return 0;
	}*/ 
}
int main(){
	start();
	cerr<<"Starting";
	while (clock()<=125);
	cerr<<'.';
	while (clock()<=250);
	cerr<<'.';
	while (clock()<=375);
	cerr<<'.';
	while (clock()<=500);
	cerr<<"begin!"<<endl;
	while (1){
		data_create();
		int time1,time2,thx,wph;
		time1=clock();
		system("1.exe < input > output1");
		time1=clock()-time1;
		time2=clock();
		system("2.exe < input > output2");
		time2=clock()-time2;
		cerr<<"1:"<<setw(4)<<time1<<"ms   "<<"2:"<<setw(4)<<time2<<"ms"<<endl;
		bool tle=0;
		freopen("error.log","w",stdout);
		if (time1>TL){
			cout<<"1 TLE"<<setw(6)<<time1<<"ms\n";
			tle=1;
		}
		if (time2>TL){
			cout<<"2 TLE"<<setw(6)<<time2<<"ms\n";
			tle=1;
		}
		if (judge()||tle){
			break;
		}
		fclose(stdout);
	}
	return 0;
}
