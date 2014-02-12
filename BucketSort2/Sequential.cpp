#include "stdafx.h"
#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include <iostream>
#include <stdint.h>
#include <assert.h>
using namespace std;
#define n 10000000            /*length of list*/
#define bsize 1000000         /*size of buckets*/
#define m 100                 /*number of buckets*/
#define NOT_PRINT 1
int list[n];                  /*unsorted list of integers*/
int final[n];                 /*sorted list of integers*/
int bucket[m][bsize];         /*buckets*/
int count[m];                 /*number of items stored in bucket*/
int minval;
int maxval;


void initialize()
{
	for(int i =0; i < n; i++)
	{
		list[i] = rand();
		if(list[i]  > maxval)
		{
			maxval = list[i];
		}
		if(list[i] < minval)
		{
			minval = list[i];
		}
	}
}
int lt(const void *p, const void *q) 
{
	return (*(int *)p - *(int *)q);
}
void printBuckets()
{
	cout << "Elements in corresponding bucket" << endl;
	for (int i = 0; i < m; i++)
	{
		cout << count[i] << "\t";
	}
	cout << endl << endl;

	for (int j = 0; j < bsize; j++) 
	{
		for (int i = 0; i < m; i++) 
		{
			cout << bucket[i][j] << "\t ";
		}
		cout << endl;
	}

}

int testResults()
{
	for(int i = 0; i < n - 1; i ++)
	{
		if(final[i+1] < final[i])
		{
			return 0;
		}
		else return 1;
	}
}

void seqDistribute()
{
	int const range = maxval - minval + 1;
	for(int i = 0; i < n ; i++)
	{
		int bnum = (int) ((float) m * ((float)list[i] - minval) / range);
		--bnum;
		if(bnum >= m || count[bnum] >= bsize)
		{
			cout<<"error\n"<<endl;	
			cout<<"bnum -"<<bnum<<"\n";
			cout<<"m -"<<m<<"\n";
			cout<<"list[i] -"<<list[i]<<"\n";
			cout<<"minval -"<<minval<<"\n";
			cout<<"range -"<<range<<"\n";
			exit(0);
		}
		bucket[bnum][count[bnum]++] = list[i];
		
		if(NOT_PRINT == 0)
		{
			printBuckets();
		}
	}
}


void seqSort()
{	 
	for(int i = 0; i < m; i++)
	{
		qsort(bucket[i], count[i], sizeof(int), lt);
	}
}

void seqMerge()
{
	for (int i = 0; i < m; i++){
		int startIndex = i * bsize;
		if(startIndex != 0)
			--startIndex;
		for (int j = 0; j < bsize; j++)
		{
			final[startIndex++] = bucket[i][j];
		}
	}
	
	if (NOT_PRINT == 0){		

		for (int i = 0; i < n; i++)
		{
			cout << final[i] << "\t";
			if ((i + 1) % 8 == 0)
			{
				cout << endl;
			}
		}
	}
}

void sequential()
{
	int sequentialTime;
	clock_t startTime;
	clock_t endTime;
	minval  = INT_MAX;
	maxval	= INT_MIN;
	initialize();
	startTime = clock();
	seqDistribute();
	seqSort();
	seqMerge();
	endTime = clock();
	sequentialTime = endTime - startTime;
	cout<<"Sequential time : "<<sequentialTime<<endl;
	int test = testResults();
	if(test == 0)
	{
		cout<<"\nResults are invalid. "<<endl;
	}
	else 
	{
		cout<<"\nResults are valid. "<<endl;
	}

}
void reset()
{
	initialize();
	//final bucket count1
	for (int i = 0; i < n; i++){
		final[i] = 0;
	}
	for (int i = 0; i < m; i++){
		for (int j = 0; j < count[i]; j++){
			bucket[i][j] = 0;
		}
		count[i] = 0;		
	}

}
/* ---------------------------------MAIN----------------------------------------- */
int main(int argc,_TCHAR* argv[])
{
	
	sequential();
	resert();
	cin.get();
	return 0;
}
