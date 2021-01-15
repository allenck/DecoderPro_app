#ifndef BLOCKBOSSLOGICXML_H
#define BLOCKBOSSLOGICXML_H
#include "abstractxmladapter.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT BlockBossLogicXml : public AbstractXmlAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit BlockBossLogicXml(QObject *parent = 0);
    ~BlockBossLogicXml();
    BlockBossLogicXml(const BlockBossLogicXml&) : AbstractXmlAdapter() {}
    /*public*/ QDomElement store(QObject* o) override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode) throw (JmriConfigureXmlException) override;
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception) override;
    /*public*/ int loadOrder()const override;

signals:

public slots:
private:
    Logger * log;
    QDomElement storeSensor(QString name);

};

#endif // BLOCKBOSSLOGICXML_H
