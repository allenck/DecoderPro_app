#ifndef DEFAULTLOGIXMANAGER_H
#define DEFAULTLOGIXMANAGER_H
#include "abstractmanager.h"
#include "logixmanager.h"
#include "libPr3_global.h"

class DecimalFormat;
class Logix;
class LIBPR3SHARED_EXPORT DefaultLogixManager : public LogixManager
{
    Q_OBJECT
public:
    explicit DefaultLogixManager(QObject *parent = 0);
    int getXMLOrder() const override;
    /*public*/ QString getSystemPrefix()const  override;
    /*public*/ char typeLetter()const   override;
    /*public*/ Logix* createNewLogix(QString systemName, QString userName) override;
    /*public*/ Logix* createNewLogix(QString userName) override;
    /*public*/ void deleteLogix(Logix* x) override;
    /*public*/ void activateAllLogixs() override;
    /*public*/ Logix* getLogix(QString name) override;
    /*public*/ Logix* getBySystemName(QString name)const override;
    /*public*/ Logix* getByUserName(QString key)const override;
    /*public*/ void setLoadDisabled(bool s) override;
    static DefaultLogixManager* _instance;// = NULL;
    QT_DEPRECATED static /*public*/ DefaultLogixManager* instance();
    /*public*/ QString getBeanTypeHandled(bool plural) const override;
    /*public*/ QString getNamedBeanClass()const override ;

signals:

 public slots:
private:
    DecimalFormat* paddedNumber;// = new DecimalFormat("0000");
    bool loadDisabled = false;
    static Logger* log;
};

#endif // DEFAULTLOGIXMANAGER_H
