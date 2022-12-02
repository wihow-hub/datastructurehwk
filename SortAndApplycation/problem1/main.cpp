#include <iostream>
#include <ctime>
#include<stdlib.h>
#include<vector>
#include<fstream>
#include<list>
#include<cmath>
#define random(a, b) (rand() % (b - a) + a)

using namespace std;

vector<vector<int> >res(5,vector<int>(2,0));
int Mergecmpcnt = 0, Mergeswapcnt = 0;
int Qsortcmpcnt = 0, Qsortswapcnt = 0;
int Radixcmpcnt = 0, Radixswapcnt = 0;

void create_file(){
    ofstream out;
    out.open("/Users/mac/wihow/code/datastructure/作业四/problem1/data.txt",ios::trunc);

    srand((int)time(NULL));
    for (int i = 0; i < 10000; i++)
    {
        out << random(1, 10000) << " ";
    }
    out<<"\n";
    out.close();
}

void read_file(vector<int>& v){
    vector<int>::iterator it;
    ifstream data("/Users/mac/wihow/code/datastructure/作业四/problem1/data.txt");
    int d;
    while (data >> d)
        v.push_back(d);
    data.close();
}

void write_file(vector<int>& data,int swi){
    ofstream result;
    switch(swi){
        case 0:
            result.open("/Users/mac/wihow/code/datastructure/作业四/problem1/冒泡data.txt",ios::trunc);
            for (int i = 0; i < 10000; i++)
            {
                result << data[i] << " ";
            }
            result<<"\n";
            result.close();
            break;
        case 1:
            result.open("/Users/mac/wihow/code/datastructure/作业四/problem1/插入data.txt",ios::trunc);
            for (int i = 0; i < 10000; i++)
            {
                result << data[i] << " ";
            }
            result<<"\n";
            result.close();
            break;
        case 2:
            result.open("/Users/mac/wihow/code/datastructure/作业四/problem1/归并data.txt",ios::trunc);
            for (int i = 0; i < 10000; i++)
            {
                result << data[i] << " ";
            }
            result<<"\n";
            result.close();
            break;
        case 3:
            result.open("/Users/mac/wihow/code/datastructure/作业四/problem1/快排data.txt",ios::trunc);
            for (int i = 0; i < 10000; i++)
            {
                result << data[i] << " ";
            }
            result<<"\n";
            result.close();
            break;
        case 4:
            result.open("/Users/mac/wihow/code/datastructure/作业四/problem1/基数data.txt",ios::trunc);
            for (int i = 0; i < 10000; i++)
            {
                result << data[i] << " ";
            }
            result<<"\n";
            result.close();
            break;
    }
}


