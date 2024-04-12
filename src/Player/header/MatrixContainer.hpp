#ifndef _MATRIXCONTAINER_HPP_
#define _MATRIXCONTAINER_HPP_

using namespace std;
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <utility>
// #include "../../GameObject/header/GameObject.hpp"
#include "../../GameObject/header/Animal.hpp"
#include "../../GameObject/header/Plant.hpp"
// #include "../../GameObject/header/Product.hpp"
// #include "../../GameObject/header/Building.hpp"
#include "pcolor.hpp"

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
        for (int i = 0; i < rowSize; ++i)
        {
            buffer[i].clear();
        }
        buffer.clear();
    }

    // *Getter */
    int getRow()
    {
        return rowSize;
    }

    int getCol()
    {
        return colSize;
    }

    /* SELECTOR */
    /**
     * Menambahakan item pada matrix[r][c]
     * @param r row
     * @param c column
     * @param T item
     */
    void addItem(int r, int c, const T &item)
    {
        // handle out of idx
        if (r >= rowSize || c >= colSize || r < 0 || c < 0)
        {
            /**
             * -TODO: throw IndexOutOfBound
             */
        }
        else
        {
            if (isCellEmpty(r, c))
            {
                buffer[r][c] = item;
            }
            else
            {
                /**
                 * TODO: throw cellterisi ?
                 */
            }
        }
    }

    /**
     * addItem by string
     * @param koordinat : string
     * @param item : T
     * @return Item
     */
    T addItem(string koordinat, T item)
    {
        pair<int, int> pair = strToRowCol(koordinat);
        addItem(pair.first, pair.second, item);
    }

    /**
     Mendapatkan item dari matrix[r][c]
     *(indexing dari 1)
     * @param r row
     * @param c column
     * @return Item pada cell tersebut : T
     */
    T getItem(int r, int c)
    {
        if (r >= rowSize || c >= colSize || r < 0 || r < 0)
        {
            /**
             * -TODO: throw IndexOutOfBound
             */
        }
        else
        {
            if (isCellEmpty(r, c))
            {
                /**
                 * TODO: throuw CellEmptyException
                 */
            }
        }
        return buffer[r][c];
    }

    /**
     * getItem by string
     * @param koordinat : string
     * @return Item
     */
    T getItem(string koordinat)
    {
        pair<int, int> pair = strToRowCol(koordinat);
        getItem(pair.first, pair.second);
    }

    /**
     * Mendapatkan item dari suatu cell
     * @param koordinat
     * @return Item pada cell tersebut : T
     */
    pair<int, int> strToRowCol(string koordinat)
    {
        // Cari nilai kolom
        int i = 0;
        int c = 0;
        pair<int, int> pair;
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
                c *= 26;
                c += koordinat[i] - 'A' + 1;
                i++;
            }
        }

        // Cari nilai baris
        int r = 0;
        for (int j = i; j < koordinat.length(); j++)
        {
            // Cek
            if (koordinat[j] >= '0' && koordinat[j] <= '9')
            {
                r *= 10;
                r += koordinat[j] - '0';
            }
            else
            {
                /**
                 * TODO: throw invalidInput
                 */
            }
        }
        r--;
        c--;
        return pair;
    }

    /**
     * Mendapatkan makanan dari suatu cell
     * @param koordinat
     * @return makanan pada cell tersebut atau throw NotEdible atau NotProduct
     */
    T getMakanan(int r, int c)
    {
        if (dynamic_cast<Product *>(getItem(r, c)) != NULL)
        {
            if (dynamic_cast<Product *>(getItem(r, c))->getAddedWeight() != 0)
            {
                return getItem(r, c);
            }
            else
            {
                /**
                 * -TODO: throw NotEdible
                 */
            }
        }
        else
        {
            /**
             * -TODO: throw NotProduct
             */
        }
    }

    /**
     * getMakananbyString
     * @param koordinat : string
     */
    T getMakanan(string koordinat)
    {
        pair<int, int> pair = strToRowCol(koordinat);
        getMakanan(pair.first, pair.second);
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
            buffer[r][c] = NULL;
        }
        else
        {
            /**
             * -TODO: throw CellEMpty
             */
        }
    }

    /**
     * removeItem by string
     * @param koordinat : string
     * @return Item
     */
    T removeItem(string koordinat)
    {
        pair<int, int> pair = strToRowCol(koordinat);
        removeItem(pair.first, pair.second);
    }

    /**
     * Mengecek cell matrix[r][c] kosong atau tidak
     * @param r row
     * @param c column
     * @return cell matrix berisi atau kosong : boolean
     */
    bool isCellEmpty(int r, int c)
    {
        return buffer[r][c] == NULL;
    }

    /**
     * Mengecek cell matrix[r][c] kosong atau tidak
     * @param koordinat string koordinat
     * @return cell matrix berisi atau kosong : boolean
     */
    bool isCellEmpty(string koordinat)
    {
        pair<int, int> pair = strToRowCol(koordinat);
        isCellEmpty(pair.first, pair.second);
    }

    /**
     * Mengecek cell matrix[r][c] kosong atau tidak
     * @param obj objek pembanding
     * @return true jika matrix mengandung objek dengan kelas yang sama dengan obj
     */
    bool isTypeEmpty(T obj)
    {
        for (int i = 0; i < rowSize; i++)
        {
            for (int j = 0; j < colSize; j++)
            {
                if (!isCellEmpty(i, j) && typeid(buffer[i][j]) == typeid(obj))
                {
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * @return true jika tidak ada makanan edible pada matrix
     */
    bool isFoodEmpty()
    {
        Product *temp = new Product();
        for (int i = 0; i < rowSize; i++)
        {
            for (int j = 0; j < colSize; j++)
            {

                if (!isCellEmpty(i, j))
                {
                    Product *obj = dynamic_cast<Product *>(getItem(i, j));
                    if (typeid(obj) == typeid(temp) && obj->getAddedWeight() != 0)
                    {
                        temp->~Product();
                        obj->~Product();
                        return false;
                    }
                    obj->~Product();
                }
            }
        }
        temp->~Product();
        return true;
    }

    /**
     * Mengecek apakah matrix kosong atau tidak
     * @return true jika matrix kosong
     */
    bool isMatrixEmpty()
    {
        for (int i = 0; i < rowSize; i++)
        {
            for (int j = 0; j < colSize; j++)
            {
                if (buffer[i][j] != NULL)
                {
                    return false;
                }
            }
        }
        return true;
    }

    /**
     * Mengecek apakah matrix penuh atau tidak
     * @return true jika matrix penuh
     */
    bool isMatrixFull()
    {
        for (int i = 0; i < rowSize; i++)
        {
            for (int j = 0; j < colSize; j++)
            {
                if (buffer[i][j] == NULL)
                {
                    return false;
                }
            }
        }
        return true;
    }

    /**
     * Memprint matrix
     */
    void printMatrix(bool isWarna)
    {
        if (isWarna)
        {
            // print koordinat column
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
                // print tabel
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
                    // print koordinat baris
                    if (j == 0)
                    {
                        cout << setfill('0') << setw(2) << i + 1 << " ";
                    }

                    // print kode
                    if (buffer[i][j] == NULL)
                    {
                        cout << "|"
                             << "     ";
                    }
                    else // tidak null
                    {
                        Animal *a = dynamic_cast<Animal *>(buffer[i][j]);
                        Plant *p = dynamic_cast<Plant *>(buffer[i][j]);
                        if (a == NULL)
                        {
                            if (p->isReadyToHarvest())
                            {
                                cout << "| ";
                                print_greens(buffer[i][j]->getKodeHuruf());
                                cout << " ";
                            }
                            else
                            {
                                cout << "| ";
                                print_reds(buffer[i][j]->getKodeHuruf());
                                cout << " ";
                            }
                        }
                        else
                        {
                            if (a->isReadyToHarvest())
                            {
                                cout << "| ";
                                print_greens(buffer[i][j]->getKodeHuruf());
                                cout << " ";
                            }
                            else
                            {
                                cout << "| ";
                                print_reds(buffer[i][j]->getKodeHuruf());
                                cout << " ";
                            }
                        }
                    }
                }
                // cout << "|  " << i + 1 << endl;
                cout << "|" << endl;
            }

            // print tabel paling bawag(cont.)
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
        else
        {
            // print koordinat column
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
                // print tabel
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
                    // print koordinat baris
                    if (j == 0)
                    {
                        cout << setfill('0') << setw(2) << i + 1 << " ";
                    }

                    // print kode
                    if (buffer[i][j] == NULL)
                    {
                        cout << "|"
                             << "     ";
                    }
                    else // tidak null
                    {
                        cout << "| " << buffer[i][j]->getKodeHuruf() << " ";
                    }
                }
                // cout << "|  " << i + 1 << endl;
                cout << "|" << endl;
            }

            // print tabel paling bawag(cont.)
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
    }

    /**
     * @return banyaknya space kosong pada matrix
     */
    int emptySpace()
    {
        int hasil = 0;
        for (int i = 0; i < rowSize; i++)
        {
            for (int j = 0; j < colSize; j++)
            {
                if (isCellEmpty(i, j))
                {
                    hasil++;
                }
            }
        }
        return hasil;
    }

    /**
     * @return true if object with class T exist in the matrix
     */
    template <class T>
    bool isObjectEmpty()
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (!isCellEmpty(i + 1, j + 1) && dynamic_cast<T>(buffer[i][j]) != NULL)
                {
                    return false;
                }
            }
        }
        return true;
    }
};

#endif
