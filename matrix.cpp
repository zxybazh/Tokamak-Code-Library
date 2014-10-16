class Matrix{
    public:
        LL a[2][2];
        Matrix(){
            memset(a, 0, 32);
        }
        LL* operator[](int i){
            return a[i];
        }
        const LL* operator[](int i) const{
            return a[i];
        }
};
   
Matrix operator *(const Matrix &a, const Matrix &b){
    Matrix c;
    fo(i, 0, 1) fo(j, 0, 1) fo(k, 0, 1)
    c[i][j] = (c[i][j] + a[i][k] * b[k][j] % m) % m;
    return c;
}
   
class Nanomat{
    public:
        LL a[2];
        Nanomat(){
            memset(a, 0, 16);
        }
        LL& operator[](int i){
            return a[i];
        }
        const LL& operator[](int i) const{
            return a[i];
        }
};
   
Nanomat operator *(const Nanomat &a, const Matrix &b){
    Nanomat c;
    fo(i, 0 ,1) fo(j, 0, 1)
        c[i] = (c[i] + a[j] * b[j][i] % m) % m;
    return c;
}