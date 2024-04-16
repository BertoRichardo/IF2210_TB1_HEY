#ifndef _GAMEEXCEPTION_HPP_
#define _GAMEEXCEPTION_HPP_

#include <iostream>
#include <vector>
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
};

class IndexInvalidException : public GameException
{

public:
    /**
     * Menciptakan GameException dengan pesan
     * "Index Invalid"
     */
    IndexInvalidException();

    void displayMessage() const;
};

class ResourceInsufficientException : public GameException
{
private:
    vector<pair<string, int>> insufficientMaterial;

public:
    /**
     * Menciptakan Exception ketika walikota tidak bisa membangun bangunan
     * karena sumber daya tidak cukup
     * @param
     */
    ResourceInsufficientException(const vector<pair<string, int>> &insufficientMaterial_);

    void displayMessage() const;
};

class InputInvalidException : public GameException
{
public:
    /**
     * Exception saat input invalid
     * @param
     */
    InputInvalidException();

    void displayMessage() const;
};

class CommandInvalidException : public GameException
{
public:
    /**
     * Exception saat command invalid atau tidak tersedia
     * @param
     */
    CommandInvalidException();

    void displayMessage() const;
};

/**
 * TODO: implement all exception which this game need
 */

class CustomException : public GameException
{
public:
    /**
     * Menciptakan GameException yang disesuaikan dengan
     * kesalahan tertentu
     * Hanya dapat dilakukan pada pesan sebuah kalimat saja
     */
    CustomException(const string &message_);
    ~CustomException();
    void displayMessage() const;
};

#endif