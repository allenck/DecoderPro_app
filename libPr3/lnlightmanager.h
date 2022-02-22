#ifndef LNLIGHTMANAGER_H
#define LNLIGHTMANAGER_H
#include "abstractlightmanager.h"
#include "lntrafficcontroller.h"


class LIBPR3SHARED_EXPORT LnLightManager : public AbstractLightManager
{
    Q_OBJECT
public:
    explicit LnLightManager(LocoNetSystemConnectionMemo* memo, QObject *parent = 0);
    /**
     *  Returns the system letter for Loconet
     */
//    /*public*/  QString getSystemPrefix();
    /**
     * Method to create a new Light based on the system name
     * Returns null if the system name is not in a valid format
     * Assumes calling method has checked that a Light with this
     *    system name does not already exist
     */
    /*public*/ Light* createNewLight(QString systemName, QString userName)override;
    /**
     *  Get the bit address from the system name
     */
    /*public*/ int getBitFromSystemName (QString systemName) throw (Exception);
    /**
     * Public method to validate system name format
     *   returns 'true' if system name has a valid format, else returns 'false'
     */
    /*public*/ NameValidity validSystemNameFormat(QString systemName)override;
    /**
     * Public method to validate system name for configuration
     *   returns 'true' if system name has a valid meaning in current configuration,
     *      else returns 'false'
     *   for now, this method always returns 'true'; it is needed for the Abstract Light class
     */
    /*public*/ bool validSystemNameConfig(QString systemName)override;
    /**
     * A method that determines if it is possible to add a range of lights in numerical
     * order eg 11 thru 18, primarily used to show/not show the add range box in the add Light window
     **/
    /*public*/ bool allowMultipleAdditions(QString systemName)override;
    /*public*/ QString getNamedBeanClass()const override {
        return "LnLight";
    }
    /*public*/ SystemConnectionMemo* getMemo() override {return AbstractManager::getMemo();}
//  /*public*/ QSet<NamedBean*> getNamedBeanSet() override {return AbstractManager::getNamedBeanSet();}
  /*public*/ NamedBean* getBySystemName(QString name) override {return AbstractManager::getBySystemName(name);}
  /*public*/ void addPropertyChangeListener(PropertyChangeListener* l) override{PropertyChangeSupport::addPropertyChangeListener(l);}
  /*public*/ void removePropertyChangeListener(PropertyChangeListener* l) override{PropertyChangeSupport::removePropertyChangeListener(l);}

  QObject* pself() override{return (QObject*)this;}

  QObject* vself() override { return (QObject*)this;}
signals:
    
public slots:
private:
    LnTrafficController* _trafficController;
    //QString prefix;
 Logger log;
    
};

#endif // LNLIGHTMANAGER_H