void print(vector<int>& arr){
    for(int i = 0;i<arr.size();i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}


void BubbleSort(){
    vector<int> array;
    read_file(array);
    int length = array.size();
    int cmpcnt = 0, swapcnt = 0;
    int i,j,temp;
    for(i=1;i<length;i++){
        for(j=0;j<length-i;j++){
            cmpcnt++;
            if(array[j] > array[j+1]){
                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
                swapcnt++;
                swapcnt++;
            }
        }
    }
    res[0][0] = cmpcnt;
    res[0][1] = swapcnt;
    write_file(array,0);

}



void InsertionSort(){
    vector<int> a;
    read_file(a);
    int len = a.size();
    int cmpcnt = 0, swapcnt = 0;
    for (int j=1; j<len; j++)
    {
        int key = a[j];
        int i = j-1;
        while (i>=0 && ++cmpcnt && a[i]>key && ++cmpcnt)
        {
            a[i+1] = a[i];
            i--;
            swapcnt++;
        }
        a[i+1] = key;
    }
    res[1][0] = cmpcnt;
    res[1][1] = swapcnt;
    write_file(a,1);

}



void Merge(vector<int>& arr,int low,int mid,int high){
    int i=low,j=mid+1,k=0;
    int *temp=new(nothrow) int[high-low+1];
    if(!temp){
        cout<<"error";
        return;
    }
    while(i<=mid && j<=high && ++Mergecmpcnt && ++Mergecmpcnt){
        if(arr[i]<=arr[j])
            temp[k++]=arr[i++];
        else
            temp[k++]=arr[j++];
        ++Mergeswapcnt;
    }
    while(i<=mid && ++Mergecmpcnt){
        temp[k++]=arr[i++];
        ++Mergeswapcnt;
    }

    while(j<=high && ++Mergecmpcnt){
        temp[k++]=arr[j++];
        ++Mergeswapcnt;
    }

    for(i=low,k=0;i<=high;i++,k++,Mergecmpcnt++){
        arr[i]=temp[k];
        ++Mergeswapcnt;
    }

    delete []temp;
}


void MergeSort(vector<int>& arr,int low,int high){
    if(low<high){
        Mergecmpcnt++;
        int mid=(low+high)/2;
        MergeSort(arr,low,mid);
        MergeSort(arr,mid+1,high);
        Merge(arr,low,mid,high);
    }
    res[2][0] = Mergecmpcnt;
    res[2][1] = Mergeswapcnt;

}


int sortdet(vector<int>& arr, int left, int right) {
    int tempvalue;
    tempvalue = arr[left];
    while (left < right && ++Qsortcmpcnt) {
        while (left < right && arr[right] >= tempvalue && ++Qsortcmpcnt && ++Qsortcmpcnt)
            right--;
        arr[left] = arr[right];
        ++Qsortswapcnt;
        while (left < right && arr[left] <= tempvalue && ++Qsortcmpcnt && ++Qsortcmpcnt)
            left++;
        arr[right] = arr[left];
        ++Qsortswapcnt;
    }
    arr[left] = tempvalue;
    return left;
}
void qsort(vector<int>& arr,int left,int right) {
    int temp;
    while (left < right && ++Qsortcmpcnt) {
        temp = sortdet(arr, left, right);
        qsort(arr, left, temp - 1);
        left = temp + 1;
    }
    res[3][0] = Qsortcmpcnt;
    res[3][1] = Qsortswapcnt;
}


int maxbit(vector<int>& data, int n) {
    int d = 1;
    int p = 10;
    for(int i = 0; i < n; ++i)
    {
        while(data[i] >= p)
        {
            p *= 10;
            ++d;
        }
    }
    return d;
}

void sort_radix(vector<int>&data, int n)
{
    int d = maxbit(data, n);
    int tmp[n];
    int count[10];
    int i, j, k;
    int radix = 1;
    for(i = 1; i <= d; i++)
    {
        for(j = 0; j < 10; j++)
            count[j] = 0;
        for(j = 0; j < n; j++)
        {
            k = (data[j] / radix) % 10;
            count[k]++;
        }
        for(j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j];
        for(j = n - 1; j >= 0; j--)
        {
            k = (data[j] / radix) % 10;
            tmp[count[k] - 1] = data[j];
            count[k]--;
        }
        for(j = 0; j < n; j++)
            data[j] = tmp[j];
        radix = radix * 10;
    }
    res[4][0] = Radixcmpcnt;
    res[4][1] = Radixswapcnt;
}



int main()
{
    create_file();
    BubbleSort();

    InsertionSort();

    vector<int> Merarr;
    read_file(Merarr);
    MergeSort(Merarr,0,Merarr.size() - 1);
    write_file(Merarr,2);

    vector<int> qsrarr;
    read_file(qsrarr);
    qsort(qsrarr,0,qsrarr.size()-1);
    write_file(qsrarr,3);

    vector<int> radixarr;
    read_file(radixarr);
    sort_radix(radixarr,radixarr.size());
    write_file(radixarr,4);

    for(int i = 0;i<res.size();i++){
        switch(i){
            case 0:
                cout<<"冒泡排序比较次数"<<res[i][0]<<"     "<<"冒泡排序交换次数"<<res[i][1]<<endl;
                break;
            case 1:
                cout<<"插入排序比较次数"<<res[i][0]<<"     "<<"插入排序交换次数"<<res[i][1]<<endl;
                break;
            case 2:
                cout<<"归并排序比较次数"<<res[i][0]<<"       "<<"归并排序交换次数"<<res[i][1]<<endl;
                break;
            case 3:
                cout<<"快速排序比较次数"<<res[i][0]<<"       "<<"快速排序交换次数"<<res[i][1]<<endl;
                break;
            case 4:
                cout<<"基数排序比较次数"<<res[i][0]<<"            "<<"基数排序交换次数"<<res[i][1]<<endl;
                break;
        }

    }

    return 0;
}