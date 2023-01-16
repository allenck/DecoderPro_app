#ifndef JMRIXCONFIGPANE_H
#define JMRIXCONFIGPANE_H

#include "preferencespanel.h"
#include "logger.h"
#include "libpref_global.h"
#include "jpanel.h"

class UserPreferencesManager;
class QComboBox;
class ConnectionConfig;
class LIBPREFSHARED_EXPORT JmrixConfigPane : public JPanel, public PreferencesPanel
{
    Q_OBJECT
    Q_INTERFACES(PreferencesPanel)
public:
    //explicit JmrixConfigPane(QWidget *parent = 0);
    ~JmrixConfigPane() {}
    /*public*/ static /*synchronized*/ JmrixConfigPane* createPanel(ConnectionConfig* c);
    /*public*/ static JmrixConfigPane* createNewPanel();
    /*public*/ static void dispose(JmrixConfigPane* confPane);

    /*public*/ static /*final*/ QString NONE_SELECTED;// = Bundle.getMessage("noneSelected");
    /*public*/ static /*final*/ QString NO_PORTS_FOUND;// = Bundle.getMessage("noPortsFound");
    /*public*/ static /*final*/ QString NONE;// = Bundle.getMessage("none");


    /*public*/ QString getConnectionName();
    /*public*/ QString getCurrentManufacturerName();
    /*public*/ QString getCurrentProtocolName();
    /*public*/ QString getCurrentProtocolInfo();
    /*public*/ QObject* getCurrentObject() ;
    /*public*/ bool getDisabled();
    /*public*/ void setDisabled(bool disabled);
    /*public*/ QString getPreferencesItem() override;
    /*public*/ QString getPreferencesItemText() override;
    /*public*/ QString getTabbedPreferencesTitle() override;
    /*public*/ QString getLabelKey() override;
    /*public*/ QWidget* getPreferencesComponent() override;
    /*public*/ bool isPersistant() override;
    /*public*/ QString getPreferencesTooltip() override;
    /*public*/ void savePreferences() override;
    /*public*/ bool isDirty() override;
    /*public*/ bool isRestartRequired() override;
    /*public*/ bool isPreferencesValid() override;
    QString className() override {return "jmri.jmrix.JmrixConfigPane";}
    QObject* ppself() override {return this;}

signals:

public slots:
   /*public*/ void updateComboConnection();
   void On_modeBox_currentIndexChanged(int);
private:
   /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("JmrixConfigPane");
   /*private*/ static /*synchronized*/ JmrixConfigPane* createPanel(int index);
   /*private*/ bool _isDirty;// = false;
   QComboBox* modeBox;// = new JComboBox<>();
   QComboBox* manuBox;// = new JComboBox<>();

   JPanel* details;// = new JPanel();
   QStringList classConnectionNameList;
   QList<ConnectionConfig*> classConnectionList;
   QStringList* manufactureNameList;

   UserPreferencesManager* p;// = jmri.InstanceManager.getDefault(jmri.UserPreferencesManager.class);

   ConnectionConfig* ccCurrent = nullptr;

private slots:
   void selection();

protected:
   JmrixConfigPane(QWidget *parent = 0) : JPanel(parent){}
   /**
    * Use "instance" to get one of these. That allows it to reconnect to
    * existing information in an existing ConnectionConfig object. It's
    * permitted to call this with a NULL argument, e.g. for when first
    * configuring the system.
    */
   /*prtected*/ JmrixConfigPane(ConnectionConfig* original, QWidget* parent = 0);

   friend class ConnectionsPreferencesPanel;
};

#endif // JMRIXCONFIGPANE_H
