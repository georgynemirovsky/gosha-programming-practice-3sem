#include <iostream>
#include <cmath>

using namespace std;


class Matrix {
    public:
        Matrix(double arr[], size_t n_elements) {
            int s = 0;
            size = int(sqrt(n_elements));
            mat = new double* [size];
            for (int i = 0; i < size; i++) {
                mat[i] = new double[size];
            }
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    mat[i][j] = arr[s];
                    s++;
                }
            }// Заполнение матрицы из массива
        }

        Matrix(int element, size_t n_elements) {
            size = int(sqrt(n_elements));
            mat = new double* [size];
            for (int i = 0; i < size; i++) {
                mat[i] = new double[size];
            }
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    mat[i][j] = element;
                }
            }
        }

        Matrix() : Matrix(1, 1){
            // Определить конструктор по умолчанию, как матрицу размера 1 с элементом равным 1
        }

        Matrix(const Matrix& other) {
            this->mat = new double* [size];
            for (int i = 0; i < size; i++) {
                this->mat[i] = new double [size];
            }
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    this->mat[i][j] = mat[i][j];
                }
            }
            // Определить копирующий конструктор
        }

        void printMatrix() {
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    cout << mat[i][j] << " ";
                }
                cout << "\n";
            }
            // Вывести матрицу: каждое значение в строке разделено пробелом, строки отделены \n
        }

        int calcDeterminant() {
            double tmp, d;
            double** mat_help = new double* [size];
            for (int i = 0; i < size; i++) {
                mat_help[i] = new double[size];
            }

            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    mat_help[i][j] = mat[i][j];
                }
            }
            for (int k = 0; k < size - 1; k++) {
                for (int i = k + 1; i < size; i++) {
                    tmp = -mat_help[i][k] / mat_help[k][k];
                    for (int j = 0; j < size; j++) {
                        mat_help[i][j] += mat_help[k][j] * tmp;
                    }
                }
            }
            d = 1;
            for (int i = 0; i < size; i++) {
                d *= mat_help[i][i];
            }
            for (int i = 0; i < size; i++) {
                delete [] mat_help[i];
            }
            delete [] mat_help;
            return d;
            // Вычислить детерминант
        }

        void calcSquare() {
            double** mat_help = new double* [size];
            for (int i = 0; i < size; i++) {
                mat_help[i] = new double[size];
            }

            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    mat_help[i][j] = mat[i][j];
                }
            }
            double s = 0;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    s = 0;
                    for (int m = 0; m < size; m++) {
                        s += mat_help[m][j] * mat_help[i][m];
                    }
                    mat[i][j] = s;
                }
            }
            for (int i = 0; i < size; i++) {
                delete [] mat_help[i];
            }
            delete [] mat_help;
            // Вычислить квадрат матрицы, результат оставить в том же экземпляре класса
        }

        void matTranspose() {
            double** mat_help = new double* [size];
            for (int i = 0; i < size; i++) {
                mat_help[i] = new double[size];
            }

            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    mat_help[i][j] = mat[i][j];
                }
            }
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    mat[i][j] = mat_help[j][i];
                }
            }
            for (int i = 0; i < size; i++) {
                delete [] mat_help[i];
            }
            delete [] mat_help;
            // Осуществляет транспонирование матрицы, результат сохраняется тут же
        }

        ~Matrix() {
            for (int i = 0; i < size; i++) {
                delete [] mat[i];
            }
            delete [] mat;
            // Определить деструктор
        }

    private:
        double** mat;  // массив для хранения значений матрицы
        int size;  // размер стороны матрицы
};


int main () {
    double arr[9] = {1, -1, 1, 2, 1, 1, 1, 1, 2};
    Matrix matr(arr,9);
    matr.printMatrix();
    cout << matr.calcDeterminant() << endl;
    matr.calcSquare();
    matr.printMatrix();
    matr.matTranspose();
    matr.printMatrix();
    return 0;
}
