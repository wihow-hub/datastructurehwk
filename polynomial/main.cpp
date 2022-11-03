#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

struct Term {
    Term *Next, *current;
    double Coef;
    double Exp;

    Term(double co, double ex);
};

Term::Term(double co, double ex) {
    Exp = ex;
    Coef = co;
    Next = NULL;
}

class polynomial {
public:
    int count, current_position;
    Term *head, *current;

    polynomial();

    polynomial(polynomial &a);

    ~polynomial();

    void remove(int position);

    void set_position(int position);

    void Insert(double co, double ex);

    void Insert_sort(double co, double ex);

    void outputPoly();

    void outputPoly_file(fstream &file);

    void empty();

    void fix();

    polynomial &operator=(polynomial &a);

    //simple operation
    polynomial &operator+(polynomial &operand);

    polynomial &operator-(polynomial &operand);

    polynomial &div();

    polynomial &operator*(polynomial &operand);

    polynomial &operator/(polynomial &operand);


};

//ADT


//implement the ADT
polynomial::polynomial() {
    head = new Term(0, 0);
    current = head;
    current_position = -1;
    count = 0;
}

polynomial::polynomial(polynomial &a) {
    empty();
    count = a.count;
    Term *p = a.head;
    for (int i = 0; i < a.count; i++) {
        p = p->Next;
        Insert_sort(p->Coef, p->Exp);
    }
}

polynomial::~polynomial() {

}

void polynomial::remove(int position) {
    set_position(position - 1);
    Term *previous, *following;
    previous = current;
    following = current->Next;
    previous->Next = following->Next;
    delete following;
    count--;
}

void polynomial::set_position(int position) {
    if (current_position > position) {
        current_position = -1;
        current = head;
    }
    for (; position != current_position; current_position++)
        current = current->Next;
}

void polynomial::Insert(double co, double ex) {
    Term *p = head;
    while (p->Next != NULL) p = p->Next;
    Term *new_term = new Term(co, ex);
    p->Next = new_term;
    count++;
}

void polynomial::Insert_sort(double co, double ex) {
    if (count != 0) {
        Term *p = head->Next;
        while (p->Coef != co && p->Next != NULL) p = p->Next;
        if (p->Coef == co) {
            p->Exp += ex;
            return;
        }
    }
    set_position(-1);
    Term *new_term = new Term(co, ex);
    count++;
    while (current->Next != NULL && co > current->Next->Coef) set_position(current_position + 1);
    if (current == NULL) current->Next = new_term;
    else {
        new_term->Next = current->Next;
        current->Next = new_term;
    }
}

void polynomial::outputPoly() {
    if (count == 0) cout << '0';
    else {
        set_position(count - 1);
        while (current_position >= 0) {
            if (current_position == count - 1) {
                if (current->Coef == 0) cout << current->Exp;
                else if (current->Coef == 1) {
                    if (current->Exp != 1 && current->Exp != -1) cout << current->Exp << 'x';
                    else if (current->Exp == -1) cout << '-' << 'x';
                    else cout << 'x';
                } else {
                    if (current->Exp != 1 && current->Exp != -1) cout << current->Exp << 'x' << current->Coef;
                    else if (current->Exp == -1) cout << '-' << 'x' << current->Coef;
                    else cout << 'x' << current->Coef;
                }
            } else {
                if (current->Exp >= 0) {
                    if (current->Coef == 0) cout << '+' << current->Exp;
                    else if (current->Coef == 1) {
                        if (current->Exp == 1) cout << '+' << 'x';
                        else cout << '+' << current->Exp << 'x';
                    } else {
                        if (current->Exp == 1) cout << '+' << 'x' << current->Coef;
                        else cout << '+' << current->Exp << 'x' << current->Coef;
                    }
                } else {
                    if (current->Coef == 0) cout << current->Exp;
                    else if (current->Coef == 1) {
                        if (current->Exp == -1) cout << '-' << 'x';
                        else cout << current->Exp << 'x';
                    } else {
                        if (current->Exp == -1) cout << '-' << 'x' << current->Coef;
                        else cout << current->Exp << 'x' << current->Coef;
                    }
                }
            }
            set_position(current_position - 1);
        }
    }
}

