#include <iostream>

using namespace std;

int main()
{
    std::string str;

    str = "Ex1\n";
    str += "Ex2\n";
    str += 13;

    std::cout << str;
}

//#include <iostream>

//using namespace std;

//class A
//{
//public:
//    virtual int get_num(void) = 0;
//};

//class B : public A
//{
//    int num;
//public:
//    B(int num): num(num) {}

//    virtual int get_num(void)
//    {
//        return B::num;
//    }
//};

//int main()
//{
//    char str[40];

//    cout << "N 1\n\r";
//    cin >> str;

//    try
//    {
//        cout << stoi(str) << '\n';
//        cout << "Digitado: " << str << '\n';
//    }
//    catch (exception Ex)
//    {
//        cout << "Excessao\n";
//        cout << Ex.what();
//        cout << '\n';
//    }

//    return 0;
//}
