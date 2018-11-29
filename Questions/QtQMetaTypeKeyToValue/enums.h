#ifndef ENUMS_H
#define ENUMS_H

#include <QObject>
#include <QMetaEnum>

namespace MyNamespace
{
    Q_NAMESPACE

    enum Genres
    {
        ACTION,
        FANTASY,
        ROMANCE
    };
    Q_ENUM_NS(Genres)

    template<typename EnumT>
    static QString EnumToString(const EnumT value)
    {
        return QMetaEnum::fromType<EnumT>().valueToKey(value);
    }

    template<typename EnumT>
    static EnumT StringToEnum(const QString value)
    {
        // nice conversion for the sting and the enum ...
        return (EnumT)QMetaEnum::fromType<EnumT>().keyToValue(value.toUpper().toStdString().c_str());
    }
}

#endif // ENUMS_H
