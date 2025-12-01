#include <bits/stdc++.h>
using namespace std;

unordered_map<char, vector<string>> g;
unordered_map<char, set<char>> FIRST, FOLLOW;
set<char> nonterm, term;
char startSymbol;

// FIRST set for a symbol X (terminal or nonterminal)
set<char> first(char X) {
    if (islower(X) || X == '#') return {X};

    if (!FIRST[X].empty()) return FIRST[X];

    set<char> res;
    for (auto &prod : g[X]) {
        bool allNullable = true;
        for (auto &c : prod) {
            set<char> t = first(c);
            for (char x : t) if (x != '#') res.insert(x);
            if (t.find('#') == t.end()) {
                allNullable = false;
                break;
            }
        }
        if (allNullable) res.insert('#');
    }
    FIRST[X] = res;
    return res;
}

void computeFOLLOW() {
    FOLLOW[startSymbol].insert('$');

    bool changed = true;
    while (changed) {
        changed = false;
        for (auto &[A, prods] : g) {
            for (auto &prod : prods) {
                int n = prod.size();
                for (int i = 0; i < n; i++) {
                    char B = prod[i];
                    if (!nonterm.count(B)) continue;

                    bool nullableSuffix = true;
                    for (int j = i + 1; j < n; j++) {
                        char C = prod[j];
                        auto f = first(C);

                        for (char x : f)
                            if (x != '#')
                                if (FOLLOW[B].insert(x).second) changed = true;

                        if (f.find('#') == f.end()) {
                            nullableSuffix = false;
                            break;
                        }
                    }

                    if (nullableSuffix) {
                        for (char x : FOLLOW[A])
                            if (FOLLOW[B].insert(x).second) changed = true;
                    }
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        char A;
        string arrow, rhs;
        cin >> A >> arrow >> rhs;

        g[A].push_back(rhs);
        nonterm.insert(A);
        for (char c : rhs)
            if (islower(c) || c == '#') term.insert(c);
            else if (isupper(c)) nonterm.insert(c);
    }

    startSymbol = *nonterm.begin();

    // compute FIRST
    for (char A : nonterm) first(A);

    // compute FOLLOW
    computeFOLLOW();

    cout << "FIRST sets:\n";
    for (char A : nonterm) {
        cout << A << " : { ";
        for (char c : FIRST[A]) cout << c << " ";
        cout << "}\n";
    }

    cout << "\nFOLLOW sets:\n";
    for (char A : nonterm) {
        cout << A << " : { ";
        for (char c : FOLLOW[A]) cout << c << " ";
        cout << "}\n";
    }

    return 0;
}
