#include<iostream>
#include<math.h>

using namespace std;

int M,N,k;
int **a,**b,*num_0,*odd,*even,*com;
int MaxCount=0,num=0;

void GetData()
{
    cout << "请依次输入行数N、列数M、激光照射次数k(3≤N≤100，3≤M≤20，1<=k<=M):\n";
    cin >> N >> M>>k;
    a = new int*[N];
    b = new int*[N];
    for (int i = 0; i < N; i++)
    {
        a[i] = new int[M];
        b[i] = new int[M];
    }

    cout << "请输入数据阵列："<<endl;
    for(int i=0;i<N;i++)
        for (int j = 0; j < M; j++)
        {
            cin >> a[i][j];
            b[i][j] = a[i][j];
        }
}

inline void Trans(int **arr,int m)//列反转
{
    int n = N;
    while (n--)
        arr[n][m] = abs(arr[n][m] - 1);
}

int Judge(int **arr)//计算导通行数
{
    int count=0;
    for (int i = 0; i < N; i++)
    {
        bool L = true;
        for (int j = 0; j < M; j++)
        {
            if (arr[i][j] == 0)
            {
                L = false;
                break;
            }
        }
        if(L)
            count++;
    }
    return count;
}

void selectSort(int*arr,int len)
{
    int index,temp;
    for (int i = 0; i < len - 1; i++)
    {
        temp = arr[i];
        index = i;
        for (int j = i + 1; j < len; j++)
        {
            if (arr[j] < arr[index])
                index = j;
        }
        arr[i] = arr[index];
        arr[index] = temp;
    }
}

void Count(int**arr)                                     //计数每行0的个数存在num_0里,0的个数为偶数且小于k的存于even，类似的奇数存于odd里
{
    num_0 = new int[N];
    odd = new int[N];
    even = new int[N];
    com = new int[N];

    int count0 = 0, count1 = 0;

    for (int i = 0; i < N; i++)
    {
        int temp=0;
        for (int j = 0; j < M; j++)
            if (arr[i][j] == 0)
                temp++;
        num_0[i] = temp;
    }

    for (int i = 0; i < N; i++)
    {
        if (num_0[i] <= k && num_0[i] % 2 == 0)
            even[count0++] = num_0[i];
        if (num_0[i] <= k && num_0[i] % 2 == 1)
            odd[count1++] = num_0[i];
    }
    selectSort(even, count0 );
    selectSort(odd, count1 );
    if (k % 2 == 0)
    {
        for (int i = 0; i < count0; i++)
            com[i] = even[i];
        num = count0;
    }
    if (k % 2 == 1)
    {
        for (int i = 0; i < count1; i++)
            com[i] = odd[i];
        num = count1;
    }
}

void GetResult()
{
    for(int i=0;i<num;i++)
        for (int j = 0; j < N; j++)
        {
            if (com[i] == num_0[j])
            {
                for (int n = 0; n < N; n++)
                    for (int m = 0; m < M; m++)
                        b[n][m] = a[n][m];
                for(int m=0;m<M;m++)
                    if (b[j][m] == 0)
                        Trans(b, m);
            }
            MaxCount = (MaxCount >= Judge(b) ? MaxCount : Judge(b));
        }
    cout << "最大导通数为：" << MaxCount << endl;
}

int main()
{
    GetData();
    Count(a);
    GetResult();
    //system("pause");
}
