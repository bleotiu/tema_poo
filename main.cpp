#include <iostream>
#include <fstream>
//#include "Vector.cpp"
using namespace std;

int modul (const int & x){
    if (x < 0)
        return -x;
    return x;
}

///Vector
class Vector {
    int capacity,length;
    int *p;
public:
    ///constructors
    Vector (int n = 0){
        capacity = n;
        length = n;
        p = new int[capacity];
        for (int i = 0; i < capacity; ++i)
            p[i] = 0;
    }
    Vector (int n,const int *v){
        capacity = n;
        length = n;
        p = new int[n];
        for (int i = 0; i < length; ++i)
            p[i] = v[i];
    }
    Vector (const Vector& v){
        capacity = v.capacity;
        length = v.length;
        p = new int[capacity];
        for (int i = 0 ; i < v.length; ++i)
            p[i] = v.p[i];
    }
    ///destructor
    ~Vector (){
        capacity = 1;
        length = 0;
        delete[] p;
    }
    ///copy
    Vector& operator = (const Vector&v){
        if (v.p == p)
            return *this;
        delete[]p;  ///eliberare memorie veche
        capacity = v.capacity;
        length = v.length;
        p = new int[capacity];
        for (int i = 0; i < length; ++i)
            p[i] = v.p[i];
        return *this;
    }
    int & operator [] (int pos){
        if (pos < capacity)
            return p[pos];
        //else
        //eroare
    }

    bool operator == (const Vector &v){
        if (length != v.length)
            return false;
        for (int i = 0; i < length; ++i)
            if (p[i] != v.p[i])
                return false;
        return true;
    }
    bool operator != (const Vector & v){
        return !(*this == v);
    }
    bool operator < (const Vector & v){
        if (length < v.length)
            return true;
        if (length == v.length){
            int i = 0;
            while (i < length && p[i] == v.p[i])
                ++i;
            if (i < length && p[i] < v.p[i])
                return true;
        }
        return false;
    }
    int GetSize (){
        return capacity;
    }
    void SetSize (int n){
        delete[] p;
        length = capacity = n;
        p = new int [n];
        for (int i = 0; i < capacity; ++i)
            p[i] = 0;
    }
    int Sum (){
        int S = 0;
        for (int i = 0; i < length; ++i)
            S += p[i];
        return S;
    }
    int AbsSum (){
        int S = 0;
        for (int i = 0; i < length; ++i)
            S += modul (p[i]);
        return S;
    }
    int Max (int &pos){
        if (length < 1){ ///maximul pe vector nul
            pos = -1;
            return 0;
        }
        int mx = p[0];
        pos = 0;
        for (int i = 1; i < length; ++i)
            if (mx < p[i]){
                mx = p[i];
                pos = i;
            }
        return mx;
    }
    void Sort (){
        if (length < 2) ///nu are ce sorta
            return;
        int i,j;
        for (i = 0; i < length; ++i)
            for (j = i + 1; j < length; ++j)
                if (p[i] > p[j])
                    swap (p[i],p[j]);
    }

    friend istream& operator>> (istream &input,Vector& v);
    friend ostream& operator << (ostream &output, const Vector& v);
    friend class Matrix;
    friend Matrix operator * (Vector & v, Vector & w);
    friend Vector operator * (const int & x, Vector & v);
    friend Vector operator * (const Vector & v,const int & x);
    friend Vector operator * (Vector & v, Matrix & m);
    friend Vector operator * (Matrix & m, Vector & v);
};

///citire vector
istream & operator>>(istream &input, Vector& v) {
    if(!v.length || v.AbsSum() > 0){ //vector neinitializat sau vector cu elemente in el
       // if(v.AbsSum() > 0)
         //   cout << v;
        int n;
        input >> n;
        v.capacity = n;
        v.length = n;
    }
    delete []v.p;
    v.p = new int[v.length];
    for (int i = 0; i < v.length; ++i)
        input >> v.p[i];
    return input;
}

///afisare vector
ostream& operator << (ostream &output,const Vector& v) {
    //output << "Vectorul are " << v.capacity << "elemente si este : " ;
    for (int i = 0; i < v.length; ++i)
        output << v.p[i] << ' ';
    output << '\n';
    return output;
}

