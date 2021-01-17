#ifndef TRANSITMANAGER_H
#define TRANSITMANAGER_H
#include "abstractmanager.h"
#include "logger.h"
#include "transit.h"
#include "liblayouteditor_global.h"

class DecimalFormat;
class LIBLAYOUTEDITORSHARED_EXPORT TransitManager : public AbstractManager
{
    Q_OBJECT
public:
    explicit TransitManager(QObject *parent = 0);
    ~TransitManager() override{}
    TransitManager(const TransitManager&) : AbstractManager() {}
    int getXMLOrder() const override;
    QString getSystemPrefix()const override;
    char typeLetter()const override ;

    /**
     * Method to create a new Transit if the Transit does not exist
     *   Returns null if a Transit with the same systemName or userName
     *       already exists, or if there is trouble creating a new Transit.
     */
    Transit* createNewTransit(QString systemName, QString userName);
    /*public*/ Transit* createNewTransit(QString userName);
    /*public*/ Transit* getTransit(QString name) ;
    /*public*/ Transit* getBySystemName(QString name)const ;
    /*public*/ Transit* getByUserName(QString key)const ;
    /*public*/ void deleteTransit(Transit* z) ;
    /*public*/ QList<Transit*>* getListUsingSection(Section* s);
    /*static*/ /*public*/ TransitManager* instance();
    /*public*/ QList<Transit*> getListUsingBlock(Block* b);
    /*public*/ QList<Transit*> getListEntryBlock(Block* b);
    /*public*/ QString getNamedBeanClass()const override {
        return "Transit";
    }

signals:
    
public slots:
private:
 Logger log;
 DecimalFormat* paddedNumber;// = new DecimalFormat("0000");

 int lastAutoTransitRef;// = 0;
 static TransitManager* _instance;// = NULL;

    
};
Q_DECLARE_METATYPE(TransitManager)
#endif // TRANSITMANAGER_H
