#ifndef _MATRIXCONTAINER_HPP_
#define _MATRIXCONTAINER_HPP_

using namespace std;
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <map>
#include <vector>
#include "../../Util/header/Util.hpp"
#include "../../GameObject/header/Animal.hpp"
#include "../../GameObject/header/Plant.hpp"
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
            buffer[i].resize(c, NULL);
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
    /**
     * @return row matrix
     */
    int getRow() const
    {
        return rowSize;
    }

    /**
     * @return col Matrix
     */
    int getCol() const
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
    void addItem(string koordinat, T item)
    {
        pair<int, int> pair = Util::strToRowCol(koordinat);
        addItem(pair.first, pair.second, item);
    }

    /**
     * Menambahakan item pada matrix berdasarkan algoritma First Fit & Write
     * @param T item
     */
    void addItem(const T &item)
    {
        for (int i = 0; i < rowSize; i++)
        {
            for (int j = 0; j < colSize; j++)
            {
                if (isCellEmpty(i, j))
                {
                    buffer[i][j] = item;
                    return;
                }
            }
        }
        /**
         * @todo: throw matrix full
         */
    }

    /**
     Mendapatkan item dari matrix[r][c]
     * @param r row
     * @param c column
     * @return Item pada cell tersebut : T
     */
    T getItem(int r, int c) const
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
    T getItem(string koordinat) const
    {
        pair<int, int> pair = Util::strToRowCol(koordinat);
        return getItem(pair.first, pair.second);
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
        return NULL;
    }

    /**
     * getMakananbyString
     * @param koordinat : string
     */
    T getMakanan(string koordinat)
    {
        pair<int, int> pair = Util::strToRowCol(koordinat);
        return getMakanan(pair.first, pair.second);
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
             * -TODO: throw CellEmpty
             */
        }
    }

    /**
     * removeItem by string
     * @param koordinat : string
     * @return Item
     */
    void removeItem(string koordinat)
    {
        pair<int, int> pair = Util::strToRowCol(koordinat);
        removeItem(pair.first, pair.second);
    }

    /**
     * Mengecek cell matrix[r][c] kosong atau tidak
     * @param r row
     * @param c column
     * @return cell matrix berisi atau kosong : boolean
     */
    bool isCellEmpty(int r, int c) const
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
        pair<int, int> pair = Util::strToRowCol(koordinat);
        return isCellEmpty(pair.first, pair.second);
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
        for (int i = 0; i < rowSize; i++)
        {
            for (int j = 0; j < colSize; j++)
            {
                if (!isCellEmpty(i, j))
                {
                    Product *obj = dynamic_cast<Product *>(getItem(i, j));
                    if (obj != NULL && obj->getAddedWeight() != 0)
                    {
                        return false;
                    }
                }
            }
        }
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
    void printMatrix()
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
                    cout << "| ";
                    printElmt(i, j);
                    cout << " ";
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

    void printElmt(int r, int c)
    {
        cout << r << c << 'a';
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
     * @return vector of pair emptyPoints
     */
    vector<pair<int, int>> getEmptySpacePoints()
    {
        vector<pair<int, int>> result;
        for (int i = 0; i < rowSize; i++)
        {
            for (int j = 0; j < colSize; j++)
            {
                if (isCellEmpty(i, j))
                {
                    result.push_back(make_pair(i, j));
                }
            }
        }
        return result;
    }

    /**
     * Mendapatkan Inventory dan jumlahnya
     * @return map<string, pair<GameObject* , int>>
     */
    map<string, int> getGroupedItem()
    {
        map<string, int> groupedItem;
        for (int i = 0; i < getRow(); i++)
        {
            for (int j = 0; j < getCol(); j++)
            {
                groupedItem[getItem(i, j)->getName()]++;
            }
        }
        return groupedItem;
    }

public:
    /**
     * @return true if object with class T exist in the matrix
     */
    template <class U>
    bool isObjectEmpty()
    {
        for (int i = 0; i < rowSize; i++)
        {
            for (int j = 0; j < colSize; j++)
            {
                if (!isCellEmpty(i, j) && dynamic_cast<T>(buffer[i][j]) != NULL)
                {
                    return false;
                }
            }
        }
        return true;
    }
};

#endif
