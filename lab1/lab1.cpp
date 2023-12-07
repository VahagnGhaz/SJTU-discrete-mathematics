#include "common.h"
#include <iostream>
using namespace Minisat;

bool lab1(int states[], int n, int button[][2], int m, bool answer[])
{
    Solver solver;
    Var variables[1000];
    int i, j;
    for (i = 0; i < m; ++i)
        variables[i] = solver.newVar();

    // your solution start from here.
    // TODO: your code here

    int stone_swith_map[n][2];
    int k = 0, a, b;

    // initialize all to -1
    for (int i = 0; i < n; i++)
        for (int j = 0; j < 2; j++)
            stone_swith_map[i][j] = -1;

    // populate mapping: for each stone list controlling switches, if has no 2ed switch, assign -1
    for (i = 0; i < n; ++i){
        k = 0;
        for (j = 0; j < m; ++j){
            if (button[j][0] - 1 == i)
                stone_swith_map[i][k++] = j;
            if (button[j][1] - 1 == i)
                stone_swith_map[i][k++] = j;
        }
    }
    // populate solver
    for (i = 0; i < n; ++i){
        a = stone_swith_map[i][0];
        if (stone_swith_map[i][1] != -1){
            b = stone_swith_map[i][1];
            if (states[i]){
                // (a^b) V (~a^~b) <=> NXOR <=> (a V ~b) ^ (~a V b)
                solver.addClause(mkLit(variables[a]), ~mkLit(variables[b]));
                solver.addClause(~mkLit(variables[a]), mkLit(variables[b]));
            }
            else{
                //  (a ^ ~b) V  (~a ^ b) <=> XOR <=> (~a V ~b) ^ (a V b)
                solver.addClause(mkLit(variables[a]), mkLit(variables[b]));
                solver.addClause(~mkLit(variables[a]), ~mkLit(variables[b]));
            }
        }
        else{
            if (states[i])
                solver.addClause(~mkLit(variables[a])); // ~a
            else
                solver.addClause(mkLit(variables[a])); // a
        }
    }

    // your solution end here.
    // solve SAT problem
    auto sat = solver.solve();
    if (sat)
    {
        for (i = 0; i < m; ++i)
            answer[i] = (solver.modelValue(variables[i]) == l_True);
        return true;
    }
    return false;
}