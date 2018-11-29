#include <QCoreApplication>

#include <QDebug>
#include "enums.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << MyNamespace::EnumToString(MyNamespace::Genres::FANTASY);

    if(MyNamespace::StringToEnum<MyNamespace::Genres>("FANTASY") == MyNamespace::Genres::FANTASY)
    {
        qDebug() << "Yayy!";
    }
    else
    {
        qDebug() << "Nayy!";
    }

    return a.exec();
}
