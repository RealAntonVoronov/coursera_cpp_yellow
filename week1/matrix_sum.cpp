#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

// Реализуйте здесь
class Matrix{
public:
    Matrix(){
        n_rows = 0;
        n_cols = 0;
    }
    Matrix(int num_rows, int num_cols){
        Reset(num_rows, num_cols);
    }
    void Reset(int num_rows, int num_cols){
        if (num_rows > 0 and num_cols > 0){
            n_rows = num_rows;
            n_cols = num_cols;
            matrix.assign(n_rows, vector<int>(num_cols));
        }
        else if (num_rows == 0 or num_cols == 0){
            n_rows = n_cols = 0;
        }
        else throw out_of_range("");
    }
    int At (int i_row, int j_col) const {
        if (i_row >= n_rows or i_row < 0 or j_col < 0 or j_col >= n_cols){
            throw out_of_range("out of range");
        }
        else return matrix.at(i_row).at(j_col);
    }
    int& At (int i_row, int j_col) {
        if (i_row >= n_rows or i_row < 0 or j_col < 0 or j_col >= n_cols){
            throw out_of_range("out of range");
        }
        else return matrix.at(i_row).at(j_col);
    }
    int GetNumRows() const{
        return n_rows;
    }
    int GetNumColumns() const {
        return n_cols;
    }
private:
    int n_rows, n_cols;
    vector<vector<int>> matrix;
};
// * оператор ввода для класса Matrix из потока istream
istream& operator >> (istream& stream, Matrix& m){
    int n_rows, n_cols;
    stream >> n_rows >> n_cols;
    m = Matrix(n_rows, n_cols);
    for (int i = 0; i < n_rows; i++){
        for (int j = 0; j < n_cols; j++){
            int m_ij;
            stream >> m_ij;
            m.At(i, j) = m_ij;
        }
    }
    return stream;
}
// * оператор вывода класса Matrix в поток ostream
ostream& operator << (ostream& stream, const Matrix& m){
    int n_rows = m.GetNumRows();
    int n_cols = m.GetNumColumns();
    stream << n_rows << " " << n_cols << endl;
    for (int i = 0; i < n_rows - 1; i++){
        for (int j = 0; j < n_cols - 1; j++){
            stream << m.At(i, j) << " ";
        }
        stream << m.At(i, n_cols - 1) << endl;
    }
    for (int j = 0; j < n_cols - 1; j++){
        stream << m.At(n_rows - 1, j) << " ";
    }
    stream << m.At(n_rows - 1, n_cols - 1);
    return stream;
}
// * оператор проверки на равенство двух объектов класса Matrix
bool operator == (const Matrix& lhs, const Matrix& rhs){
    if (lhs.GetNumRows() != rhs.GetNumRows() or lhs.GetNumColumns() != rhs.GetNumColumns()){
        return false;
    }
    else{
        int n_rows = lhs.GetNumRows();
        int n_cols = lhs.GetNumColumns();
        for (int i = 0; i < n_rows; i++){
            for (int j = 0; j < n_cols; j++){
                if (lhs.At(i, j) != rhs.At(i, j)){
                    return false;
                }
            }
        }
        return true;
    }
}
// * оператор сложения двух объектов класса Matrix
Matrix operator + (const Matrix& lhs, const Matrix& rhs){
    if (lhs.GetNumRows() != rhs.GetNumRows()){
        throw invalid_argument("n_rows is not equal");
    }
    else if (lhs.GetNumColumns() != rhs.GetNumColumns()){
        throw invalid_argument("n_cols is not equal");
    }
    else{
        int n_rows = lhs.GetNumRows();
        int n_cols = lhs.GetNumColumns();
        Matrix res(n_rows, n_cols);
        for (int i = 0; i < n_rows; i++){
            for (int j = 0; j < n_cols; j++){
                res.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
            }
        }
        return res;
    }
}