
#include<iostream>
#include<fstream>


using namespace std;
//枚举类型Error_code   
enum Error_code{ not_present, success, overflow, duplicate_error };

//结点类B_node   
template <class Record>
class B_node
{
public:
    int order;//Btree阶数
    int count;//关键字个数
    Record *data;//存放结点关键字
    B_node<Record> **branch;//存放子结点指针

    B_node(int num)//构造函数
    {
        order = num;
        data = new Record[order - 1];
        branch = new B_node<Record>*[order];
        int i = 0;
        count = 0;
        for (i = 0; i<order - 1; i++)
            data[i] = 0;
        for (i = 0; i<order; i++)
            branch[i] = NULL;
    }
};

//Btree类   
template <class Record>
class B_tree {
public:
    B_tree(){ root = NULL; }//构造函数
    void connect(int num){ order = num; }//传入阶数
    void search(Record &target);//搜索关键字
    Error_code insert(const Record &new_entry);//插入关键字
    Error_code remove(const Record &target);//删除关键字
    void print();//打印关键字
    int order;//存放阶数
    B_node<Record> *root;//根节点

    //搜索关键字应用的函数
    Error_code recursive_search_tree(B_node<Record> *current, Record &target);
    Error_code search_node(B_node<Record> *current, const Record &target, int &position);

    //插入关键字应用的函数
    Error_code push_down(B_node<Record> *current, const Record &new_entry, Record &median, B_node<Record> *&right_branch);
    void push_in(B_node<Record> *current, const Record &entry, B_node<Record> *right_branch, int position);
    void split_node(B_node<Record> *current, const Record &extra_entry, B_node<Record> *extra_branch, int position, B_node<Record> *&right_half, Record &median);

    //删除关键字应用的函数
    Error_code recursive_remove(B_node<Record> *current, const Record &target);
    void remove_data(B_node<Record> *current, int position);
    void copy_in_predecessor(B_node<Record> *current, int position);
    void restore(B_node<Record> *current, int position);
    void move_left(B_node<Record> *current, int position);
    void move_right(B_node<Record> *current, int position);
    void combine(B_node<Record> *current, int position);

    //打印关键字应用的函数
    void print_node(B_node<Record> *current);
};

//搜索关键字   
template <class Record>
void B_tree<Record>::search(Record &target)
{
    Error_code result;
    result = recursive_search_tree(root, target);//逐层搜索
    if (result == success)//找到
        cout << "Find " << target << " in B_tree." << endl;
    if (result == not_present)//未找到
        cout << "Don't find " << target << " in B_tree." << endl;
}

//逐层搜索关键字   
template <class Record>
Error_code B_tree<Record>::recursive_search_tree(B_node<Record> *current, Record &target)
{
    Error_code result = not_present;
    int position;
    if (current != NULL)
    {
        result = search_node(current, target, position);//在当前结点中搜索关键字
        if (result == not_present)
            result = recursive_search_tree(current->branch[position], target);//递归调用搜索子树中的结点
        else
            target = current->data[position];
    }
    return result;
}

//在当前结点中搜索关键字   
template <class Record>
Error_code B_tree<Record>::search_node(B_node<Record> *current, const Record &target, int &position)
{
    position = 0;
    while (position<current->count&&target>current->data[position])//循环搜索
        position++;
    if (position<current->count&&target == current->data[position])//找到
        return success;
    else//未找到
        return not_present;
}

//插入关键字   
template <class Record>
Error_code B_tree<Record>::insert(const Record &new_entry)
{
    Record median;
    B_node<Record> *right_branch, *new_root;
    Error_code result = push_down(root, new_entry, median, right_branch);
    if (result == overflow)//树高为0，或结点分裂后，生成新结点
    {
        new_root = new B_node<Record>(order);
        new_root->count = 1;
        new_root->data[0] = median;
        new_root->branch[0] = root;
        new_root->branch[1] = right_branch;
        root = new_root;
        result = success;
    }
    return result;
}

//逐层搜索，在合适位置插入新结点   
template <class Record>
Error_code B_tree<Record>::push_down(B_node<Record> *current, const Record &new_entry, Record &median, B_node<Record> *&right_branch)
{
    Error_code result;
    int position;
    if (current == NULL) //树高为0返回overflow
    {
        median = new_entry;
        right_branch = NULL;
        result = overflow;
    }
    else
    {
        if (search_node(current, new_entry, position) == success)//在本层结点中找到关键字，返回duplicate_error
            result = duplicate_error;
        else
        {
            Record extra_entry;
            B_node<Record> *extra_branch;
            result = push_down(current->branch[position], new_entry, extra_entry, extra_branch);//递归调用，逐层查找
            if (result == overflow)//树高为0，或有结点分裂
            {
                if (current->count<order - 1)//元素个数小于阶数-1
                {
                    result = success;
                    push_in(current, extra_entry, extra_branch, position);//直接插入
                }
                else split_node(current, extra_entry, extra_branch, position, right_branch, median);//分裂结点
            }
        }
    }
    return result;
}