void polynomial::outputPoly_file(fstream &file) {
    if (count == 0) file << '0';
    else {
        set_position(count - 1);
        while (current_position >= 0) {
            if (current_position == count - 1) {
                if (current->Coef == 0) file << current->Exp;
                else if (current->Coef == 1) {
                    if (current->Exp != 1 && current->Exp != -1) file << current->Exp << 'x';
                    else if (current->Exp == -1) file << '-' << 'x';
                    else file << 'x';
                } else {
                    if (current->Exp != 1 && current->Exp != -1) file << current->Exp << 'x' << current->Coef;
                    else if (current->Exp == -1) file << '-' << 'x' << current->Coef;
                    else file << 'x' << current->Coef;
                }
            } else {
                if (current->Exp >= 0) {
                    if (current->Coef == 0) file << '+' << current->Exp;
                    else if (current->Coef == 1) {
                        if (current->Exp == 1) file << '+' << 'x';
                        else file << '+' << current->Exp << 'x';
                    } else {
                        if (current->Exp == 1) file << '+' << 'x' << current->Coef;
                        else file << '+' << current->Exp << 'x' << current->Coef;
                    }
                } else {
                    if (current->Coef == 0) file << current->Exp;
                    else if (current->Coef == 1) {
                        if (current->Exp == -1) file << '-' << 'x';
                        else file << current->Exp << 'x';
                    } else {
                        if (current->Exp == -1) file << '-' << 'x' << current->Coef;
                        else file << current->Exp << 'x' << current->Coef;
                    }
                }
            }
            set_position(current_position - 1);
        }
    }
}

void polynomial::empty() {
    set_position(-1);
    while (head->Next != NULL) remove(0);
}

polynomial &polynomial::div() {
    set_position(0);
    while (current_position < count) {
        if (current->Coef == 0) {
            remove(current_position);
        } else {
            current->Exp *= current->Coef;
            current->Coef--;
        }
        set_position(current_position + 1);
    }
    return *this;
}

void polynomial::fix() {
    set_position(-1);
    while (current_position < count - 1) {
        set_position(current_position + 1);
        if (current->Exp == 0 || (current->Exp<0.00001 && current->Exp>0) || (current->Exp<0 && current->Exp>-0.00001) ) remove(current_position);
    }
}

polynomial &polynomial::operator=(polynomial &a) {
    empty();
    set_position(-1);
    Term *p = a.head;
    for (int i = 0; i < a.count; i++) {
        p = p->Next;
        Insert(p->Coef, p->Exp);
    }
}


polynomial &polynomial::operator+(polynomial &oprand) {
    oprand.set_position(-1);
    while (oprand.current_position < oprand.count - 1) {
        oprand.set_position(oprand.current_position + 1);
        if (count > 0) {
            set_position(0);
            while (oprand.current->Coef != current->Coef && current->Next != NULL) set_position(current_position + 1);
            if (current->Coef == oprand.current->Coef) {
                current->Exp += oprand.current->Exp;
            } else {
                Insert_sort(oprand.current->Coef, oprand.current->Exp);
            }
        } else Insert_sort(oprand.current->Coef, oprand.current->Exp);
    }
    fix();
    return *this;
}

polynomial &polynomial::operator-(polynomial &oprand) {
    oprand.set_position(-1);
    while (oprand.current_position < oprand.count - 1) {
        oprand.set_position(oprand.current_position + 1);
        set_position(0);
        while (oprand.current->Coef != current->Coef && current->Next != NULL) set_position(current_position + 1);
        if (current->Coef == oprand.current->Coef) {
            current->Exp -= oprand.current->Exp;
        } else {
            Insert_sort(oprand.current->Coef, -oprand.current->Exp);
        }
    }
    fix();
    return *this;
}

polynomial &polynomial::operator*(polynomial &oprand) {
    oprand.set_position(-1);
    int num = count;
    while (oprand.current_position < oprand.count - 1) {
        oprand.set_position(oprand.current_position + 1);
        set_position(-1);
        while (current_position < num - 1) {
            set_position(current_position + 1);
            int comulti = current->Coef + oprand.current->Coef;
            int epmulti = current->Exp * oprand.current->Exp;
            Insert(comulti, epmulti);
        }
    }
    oprand.empty();
    Term *p = head;
    for (int i = 0; i < num - 1; i++) p = p->Next;
    count -= num;
    head = p->Next;

    p = head;
    while (p->Next != NULL) {
        p = p->Next;
        oprand.Insert_sort(p->Coef, p->Exp);
    }

    return oprand;
}

