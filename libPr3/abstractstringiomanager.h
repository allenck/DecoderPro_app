#ifndef ABSTRACTSTRINGIOMANAGER_H
#define ABSTRACTSTRINGIOMANAGER_H
#include "abstractmanager.h"
#include "stringiomanager.h"

class AbstractStringIOManager : public AbstractManager, public StringIOManager
{
    Q_OBJECT
    Q_INTERFACES(StringIOManager)
public:
    AbstractStringIOManager(SystemConnectionMemo* memo, QObject* parent = nullptr);
    /*public*/ int getXMLOrder()const override;
    /*public*/ QChar typeLetter()const override;
    /*public*/ QString getBeanTypeHandled(bool plural)const override;
    /*public*/ QString getNamedBeanClass() const override;

};

#endif // ABSTRACTSTRINGIOMANAGER_H
