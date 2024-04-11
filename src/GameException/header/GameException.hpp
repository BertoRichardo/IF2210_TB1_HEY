#ifndef _GAMEEXCEPTION_HPP_
#define _GAMEEXCEPTION_HPP_

#include <iostream>
using namespace std;

/**
 * Kelas ini bertindak sebagai abstract class
 * TODO: Implement All exception for this game
 */
class GameException
{
protected:
    string message;

public:
    /**
     * Default COnstructor
     * Mengisi pesan kesalahan dengan pesan
     * "Opps, terjadi kesalahan"
     */
    GameException();
    /**
     * Pesan kesalahan dibentuk dengan pesan tertentu
     * @param message_ pesan kesalahan
     */
    GameException(const string &);

    virtual ~GameException();
    /**
     * Mengganti isi message dengan pesan kesalahan lain
     * @param message_ pesan kesalahan lain
     */
    void setMessage(const string &);
    /**
     * Menampilkan pesan kesalahan
     */
    virtual void displayMessage() const = 0;
};

class FeedTypeInvalidException : public GameException
{
private:
    string animalType;
    string productType;

public:
    /**
     * Menciptakan GameException dengan pesan
     * "Jenis Product tidak dapat dimakan"
     * - disimpan pula jenis hewan dan product yang akan dimakan
     * @param animalType_ jenis hewan yang diberi makan
     * @param productType_ jenis product pakan
     */
    FeedTypeInvalidException(const string &, const string &);

    void displayMessage() const;

    /**
     * Menciptakan GameException dengan pesan
     * "Index Invalid"
     * @param row
     * @param col
     */
};

class IndexInvalidException : public GameException
{
private:
    int row;
    int col;

public:
    /**
     * Menciptakan GameException dengan pesan
     * "Index Invalid"
     * @param row
     * @param col
     */
    IndexInvalidException(const int &, const int &);

    void displayMessage() const;
};

/**
 * TODO: implement all exception which this game need
 */
#endif