#include <iostream>
#include <string>
#include <sstream>
#include <conio.h>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <windows.h>
using namespace std;
#define nhanvientxt "Nhan Vien.txt"
#define nhanvienouttxt "Nhan Vien_out.txt"
#define nhanviensearch "NhanVien_search.txt"
#define A 1500000 //LCB
/*string nhanvientxt = "Nhan Vien.txt"; //main !
string nhavienouttxt = "Nhan Vien_out.txt";
string nhanviensearch = "NhanVien_search.txt";*/

//class đọc thông tin tài khoản mật khẩu
class account {
    string name;
    string password;
    public:
    string getName(){
        return name;
    }
    string getPassword(){
        return password;
    }
    void readAccount(ifstream &);
};
class list_account{
    int numOfAcount;
    account *la;
    public:
    list_account(int =0);
    void readfile_account(ifstream &in);
    int check(string s);
    string tranpass();
    ~list_account();
};

class birthday
{ //class ngày tháng năm sinh để sau này lấy cho dễ
    int day;
    int month;
    int year;

public:
    int getDay()
    {
        return day;
    }
    void setDay(int day)
    {
        this->day = day;
    }
    int getMonth()
    {
        return month;
    }
    void setMonth(int month)
    {
        this->month = month;
    }
    int getYear()
    {
        return year;
    }
    void setYear(int year)
    {
        this->year = year;
    }
    const birthday &operator=(const birthday &x);
    friend bool operator==(const birthday &, const birthday &);
    friend bool operator<(const birthday &d1, const birthday &d2);
    friend bool operator!=(const birthday &d1, const birthday &d2);
    friend birthday operator-(const birthday &, int);
    friend ostream &operator<<(ostream &out, const birthday &);
};
birthday SystemDate();
int monthStrToInt(string a); /////////////////////
birthday dateNow;            //lấy thời gian hiện tại

//nhan vien
class member
{
protected:
    string mID;       //mã nhân viên
    string mlname;    //họ và đệm
    string firstname; //tên
    string gID;       //mã đơn vị
    string pnumber;
    birthday ns;
    int gender;
    string position; //mã chức vụ
    float C_salary;  //hệ số lương
    int year_in;
    string degree;        //trình độ, cấp bậc
    string L_certificate; // bằng ngoại ngữ
public:
    member();
    member(string, string, string, string, string, birthday, int, string, float, int, string, string);
    //hàm getter
    string getMID() const;
    string getGID() const;
    int getGender() const;
    birthday getBirthday() const;
    string getFullName() const;
    string getMlname() const;
    string getFirstname() const;
    float getC_salary() const;
    int getYear_in() const;

    void readfile_M(ifstream &);
    int getSalary();    //tinh luong
    int getNewsalary(); //thực lĩnh
    bool isEqual(int, string);

    friend istream &operator>>(istream &in, member &);
    friend ostream &operator<<(ostream &out, member &);
    //const member &operator = (const member &m);  // hàm gán, tham chiếu hằng, hằng
    friend bool operator<(const member &, const member &);
    friend bool operator>(const member &, const member &);
};

//don vi
class group
{
private:
    string gID; //ma don vi
    string gName;
    string mID; //ma nhan vien
public:
    string getGID()
    {
        return gID;
    }
    group(string = "", string = "", string = "");
    void readfile_G(ifstream &);
    friend ostream &operator<<(ostream &out, const group &);
};

//chuc vu
class Position
{
private:
    string pID;
    string pName;
    float pAllowance;

public:
    Position(string = "", string = "", float = 0);
    void readfile_P(ifstream &);
    friend ostream &operator<<(ostream &out, const Position &);
};

//danh sach
class list
{
private:
    int numofMem; //sl nv
    int numofGr;  //sl đơn vị
    int numofP;
    int ml, fl, mh, fh, mm, fm, mt, ft, ma, fa, mp, fp;
    member *list_mem;
    group *list_gr;
    Position *list_p;

public:
    list(int = 0, int = 0, int = 0);
    list(const list &);
    ~list();

    void readfile_mem(ifstream &in); //nhap danh sach nhan vien tu file
    void readfile_gr(ifstream &in);  //nhap danh sach don vi tu file
    void readfile_p(ifstream &in);   //Nhap danh sach chuc vu
    void writefile_mem(ofstream &ofs, string txt);

    void display_mem(); //in danh sach nhan vien
    void count_gender(int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &);
    void display_gr(); //in bang thong ke theo don vi
    void display_p();  //in bang thong ke cac chuc vu
    void menu_dis();

    int check(member &);
    void add(member &, int k, string txt); //bo sung 1 doi tuong vao vi tri k bat ki
    void add_menu();

    void sort();                                                   //sap xep danh sach nhan vien theo thu tu tang/giam -> hàm chính
    void sort(bool CompFunc(const member &, const member &, int)); //hàm phụ
    void QuickSort(int l, int r, int key, bool CompFunc(const member &, const member &, int));
    void menu_Sort(int &);

    int search(int, string, int a[100]); //ham tim kiem 1 nhan vien
    void search();                       //tim kiem nhan vien tu ten, gioi tinh...
    int menu_Search(string &);

    //xoa
    void delete_mem(member &);    //xoa 1 nhan vien bat ki
    void delete_mem();            //main
    void delete_mem_age(int);     //xoa theo tuoi///////////
    void delete_mem_name_id(int); //xóa theo tên or id

    //tính tổng lương, tổng thực lĩnh
    void getSumOfSalary(int&,int&,int&, int&, int&,int&, int&,int&,int&,int&, int&,int&);

    member &operator[](int i) const; //toan tu lay phan tu thu i [] trong danh sach nhan vien
    const list &operator=(const list &);
    friend ostream &operator<<(ostream &out, const list &);

    //menu main
    void menu();
};

//Ham xoa ki tu trang du thua
void del_ws(string &s);
bool ascending(const member &m1, const member &m2, int key);  //tang dan
bool descending(const member &m1, const member &m2, int key); //giam dan
bool checkFile(string path);                                  //check file path có tồn tại ko?

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

string tk,mk;
int test =0, d;
void login();

