#include <iostream>
#include <time.h> 


using namespace std;

void p(int** m) {

    for (int i = 0; i < _msize(m) / sizeof(int); i++) {
        for (int j = 0; j < _msize(m) / sizeof(int); j++) {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
}

int** create_matrix(int size, int percent) {

    int** mat = new int*[size];
    srand(time(NULL));
    for (int i = 0; i < size; ++i) {
        mat[i] = new int[size];

        for (int j = 0; j < size; ++j) {
            if ((rand() % 100) < percent) {
                mat[i][j] = 1;
            }
            else {
                mat[i][j] = 0;
            }
        }
    }
    return mat;
}

void swap_row(int**& m, int r1,int r2) {

    if ((r1 < _msize(m) / sizeof(int)) && (r2 < _msize(m) / sizeof(int))) {
        int* temp = m[r1];
        m[r1] = m[r2];
        m[r2] = temp;
    }
}
void swap_collumn(int**& m, int c1, int c2) {

    if ((c1 < _msize(m) / sizeof(int)) && (c2 < _msize(m) / sizeof(int))) {
        for (int i = 0; i < _msize(m) / sizeof(int); i++) {
            int temp = m[i][c1];
            m[i][c1] = m[i][c2];
            m[i][c2] = temp;
        }
    }
}

int min_row(int**& m, int from) {

    int min = INT_MAX;
    int row = 0;
    for (int i = from; i < _msize(m) / sizeof(int); i++) {
        int temp = 0;
        for (int j = from; j < _msize(m) / sizeof(int); j++) {
            if (m[i][j] == 1)
                temp++;
        }
        if (temp <= min) {
            min = temp;
            row = i;
        }
    }

    return row;
}

int max_collumn(int**& m,int from) {

    int max = INT_MIN;
    int collumn = 0;
    for (int i = from; i < _msize(m) / sizeof(int); i++) {
        if (m[from][i] == 1) {
            int temp = 0;
            for (int j = from; j < _msize(m) / sizeof(int); j++) {
                if (m[j][i] == 1)
                    temp++;
            }
            if (temp >= max) {
                max = temp;
                collumn = i;
            }
        }
    }

    return collumn;
}

void swap(int*& m,int el1,int el2) {
    if ((el1 < _msize(m) / sizeof(int)) && (el2 < _msize(m) / sizeof(int))) {
        int temp = m[el1];
        m[el1] = m[el2];
        m[el2] = temp;
    }
}

void replace(int**& m) {
    int* row = new int[_msize(m) / sizeof(int)];
    int* col = new int[_msize(m) / sizeof(int)];


    for (int i = 0; i < _msize(m) / sizeof(int); i++) {
        row[i] = i + 1;
        col[i] = i + 1;
    }

    for (int i = 0; i < _msize(m) / sizeof(int); i++) {
        int r = min_row(m, i);
        swap(row, i, r);
        swap_row(m,i, r);
        int c = max_collumn(m, i);
        swap(col, i, c);
        swap_collumn(m, i, c);
    }
    cout << "  ";
    for (int i = 0; i < _msize(m) / sizeof(int); i++) {
        cout << row[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < _msize(m) / sizeof(int); i++) {
        cout << col[i] << " ";
        for (int j = 0; j < _msize(m) / sizeof(int); j++) {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
}
void replace_w(int**& m) {


    for (int i = 0; i < _msize(m) / sizeof(int); i++) {
        swap_row(m, i, min_row(m, i));
        swap_collumn(m, i, max_collumn(m, i));
    }

}



bool check_conflicts(int**& m, int r, int c) {
    bool conflicts = false;

    for (int j = c+1; j < _msize(m) / sizeof(int); j++) {
        if (r<j) {
            if (m[j][r] == 1) {
                conflicts = true;
                m[j][r] = 0;
            }
        }
    }
    
    return conflicts;
}
void find_zero_matrix(int**& m) {
    int best = 0;
    int temp;
    bool conflicts = false;
    for (int i = 0; i < _msize(m) / sizeof(int); i++) {
        temp = i;
        for (int j = i; j < _msize(m) / sizeof(int); j++) {
            if (m[i][j] == 1) {
                temp = j;
            }
        }
        if (temp > best) {
            best = temp;
        }

        if (conflicts == false) {
            conflicts = check_conflicts(m, i, best);
        } else 
        check_conflicts(m, i, best);
    }
    
    if (conflicts) {
        cout << "Matrix has conflicts!\n";

    }else  cout << "Matrix does not have conflicts!\n";

}


bool find_zero_matrix_short(int**& m) {
    int best = 0;
    int temp;

    for (int i = 0; i < _msize(m) / sizeof(int); i++) {
        temp = i;
        for (int j = i; j < _msize(m) / sizeof(int); j++) {
            if (m[i][j] == 1) {
                temp = j;
            }
        }
        if (temp > best) {
            best = temp;
        }

        if (check_conflicts(m, i, best)) return true;
    }
    return false;
}

void test_0() {
    while (true) {
        int size;
        int percent;
        cin >> size;
        cin >> percent;

        int** mat = create_matrix(size, percent);

        p(mat);
        cout << endl;

        replace_w(mat);
        p(mat);
        find_zero_matrix(mat);

        cout << endl;
        p(mat);
    }
};

void test_1() {
    int size;
    int percent;
    cin >> size;
    cin >> percent;
    double d = 0;
    for (int i = 0; i < 100; i++) {
        int** mat = create_matrix(size, percent);
        replace_w(mat);
        if (find_zero_matrix_short(mat))
            d++;

    }
    cout << d / 100;
    cout << endl;
};

void test_2() {
    int size;
    cin >> size;
    double d;
    for (int n = 0; n < 100; n++) {
        d = 0;
        for (int i = 0; i < 100; i++) {
            int** mat = create_matrix(size, n);
            replace_w(mat);
            if (find_zero_matrix_short(mat))
                d++;
        }
        cout << n << "%=> " << d/100 << "||";

    }
    cout << endl;
};

void test_3() {
    int size = 10;
    for (int n = 10; n <= 30; n=n+5) {
        for (int i = 0; i < 100; i++) {
            int** mat = create_matrix(size, i);
            replace_w(mat);
            if (find_zero_matrix_short(mat))
                cout << "1, ";
            else cout << "0, ";

        }

        cout << endl;
        cout << endl;
    }
};
int main()
{
    test_2();
    system("pause");

}

/*
 mat = {
     {1,	0,	1,	0,	1,	0},
     {0,	1,	1,	1,	1,	1},
     {1,	0,	1,	1,	1,	0},
     {1,	1,	1,	1,	0,	1},
     {1,	0,	1,	0,	1,	0},
     {1,	0,	1,	0,	1,	0}
 };*/