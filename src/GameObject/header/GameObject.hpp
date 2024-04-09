#ifndef _GAMEOBJECT_HPP_
#define _GAMEOBJECT_HPP_

#include <iostream>
using namespace std;

class GameObject
{
protected:
    string kodeHuruf;
    string name;
    int price;
public:
    /**
     * Default Constructor untuk GameObject.
     * melakukan assign nilai dengan nilai default
     * - kodeHuruf = ""
     * - name = ""
     * - price = 0
     * + kodeHuruf == "" (artinya object kosong, memudahkan identifikasi kekosongan elemen pada Container)
    */
    GameObject();

    /**
     * User Defined Constructor untuk GameObject.
     * Nilai diisi dengan parameter yang bersesuaian
     * @param _kodeHuruf Kode huruf yang akan diassign ke dalam object sesuai config
     * @param _name Nama object yang sesuai dengan config
     * @param _price Nilai harga jual/beli object
    */
    GameObject(const string &, const string &, int);

    /**
     * Destructor 
     * - do nothing
    */
    ~GameObject();
    
    /*Selektor*/
    /**
     * @return kodeHuruf : string
    */
    string getKodeHuruf() const;
    /**
     * @param kodeHuruf_ kodeHuruf baru yang akan diassign pada kodeHuruf
    */
    void setKodeHuruf(const string &);

    /**
     * @return name : string
    */
    string getName() const;
    /**
     * @param name_ nama object yang baru
    */
    void setName(const string &);

    /**
     * @return price : int
     */
    int getPrice() const;
    /**
     * @param price price baru
    */
    void setPrice(int);

    /**
     * Mengecek apakah object kosong atau tidak.
     * Object kosong jika tidak kodeHuruf kosong
     * @return boolean : true or false
    */
    bool isEmpty() const;

    /**
     * Mengganti seluruh nilai atribut dengan nilai default
     * a.k.a. Mengosongkan object
    */
    virtual void clearData();
};

#endif