list_account acc;
list com;
//main
int main()
{
    cout << left;
    login();
    if (d!=3) {
    ifstream filein_M;
    com.readfile_mem(filein_M);
    ifstream filein_G;
    com.readfile_gr(filein_G);
    ifstream filein_p;
    com.readfile_p(filein_p);
    dateNow = SystemDate(); //lấy time hiện tại
    com.menu();
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void del_ws(string &s) //Hàm xóa khoảng trắng
{
    while (s[0] == ' ')
    {
        for (int k = 0; k < s.length(); k++)
        {
            s[k] = s[k + 1];
        }
    }
    while (s[s.length() - 1] == ' ')
    {
        s.resize(s.size() - 1);
    }
    for (int i = 0; i < s.length(); i++)
    {
        while (s[i] == ' ' && s[i + 1] == ' ')
        {
            for (int k = i + 1; k < s.length(); k++)
            {
                s[k] = s[k + 1];
            }
        }
    }
}
//phần class của chức năng đăng nhập
void account::readAccount(ifstream &in)
{
    getline(in, name, '|');
    del_ws(name);
    getline(in, password, '\n');
    del_ws(password);
}
//phần đọc file vào list_account
list_account::list_account(int numA) : numOfAcount(numA){
    la = new account[numOfAcount];
}
list_account::~list_account(){
    delete [] la;
}
int list_account::check(string s){    //check tk mk có tồn tại hay khum
    int temp=0;
    for(int i=0;i<numOfAcount;i++){
        if(s.compare(la[i].getName())==0) {
            temp =1;
            break;
        }
    }
    for(int i=0;i<numOfAcount;i++){
        if(s.compare(la[i].getPassword())==0) {
            temp =1;
            break;
        }
    }
    if(temp==1) return 1;
    else return 0;
}
void list_account::readfile_account(ifstream &in){
    in.open("Tai Khoan.txt",ios_base::in);
    int i=0;
    while(!in.eof()){
        int newSize = numOfAcount+1;
        account *newArr = new account[newSize];
        for(int j=0;j<numOfAcount;j++)
        newArr[j] = la[j];
        delete [] la;
        numOfAcount = newSize;
        la = newArr;
        la[i].readAccount(in);
        i++;
    }
    in.close();
}
//hàm chuyển chữ nhập vào thành dấu *
string list_account::tranpass(){          
    string pw;
    for (char c; (c = getch()); )
    {
        if (c == '\n' || c == '\r') { //phím enter
            cout << "\n";
            break;
        } else if (c == '\b') {        //phím xóa
            cout << "\b \b";           //\b là lùi con nháy về trái 1 ký tự, dấu cách để “xóa” ký tự đó rồi \b nữa để lùi lại vị trí sau khi xóa.
            if (!pw.empty()) pw.erase(pw.size()-1);
       } else if (c == -32) {          //phím mũi tên
            _getch();                  //bỏ qua k hiển thị gì khi nhập vào phím mũi tên
        } else if (isprint(c)) {       //isprint tức là chỉ nhận những ký tự in ra được
            cout << '*';
            pw += c;
        }
    }
    return pw;
}
//hàm login chính
void login(){            
    ifstream filein_A;
    int t;
    d=0;
    acc.readfile_account(filein_A);
    do {
    cout <<"Nhap ten tai khoan: ";
    getline(cin,tk);
    if(acc.check(tk)!=1) cout <<"TEN TAI KHOAN KHONG TON TAI, VUI LONG NHAP LAI!"<<endl;
    }while(acc.check(tk)!=1);
    do {
    cout <<"Nhap mat khau: ";
    string mk = acc.tranpass();
    d++;
    t = acc.check(mk);
    if(t!=1 && d!=3) cout <<"MAT KHAU KHONG DUNG, VUI LONG NHAP LAI!"<<endl;
    }while(t!=1 && d!=3);
    if (t==1){ 
        cout <<"DANH NHAP THANH CONG!, VUI LONG DOI VAI GIAY DE SU DUNG CHUC NANG..."<<endl;
        d--;
        Sleep(1500);
    } else cout <<"BAN DA NHAP SAI QUA 3 LAN, VUI LONG THU LAI SAU!!"<<endl;
}

//hàm sắp xếp
bool ascending(const member &m1, const member &m2, int key)
{
    birthday ns1 = m1.getBirthday();
    birthday ns2 = m2.getBirthday();
    switch (key)
    {
    case 1:
        return m1.getMID().compare(m2.getMID()) > 0 ? true : false;
    case 2:
        //so sánh nếu tên giống nhau thì so sánh họ
        if (m1.getFirstname().compare(m2.getFirstname()) != 0)
            return m1.getFirstname().compare(m2.getFirstname()) > 0 ? true : false;
        //int compare (size_t pos, size_t len, const string& str,size_t subpos, size_t sublen) const;
        //pos vị trí kí tự đầu tiên trong chuỗi ss -> m1
        //len độ dài chuỗi ss -> m1
        //subpos, sublen tương tự pos, len ->m2
        //ss 2 kí tự đầu trong họ (vd: lí, lê chỉ có 2 kí tự)
        else
            return m1.getMlname().compare(0, 2, m2.getMlname(), 0, 2) > 0 ? true : false;
    case 3:
        return m1.getGID().compare(m2.getGID()) > 0 ? true : false;
    case 4:
        //ss nếu năm bằng nhau thì ss tháng
        if (ns1.getYear() != ns2.getYear())
            return ns1.getYear() > ns2.getYear();
        //nếu tháng bằng nhau thì ss ngày
        else if (ns1.getMonth() != ns2.getMonth())
            return ns1.getMonth() > ns2.getMonth();
        return ns1.getDay() > ns2.getDay();
    case 5:
        return m1.getC_salary() > m2.getC_salary();
    case 6:
        return m1.getYear_in() > m2.getYear_in();
    default: return false;
    }
}

bool descending(const member &m1, const member &m2, int key)
{
    birthday ns1 = m1.getBirthday();
    birthday ns2 = m2.getBirthday();
    switch (key)
    {
    case 1:
        return m1.getMID().compare(m2.getMID()) < 0 ? true : false;
    case 2:
        if (m1.getFirstname().compare(m2.getFirstname()) != 0)
            return m1.getFirstname().compare(m2.getFirstname()) < 0 ? true : false;
        else
            return m1.getMlname().compare(0, 2, m2.getMlname(), 0, 2) < 0 ? true : false;
    case 3:
        return m1.getGID().compare(m2.getGID()) < 0 ? true : false;
    case 4:
        if (ns1.getYear() != ns2.getYear())
            return ns1.getYear() < ns2.getYear();
        else if (ns1.getMonth() != ns2.getMonth())
            return ns1.getMonth() < ns2.getMonth();
        return ns1.getDay() < ns2.getDay();
    case 5:
        return m1.getC_salary() < m2.getC_salary();
    case 6:
        return m1.getYear_in() < m2.getYear_in();
    default: return false;
    }
}

bool checkFile(string path)
{
    ifstream isf(path);
    return isf.good();
}

//birthday
ostream &operator<<(ostream &out, const birthday &d) //////////////////
{
    out << d.day << "   " << d.month << "   " << d.year << endl;
    return out;
}

bool operator<(const birthday &d1, const birthday &d2)
{
    if (d1.year < d2.year)
    {
        return true;
    }

    if (d1.year == d2.year)
    {
        if (d1.month < d2.month)
        {
            return true;
        }
        if (d1.month == d2.month)
        {
            if (d1.day < d2.day)
            {
                return true;
            }
            return false;
        }
    }
    return false;
}

bool operator!=(const birthday &d1, const birthday &d2)
{
    if (d1.year == d2.year && d1.month == d2.month && d1.day == d2.day)
    {
        return false;
    }
    return true;
}

const birthday &birthday::operator=(const birthday &x)
{
    if (this != &x)
    {
        day = x.day;
        month = x.month;
        year = x.year;
    }
    return *this;
}

birthday operator-(const birthday &d, int x)
{
    birthday dateResult = d;
    dateResult.year -= x;
    return dateResult;
}

bool operator==(const birthday &d1, const birthday &d2)
{
    if (d1.day == d2.day && d1.month == d2.month && d1.year == d2.year)
    {
        return true;
    }
    return false;
}

//member
member::member()
{
    mID = "";
    mlname = "";
    firstname = "";
    gID = "";
    pnumber = "";
    ns.setDay(0);
    ns.setMonth(0);
    ns.setYear(0);
    gender = 0;
    position = "";
    C_salary = 0;
    year_in = 0;
    degree = "";
    L_certificate = "";
}

member::member(string mID, string mlname, string firstname, string gID, string pnumber, birthday ns, int gender, string pos, float C_salary, int year_in, string degree, string L_cer)
    : mID(mID), mlname(mlname), firstname(firstname), gID(gID), pnumber(pnumber), ns(ns), gender(gender), position(pos),
      C_salary(C_salary), year_in(year_in), degree(degree), L_certificate(L_cer) {}

//member::getter
string member::getMID() const
{
    return mID;
}

string member::getGID() const
{
    return gID;
}

int member::getGender() const
{
    return gender;
}

string member::getMlname() const
{
    return mlname;
}

string member::getFirstname() const
{
    return firstname;
}

float member::getC_salary() const
{
    return C_salary;
}

int member::getYear_in() const
{
    return year_in;
}

birthday member::getBirthday() const
{
    return ns;
}

string member::getFullName() const
{
    return mlname + " " + firstname;
}
//
void member::readfile_M(ifstream &in)
{
    string s; //bỏ qua dòng đầu
    char t;   // đọc kí tự bỏ qua
    getline(in, mID, '|');
    del_ws(mID);
    getline(in, mlname, '|');
    del_ws(mlname);
    getline(in, firstname, '|');
    del_ws(firstname);
    getline(in, gID, '|');
    del_ws(gID);
    getline(in, pnumber, '|');
    del_ws(pnumber);
    int day;
    in >> day;
    ns.setDay(day);
    in >> t; // đọc |, bỏ qua nó
    int month;
    in >> month;
    ns.setMonth(month);
    in >> t;
    int year;
    in >> year;
    ns.setYear(year);
    in >> t;
    in >> gender;
    getline(in, s, '|');
    getline(in, position, '|');
    del_ws(position);
    in >> C_salary;
    getline(in, s, '|');
    in >> year_in;
    getline(in, s, '|');
    getline(in, degree, '|');
    del_ws(degree);
    getline(in, L_certificate, '\n');
    del_ws(L_certificate);
}

ostream &operator<<(ostream &out, member &m)
{
    //du nguyen
    out << setw(6) << m.mID << setw(17) << "|" + m.mlname << setw(7) << "|" + m.firstname << setw(6) << "|" + m.gID << setw(15) 
        << "|" + m.pnumber << right << setfill('0') << "|" << setw(2) << m.ns.getDay() << "/" << setw(2) << m.ns.getMonth() << "/" 
        << setfill(' ') << left << setw(5) << m.ns.getYear() << "|" << setw(9) << (m.gender==1?"Nu":"Nam") << setw(10) << "|" + m.position 
        << "|" << setw(12) << m.C_salary << "|" << setw(8) << m.year_in << setw(10) << "|" + m.degree << setw(12) << "|" + m.L_certificate;
    return out;
}

istream &operator>>(istream &in, member &m)
{
    int temp, check = 0;
    int gt = 0;
    string s;
    int a[100];
    do
    {
        cout << "Nhap ma nhan vien: ";
        in >> m.mID;
        check = com.search(1, m.mID, a);
        if (check > 0)
        {
            cout << "\nBAN DA NHAP TRUNG MA NHAN VIEN CO SAN!" << endl;
            cout << "MOI BAN NHAP LAI: " << endl
                 << endl;
        }
    } while (check > 0);
    cout << "Nhap ho va ten dem: ";
    getline(in >> ws, m.mlname);
    m.mlname += " ";
    cout << "Nhap ten: ";
    getline(in >> ws, m.firstname);
    cout << "Nhap ma don vi: ";
    getline(in >> ws, m.gID);
    cout << "Nhap so dien thoai: ";
    in >> m.pnumber;
    cout << "Nhap ngay/thang/nam sinh: " << endl;
    cout << "Nhap ngay sinh: ";
    in >> temp;
    m.ns.setDay(temp);
    cout << "Nhap thang sinh: ";
    in >> temp;
    m.ns.setMonth(temp);
    cout << "Nhap nam sinh: ";
    in >> temp;
    m.ns.setYear(temp);
    while (gt == 0)
    {
        gt = 1; //điều kiện dừng
        cout << "Nhap gioi tinh (nam/nu): ";
        in >> s;
        if (s == "nam")
            m.gender = 0;
        else if (s == "nu")
            m.gender = 1;
        else
        {
            cout << "Ban da nhap sai!" << endl;
            gt = 0;
        }
    }
    cout << "Nhap ma chuc vu: ";
    in >> m.position;
    cout << "Nhap he so luong: ";
    in >> m.C_salary;
    cout << "Nhap nam vao lam viec: ";
    in >> m.year_in;
    cout << "Nhap trinh do cua nhan vien: ";
    getline(in >> ws, m.degree);
    cout << "Nhap trinh do ngoai ngu cua nhan vien: ";
    getline(in >> ws, m.L_certificate);
    return in;
}

int member::getSalary()
{
    return (A / 100) * (int(C_salary * 100));
}

int member::getNewsalary()
{
    if (position.compare("GD") == 0 || position.compare("PGD") == 0)
    {
        return (getSalary() / 10 * 15);
    }
    else if (position.compare("TP") == 0 || position.compare("PP") == 0)
    {
        return (getSalary() / 100 * 125);
    }
    else
        return getSalary();
}

bool member::isEqual(int chon, string s)
{
    string temp; //chuyển kiểu int/float sang string
    ostringstream convert, convert1, convert2;
    switch (chon)
    {
    case 1:
        return s.compare(this->mID);
    case 2:
        return s.compare(this->mlname);
    case 3:
        return s.compare(this->firstname);
    case 4:
        return s.compare(this->gID);
    case 5:
        return s.compare(this->pnumber);
    case 6:
        convert << this->ns.getDay();
        temp = convert.str();
        convert1 << this->ns.getMonth();
        temp += convert1.str();
        convert2 << this->ns.getYear();
        temp += convert2.str();
        return s.compare(temp);
    case 7:
        convert << this->gender;
        temp = convert.str();
        return s.compare(temp);
    case 8:
        return s.compare(this->position);
    case 9:
        convert << this->C_salary;
        temp = convert.str();
        return s.compare(temp);
    case 10:
        convert << this->year_in;
        temp = convert.str();
        return s.compare(temp);
    case 11:
        return s.compare(this->degree);
    case 12:
        return s.compare(this->L_certificate);
    case 13:
        return s.compare(this->getFullName());
    default: return false;
    }
}

//group
group::group(string gID, string gName, string mID)
    : gID(gID), gName(gName), mID(mID) {}

void group::readfile_G(ifstream &in)
{
    getline(in, gID, '|');
    del_ws(gID);
    getline(in, gName, '|');
    del_ws(gName);
    getline(in, mID, '\n');
    del_ws(mID);
}

ostream &operator<<(ostream &out, const group &g)
{
    out << setw(10) << g.gID << "|" << setw(19) << g.gName << "|" << setw(9) << g.mID;
    return out;
}

//position
Position::Position(string pID, string pName, float pAllowance)
    : pID(pID), pName(pName), pAllowance(pAllowance) {}

void Position::readfile_P(ifstream &in)
{
    string s;
    getline(in, pID, '|');
    del_ws(pID);
    getline(in, pName, '|');
    del_ws(pName);
    in >> pAllowance;
    getline(in, s, '\n');
}

ostream &operator<<(ostream &out, const Position &p)
{
    out << setw(10) << p.pID << "|" << setw(19) << p.pName << "|" << setw(9) << p.pAllowance;
    return out;
}

//list
//Khoi tao
list::list(int NMem, int NGr, int NP)
    : numofMem(NMem), numofGr(NGr), numofP(NP)
{
    list_mem = new member[numofMem];
    list_gr = new group[numofGr];
    list_p = new Position[numofP];
}

list::list(const list &l)
{
    this->numofMem = l.numofMem;
    this->numofGr = l.numofGr;
    this->numofP = l.numofP;

    this->list_mem = new member[numofMem];
    this->list_gr = new group[numofGr];
    this->list_p = new Position[numofP];

    for (int i = 0; i < numofMem; i++)
    {
        this->list_mem[i] = l.list_mem[i];
    }
    for (int i = 0; i < numofGr; i++)
    {
        this->list_gr[i] = l.list_gr[i];
    }
    for (int i = 0; i < numofP; i++)
    {
        this->list_p[i] = l.list_p[i];
    }
}

list::~list()
{
    delete[] list_mem;
    delete[] list_gr;
    delete[] list_p;
}

//doc file nhan vien
void list::readfile_mem(ifstream &in)
{
    in.open(nhanvientxt, ios_base::in);
    string s;
    getline(in, s, '\n');
    int i = 0;
    while (!in.eof())
    {
        //tăng mảng lên
        int newSize = numofMem + 1;
        member *newArr = new member[newSize];
        for (int j = 0; j < numofMem; j++)
            newArr[j] = list_mem[j];
        delete[] list_mem;
        numofMem = newSize;
        list_mem = newArr;
        //doc file
        list_mem[i].readfile_M(in);
        i++;
    }
    in.close();
}
//doc file don vi : ô kê nuôn
void list::readfile_gr(ifstream &in)
{
    in.open("Don Vi.txt", ios_base::in);
    string s;
    getline(in, s, '\n'); //bỏ dòng đầu
    int i = 0;
    while (!in.eof())
    {
        //tăng mảng lên
        int newSize = numofGr + 1;
        group *newArr = new group[newSize];
        for (int j = 0; j < numofGr; j++)
            newArr[j] = list_gr[j];
        delete[] list_gr;
        list_gr = newArr;
        numofGr = newSize;
        //doc file
        list_gr[i].readfile_G(in);
        i++;
    }
    in.close();
}

void list::readfile_p(ifstream &in)
{
    in.open("Chuc Vu.txt", ios_base::in);
    string s;
    getline(in, s, '\n'); //bỏ dòng đầu
    int i = 0;
    while (!in.eof())
    {
        //tăng mảng lên
        int newSize = numofP + 1;
        Position *newArr = new Position[newSize];
        for (int j = 0; j < numofP; j++)
            newArr[j] = list_p[j];
        delete[] list_p;
        list_p = newArr;
        numofP = newSize;
        //doc file
        list_p[i].readfile_P(in);
        i++;
    }
    in.close();
}

void list::writefile_mem(ofstream &ofs, string txt)
{
    ofs.open(txt.c_str(), ios_base::trunc);
    ofs << left << setw(6) << "Ma NV" << setw(17) << "|Ho" << setw(7) << "|Ten" << setw(6) << "|Ma DV" << setw(15) << "|So dien thoai" << setw(12) << "|Ngay sinh"
        << setw(10) << "|Gioi tinh" << setw(10) << "|Chuc vu" << setw(13) << "|He so luong" << setw(9) << "|Nam vao" << setw(10) << "|Trinh do" << setw(12) << "|Ngoai ngu" << endl;
    for (int i = 0; i < numofMem - 1; i++)
    {
        ofs << left << list_mem[i] << endl;
    }
    ofs << left << list_mem[numofMem - 1];
    ofs.close();
}

void list::display_mem()
{
    cout << setw(6) << "Ma NV" << setw(17) << "|Ho" << setw(7) << "|Ten" << setw(6) << "|Ma DV" << setw(15) << "|So dien thoai" << setw(12)
        << "|Ngay sinh" << setw(10) << "|Gioi tinh" << setw(10) << "|Chuc vu" << setw(13) << "|He so luong" << setw(9) << "|Nam vao"
        << setw(10) << "|Trinh do" << setw(12) << "|Ngoai ngu" << setw(10) << "|Luong" << setw(10) << "|Thuc linh" << endl << endl;
    for (int i = 0; i < numofMem; i++)
    {
        cout << list_mem[i] << "|" << setw(9) << list_mem[i].getSalary() << "|" << setw(9) << list_mem[i].getNewsalary() << endl
             << endl;
    }
}

void list::count_gender(int &ml, int &fl, int &mh, int &fh, int &mm, int &fm, int &mt, int &ft, int &ma, int &fa, int &mp, int &fp)
{
    for (int i = 0; i < numofMem; i++)
    {
        if (list_mem[i].getGID().compare("LDR") == 0)
        {
            if (list_mem[i].getGender() == 0)
                ml++;
            else
                fl++;
        }
        else if (list_mem[i].getGID().compare("HRS") == 0)
        {
            if (list_mem[i].getGender() == 0)
                mh++;
            else
                fh++;
        }
        else if (list_mem[i].getGID().compare("MKT") == 0)
        {
            if (list_mem[i].getGender() == 0)
                mm++;
            else
                fm++;
        }
        else if (list_mem[i].getGID().compare("TNC") == 0)
        {
            if (list_mem[i].getGender() == 0)
                mt++;
            else
                ft++;
        }
        else if (list_mem[i].getGID().compare("ACT") == 0)
        {
            if (list_mem[i].getGender() == 0)
                ma++;
            else
                fa++;
        }
        else if (list_mem[i].getGID().compare("PJT") == 0)
        {
            if (list_mem[i].getGender() == 0)
                mp++;
            else
                fp++;
        }
    }
}

void list::getSumOfSalary(int &sumL,int& sumNL,int& sumH, int&sumNH, int& sumM,int& sumNM, int& sumT,int& sumNT,int& sumA,int& sumNA, int& sumP,int& sumNP){
    for(int i=0;i<numofMem;i++){
        if(list_mem[i].getGID().compare("LDR")==0) {
            sumL+=list_mem[i].getSalary();
            sumNL+=list_mem[i].getNewsalary();
        }
        else if (list_mem[i].getGID().compare("HRS")==0) {
            sumH+=list_mem[i].getSalary();
            sumNH+=list_mem[i].getNewsalary();
        }
        else if (list_mem[i].getGID().compare("MKT")==0) {
            sumM+=list_mem[i].getSalary();
            sumNM+=list_mem[i].getNewsalary();
        } 
        else if (list_mem[i].getGID().compare("TNC")==0) {
            sumT+=list_mem[i].getSalary();
            sumNT+=list_mem[i].getNewsalary();
        }
        else if (list_mem[i].getGID().compare("ACT")==0) {
            sumA+=list_mem[i].getSalary();
            sumNA+=list_mem[i].getNewsalary();
        } else {
            sumP+=list_mem[i].getSalary();
            sumNP+=list_mem[i].getNewsalary();
        }
    }
}

void list::display_gr()
{
    int ml = 0, fl = 0, mh = 0, fh = 0, mm = 0, fm = 0, mt = 0, ft = 0, ma = 0, fa = 0, mp = 0, fp = 0;
    int sumL = 0,sumNL=0 ,sumH=0 ,sumNH=0 ,sumM=0 ,sumNM=0 ,sumT=0,sumNT =0,sumA=0 ,sumNA=0 ,sumP=0 ,sumNP=0;  
    count_gender(ml, fl, mh, fh, mm, fm, mt, ft, ma, fa, mp, fp);
    getSumOfSalary(sumL,sumNL,sumH,sumNH,sumM,sumNM,sumT,sumNT,sumA,sumNA,sumP,sumNP);
    cout << setw(10) << "Ma DV" << setw(20) << "|Ten don vi" << setw(10) << "|Ma NV" << setw(21) << "|So luong nam" 
        << setw(21) << "|So luong nu" <<setw(21)<<"|Tong luong"<<setw(20)<<"|Tong thuc linh"<< endl<< endl;
    for (int i = 0; i < numofGr; i++)
    {
        if (list_gr[i].getGID().compare("LDR") == 0)
            cout << list_gr[i] << "|" << setw(20) << ml << "|" << setw(20) << fl <<"|"<<setw(20)<< sumL <<"|"<<setw(20) << sumNL 
            << endl << endl;
        else if (list_gr[i].getGID().compare("HRS") == 0)
            cout << list_gr[i] << "|" << setw(20) << mh << "|" << setw(20) << fh <<"|"<<setw(20)<< sumH <<"|"<<setw(20) << sumNH
            << endl << endl;
        else if (list_gr[i].getGID().compare("MKT") == 0)
            cout << list_gr[i] << "|" << setw(20) << mm << "|" << setw(20) << fm <<"|"<<setw(20)<< sumM <<"|"<<setw(20) << sumNM
            << endl << endl;
        else if (list_gr[i].getGID().compare("TNC") == 0)
            cout << list_gr[i] << "|" << setw(20) << mt << "|" << setw(20) << ft <<"|"<<setw(20)<< sumT <<"|"<<setw(20) << sumNT
            << endl<< endl;
        else if (list_gr[i].getGID().compare("ACT") == 0)
            cout << list_gr[i] << "|" << setw(20) << ma << "|" << setw(20) << fa <<"|"<<setw(20)<< sumA <<"|"<<setw(20) << sumNA
            << endl << endl;
        else
            cout << list_gr[i] << "|" << setw(20) << mp << "|" << setw(20) << fp <<"|"<<setw(20)<< sumP <<"|"<<setw(20) << sumNP
            << endl << endl;
    }
}

void list::display_p()
{
    cout << setw(10) << "Ma CV" << setw(20) << "|Ten chuc vu" << setw(10) << "|He so PC" << endl << endl;
    for (int i = 0; i < numofP; i++)
    {
        cout << list_p[i] << endl << endl;
    }
}

void list::menu_dis()
{
    int key;
    do{
        system("cls");
        cout<<"Hien thi theo danh sach"<<endl;
        cout<<"1: Nhan vien"<<endl;
        cout<<"2: Don vi"<<endl;
        cout<<"3: Chuc vu"<<endl;
        cout<<"0: Thoat!"<<endl;
        cout<<"Chon: ";
        cin>>key;
        switch(key){
            case 1:
                display_mem();
                system("pause");
                break;
            case 2:
                display_gr();
                system("pause");
                break;
            case 3:
                display_p();
                system("pause");
                break;
        }
    }while(key);
}
//list::search
int list::search(int chon, string s, int a[])
{
    int n = 0;
    for (int i = 0; i < numofMem; i++)
    {
        if (list_mem[i].isEqual(chon, s) == 0)
        {
            a[n++] = i;
        }
    }
    return n;
}

void list::search()
{
    int a[100];
    string tt; //thông tin
    char chon2;
    do
    {
        int chon = menu_Search(tt);
        int k = search(chon, tt, a);
        list fileSearchResult; //lưu lại danh sách kết quả tìm được
        if (k > 0)
        {
            cout << "Co " << k << " ket qua phu hop: " << endl;
            for (int i = 0; i < k; i++)
            {
                cout << list_mem[a[i]] << endl;
                fileSearchResult.add(list_mem[a[i]], 0, nhanviensearch);
            }
            //chon nhap file
            char key;
            do
            {
                cout << "Ban co muon in ket qua ra file khong?[C/K]: ";
                cin >> key;
                key = toupper(key);
                if (key != 'K' && key != 'C')
                {
                    cout << "Khong co lua chon nay! Moi ban nhap lai:" << endl;
                }
            } while (key != 'K' && key != 'C');
            if (key == 'C')
            { //xuất file
                ofstream ofs;
                string fileNameResult; //trả về tên file xuất
                string tempFileName;   // lưu tên file tạm
                do                     //chạy cho đến khi không nhập gì hoặc nhâp đúng tên file chưa tồn tại
                {
                    cout << "Nhap ten file hoac enter de luu vs ten mac dinh!: ";
                    cin.ignore();
                    getline(cin, tempFileName);
                    tempFileName = tempFileName + ".txt";

                    if (tempFileName == ".txt") //lưu mặc định/////////////////////////////////
                    {
                        fileNameResult = nhanviensearch;                      //gán tên file gốc vào tên file xuất
                        int i = 0;                                            //file xuất có tên là fileNameResult + (i).txt
                        fileNameResult.erase(fileNameResult.length() - 4, 4); //xoa .txt
                        do                                                    //thực hiện cho đến khi tạo được file chưa tồn tại
                        {
                            tempFileName = fileNameResult + "(" + to_string(i) + ").txt"; // tạo một file tạm để kiểm tra. đỡ tạo cái xóa txt nhiều lần

                            if (checkFile(tempFileName) == true)
                            { //nếu tồn tại thì tăng i lên tạo tên khác
                                i++;
                            }
                            else
                            { //nếu không tồn tại thì trả tên file cho fileNameResult
                                fileNameResult = tempFileName;
                                break;
                            }
                        } while (1);
                    }

                    else //luu theo tên người nhập////////////////////////////
                        if (checkFile(tempFileName) == true)
                    {
                        cout << "Tep nay da ton tai!. Moi nhap lại!" << endl;
                    }
                    else
                    {
                        fileNameResult = tempFileName;
                    }

                } while (checkFile(tempFileName) == true);
                cout << "Da luu file voi ten:" << fileNameResult << endl;
                fileSearchResult.writefile_mem(ofs, fileNameResult); //xuất file
            }
        }
        else
            cout << "Khong tim thay ket qua phu hop!" << endl;
        cout << "Muon tiep tuc(C/K): ";
        cin >> chon2;
        chon2 = toupper(chon2);
    } while (chon2 != 'K');
    cout << "Nhan Enter de tro ve Menu!" << endl;
}

int list::menu_Search(string &tt)
{
    int chon;
    do
    {
        system("cls");
        cout << "Ban muon tim kiem thong tin theo cach nao:" << endl;
        cout << "1: Ma nhan vien" << endl;
        cout << "2: Ho va ten" << endl;
        cout << "3: Ten" << endl;
        cout << "4: Ma don vi" << endl;
        cout << "5: So dien thoai" << endl;
        cout << "6: Ngay sinh" << endl;
        cout << "7: Gioi tinh" << endl;
        cout << "8: Ma chuc vu" << endl;
        cout << "9: He so luong" << endl;
        cout << "10: Nam vao" << endl;
        cout << "11: Trinh do, cap bac" << endl;
        cout << "12: Bang ngoai ngu" << endl;
        cout << "Chon: ";
        cin >> chon;
    } while (chon < 1 || chon > 12);
    if (chon == 6)
    {
        string s;
        tt = s;
        cout << "Nhap ngay: ";
        cin >> s;
        tt += s;
        cout << "Nhap thang: ";
        cin >> s;
        tt += s;
        cout << "Nhap nam: ";
        cin >> s;
        tt += s;
    }
    else if(chon == 7){
        cout<<"Nhap gioi tinh(0:nam/1:nu): ";
        getline(cin >> ws, tt);
    }
    else
    {
        if(chon == 2) chon += 11;
        cout << "Nhap thong tin can tim kiem: ";
        getline(cin >> ws, tt);
    }
    return chon;
}
//list::add
int list::check(member &m)
{
    int temp = 0;
    for (int i = 0; i < numofMem; i++)
    {
        if (m.getMID().compare(list_mem[i].getMID()) == 0)
        {
            temp = -1;
            break;
        }
    }
    if (temp == -1)
    {
        cout << "\nBAN DA NHAP TRUNG MA NHAN VIEN CO SAN!" << endl;
        cout << "MOI BAN NHAP LAI: " << endl
             << endl;
        return -1;
    }
    else
        return 0;
}

void list::add(member &m, int k, string txt)
{
    numofMem++;
    member *b = new member[numofMem];
    for (int i = 0; i < numofMem - 1; i++)
        b[i] = list_mem[i];
    for (int i = numofMem - 1; i > k; i--)
        b[i] = b[i - 1];
    b[k] = m;
    /*Tiến hành cấp phát động lại list_mem*/
    delete[] list_mem;
    list_mem = new member[numofMem];
    for (int i = 0; i < numofMem; i++)
        list_mem[i] = b[i];
    ofstream ofs;
    writefile_mem(ofs, txt);
}

void list::add_menu()
{
    int cv;
    member m;
    int k, x;
    do
    {
        system("cls");
        cout << "--------------CHUC NANG---------------" << endl;
        cout << "1: Them nhan vien vao dau danh sach" << endl;
        cout << "2: Them nhan vien vao cuoi danh sach" << endl;
        cout << "3: Them vao vi tri bat ki" << endl;
        cout << "0: Thoat!" << endl;
        cout << "Chon: ";
        cin >> cv;
        switch (cv)
        {
        case 1:
            cout << "Nhap nhan vien muon them vao dau danh sach: " << endl;
            cin >> m;
            add(m, 0, nhanvientxt);
            cout << "------------Da them thanh cong!-------------" << endl;
            break;
        case 2:
            cout << "Nhap nhan vien muon them vao cuoi danh sach: " << endl;
            cin >> m;
            k = --numofMem;
            add(m, k, nhanvientxt);
            cout << "------------Da them thanh cong!-------------" << endl;
            break;
        case 3:
            cout << "Nhap nhan vien muon them vao vi tri bat ki trong danh sach: " << endl;
            cin >> m;
            do
            {
                cout << "Nhap vi tri muon them:";
                cin >> k;
                if (k < 0 && k > numofMem)
                {
                    cout << "Ban da nhap vi tri vuot ngoai danh sach, moi ban nhap lai!";
                    k = -1;
                }

            } while (k == -1);
            add(m, k, nhanvientxt);
            cout << "------------Da them thanh cong!-------------" << endl;
            break;
        case 0:
            cout << "Nhan Enter de nhap lai chuc nang!" << endl;
            break;
        default:
            cout << "Ban da nhap sai!" << endl;
            cout << "Nhan Enter de tiep tuc!" << endl;
            getch();
        }
    } while (cv != 0);
}
//list::delete
void list::delete_mem_age(int key)
{
    birthday dayAge;
    bool checkdel = false;
    int run = 0;
    int age = 60;
    if (key == 4)
    {
        int nam;
        cout << "Nhap nam sinh:";
        cin >> nam;
        dayAge = dateNow;
        dayAge.setYear(nam);
    }
    else if (key == 5)
    {
        cout << "Nhap tuoi muon xoa:";
        cin >> age;
        dayAge = dateNow - age;
    }
    else if (key == 6)
    {

        dayAge = dateNow - age;
    }

    do
    {
        //tim diem xoa
        if (key == 5 || key == 6)
        {
            while (dayAge < list_mem[run].getBirthday() && run < numofMem) //nếu chưa đủ 60(age) tuổi thì bỏ qua
            {
                run++;
            }
        }
        //tim diem xoa
        if (key == 4)
        {
            while (dayAge.getYear() != list_mem[run].getBirthday().getYear() && run < numofMem) //nếu chưa đủ 60(age) tuổi thì bỏ qua
            {
                run++;
            }
        }

        //gán lại mảng để xóa
        if (run < numofMem)
        {
            checkdel = true;
            //>= 60 tuổi
            int newSize = numofMem - 1;
            member *newArr = new member[newSize];
            int i = 0;
            int j = 0;
            //gán phần tử cho mảng mới bỏ qua phần tử muốn xóa
            while (i < numofMem && j < newSize)
            {
                if (i == run) //Nếu gặp người cần xóa thì tăng i để bỏ qua
                {
                    i++;
                }
                newArr[j] = list_mem[i];
                i++;
                j++;
            }
            delete[] list_mem;
            //trả lại mảng đã xóa
            numofMem = newSize; //tru 1 vi danh sach bat dau tu 0
            list_mem = newArr;
        }

    } while (run < numofMem);
    if (checkdel == true)
    {
        cout << "------------Da xoa xong!--------------" << endl;
        cout << "-----------Enter de tiep tuc----------" << endl;
        getch();
    }
    else
    {
        cout << "Khong co nhan vien nao trung thong tin can xoa!" << endl;
        cout << "---------------Enter de tiep tuc--------------" << endl;
        getch();
    }
    if (numofMem > 0)
    {
        ofstream ofs;
        writefile_mem(ofs, nhanvienouttxt);
    }
}

void list::delete_mem_name_id(int option) //xóa theo tên hoặc id
{
    int a[100];
    string content;

    if (option == 1)
    {
        cout << "Nhap ma nhan vien: ";
    }
    else if (option == 3)
    {
        cout << "Nhap ten nhan vien: ";
    }
    else if (option == 13)
    {
        cout << "Nhap ho ten nhan vien: ";
    }
    cin.ignore();
    getline(cin, content);
    int n = search(option, content, a);
    if (n == 0)
    {
        cout << "Khong co nguoi nao co thong tin trung khop!" << endl;
        cout << "----------Nhan Enter de tiep tuc!---------" << endl;
        getch();
    }
    else
    {
        int newSize = numofMem - n;
        member *newListMember = new member[newSize];
        int i = 0;
        int j = 0;
        int t = 0;
        while (i < numofMem && j < newSize)
        {
            if (i == a[t])
            {

                t++;
                i++;
            }
            else
            {
                newListMember[j] = list_mem[i];
                i++;
                j++;
            }
        }
        delete[] list_mem;
        numofMem = newSize;
        list_mem = newListMember;
        for (int i = 0; i < numofMem; i++)
        {
            list_mem[i];
        }
        if (numofMem > 0)
        {
            ofstream ofs;
            writefile_mem(ofs, nhanvienouttxt);
        }
        cout << "-----------Da xoa xong!------------" << endl;
        cout << "------Nhan Enter de tiep tuc!------" << endl;
        getch();
    }
}
//main_del_mem
void list::delete_mem()
{
    int ktr = 0;
    do
    {
        system("cls");
        cout << " 1. Xoa theo ID.\n";
        cout << " 2. Xoa theo ten.\n";
        cout << " 3. Xoa theo ho ten.\n";
        cout << " 4. Xoa theo nam sinh. \n";
        cout << " 5. Xoa lon hon tuoi.\n";
        cout << " 6. Xoa nguoi tren 60 tuoi.\n";
        cout << " 7. Hien thi ds.\n";
        cout << " 0. Ket Thuc\n";
        cout << "Chon chuc nang: ";
        int key;
        cin >> key;
        switch (key)
        {
        case 1:
            cout << " 1. Xoa theo ID.\n";
            this->delete_mem_name_id(1);
            break;
        case 2:
            cout << " 2. Xoa theo ten.\n";
            this->delete_mem_name_id(3);
            break;
        case 3:
            cout << "3. Xoa theo ho ten.\n";
            this->delete_mem_name_id(13);
            break;
        case 4:
            cout << " 4. Xoa theo nam sinh. \n";
            this->delete_mem_age(key);
            break;
        case 5:
            cout << " 5. Xoa theo tuoi.\n";
            this->delete_mem_age(key);
            break;
        case 6:
            cout << " 6. Xoa nguoi tren 60 tuoi.\n";
            this->delete_mem_age(key);
            break;
        case 7:
            cout << " 7. Hien thi ds.\n";
            this->display_mem();
            system("pause");
            break;
        case 0:
            ktr = -1;
            break;
        default:
            cout << "Khong co chuc nang nay. Moi nhap lai!" << endl;
            cout << "-------Nhan Enter de tiep tuc!-------" << endl;
            getch();
        }

    } while (ktr != -1);
}
//trả về ngày hiện tại
birthday SystemDate()
{
    birthday dateResult;
    time_t now = time(0);   //hàm trả về thời gian là s
    char *dt = ctime(&now); //chuyển s thành date
    //012345678901234567890123 để tìm vị trí ngày cho dễ
    //Fri Oct 29 21:53:17 2021

    //bắt đầu lấy ngày
    string date(dt); //chuyển char thành string
    char sday[2];    //ngày có hai chữ số và một kí tự kết thúc \0->chuoi
    int length = date.copy(sday, 2, 8);
    sday[length] = '\0';        //thhêm ký tụ kết thúc để chuyển char thành string
    int iday;                   //day kiểu int
    stringstream(sday) >> iday; //chuyển string thành int
    dateResult.setDay(iday);

    // //lấy năm
    string year(dt);
    char syear[4];
    length = year.copy(syear, 4, 20);
    syear[length] = '\0';
    int iyear;
    stringstream(syear) >> iyear;
    dateResult.setYear(iyear);

    //bat dau lay thang
    string month(dt);
    char cmonth[4];
    month.copy(cmonth, 3, 4);
    string smonth(cmonth);
    int imonth = monthStrToInt(smonth);

    dateResult.setMonth(imonth);
    return dateResult;
}

//chuyển ngày chữ sang ngày số
int monthStrToInt(string a)
{
    if (a == "Jan")
        return 1;
    if (a == "Feb")
        return 2;
    if (a == "Mar")
        return 3;
    if (a == "Apr")
        return 4;
    if (a == "May")
        return 5;
    if (a == "Jun")
        return 6;
    if (a == "Jul")
        return 7;
    if (a == "Aug")
        return 8;
    if (a == "Sep")
        return 9;
    if (a == "Oct")
        return 10;
    if (a == "Nov")
        return 11;
    if (a == "Dec")
        return 12;
    else return 0;
}

//list::sort
void list::sort()
{
    int key;
    do
    {
        system("cls");
        cout << "1: Tang dan" << endl;
        cout << "2: Giam dan" << endl;
        cout << "Chon: ";
        cin >> key;

    } while (key != 1 && key != 2);
    if (key == 1)
        sort(ascending);
    else if (key == 2)
        sort(descending);
}

void list::sort(bool CompFunc(const member &, const member &, int))
{
    int key;
    do
    {
        menu_Sort(key);
        if (key == 7)
            display_mem();
        else if (key != 0)
            QuickSort(0, numofMem - 1, key, CompFunc); //nếu kp đk dừng(key=0) thì tiếp tục
            ofstream ofs;
            writefile_mem(ofs, nhanvienouttxt);
        if(key != 0){
            cout << "-----------Da sap xep xong!------------" << endl;
            system("pause");
        }
    } while (key);
}

void list::QuickSort(int l, int r, int key, bool CompFunc(const member &, const member &, int))
{
    //key -> trong menu_Sort
    int i = l, j = r;
    member q = list_mem[(l + r) / 2]; //lấy phần tử ở giữa ds
    while (i < j)
    {
        while ((CompFunc)(q, list_mem[i], key))
            i++;
        while ((CompFunc)(list_mem[j], q, key))
            j--;
        if (i <= j)
        {
            member temp = list_mem[i];
            list_mem[i] = list_mem[j];
            list_mem[j] = temp;
            i++;
            j--;
        }
    }
    if (i < r)
        QuickSort(i, r, key, CompFunc);
    if (j > l)
        QuickSort(l, j, key, CompFunc);
}

void list::menu_Sort(int &key)
{
    do
    {   system("cls");
        cout << "Ban muon sap xep theo cach nao: " << endl;
        cout << "1: Ma nhan vien" << endl;
        cout << "2: Ho va ten" << endl;
        cout << "3: Ma don vi" << endl;
        cout << "4: Ngay sinh" << endl;
        cout << "5: He so luong" << endl;
        cout << "6: Nam vao" << endl;
        cout << "7: Hien thi danh sach nhan vien " << endl;
        cout << "0: Thoat!" << endl;
        cout << "Chon: ";
        cin >> key;
    } while (key < 0 || key > 7);
}

void list::menu()
{
    int chon;
    member m;
    int k, x;
    do
    {
        system("cls");
        cout << "--------------MENU---------------" << endl;
        cout << "1: Hien thi" << endl;
        cout << "2: Thong ke" << endl;
        cout << "3: Sua thong tin nhan vien" << endl;
        cout << "4: Them mot nhan vien" << endl;
        cout << "5: Tim kiem nhan vien" << endl;
        cout << "6: Xoa mot nhan vien" << endl;
        cout << "7: Sap xep danh sach nhan vien" << endl;
        cout << "0: Thoat!" << endl;
        cout << "Chon: ";
        cin >> chon;
        switch (chon)
        {
        case 1:
            menu_dis();
            break;
        case 2:
            
            break;
        case 3:
            
            break;
        case 4:
            add_menu();
            getch();
            break;
        case 5:
            search();
            getch();
            break;
        case 6:
            delete_mem();
            break;
        case 7:
            sort();
            break;
        case 0:
            break;
        default:
            cout << "Ban da nhap sai!" << endl;
            cout << "Nhan Enter de nhap lai chuc nang!" << endl;
            getch();
        }
    } while (chon);
}