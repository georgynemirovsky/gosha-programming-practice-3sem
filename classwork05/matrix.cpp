#include <iostream>
template<typename Field, int M, int  N>//M - число солбцов, N - число строк
class Matrix
{
public:
    Field **matrix;
    Matrix()
    {
        matrix = new Field* [N];
        for (int i = 0; i < N; i++)
        {
            matrix[i] = new Field [M];
        }

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                matrix[i][j] = 0;
            }
        }
    }

    Matrix(Field* arr)
    {
        matrix = new Field* [N];
        for (int i = 0; i < N; i++)
        {
            matrix[i] = new Field [M];
        }

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                matrix[i][j] = arr[j + M * i];
            }
        }
    }

    ~Matrix()
    {
        for (int i = 0; i < N; i++)
        {
            delete [] matrix[i];
        }
        delete [] matrix;
    }

    void print()
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << '\n';
        }
    }

    Matrix<Field, M, N> operator+(const Matrix<Field, M, N>& rha)
    {
        Field* temp = new Field [N * M];
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                temp[j + i * M] = matrix[i][j] + rha.matrix[i][j];
            }
        }
        return Matrix (temp);
    }

    Matrix<Field, M, N> operator-(const Matrix<Field, M, N>& rha)
    {
        Field* temp = new Field [N * M];

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                temp[j + i * M] = matrix[i][j] - rha.matrix[i][j];
            }
        }
        return (Matrix (temp));
    }

    void operator=(const Matrix<Field, M, N>& rha)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                matrix[i][j] = rha.matrix[i][j];
            }
        }
    }
};

template<typename Field, int M, int N, int K>
Matrix<Field, M, K> operator*(const Matrix<Field, N, M>& lha, const Matrix<Field, K, N>& rha)
{
    Matrix<Field, M, K> res;

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < K; j++)
        {
            Field sum = 0;
            for (int k = 0; k < N; k++)
            {
                sum += lha.matrix[i][k] * rha.matrix[k][j];
            }
            res.matrix[i][j] = sum;
        }
    }
    return res;
}

int main()
{
    int *arr = new int [12];
    for (int i = 0; i < 12; i++)
    {
        arr[i] = i;
    }
    Matrix<int, 4, 3> matr(arr);
    Matrix<int, 4, 3> matr2(arr);
    Matrix<int, 3, 4> matr3(arr);
    std::cout << "matr = matr2" << '\n';
    matr2.print();
    std::cout << '\n' << "matr3" << '\n';
    matr3.print();
    std::cout << '\n' << "matr + matr2" << '\n';
    (matr + matr2).print();
    std::cout << '\n' << "matr - matr2" << '\n';
    (matr - matr2).print();
    std::cout << '\n' << "matr * matr3" << '\n';
    (matr * matr3).print();
    delete [] arr;
    return 0;
}
