#ifndef _MATRIXCONTAINER_HPP_
#define _MATRIXCONTAINER_HPP_

using namespace std;
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
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
     * Default Constructor
     */
    MatrixContainer()
    {
        rowSize = 0;
        colSize = 0;
        buffer.resize(0);
    }

    /**
     * User Defined Constructor
     * @param r ukuran row
     * @param c ukuran column
     */
    MatrixContainer(int r, int c)
    {
        rowSize = r;
        colSize = c;
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
     * Mendapatkan item dari matrix[r][c]
     * @param r row
     * @param c column
     * @return Item pada cell tersebut : T
     */
    T getItem(string koordinat)
    {
        // Cari nilai kolom
        int i = 0;
        int c = 0;
        if (koordinat[i] < 'A' || koordinat[i] > 'Z')
        {
            /**
             * TODO: Throw invalidInput
             */
        }
        else
        {
            while (koordinat[i] >= 'A' && koordinat[i] <= 'Z')
            {
                c += c * 10 + koordinat[i] - 'A';
                i++;
            }
        }

        // Cari nilai baris
        int r = 0;
        for (int j = i; j < koordinat.length(); i++)
        {
            // Cek
            if (koordinat[i] >= '0' && koordinat[i] <= '9')
            {
                r += r * 10 + koordinat[i] - '0';
            }
            else
            {
                /**
                 * TODO: throw invalidInput
                 */
            }
        }

        return getItem(r, c);
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
        cout << rowSize << endl;
        cout << colSize << endl;
        char c = 'A';
        int idx = 0;
        for (int j = 0; j < colSize; j++)
        {
            if (j == 0)
            {
                cout << "   ";
            }
            if (idx <= 25)
            {
                cout << "   " << char(c + idx) << "  ";
            }
            else
            {
                char front = c + (((idx / 26) - 1) % 26);
                char back = c + (idx % 26);
                cout << "  " << front << back << "  ";
            }
            idx++;
        }
        cout << endl;
        for (int i = 0; i < rowSize; i++)
        {
            for (int j = 0; j < colSize; j++)
            {
                if (j == 0)
                {
                    cout << "   ";
                }
                cout << "+-----";
            }
            cout << "+" << endl;
            for (int j = 0; j < colSize; j++)
            {
                if (j == 0)
                {
                    cout << setfill('0') << setw(2) << i + 1 << " ";
                }
                if (buffer[i][j].getKodeHuruf() == "")
                {
                    cout << "|"
                         << "     ";
                }
                else
                {
                    cout << "| " << buffer[i][j].getKodeHuruf() << " ";
                }
            }
            // cout << "|  " << i + 1 << endl;
            cout << "|" << endl;
        }
        for (int j = 0; j < colSize; j++)
        {
            if (j == 0)
            {
                cout << "   ";
            }
            cout << "+-----";
        }
        cout << "+";
        cout << endl;
    }
};

#endif
