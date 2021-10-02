#include "tee.h"

int main(int argc, char** argv)
{
    Tee tee{argc, argv};
    tee.Write();

    return 0;
}