polynomial &polynomial::operator/(polynomial &operand) {
    polynomial factor, factor_temp;
    while (count > 0) {
        set_position(count - 1);
        operand.set_position(operand.count - 1);
        if (operand.current->Coef > current->Coef) {
            Term *p = head;
            while (p->Next != NULL) {
                p = p->Next;
                Term *extra = new Term(p->Coef, p->Exp);
                extra->Next = factor.head->Next;
                factor.head->Next = extra;
                factor.count++;
            }
            break;
        } else {
            set_position(count - 1);
            operand.set_position(operand.count - 1);
            factor_temp.Insert(current->Coef - operand.current->Coef, current->Exp / operand.current->Exp);
            factor.Insert_sort(current->Coef - operand.current->Coef, current->Exp / operand.current->Exp);
            polynomial temp;
            temp = operand;
            Term * q;
            q=temp.head;
            while(q->Next!=NULL){
                q=q->Next;
                q->Coef+=(current->Coef - operand.current->Coef);
                q->Exp*=(current->Exp / operand.current->Exp);
            }

            *this - temp;
            fix();
            factor_temp.empty();
        }
    }
            *this=factor;
            return *this;
}


int main() {







    fstream text;
    text.open("/Users/mac/wihow/inputfile.txt");
    if (!text.is_open()) {
        cout << "打开文件失败！" << endl;
    }

    string s1;
    getline(text, s1);
    cout << s1 << endl;
    string s2;
    getline(text, s2);
    cout << s2 << endl;
    string oper;
    getline(text, oper);
    cout << oper << endl;
    string::iterator it;
    int num1 = 0;
    for (it = s1.begin(); it != s1.end(); it++) {
        if (*it == '(') num1++;
        if (!(*it <= '9' && *it >= '0' || *it == '-' || *it == '.')) *it = ' ';
    }
    struct number {
        double conum = 0;
        double exnum = 0;
    } a[100];
    istringstream inp1(s1);
    for (int i = 0; i < num1 - 1; i++) {
        inp1 >> a[i].exnum;
        inp1 >> a[i].conum;
    }

    polynomial oprand1;
    for (int i = 0; i < num1 - 1; i++) {
        oprand1.Insert_sort(a[i].conum, a[i].exnum);
    }
    oprand1.outputPoly();

    int num2 = 0;
    for (it = s2.begin(); it != s2.end(); it++) {
        if (*it == '(') num2++;
        if (!(*it <= '9' && *it >= '0' || *it == '-' || *it == '.')) *it = ' ';
    }
    struct number2 {
        int conum = 0;
        double exnum = 0;
    } a2[100];
    istringstream inp2(s2);
    for (int i = 0; i < num2 - 1; i++) {
        inp2 >> a2[i].exnum;
        inp2 >> a2[i].conum;
    }

    cout << endl;
    polynomial oprand2;
    for (int i = 0; i < num2 - 1; i++) {
        oprand2.Insert_sort(a2[i].conum, a2[i].exnum);
    }
    oprand2.outputPoly();

    fstream text2;
    text2.open("/Users/mac/wihow/outputfile.txt");

    cout << endl;
    if (*oper.begin() == 'A') {
        oprand1 + oprand2;
        oprand1.outputPoly();
        oprand1.outputPoly_file(text2);
    } else if (*oper.begin() == 'S') {
        oprand1 - oprand2;
        oprand1.outputPoly();
        oprand1.outputPoly_file(text2);
    } else if (*oper.begin() == 'M') {
        oprand1 * oprand2;
        oprand2.outputPoly();
        oprand2.outputPoly_file(text2);
    } else if (*oper.begin() == 'D') {
        oprand1 / oprand2;
        oprand1.outputPoly();
        oprand1.outputPoly_file(text2);
    }else {
        oprand1.div();
        oprand1.outputPoly();
        oprand1.outputPoly_file(text2);
    }
    text2.close();



    return 0;
}