#include<iostream>
using namespace std;
typedef unsigned long long ull;
void inputHandle(int &n,int &m,int* &income,ull* &presum){
    scanf("%d%d",&n,&m);
    income = new int[n];
    presum = new ull[n+1];
    presum[0]=0;
    for (int* i = income; i < income+n; i++)
        scanf("%d",i);
}

int binarySearch(int *arr,int l,int r,int target,bool mode){
    register int left=l,right=r;
    register int mid;
    while(left<right){
        mid = (left+right)>>1;
        if(arr[mid]<target){
            left=mid+1;
        }
        else if(arr[mid]>target){
            right=mid;
        }
        else{
            //处理重复数据的方式
            if(mode){               //区间最右
                right=r;
                while(mid<right&&arr[mid]==target)
                    ++mid;
            }
            else{                   //区间最左
                left=l;
                while(mid>=left&&arr[mid-1]==target)
                    --mid;
            }   
            return mid;
        }
    }
    //target不在arr中
	//选择区间最右
    if(arr[mid]<target&&mid<r)
    	++mid;
    
	return mid;     
}


int check(int n,int m,int *income,ull *presum){
    int l,r;
    int leftAddr,rightAddr;
    for(int i=0;i<m;i++){
        scanf("%d%d",&l,&r);
        //所有的区间都是[l,r)
        leftAddr=binarySearch(income,0,n,l,0);
        rightAddr=binarySearch(income,0,n,r,1);
        
        int num=rightAddr-leftAddr;
        if(num==0)
            printf("0\n");
        else{
            printf("%llu\n",(presum[rightAddr]-presum[leftAddr])/num);
        } 
           
    }
}

void siftDown(int *a, int start, int m) {
	int i = start;
	int j = 2 * i + 1; //j是i的左子女位置
	int tmp = a[i];
	while (j <= m) {   //检查是否到最后位置
		if (j<m&&a[j]<a[j + 1])j++;     //让j指向两子女中的大者
		if (tmp >= a[j])break;  //大则不做调整
		else { a[i] = a[j]; i = j; j = 2 * j + 1; }//否则大者上移, i, j下降
	}
	a[i] = tmp;//回放tmp中暂存的元素
}
void HeapSort(int *a, int n) {
	int i;
	for (i = (n - 2) / 2; i >= 0; i--) 	//将表转换为堆
		siftDown(a, i, n - 1);
	for (i = n - 1; i >= 0; i--) {		//对表排序
		int tmp = a[0];
		a[0] = a[i];
		a[i] = tmp;
		siftDown(a, 0, i - 1);
	}
};

int main(){
    int n,m;
    int *income;
    ull *presum;
    inputHandle(n,m,income,presum);
    HeapSort(income,n);
    for(int i=0;i<n;i++){  // get presum
        presum[i+1]=presum[i]+income[i];
    }
    check(n,m,income,presum);

    return 0;
}
/*
10 3
1 2 3 4 5 5 5 8 40 40

10 5
100
40
30
60
30
30
40
40
60
200

*/