#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

struct ListEntry{
    int val;
    unsigned type;
};


class ListReader;
class ListReaderFromFile;
class ListDiffer {
    public: 
        virtual int getDists() = 0;
        virtual int getSim() = 0;
        virtual void populate(ListReader* reader) = 0;
        virtual ~ListDiffer(){} // compiler error when =0 ??? 
        friend ListReader;
        friend ListReaderFromFile; // idk i feel like friendship should be inherited! oh well
};

// a specific implementation
class ListDifferMemLocal : public ListDiffer {
    public:
        int getDists() override;
        int getSim() override;
        void populate(ListReader* reader) override;
        ListDifferMemLocal() = default;
        ~ListDifferMemLocal() = default;
    private:
        vector<ListEntry> list; //store all entries in one list for mem locality
};

// abstract base class, in case we want to read from file or from command line linput, etc
class ListReader {
    public: 
    virtual bool readEntry(ListEntry& e) = 0; // return true if successful read
};

class ListReaderFromFile : public ListReader{
    public: 
        ListReaderFromFile(string filename){ in.open(filename); }
        bool readEntry(ListEntry& e) override;
    private:
        ifstream in;
        unsigned nextType = 0; 
};

class Solver{
    public:
        Solver(){ ld = new ListDifferMemLocal; }
        ~Solver(){ delete ld; }
        void inputData(string filename);
        int answer(){ return ld->getDists(); }
        int answer2(){ return ld->getSim(); }

    private:
        ListDiffer* ld = nullptr;
};

int main(int argc, char* argv[]){
    if(argc < 2)
        return -1;
    Solver s;
    s.inputData(string(argv[1]));
    cout << s.answer() << endl;
    cout << s.answer2() << endl;
    return 0;
}

void Solver::inputData(string filename){
    ListReaderFromFile lr(filename);
    ld->populate(&lr);
}

void ListDifferMemLocal::populate(ListReader* r){
    list.reserve(200);
    ListEntry e;
    while(r->readEntry(e)){
        list.push_back(e);
    }
    sort(list.begin(), list.end(), [](ListEntry l1, ListEntry l2){ 
            return (l1.val < l2.val || (l1.val == l2.val && l1.type <= l2.type));  // sort by type as well for 2nd challenge
            });
}

int ListDifferMemLocal::getDists(){
    int runningTotal = 0;
    unsigned counts[2] = {0, 0};
    for(ListEntry& x : list){
        counts[x.type]++;
        runningTotal += (counts[x.type] <= counts[(x.type + 1) & 1] ? x.val : -x.val);
    }
    
    return runningTotal;
}

int ListDifferMemLocal::getSim(){
    int runningTotal = 0;
    for(auto itr = list.begin(); itr != list.end();){
        unsigned lcount = 0;
        int val = itr->val;
        while(itr != list.end() && itr->type == 0 && itr->val == val){
            lcount++;
            itr++;
        }
        unsigned factor = 0;
        while(itr != list.end() && itr->type == 1 && itr->val == val){
            factor++;
            itr++;
        }
        runningTotal += val * lcount * factor;
    }
    return runningTotal;
}

bool ListReaderFromFile::readEntry(ListEntry& e){
    if(in >> e.val){
        e.type = nextType;
        nextType = (nextType + 1) & 1;
        return true;
    }
    return false;
}
