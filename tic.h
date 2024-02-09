#pragma once
#include<vector>
using namespace std;

char Winx(vector<vector<int>> vect) {
    //check x
    // Check rows
    if (vect[0][0] == 0 && vect[0][1] == 0 && vect[0][2] == 0)  return 'x';
    else if (vect[1][0] == 0 && vect[1][1] == 0 && vect[1][2] == 0) return 'x';
    else if (vect[2][0] == 0 && vect[2][1] == 0 && vect[2][2] == 0) return 'x';

    // Check columns
    else if (vect[0][0] == 0 && vect[1][0] == 0 && vect[2][0] == 0)     return 'x';
    else if (vect[0][1] == 0 && vect[1][1] == 0 && vect[2][1] == 0)     return 'x';
    else if (vect[0][2] == 0 && vect[1][2] == 0 && vect[2][2] == 0)     return 'x';

    // Check diagonal
    else if (vect[0][0] == 0 && vect[1][1] == 0 && vect[2][2] == 0)    return 'x';

    // Check anti-diagonal
    else if (vect[0][2] == 0 && vect[1][1] == 0 && vect[2][0] == 0)     return 'x';

    return 'w';
}
char WinY(vector<vector<int>> vect) {
    // Check rows
    if (vect[0][0] == 1 && vect[0][1] == 1 && vect[0][2] == 1)  return 'o';
    else if (vect[1][0] == 1 && vect[1][1] == 1 && vect[1][2] == 1) return 'o';
    else if (vect[2][0] == 1 && vect[2][1] == 1 && vect[2][2] == 1) return 'o';

    // Check columns
    else if (vect[0][0] == 1 && vect[1][0] == 1 && vect[2][0] == 1)     return 'o';
    else if (vect[0][1] == 1 && vect[1][1] == 1 && vect[2][1] == 1)     return 'o';
    else if (vect[0][2] == 1 && vect[1][2] == 1 && vect[2][2] == 1)     return 'o';

    // Check diagonal
    else if (vect[0][0] == 1 && vect[1][1] == 1 && vect[2][2] == 1)    return 'o';

    // Check anti-diagonal
    else if (vect[0][2] == 1 && vect[1][1] == 1 && vect[2][0] == 1)     return 'o';

    return 'w'; // No winner found
}

