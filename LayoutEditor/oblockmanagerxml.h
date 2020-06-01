#ifndef OBLOCKMANAGERXML_H
#define OBLOCKMANAGERXML_H
#include "abstractxmladapter.h"
#include "liblayouteditor_global.h"

class PortalManager;
class OBlockManager;
class OBlock;
class OPath;
class Portal;
class LIBLAYOUTEDITORSHARED_EXPORT OBlockManagerXml : public AbstractXmlAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit OBlockManagerXml(QObject *parent = 0);
 ~OBlockManagerXml() override {}
 OBlockManagerXml(const OBlockManagerXml&) : AbstractXmlAdapter() {}
    /*public*/ QDomElement store(QObject* o);
    QDomElement storePortal(Portal* portal);
    QDomElement storePathKey(OPath* path);
    QDomElement storePath(OPath* path);
    /*public*/ bool load(QDomElement blocks) throw (Exception) override;
    OBlock* getBlock(QString sysName);
    OPath* getPath(OBlock* block, QString name);
    //Portal* getPortal(OBlock* fromBlock, QString name, OBlock* toBlock);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception) override;
    Portal* loadPortal(QDomElement elem);
    OPath* loadPath(QDomElement elem, OBlock* block);
    /*public*/ int loadOrder() const override;

signals:

public slots:
private:
    /**
    * Due to the forward and backward referencing among OBlock, OPath and Portal
    * no precedence order exists to fully create these objects in one pass.
    * The unique naming of these objects allows the use of Hashmaps to hold them
    * for update.
    */
    QMap <QString, OBlock*>* _blockMap;
    QMap <QString, OPath*>* _pathMap;
    QMap <QString, Portal*>* _portalMap;
    OBlockManager* _manager;
    PortalManager* _portalMgr;
    Logger* log;
//    Portal* getPortal(QString name);
    void loadBlock(QDomElement elem);

};
Q_DECLARE_METATYPE(OBlockManagerXml)
#endif // OBLOCKMANAGERXML_H
