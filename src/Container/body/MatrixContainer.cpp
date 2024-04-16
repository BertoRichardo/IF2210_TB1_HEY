#include "../header/MatrixContainer.hpp"

template <>
void MatrixContainer<GameObject *>::printElmt(int r, int c)
{
    cout << buffer[r][c]->getKodeHuruf();
}

template <>
void MatrixContainer<Plant *>::printElmt(int r, int c)
{
    if (buffer[r][c]->isReadyToHarvest()){
        print_greens(buffer[r][c]->getKodeHuruf());
    }
    else{
        print_reds(buffer[r][c]->getKodeHuruf());
    }
}

template <>
void MatrixContainer<Animal *>::printElmt(int r, int c)
{
    if (buffer[r][c]->isReadyToHarvest()){
        print_greens(buffer[r][c]->getKodeHuruf());
    }
    else{
        print_reds(buffer[r][c]->getKodeHuruf());
    }
}