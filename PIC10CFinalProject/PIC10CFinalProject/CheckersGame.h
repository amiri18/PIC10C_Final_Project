#ifndef __CHECKERS_GAME__
#define __CHECKERS_GAME__

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class CheckBoard{
private:
    int blackCount;
    int whiteCount;
    vector<vector<int>> board;
    
    char dis(int input) const;
public:
    CheckBoard();
    void display() const;
};


#endif 
