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
    cerr << "Hewan bertipe " << animalType << " tidak dapat memakan product bertipe " << productType << "\n\n";
}

/*IndexInvalidException*/
IndexInvalidException::IndexInvalidException() : GameException("Index Out Of Bound")
{
}

void IndexInvalidException::displayMessage() const
{
    cerr << message << "\n\n";
}

/*ResourceInsufficientException*/
ResourceInsufficientException::ResourceInsufficientException(
    int insGulden_,
    const vector<pair<string, int>> &insufficientMaterial_)
    : GameException("Kamu tidak punya sumber daya yang cukup! Masih memerlukan ")
{
    insGulden = insGulden_;
    insufficientMaterial = insufficientMaterial_;
}

void ResourceInsufficientException::displayMessage() const
{
    cerr << message;
    if (insGulden > 0)
    {
        cerr << insGulden << "gulden" << endl;
    }

    int i = 0;
    for (auto material : insufficientMaterial)
    {
        if (i != 0)
        {
            cerr << ", ";
        }
        cerr << material.second << " " << material.first;
    }
    cerr << "!" << "\n\n";
}

InputInvalidException::InputInvalidException(): GameException("Maaf, input Anda tidak valid T__T")
{}

void InputInvalidException::displayMessage() const
{
    cerr << message << "\n\n";
}

CommandInvalidException::CommandInvalidException(): GameException("Maaf, command Anda tidak tersedia >//<")
{}

void CommandInvalidException::displayMessage() const 
{
    cerr << message << "\n\n";
}

/**
 * Custom Exception
 */
CustomException::CustomException(const string &message_) : GameException(message_)
{
}

CustomException::~CustomException()
{
    message.clear();
}

void CustomException::displayMessage() const
{
    cerr << message << "\n\n";
}
