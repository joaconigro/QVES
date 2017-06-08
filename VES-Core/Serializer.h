#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <QString>
#include "ves-core_global.h"
#include "Serializable.h"

class VESCORESHARED_EXPORT Serializer
{
public:
    virtual ~Serializer() {}

    virtual void save(const Serializable& serializable, const QString& filepath, const QString& rootName = "") = 0;
    virtual void load(Serializable& serializable, const QString& filepath) = 0;
};

#endif // SERIALIZATION_H
