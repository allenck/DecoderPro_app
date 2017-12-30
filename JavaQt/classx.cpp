#include "classx.h"

template<class T>
T* ClassX<T>::forName(QString adapterName)
{
 QObject* adapter = NULL;
 QString aName = adapterName.mid(adapterName.lastIndexOf(".") +1);
 int typeId = QMetaType::type(aName.toLocal8Bit());
 if(typeId > 0)
 {
#if QT_VERSION < 0x050000
  adapter = (QObject*)QMetaType::construct(typeId);
#else
  adapter = (QObject*)QMetaType::create(typeId);
#endif
 }
 return adapter;
}