///Matrix
class Matrix{
    int r,c;
    Vector *m;
public:
    Matrix (int N = 0, int M = 0){
        r = N;
        c = M;
        m = new Vector[r];
        for (int i = 0 ;i < N; ++i){
            Vector *curr = new Vector (M);
            m[i] = *curr;
            delete curr;
        }
    }
    Matrix (int N, int M, int* cnt[]){
        r = N;
        c = M;
        m = new Vector[N];
        int i,j;
        for (i = 0 ;i < N; ++i){
            Vector *curr = new Vector (M);
            m[i] = *curr;
            delete curr;
        }
        for (i = 0; i < N; ++i)
            for (j = 0; j < M; ++j)
                m[i][j] = cnt[i][j];
    }
    Matrix (Vector & v, Vector & w){
        r = v.capacity;
        c = w.capacity;
        m = new Vector[r];
        int i;
        for (i = 0 ; i < r; ++i)
            m[i] = w * v[i];
    }
    Matrix (const Matrix & M){
        r = M.r;
        c = M.c;
        m = new Vector[r];
        for (int i = 0; i < r; ++i)
            m[i] = M.m[i];
    }
    ~Matrix (){
        /// ???? merge bine oare?
        for (int i = 0; i < r; ++i){
       //     delete [] m[i].p;//~Vector();
        }
        delete []m;
    }
    Matrix& operator = (const Matrix & M){
        if (m == M.m)
            return *this;
        r = M.r;
        c = M.c;
        /*for (int i = 0; i < r; ++i){
            delete [] m[i].p;
        }*/
        delete []m;
        m = new Vector[r];
        for (int i = 0; i < r; ++i)
            m[i] = M.m[i];
        return *this;
    }
    Vector & operator [] (int pos){
        if(pos < r)
            return m[pos];
        //else
        //eroare
    }
    Vector operator [] (int pos) const{
        if(pos < r)
            return m[pos];
        //else
        //eroare
    }
    Matrix operator + (const Matrix & M){
        if (r == M.r && c == M.c){
            Matrix rez (r,c);
            int i,j;
            for (i = 0 ; i  < r; ++i)
                for (j = 0 ; j < c; ++j)
                    rez[i][j] = m[i][j] + M[i][j];
            return rez;
        }
        //else
        //eroare
    }

    bool operator == (const Matrix & M){
        if (r != M.r || c != M.c)
            return false;
        for (int i = 0; i < r; ++i)
            if (m[i] != M.m[i])
                return false;
        return true;
    }

    bool operator != (const Matrix & M){
        return !(*this == M);
    }

    bool operator < (const Matrix & M){
        if (r * c < M.r * M.c)
            return true;
        return false;
    }
    int GetRows (){
        return r;
    }
    int GetColumns (){
        return c;
    }
    friend istream & operator >> (istream & input, Matrix & m);
    friend ostream & operator << (ostream & output, const Matrix & m);
    friend Matrix operator * (const int & x, Matrix & M);
    friend Matrix operator * (Matrix & M, const int & x);
    friend bool ecuatie (Matrix & A, Vector & X, Vector & Y);
};

///citire matrice
istream & operator >> (istream & input, Matrix & m){
    input >> m.r >> m.c;
    delete[] m.m;
    m.m = new Vector[m.r];
    for (int i= 0; i < m.r; ++i) {
        m[i].SetSize(m.c);
        input >> m[i];
    }
    return input;
}

///afisare matrice
ostream & operator << (ostream & output,const Matrix & m){
    output << m.r << ' ' << m.c << '\n';
    for (int i = 0; i < m.r; ++i)
        output << m[i];
    return output;
}

/// vector * scalar
Vector operator * (const int & x,Vector & v){
    Vector curr (v);
    for (int i = 0 ;i < v.capacity; ++i)
        curr[i] = x * v[i];
    return curr;
}

Vector operator * (const Vector & v,const int & x){
    Vector curr (v);
    for (int i = 0 ;i < v.capacity; ++i)
        curr[i] = x * curr[i];
    return curr;
}

///vector * vector
Matrix operator * (Vector & v, Vector & w){
    Matrix result(v.capacity,w.capacity);
    int i,j;
    for (i = 0; i < v.capacity; ++i)
        for (j = 0 ; j < w.capacity; ++j)
            result[i][j] = v[i] * w[j];
    return result;
}

///vector * matrice
Vector operator * (Vector & v, Matrix & m){
    int N = m.GetRows(), M = m.GetColumns();
    if (v.capacity == N){
        Vector result (M);
        int i,j;
        for (i = 0; i < M; ++i){
            for (j = 0; j < N; ++j)
                result[i] += v[j] * m[j][i];
            return result;
        }
    }
    //else
    //eroare
}

Vector operator * (Matrix & m, Vector & v){
    int N = m.GetRows(), M = m.GetColumns();
    if (v.capacity == M){
        Vector result (N);
        int i,j;
        for (i = 0; i < N; ++i){
            for (j = 0; j < M; ++j)
                result[i] += v[j] * m[i][j];
        }
        return result;
    }
    //else
    //eroare
}

/// scalar * Matrice
Matrix operator * (const int & x, Matrix & M){
    Matrix rezultat (M);
    for (int i = 0; i < M.r; ++i)
        rezultat[i] = x * rezultat[i];
    return rezultat;
}

Matrix operator * (Matrix & M, const int & x){
    Matrix rezultat (M);
    for (int i = 0; i < M.r; ++i)
        rezultat[i] = x * rezultat[i];
    return rezultat;
}

///Ecuatie AX = Y, unde A = matrice mxn si X = vector n, Y = vector m
bool ecuatie (Matrix & A, Vector & X, Vector & Y){
    if (A.c != X.GetSize() || A.r != Y.GetSize())
        return false;
    Vector rezultat = A * X;
    //cout << rezultat << Y;
    return (rezultat == Y);
}

int main() {
    ifstream fin ("input");
    ofstream fout ("output");
    Vector a,b;
    int n,i;
    fin >> a >> b;
    fout << a << b;
    Matrix c;
    fin >> c;
    c = c + c;
    cout << c << a << b;
    if (ecuatie(c,a,b))
        cout << "DA\n";
    else
        cout << "NU\n";
    int x=5,y=4;
    //cout << c * x + c << c;
    fin >> a;
    cout << a;
    a = a * a * a;
    cout << a;
    fin >> c;
    cout << c;
    return 0;
}