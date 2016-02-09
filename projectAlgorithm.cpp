#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <ctime>

using namespace std;

#define bigInt	long long int

bigInt table[100000000],
	   index[100000000];

class	logarithm{
	bigInt a, b, p;
	bigInt m;

	void quickSort(bigInt low, bigInt high);
	void partition(bigInt low, bigInt high, bigInt &pivot);
	bigInt findMatch(bigInt low, bigInt high, bigInt &num);
	bigInt bigMod(bigInt &b, bigInt p, bigInt &m);
	//bigInt mod(bigInt num, bigInt m);
	bigInt countOrder(bigInt a, bigInt p);

public:
	void calculateLogaritm(bigInt a, bigInt b, bigInt p);
};

//________________________________________________________________________________
bigInt logarithm::bigMod(bigInt &b, bigInt p, bigInt &m)
{
	if(p == 0)
		return 1;
	if(p % 2 == 0)
		return ( bigMod(b, p/2, m) * bigMod(b, p/2, m) ) % m; // square(x) = x * x
	else
		return ( (b % m) * bigMod(b, p-1, m) ) % m;
}

//________________________________________________________________________________
//bigInt logarithm::mod(bigInt num, bigInt m)
//{
//	if((num % m) >= 0)
//		return num % m;
//	return m + (num % m);
//}
//________________________________________________________________________________
void logarithm::calculateLogaritm(bigInt a, bigInt b, bigInt p)
{
	//declarations
	bigInt x, i, pos = 0,
		   a_inv, a_invm;
	double help;

	//initializations
	m = ceil(pow(1.0 * (p-1), 1.0 / 2)) ;
	
	//constructing table
	x = 1;
	table[0] = x;
	index[0] = 0;
	for(bigInt j = 1 ; j < m ; j++)
	{	
		//x = mod(x * a, p);
		x = (x * a) % p;
		table[j] = x;
		index[j] = j;
	}
	
	//sorting table
	quickSort(0,m-1);

	//calculating inverse of a pow m
	for(i = 1 ; 1 ; i++)
	{
		help = 1.0 *(p * i + 1) / a;
		if((help - floor(help)) == 0)
			break;
	}
	a_inv = help;
	a_invm = bigMod(a_inv, m ,p);

	//finding obtain
	i = 0;
	x = b;
	pos = findMatch(0, m-1, x);
	if(!pos)
		for(i = 1 ; i < m ; i++)
		{
			//x = mod(x * a_invm, p);
			x = (x * a_invm) % p;
			pos = findMatch(0, m-1, x);
			if(pos)	break;
		}
	
	pos = index[pos];
	cout<<pos + m * i<<endl;
}
//________________________________________________________________________________
bigInt logarithm::findMatch(bigInt low, bigInt high, bigInt &num)
{
	if(low <= high)
	{
		int mid = (low + high) / 2;
		if(table[mid] == num)	return mid;
		else if(table[mid] > num)	return findMatch(low, mid - 1, num);
		else return findMatch(mid + 1, high, num);
	}
	else return 0;
}

//________________________________________________________________________________
void logarithm::quickSort(bigInt low, bigInt high)
{
	bigInt pivotItem;
	if(high > low)
	{
		partition(low, high, pivotItem);
		quickSort(low, (pivotItem - 1));
		quickSort(pivotItem + 1, high);
	}
}

//________________________________________________________________________________
void logarithm::partition(bigInt low, bigInt high, bigInt &pivotPoint)
{
	bigInt i, j, pivot;

	pivot = table[low];
	j = low;

	for(i = low + 1 ; i <= high ; i++)
		if(table[i] < pivot)
		{
			j++;
			swap(table[i], table[j]);
			swap(index[i], index[j]);
		}
	pivotPoint = j;
	swap(table[low], table[pivotPoint]);
	swap(index[low], index[pivotPoint]);
}

//________________________________________________________________________________
int main()
{
	freopen("a.in","r+t",stdin);
	freopen("b.out","w+t",stdout);
	
	bigInt a, b, p;
	logarithm log;
	clock_t t1,t2;

	t1 = clock();
	while(cin>>p>>a>>b)
		log.calculateLogaritm(a, b, p);
	t2 = clock();
	cout<<endl<<((double)t2 - t1) / CLOCKS_PER_SEC * 1000<<" ms"<<endl;

	return 0;
}
