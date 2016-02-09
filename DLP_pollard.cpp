#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

#define ll long long int

vector<ll> x;
vector<ll> alpha;
vector<ll> beta;
ll a, b, p, ans=0,u,v,d,w;
int i,j,index,n=29;

inline int gcd(int a, int b)
{
	if(b == 0)
		return a;
	else
		return gcd(b, a % b);
}

ll bigmod(int b,int p,int m)
{
	if (p == 0)
		return 1;
	else if (p%2 == 0)
		return (int)pow(1.0*bigmod(b,p/2,m),2.0) % m; // square(x) = x * x
	else
		return ((b % m) * bigmod(b,p-1,m)) % m;
}

inline int mod(int a,int b)
{
	if((a%b)>=0)
		return a%b;
	return b+(a%b);
}

inline void calc()
{
	x.clear();
	alpha.clear();
	beta.clear();
	// x[0] *************
	x.push_back(1);
	// x[1] *************
	int x1;
	x1=a;
	if(x[0]<=(p/3))
		x1=b;
	else if(x[0]<=(2*p/3))
		x1=1;
	x1%=p;
	x.push_back(x1);
	// x[2] *************
	x1=a*x[1];
	if(x[1]<=(p/3))
		x1=b*x[1];
	else if(x[1]<=(2*p/3))
		x1=x[1]*x[1];
	x1%=p;
	x.push_back(x1);
	// x[i] , x[i+1] ***************
	for(i=2;x[i]!=x[i/2];i+=2)
	{
		//*************
		x1=a*x[i];
		if(x[i]<(p/3))
			x1=b*x[i];
		else if(x[i]<(2*p/3))
			x1=x[i]*x[i];
		x1%=p;
		x.push_back(x1);
		//*************
		x1=a*x[i+1];
		if(x[i+1]<(p/3))
			x1=b*x[i+1];
		else if(x[i+1]<(2*p/3))
			x1=x[i+1]*x[i+1];
		x1%=p;
		x.push_back(x1);
	}
	index=i/2;
	// alpha[i] & beta[i] *******************
	alpha.push_back(0);
	beta.push_back(0);
	for(i=1;i<=2*index;++i)
	{
		alpha.push_back((alpha[i-1]+1)%n);
		beta.push_back(beta[i-1]%n);
		if(x[i-1]<(p/3))
		{
			alpha[i]=(alpha[i-1]%n);
			beta[i]=(beta[i-1]+1)%n;
		}
		else if(x[i-1]<(2*p/3))
		{
			alpha[i]=(2*alpha[i-1])%n;
			beta[i]=(2*beta[i-1])%n;
		}
	}
}


int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	
	int landa,bigM1,bigM2;
	bool f;

	while(cin>>p>>a>>b)
	{
		calc();		
		f=false;
		//****************************
		/*u=mod((alpha[index*2]-alpha[index]),(p-1));
		v=mod((beta[index*2]-beta[index]),(p-1));*/

		u=mod((alpha[index*2]-alpha[index]),p-1);
		v=mod((beta[index*2]-beta[index]),p-1);
		//****************************
		d=gcd(v,p-1);
		//****************************
		landa=1;
		bigM1=bigmod(b,d,p);
		while(1)
		{
			bigM2=bigmod(a,u*landa,p);
			if(bigM1==bigM2)
				break;
			landa++;
		}
		for(w=0;w<=d;++w)
		{
			ans=(u*landa+w*(p-1))/d;
			if(bigmod(a,ans,p)==b)
			{
				f=true;
				break;
			}
		}
		if(f)
			cout<<ans%(p-1);
		/*for(i=1;x[i]!=x[2*i];i++)
			cout<<setw(3)<<i<<" : "<<setw(3)<<x[i]<<" | "<<setw(3)<<2*i<<" : "<<setw(3)<<x[2*i]<<endl;
		cout<<setw(3)<<i<<" : "<<setw(3)<<x[i]<<" | "<<setw(3)<<2*i<<" : "<<setw(3)<<x[2*i]<<endl;*/
		cout<<endl;
	}

	return 0;
}
