#include<iostream>
#include<string>
#include<sstream>
using namespace std;
int main(){
    int total = 0;
    string s;
    int i1 = 0, i2=0;
    bool work = true;
    while(getline(cin, s)){
        if( s == "don't()")
            work = false;
        else if( s == "do()")
            work = true;
        else{ // 2 numbers
            stringstream ins = stringstream(s);
            ins >> i1 >> i2;
            if(work)
                total += i1 * i2;
        }
    }

    cout << total;
    return 0;
}
