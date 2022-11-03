#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#define MAX_MA 10000
#define MAX_ZF 1000

#include<cstring>
#include<fstream>
#include<stdio.h>
using namespace std;

struct Leaf
{
    char ch;
    int count;
}p[MAX_ZF];

int size = 0;
int find(char c, Leaf q[])
{
    for (int i = 0; i <= size; i++)
    {
        if (c == q[i].ch)
        {
            return i;
        }
    }
    return -1;
}
void insert(char s[], Leaf q[])               //用结构类型数组存储叶子结点
{
    int i = 0;
    while (s[i] != '#')
    {
        int f = find(s[i], q);
        if (f == -1)
        {
            q[size].ch = s[i];
            q[size++].count++;
        }
        else
        {
            q[f].count++;
        }
        i++;
    }
}

//哈夫曼树的储存表示
typedef struct
{
    int weight;  //结点的权值
    int parent, lchild, rchild;//双亲，左孩子，右孩子的下标
}HTNode, *HuffmanTree;  //动态分配数组来储存哈夫曼树的结点

typedef char **HuffmanCode;//动态分配数组存储哈夫曼编码

//返回两个双亲域为0且权值最小的点的下标
void Select(HuffmanTree HT, int n, int &s1, int &s2)
{

    for (int i = 1; i <= n; i++)
    {
        if (HT[i].parent == 0)
        {
            s1 = i;             //s1初始化为i
            break;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        /*利用for循环找到所有结点（字符）权值最小的一个
     并且保证该结点的双亲为0*/
        if (HT[i].weight < HT[s1].weight && HT[i].parent == 0)
            s1 = i;
    }
    //后两个for循环所有结点中权值第二小的点（字符）
    for (int i = 1; i <= n; i++)
    {
        if (HT[i].parent == 0 && i != s1)
        {
            s2 = i;
            break;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        /*利用for循环找到所有结点（字符）权值第二小的一个，
     该结点满足不能是s1且双亲是0*/
        if (HT[i].weight < HT[s2].weight && HT[i].parent == 0 && i != s1)
            s2 = i;
    }

}

//构造哈夫曼树
void CreateHuffmanTree(HuffmanTree &HT, int n, int* s)
{
    if (n <= 1)
        return;
    int m = 2 * n - 1;
    HT = new HTNode[m + 1];
    for (int i = 1; i <= m; ++i)
    {
        HT[i].parent = 0; HT[i].lchild = 0; HT[i].rchild = 0;
    }
    for (int i = 1; i <= n; ++i)
    {
        HT[i].weight = s[i - 1];//输入前n个单元中叶子结点的权值
    }
    int s1, s2;
    for (int i = n + 1; i <= m; ++i)
    {
        //通过n-1次的选择，删除，合并来构造哈夫曼树
        Select(HT, i - 1, s1, s2);
        /*cout << HT[s1].weight << " , " << HT[s2].weight << endl;*/
        /*将s1,s2的双亲域由0改为i(相当于把这两个结点删除了，这两个结点不再参与Select()函数)*/
        HT[s1].parent = i;
        HT[s2].parent = i;
        //s1,与s2分别作为i的左右孩子
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        //结点i的权值为s1,s2权值之和
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
}

//从叶子到根逆向求每个字符的哈夫曼编码，储存在编码表HC中
void CreatHuffmanCode(HuffmanTree HT, HuffmanCode &HC, int n)
{
    HC = new char*[n + 1];               //分配储存n个字符编码的编码表空间
    char *cd = new char[n];             //分配临时存储字符编码的动态空间
    cd[n - 1] = '\0';                   //编码结束符
    for (int i = 1; i <= n; i++)        //逐个求字符编码
    {
        int start = n - 1;             //start 开始指向最后，即编码结束符位置
        int c = i;
        int f = HT[c].parent;           //f指向结点c的双亲
        while (f != 0)             //从叶子结点开始回溯，直到根结点
        {
            --start;
            if (HT[f].lchild == c) cd[start] = '0';
            else cd[start] = '1';
            c = f;
            f = HT[f].parent;
        }
        HC[i] = new char[n - start];
        strcpy(HC[i], &cd[start]);
    }

    delete[] cd;
}

//哈夫曼译码
void TranCode(HuffmanTree HT, char a[], char zf[], char b[], int n)
{
    /*
    HT是已经创建好的哈夫曼树
    a[]用来传入二进制编码
    b[]用来记录译出的字符
    zf[]是与哈夫曼树的叶子对应的字符（叶子下标与字符下标对应）
    n是字符个数，相当于zf[]数组得长度
    */

    int q = 2 * n - 1;//q初始化为根结点的下标
    int k = 0;//记录存储译出字符数组的下标
    int i = 0;
    for (i = 0; a[i] != '\0'; i++)
    {
        //for循环结束条件是读入的字符是结束符（二进制编码）
        //此代码块用来判断读入的二进制字符是0还是1

        if (a[i] == '0')
        {
            /*读入0，把根结点(HT[q])的左孩子的下标值赋给q
         下次循环的时候把HT[q]的左孩子作为新的根结点*/
            q = HT[q].lchild;
        }
        else if (a[i] == '1')
        {
            q = HT[q].rchild;
        }
        //判断HT[q]是否为叶子结点
        if (HT[q].lchild == 0 && HT[q].rchild == 0)
        {
            b[k++] = zf[q];   //是叶节点，把下标为q的字符赋给字符数组b[]
            q = 2 * n - 1;
            //继续译下一个字符的时候从哈夫曼树的根结点开始
        }
    }
    /*译码完成之后，用来记录译出字符的数组由于没有结束符输出的
    时候回报错，故紧接着把一个结束符加到数组最后*/
    b[k] = '\0';
}
int main()
{
    int falg = 0;//记录要编码的字符个数
    char a[MAX_MA];//储存输入的二进制字符
    char b[MAX_ZF];//存储译出的字符
    char zf[MAX_ZF] = {'0'};//储存要编码的字符
    HuffmanTree HT = NULL;//初始化树为空数
    HuffmanCode HC = NULL;//初始化编码表为空表
    ifstream in1("/Users/mac/wihow/code/hwk2forcpp/inputfile1.txt");
    char para[10000];
    for (int i = 0; i<10000; i++)
    {
        para[i] = '#';
    }
    char n;
    int num=0;
    while(in1.get(n)){
        para[num++]=n;
    }
    cout<<num;
    insert(para, p);
    falg = size;
    int *NUM = new int[falg];
    for (int i = 1; i <=size; i++){
        zf[i] = p[i-1].ch;
        NUM[i-1] = p[i-1].count;
        //cout << zf[i] << ": " << NUM[i - 1] << endl;
    }


    CreateHuffmanTree(HT, falg, NUM);//调用创建哈夫曼树的函数
    cout << endl;
    CreatHuffmanCode(HT, HC, falg);//调用创建哈夫曼编码表的函数
    ofstream out("/Users/mac/wihow/code/hwk2forcpp/outputfile1.txt");
    out << "字符" << "\t" << "出现次数" << "\t" << "对应编码" << endl;
    for (int i = 1; i <= falg; i++)
    {
        out << zf[i] << "\t" << HT[i].weight << "\t" << "\t" << HC[i] << endl;
    }




    ofstream btos("/Users/mac/wihow/code/hwk2forcpp/outputfile.txt");
    ifstream in3("/Users/mac/wihow/code/hwk2forcpp/inputfile2.txt");
    char texts[10000];
    for (int i=0;i<10000;i++){
        texts[i]='#';
    }
    int num_=0;
    while(in3.get(n)){
        texts[num_++]=n;
    }
    int o=0;
    while(texts[o]!='#'){
        for(int i=1;i<=size;i++){
            if(texts[o]==zf[i]){
                btos<<HC[i];
                cout<<zf[i];
            }
        }
        o++;
    }
    btos.close();

    cout<<endl;
    ifstream in2("/Users/mac/wihow/code/hwk2forcpp/outputfile.txt");
    in2 >> a;
    int num2= strlen(a);
    cout<<num2;
    TranCode(HT, a, zf, b, falg);//调用译码的函数，
    /*这样可以直接把数组b输出，因为最后有
    在数组b添加输出时遇到结束符会结束输出*/
    cout << endl;
    ofstream out2("/Users/mac/wihow/code/hwk2forcpp/outputfile2.txt");
    out2 << b;

    float encode_rate;
    encode_rate=(float) (num2/num)/8;
    cout<<encode_rate;
    return 0;

}