//直接插入关键字   
template <class Record>
void B_tree<Record>::push_in(B_node<Record> *current, const Record &entry, B_node<Record> *right_branch, int position)
{
    for (int i = current->count; i>position; i--)
    {
        current->data[i] = current->data[i - 1];
        current->branch[i + 1] = current->branch[i];
    }
    current->data[position] = entry;
    current->branch[position + 1] = right_branch;
    current->count++;
}

//分裂结点   
template <class Record>
void B_tree<Record>::split_node(B_node<Record> *current, const Record &extra_entry, B_node<Record> *extra_branch, int position, B_node<Record> *&right_half, Record &median)
{
    right_half = new B_node<Record>(order);
    int mid = order / 2;
    if (position <= mid)//插入左分支
    {
        for (int i = mid; i<order - 1; i++)
        {
            right_half->data[i - mid] = current->data[i];//复制右边的分支至right_half
            right_half->branch[i + 1 - mid] = current->branch[i + 1];
        }
        current->count = mid;
        right_half->count = order - 1 - mid;
        push_in(current, extra_entry, extra_branch, position);//插入关键字至左分支
    }
    else//插入右分支
    {
        mid++;
        for (int i = mid; i<order - 1; i++)
        {
            right_half->data[i - mid] = current->data[i];//复制右边的分支至right_half
            right_half->branch[i + 1 - mid] = current->branch[i + 1];
        }
        current->count = mid;
        right_half->count = order - 1 - mid;
        push_in(right_half, extra_entry, extra_branch, position - mid);
    }
    median = current->data[current->count - 1];//将current中现有最大关键字赋给median，用以提升父结点
    right_half->branch[0] = current->branch[current->count];
    current->count--;
}

//删除关键字   
template <class Record>
Error_code B_tree<Record>::remove(const Record &target)
{
    Error_code result;
    result = recursive_remove(root, target);
    if (root != NULL&&root->count == 0)
    {
        B_node<Record> *old_root = root;
        root = root->branch[0];
        delete old_root;
    }
    return result;
}

//遍历树删除关键字   
template <class Record>
Error_code B_tree<Record>::recursive_remove(B_node<Record>*current, const Record &target)
{
    Error_code result;
    int position;
    if (current == NULL) //未找到关键字
        result = not_present;
    else
    {
        if (search_node(current, target, position) == success)//结点中找到关键字
        {
            result = success;
            if (current->branch[position] != NULL)//结点不是叶结点时
            {
                copy_in_predecessor(current, position);//将左分支最大结点复制给要删除的关键字
                recursive_remove(current->branch[position], current->data[position]);//遍历要删除的新关键字
            }
            else remove_data(current, position);//直接删除关键字
        }
        else
            result = recursive_remove(current->branch[position], target);//若未找到，递归查找关键字
        if (current->branch[position] != NULL)
            if (current->branch[position]->count<(order - 1) / 2)//结点数少于(order-1)/2
                restore(current, position);//调整关键字
    }
    return result;
}

//直接删除关键字   
template <class Record>
void B_tree<Record>::remove_data(B_node<Record> *current, int position)
{
    for (int i = position; i<current->count - 1; i++)
        current->data[i] = current->data[i + 1];
    current->count--;
}

//将左分支最大结点复制给要删除的关键字   
template <class Record>
void B_tree < Record>::copy_in_predecessor(B_node<Record> *current, int position)
{
    B_node<Record>*leaf = current->branch[position];
    while (leaf->branch[leaf->count] != NULL)
        leaf = leaf->branch[leaf->count];
    current->data[position] = leaf->data[leaf->count - 1];
}

//结点数少于(order-1)/2，调整关键字   
template <class Record>
void B_tree<Record>::restore(B_node<Record> *current, int position)
{
    if (position == current->count) //不合要求的结点在最右
        if (current->branch[position - 1]->count>(order - 1) / 2)//其左兄弟结点个数足够多
            move_right(current, position - 1);//用move_right调整
        else
            combine(current, position);//合并结点
    else if (position == 0) //不合要求的结点在最左
        if (current->branch[1]->count>(order - 1) / 2)//其右兄弟结点个数足够多
            move_left(current, 1);//用move_left调整
        else
            combine(current, 1);//合并结点
    else
    if (current->branch[position - 1]->count>(order - 1) / 2)//其左兄弟结点个数足够多
        move_right(current, position - 1);//用move_right调整
    else if (current->branch[position + 1]->count>(order - 1) / 2)//其右兄弟结点个数足够多
        move_left(current, position + 1);//用move_left调整
    else combine(current, position);//合并结点
}

