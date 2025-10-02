#include "crypto.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Crypto w;
    w.show();
    return a.exec();
}
