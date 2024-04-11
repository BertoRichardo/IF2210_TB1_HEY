#include "../header/GameException.hpp"

/*GameException*/
GameException::GameException() : message("Opps, terjadi kesalahan")
{
}

GameException::GameException(const string &message_) : message(message_)
{
}

GameException::~GameException()
{
    message.clear();
}

void GameException::setMessage(const string &message_)
{
    message = message_;
}

/*FeedTypeInvalidException*/
FeedTypeInvalidException::FeedTypeInvalidException(const string &animalType_, const string &productType_) : GameException("Jenis Product tidak dapat dimakan")
{
    animalType = animalType_;
    productType = productType_;
}

void FeedTypeInvalidException::displayMessage() const
{
    cerr << message << endl;
    cerr << "Hewan bertipe " << animalType << " tidak dapat memakan product bertipe " << productType << endl;
}

/*IndexInvalidException*/
IndexInvalidException::IndexInvalidException(const int &row_, const int &col_) : GameException("Index Out Of Bound")
{
    row = row_;
    col = col_;
}

void IndexInvalidException::displayMessage() const
{
    cerr << message;
}
