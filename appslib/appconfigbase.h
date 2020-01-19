#ifndef APPCONFIGBASE_H
#define APPCONFIGBASE_H
//#include "jmripanel.h"
#include "logger.h"
#include "appslib_global.h"
#include "jmripanel.h"

class PreferencesPanel;
class APPSLIBSHARED_EXPORT AppConfigBase : public JmriPanel
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit AppConfigBase(QWidget *parent = 0);
    ~AppConfigBase() {}
    AppConfigBase(const AppConfigBase&) : JmriPanel() {}
    /*public*/ static QString getManufacturerName(int index) ;
    /*public*/ static QString getConnection(int index);
    /*public*/ static QString getPort(int index);
    /*public*/ static QString getConnectionName(int index);
    /*public*/ static bool getDisabled(int index);
    /*public*/ virtual void dispose();
    /*public*/ void saveContents();
    /*public*/ void savePressed(bool restartRequired);
    Q_INVOKABLE virtual /*public*/ QString getClassDescription();
//    Q_INVOKABLE virtual /*public*/ void setMessagePreferencesDetails() ;
    /*virtual*/ static /*public*/ QString getClassName() ;
    /*public*/ QMap<QString, PreferencesPanel*>* getPreferencesPanels();

    static QString getName();

signals:

public slots:
private:
    /*private*/ bool checkDups();
    /*private*/ bool checkPortNames();
    Logger* log;
    /*private*/ void registerWithConfigureManager(PreferencesPanel* panel);

protected:
    /**
     * All preferences panels handled, whether persisted or not. This is a
     * LinkedHashMap and not just a HashMap because parts of JMRI are dependent
     * upon the order in which preferences are read. The order is determined by
     * the
     */
    /*protected*/ QMap<QString, PreferencesPanel*>* preferencesPanels;// = new LinkedHashMap<>();


};
Q_DECLARE_METATYPE(AppConfigBase)
#endif // APPCONFIGBASE_H
