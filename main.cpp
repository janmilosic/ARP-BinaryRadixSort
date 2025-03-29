#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

bool Branje_Stevil(vector<int> &vec, const char s[]) {
    ifstream input(s);
    int st;

    if (!input.is_open()) {
        return false;
    }

    while (!input.eof()) {
        input >> st;
        vec.push_back(st);
        while (isspace(input.peek())) input.get();
    }
    input.close();
    return true;
}

void Izpis_Stevil(int* polje, unsigned int velikost) {
    ofstream output("out.txt");

    for (int i = 0; i<velikost; i++)
        output << polje[i] << ' ';
}

vector<int> Counting_Sort(const vector<int>& D, const vector<int>& index) {
    vector<int> count(2, 0);
    vector<int> output_index(D.size());

    for (int bit : D) {
        count[bit]++;
    }

    count[1] = count[0];
    count[0] = 0;

    for (int i = 0; i < D.size(); ++i) {
        int bit = D[i];
        output_index[count[bit]] = index[i];
        count[bit]++;
    }

    return output_index;
}

vector<int> Radix_Sort(const vector<int>& A) {
    vector<int> current = A;

    for (int bit = 0; bit < 8; ++bit) {
        vector<int> D(current.size());
        vector<int> index(current.size());

        for (int i = 0; i < current.size(); ++i) {
            D[i] = (current[i] >> bit) & 1;
            index[i] = i;
        }

        vector<int> sorted_index = Counting_Sort(D, index);

        vector<int> next(current.size());
        for (int i = 0; i < current.size(); ++i) {
            next[i] = current[sorted_index[i]];
        }
        current = next;
    }
    return current;
}

int main(int argc, const char* argv[]) {
    vector<int> A;

    if (argc < 2) return 0;
    if (!Branje_Stevil(A, argv[1])) return 0;

    Izpis_Stevil(&A[0], A.size());

    return 0;
}
