#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

//_`'-.,_,.-'`_`'-.,_,.-'`_`-> [ Definitions ] <-`_`'-.,_,.-'`_`'-.,_,.-'`_
typedef long long int BigInt;
typedef pair<BigInt,int> pii;

vector<pii> baby;
vector<BigInt> giant;
BigInt a, b, p, ans;
int i,j,index,m,ii,jj;

//_`'-.,_,.-'`_`'-.,_,.-'`_`'-> [ Functions ] <-'`_`'-.,_,.-'`_`'-.,_,.-'`_

BigInt bigmod(BigInt b,BigInt p,BigInt m)
{
	if ( p == 0 )
		return 1;
	else if ( p%2 == 0 )
	{
		BigInt temp = bigmod( b, p/2, m );
		return ( temp * temp ) % m;
	}
	else
		return ( (b % m) * bigmod( b, p-1, m ) ) % m;
}

//___________________________________________________________________

int b_search(BigInt key,vector<pii> base)
{
    int left=0,right=base.size()-1;
    int mid;
    while(left<=right)
    {
		mid=(left+right)/2;
		if(base[mid].first==key)
			return base[mid].second;
		else if (base[mid].first<key)
			left=mid+1;
		else
			right=mid-1;
    }
    return -1;
}

//_`'-.,_,.-'`_`'-.,_,.-'`_-> [ Main Function ] <-_`'-.,_,.-'`_`'-.,_,.-'`_
int main()
{
	clock_t a,b;
	a=clock();

	ifstream input;
	ofstream output;
	input.open("input.dat");
	output.open("output.dat");

	bool f;
	BigInt a_inverse,a_m;

	while(input>>p>>a>>b)
	{
		f=true;
		baby.clear();
		giant.clear();
		m=(int)sqrt( 1.0*(p-1) ) + 1;

		cout<<"m = "<<m<<endl;

		//_`'-.,_,.-'`_`'-.,_,.-> [ Baby Step ] <-.,_,.-'`_`'-.,_,.-'`_
		baby.push_back( pii( 1, 0 ) );
		for( i=1; i<m; ++i )
			baby.push_back( pii((baby[i-1].first*a)%p, i) );
		cout<<"jadval tamum shod...\n";
		sort( baby.begin(), baby.end() );
		cout<<"hala sort shod...\n";

		//_`'-.,_,.-'`_`'-.,_,.-> [ Giant Step ] <-.,_,.-'`_`'-.,_,.-'`_
		a_inverse=bigmod(a,p-2,p);
		cout<<"a inverse = "<<a_inverse<<endl;
		a_m=bigmod(a_inverse,m,p);
		cout<<"a^-m = "<<a_m<<endl;
		giant.push_back(b);
		jj=b_search(b,baby);
		if(jj!=-1)
		{
			f=false;
			ii=0;
		}
		for(j=1;j<m && f;++j)
		{
			giant.push_back((giant[j-1]*a_m)%p);
			if((b_search(giant[j],baby))!=-1)
			{
				f=false;
				ii=j;
				jj=b_search(giant[j],baby);
			}
		}

		//_`'-.,_,.-'`_`'-.,_,.-> [ Answer ] <-.,_,.-'`_`'-.,_,.-'`_
		ans=ii*m+jj;
		cout<<ans<<endl<<endl;

	}
	
	b=clock();
	cout<<"\n\ntime: "<<(double)(b-a)/CLOCKS_PER_SEC*1000<<" ms"<<endl;

	input.close();
	output.close();
	//system("pause");
	return 0;
}
//_`'-.'`_`'-.,-> ,_,.-'`_`'-.,_,.-[ End ] <-,.-'`_`'-.,_,.-'`_`'-.,_,.-'`_
