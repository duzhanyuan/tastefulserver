#pragma once

#include <tastefulserver/QVariantTree.h>

namespace tastefulserver {

template <class T>
T QVariantAbstractTree::value() const
{
    return asQVariant().value<T>();
}

} // namespace tastefulserver