//从右兄弟结点过渡一关键字   
template <class Record>
void B_tree<Record>::move_left(B_node<Record> *current, int position)
{
    B_node<Record>*left_branch = current->branch[position - 1], *right_branch = current->branch[position];
    left_branch->data[left_branch->count] = current->data[position - 1];//在左分支中加一关键字，为父结点值
    left_branch->branch[++left_branch->count] = right_branch->branch[0];//在左分支中加一分支，为右分支最左子分支
    current->data[position - 1] = right_branch->data[0];//父结点为右分支最小关键字
    right_branch->count--;
    for (int i = 0; i<right_branch->count; i++)//调整右分支
    {
        right_branch->data[i] = right_branch->data[i + 1];
        right_branch->branch[i] = right_branch->branch[i + 1];
    }
    right_branch->branch[right_branch->count] = right_branch->branch[right_branch->count + 1];
}

//从左兄弟结点过渡一关键字   
template <class Record>
void B_tree<Record>::move_right(B_node<Record> *current, int position)
{
    B_node<Record>*right_branch = current->branch[position + 1], *left_branch = current->branch[position];
    right_branch->branch[right_branch->count + 1] = right_branch->branch[right_branch->count];
    for (int i = right_branch->count; i>0; i--)//在右分支中加一关键字
    {
        right_branch->data[i] = right_branch->data[i - 1];
        right_branch->branch[i] = right_branch->branch[i - 1];
    }
    right_branch->count++;
    right_branch->data[0] = current->data[position];//在右分支中加入的关键字值为父结点值
    right_branch->branch[0] = left_branch->branch[left_branch->count--];//在右分支中加一分支，为左分支最右子分支
    current->data[position] = left_branch->data[left_branch->count];//父结点为左分支最大关键字
}

//合并结点   
template <class Record>
void B_tree<Record>::combine(B_node<Record> *current, int position)
{
    int i;
    B_node<Record>*left_branch = current->branch[position - 1], *right_branch = current->branch[position];
    left_branch->data[left_branch->count] = current->data[position - 1];//左分支加入父结点关键字
    left_branch->branch[++left_branch->count] = right_branch->branch[0];//右结点赋予左结点
    for (i = 0; i<right_branch->count; i++)
    {
        left_branch->data[left_branch->count] = right_branch->data[i];
        left_branch->branch[++left_branch->count] = right_branch->branch[i + 1];
    }
    current->count--;
    for (i = position - 1; i<current->count; i++) //在父结点中将赋过值的关键字删除
    {
        current->data[i] = current->data[i + 1];
        current->branch[i + 1] = current->branch[i + 2];
    }
    delete right_branch;
}

//打印Btree   
template <class Record>
void B_tree<Record>::print()
{
    print_node(root);
    cout << endl;
}

//递归打印每一关键字   
template <class Record>
void B_tree<Record>::print_node(B_node<Record> *current)
{
    int i;
    if (current == NULL)
        return;
    else
    {
        cout << "[";//关键字以[]标出
        for (i = 0; i<current->count - 1; i++)
            cout << current->data[i] << " ";
        cout << current->data[i] << "]";
        if (current->branch[0] != NULL)
        {
            cout << "(";//若有分支结点以（）标出
            for (i = 0; i<current->count; i++)
            {
                print_node(current->branch[i]);
                cout << ",";
            }
            print_node(current->branch[i]);
            cout << ")";
        }
    }
}

bool found(int q[], int k){
    int i = 0;
    if (q[0] == -1)
        return true;
    while (q[i] != -1){
        if (q[i] == k)
            return false;
        i++;
    }
    return true;
}


void drawnode(B_node<int>*current,ofstream &fp){
    int i;
    if(current==NULL){
        return ;
    }
    else{
        int num= current->data[0];;
        fp<<'n'<<num<<"[label = \" ";
        for(i=0;i<current->count-1;i++)
            fp<<current->data[i]<<',';
        fp<<current->data[i]<<"\"]"<<endl;
        if(current->branch[0]!=NULL){
            for(i=0;i<=current->count;i++){
                drawnode(current->branch[i],fp);
                fp<<'n'<<num<<" -> "<<"n"<<current->branch[i]->data[0]<<endl;
            }
        }
    }
}

void drawbtree(B_node<int>*current,ofstream &fp){
    fp.open("/Users/mac/wihow/code/Btree/balencetree.dot");
    fp<<"digraph {"<<endl;
    drawnode(current,fp);
    fp<<"}";
    fp.close();
}

