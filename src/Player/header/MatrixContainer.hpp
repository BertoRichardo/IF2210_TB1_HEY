#ifndef _MATRIXCONTAINER_HPP_
#define _MATRIXCONTAINER_HPP_

using namespace std;
#include <iostream>
#include <string>
#include <vector>

template <class T>
class MatrixContainer
{
private:
    int rowSize;
    int colSize;
    vector<vector<T>> buffer;

public:
    /**
     * User Defined Constructor
     * @param r ukuran row
     * @param c ukuran column
     */
    MatrixContainer(int r, int c)
    {
        buffer.resize(r);
        for (int i = 0; i < r; ++i)
        {
            buffer[i].resize(c);
        }
    }

    /**
     * Destructor
     */
    ~MatrixContainer()
    {
    }

    /* SELECTOR */
    /**
     * Menambahakan item pada matrix[r][c]
     * @param r row
     * @param c column
     * @param T item
     */
    void addItem(int r, int c, T item)
    {
        if (isCellEmpty(r, c))
        {
            buffer[r][c] = item;
        }
        else
        {
            /**
             * -TODO: throw
             */
        }
    }

    /**
     * Mendapatkan item dari matrix[r][c]
     * @param r row
     * @param c column
     * @return Item pada cell tersebut : T
     */
    T getItem(int r, int c)
    {
        if (!isCellEmpty(r, c))
        {
            return buffer[r][c];
        }
        else
        {
            return buffer[r][c];
            /**
             * -TODO: throw
             */
        }
    }

    /**
     * Menghapus item dari matrix[r][c]
     * @param r row
     * @param c column
     */
    void removeItem(int r, int c)
    {
        if (!isCellEmpty(r, c))
        {
            int start = c;
            int end = c + 1;
            buffer[r].erase(std::next(buffer[r].begin(), start), std::next(buffer[r].begin(), end));
        }
        else
        {
            /**
             * -TODO: throw
             */
        }
    }

    /**
     * Mengecek cell matrix[r][c] kosong atau tidak
     * @param r row
     * @param c column
     * @return cell matrix berisi atau kosong : boolean
     */
    bool isCellEmpty(int r, int c)
    {
        return buffer[r][c].isEmpty();
    }

    void printMatrix()
    {
        for (int i = 0; i < rowSize; i++)
        {

            for (int j = 0; j < colSize; j++)
            {
                cout << "+---";
            }
            cout << "+";
            for (int j = 0; j < colSize; j++)
            {
                cout << "|" << buffer[i][j].getKodeHuruf();
            }
            cout << "|";
        }
        for (int j = 0; j < colSize; j++)
        {
            cout << "+---";
        }
        cout << "+";
    }
};

#endif
