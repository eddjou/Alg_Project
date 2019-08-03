#include "stdlib.h"
#include <ctime>
#include <iostream>
#include <windows.h>
using namespace std;

template <class Type>
void Swap(Type &x,Type &y);

inline int Random(int x, int y);

template <class Type>
void BubbleSort(Type a[],int p,int r);

template <class Type>
int Partition(Type a[],int p,int r,Type x);

template <class Type>
Type Select(Type a[],int p,int r,int k);

int main()
{
	//初始化数组
	int n=40000,N=1;
	//cout<<"The repeat  time:"<<N<<endl;
	//cin>>N;
	cout<<"The Total Number Is:"<<n<<endl;
	int *a = new int[n];
        double t = 0;
        double counts = 0;
        LARGE_INTEGER nFreq;
        LARGE_INTEGER nBeginTime;
        LARGE_INTEGER nEndTime;
        QueryPerformanceFrequency(&nFreq);
        QueryPerformanceCounter(&nBeginTime);//开始计时

	for(int j=0;j<N;j++){
                //必须放在循环体外面,更改种子值，避免每次随机数列相等
                srand((unsigned)time(0));
                for(int i=0; i<n; i++)
                        a[i] = Random(0,n);

                if(n%2==1) cout<<"Mid Is"<<Select(a,0,n-1,n/2)<<endl;
                else cout<<"Mid Is"<<(Select(a,0,n-1,n/2-1)+Select(a,0,n-1,n/2))/2<<endl;
        }
        QueryPerformanceCounter(&nEndTime);//停止计时
        t = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s

        cout << "Running Time Is " << t * 1000 << "ms" << endl;
        system("pause");
}

template <class Type>
void Swap(Type &x,Type &y)
{
	Type temp = x;
	x = y;
	y = temp;
}

inline int Random(int x, int y)
{
        int ran_num = rand() % (y - x) + x;
        return ran_num;
}

//冒泡排序
template <class Type>
void BubbleSort(Type a[],int p,int r)
{
        //记录一次遍历中是否有元素的交换
        bool exchange;
        for(int i=p; i<=r-1;i++)
        {
		exchange = false ;
                for(int j=i+1; j<=r; j++)
                {
			if(a[j]<a[j-1])
                        {
                                Swap(a[j],a[j-1]);
                                exchange = true;
                        }
                }
        //如果这次遍历没有元素的交换,那么排序结束
        if(false == exchange)  break ;
        }
}

template <class Type>
int Partition(Type a[],int p,int r,Type x)
{
	int i = p-1,j = r + 1;
	while(true)
	{
		while(a[++i]<x && i<r);
		while(a[--j]>x);
		if(i>=j) break;
		Swap(a[i],a[j]);
	}
	return j;
}


template <class Type>
Type Select(Type a[],int p,int r,int k)
{
	if(r-p<75)
	{
		BubbleSort(a,p,r);
		return a[p+k-1];
	}
	//(r-p-4)/5相当于(n-5)/5
	for(int i=0; i<=(r-p-4)/5; i++)
	{
		//将元素每5个分成一组，分别排序，并将该组中位数与a[p+i]交换位置
		//使所有中位数都排列在数组最左侧，以便进一步查找中位数的中位数
		BubbleSort(a,p+5*i,p+5*i+4);
		Swap(a[p+5*i+2],a[p+i]);
	}
	//找中位数的中位数
	Type x = Select(a,p,p+(r-p-4)/5,(r-p-4)/10);
	int i = Partition(a,p,r,x);
	int j = i-p+1;
	if(k<=j) return Select(a,p,i,k);
	else return Select(a,i+1,r,k-j);
}