int main()
{
    ofstream fp;
    int x, order, s;
    char next[100];
    int k;
    cout << "请输入阶数、初始结点个数："<<endl;
    cin >> order >> x;
    B_tree<int> t;
    t.connect(order);
//	int i=0,j=0;
    cout << "输入初始结点，按照数字+逗号的格式输入（如 10,13,11）："<<endl;
    char str[100];
    int p[100];
    for (int i = 0; i < 100; i++)
        p[i] = -1;
    int Un = 1,h=0;
    while (Un){
        cin >> str;
        for (int i = 0; str[i] != '\0';){
            int q = 0,IN=0;
            while (str[i] >= '0'&&str[i] <= '9'){
                IN = 1;
                q = q * 10 + str[i] - 48;
                i++;
            }
            if (found(p, q)&&IN){
                p[h++] = q;
            }
            i++;
        }
        if (h >= x)
            Un = 0;
    }
    cout << endl;
    for (int i = 0; i<x; i++)
    {
        t.insert(p[i]);
    }
    cout << "现在的B-Tree为：" << endl << endl;
    t.print();
    drawbtree(t.root,fp);
    do
    {
        cout << endl;
        cout << "--------------------------------------------------------------------------------------" << endl;
        cout << "是否插入或删除？ 请按以下提示操作："<<endl<<endl;
        cout << "插入数字请按后面格式输入：I+要插入的数字（如I76）"<<endl<<endl;
        cout << "删除数字请按后面格式输入：D+要删除的数字（如D50）" <<endl<< endl;
        cout << "多位插入请按后面格式输入：MI+要插入的数字逗号隔开#号结束（如MI76,35#）"<<endl<<endl;
        cout << "多位删除请按后面格式输入：MD+要删除的数字逗号隔开#号结束（如MD22,43#）"<<endl<<endl;
        cout << "其它输入表示程序结束； "<<endl;
        cout << "--------------------------------------------------------------------------------------"<<endl;
        cout << "现在请输入：" << endl<<endl;
        cin >> next;
        int op,M=0;
        if (next[0] == 'I'&&next[1] >= '0'&&next[1] <= '9'){ k = 1; op = 1; }
        else if (next[0] == 'D'&&next[1] >= '0'&&next[1] <= '9'){
            k = 2; op = 2;
        }
        else if (next[0] == 'M'&&next[1] == 'I'){
            k = 3; op = 3;
        }
        else if (next[0] == 'M'&&next[1] == 'D'){
            k = 4; op = 4;
        }
        else k = 0;
        int Opnum[100];
        for (int i = 0; i < 100; i++)
            Opnum[i] = -1;
        int m;
        if (op == 1 || op == 2){
            for (int ri = 1, j = 0; next[ri] != '#';){
                int q = 0;
                while (next[ri] >= '0'&&next[ri] <= '9'){
                    q = q * 10 + next[ri] - 48;
                    ri++;
                }
                m = q;
                break;
            }
        }
        else if (op == 3 || op == 4){
            for (int ri = 2, j = 0; next[ri-1] != '#';){
                int q = 0,CO=0;
                while (next[ri] >= '0'&&next[ri] <= '9'){
                    CO = 1;
                    q = q * 10 + next[ri] - 48;
                    ri++;
                }
                if (CO)
                    Opnum[j++] = q;
                M = j;
                ri++;

            }
        }
        cout << endl;
        if (k == 1)
        {

            s = m;
            if (t.insert(s) == duplicate_error)
                cout << s << "已经在B树中了," << s << "插入失败;" <<endl<< endl;
            else
                cout << s << "插入成功！" << endl<<endl;
            cout << "现在的B-Tree为：" << endl << endl;
            t.print();
            cout << endl;
        }
        else if (k == 2)
        {

            s = m;
            if (t.remove(s) == not_present)
                cout << s << " 不在B树中，删除失败!" << endl<<endl;
            else
                cout << s << " 删除成功!" << endl<<endl;
            cout << "现在的B-Tree为：" << endl << endl;
            t.print();
            cout << endl;
        }
        else if (k == 3)
        {

            for (int i = 0; i<M; i++)
            {
                //		cin >> s;
                s = Opnum[i];
                if (t.insert(s) == duplicate_error)
                    cout << s << "已经在B树中，"<<s<<"插入失败！" << endl<<endl;
            }
            cout << "现在的B-Tree为：" << endl << endl;
            t.print();
        }
        else if (k == 4)
        {

            for (int i = 0; i<M; i++)
            {
                //		cin >> s;
                s = Opnum[i] ;
                if (t.remove(s) == not_present)
                    cout << s << " 不在B树中，"<<s<<"删除失败！" <<endl<< endl;
            }
            cout << "现在的B-Tree为：" << endl << endl;
            t.print();
            cout << endl;
        }

    } while (k);
    return 0;
}