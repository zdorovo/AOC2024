#include<iostream>
#include<fstream>
#include<sstream>
#include<list>
#include<string>
#include<array>
#include<algorithm>
#include<cmath>
#include<iterator>

using namespace std;

class LevelJudgerBase {
    public:
        virtual bool isSafe() = 0;
        void readStr(string s);
        void readList(list<int> l){ dat = l; }
    protected:
        list<int> dat;
};

void LevelJudgerBase::readStr(string s){
    stringstream ins(s);
    dat.clear();
    int i = 0;
    while( ins >> i)
        dat.push_back(i);
}


class LevelJudger : public LevelJudgerBase{
    public:
        bool isSafe() override;
};

class LevelJudger2 : public LevelJudgerBase{
    public:
        bool isSafe() override;
};

bool LevelJudger::isSafe(){
    auto itr0 = dat.begin();
    if(itr0 == dat.end())
        return true;
    auto itr1 = next(itr0);
    if(itr1 == dat.end())
        return true;
    int i0 = *itr0, i1 = *itr1;
    bool inc = i0 < i1;
    while (itr1 != dat.end()){
        if( *itr0 < *itr1 != inc)
            return false;
        if( abs(*itr0 - *itr1) > 3)
            return false;
        if(*itr0 == *itr1)
            return false;
                
        itr0++;
        itr1++;
    }

    return true;
}

template<typename T>
list<T> without(list<T>& l, typename list<T>::iterator& it){
    list<T> l1;
    for(auto it0 = l.begin(); it0 != l.end(); it0++){
        if(it0 != it)
            l1.push_back(*it0);
    }
    return l1;
}

// can tolerate a single unsafe bit
bool LevelJudger2::isSafe(){
    LevelJudger lj;
    lj.readList(dat);

    if(lj.isSafe())
        return true;

    for(auto itr = dat.begin(); itr != dat.end(); itr++){
        LevelJudger lj1;
        lj1.readList(without(dat, itr));
        if(lj1.isSafe())
            return true;
    }
    
    return false;
}



class Solver{
    public:
        Solver(string filename, LevelJudgerBase* _lj):lj(_lj){ in.open(filename); } 
        unsigned solve(); // output number of safe levels
    private: 
        ifstream in;
        LevelJudgerBase* lj;
};

unsigned Solver::solve(){
    unsigned total = 0;
    string s;

    while(getline(in, s)){
        lj->readStr(s);
        if(lj->isSafe())
            total++;
    }

    return total;
}

int main(int argc, char* argv[]){
    if(argc < 2)
        return -1;
    // input file
    string file = string(argv[1]);
    LevelJudger lj;
    Solver s1( file, &lj );

    LevelJudger2 lj2;
    Solver s2( file, &lj2 );
    // answer question
    cout << s1.solve() << endl;
    cout << s2.solve() << endl;
}
