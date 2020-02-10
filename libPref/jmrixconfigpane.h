#ifndef JMRIXCONFIGPANE_H
#define JMRIXCONFIGPANE_H

#include "preferencespane.h"
#include "logger.h"
#include "libpref_global.h"
#include "jpanel.h"

class UserPreferencesManager;
class QComboBox;
class ConnectionConfig;
class LIBPREFSHARED_EXPORT JmrixConfigPane : public QWidget
{
    Q_OBJECT
public:
    //explicit JmrixConfigPane(QWidget *parent = 0);
 ~JmrixConfigPane() {}
#if 0
    /*public*/ static JmrixConfigPane* instance(int index);
    /*public*/ static JmrixConfigPane* instance(ConnectionConfig* config);
#endif
    /*public*/ static /*synchronized*/ JmrixConfigPane* createPanel(ConnectionConfig* c);
    /*public*/ static JmrixConfigPane* createNewPanel();
#if 0
    /*public*/ static int getNumberOfInstances() ;
    /*public*/ static void dispose(int index);
 /*public*/ static int getInstanceNumber(JmrixConfigPane* confPane);
 /*public*/ static QList<JmrixConfigPane*> getListOfConfigPanes();
#endif
    /*public*/ static void dispose(JmrixConfigPane* confPane);
#if 0
    static /*final*/ QMap<int, JmrixConfigPane*> configPaneTable;// = new HashMap<>();
#endif

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
    /*public*/ virtual QString getPreferencesItem();
    /*public*/ virtual QString getPreferencesItemText();
    /*public*/ virtual QString getTabbedPreferencesTitle();
    /*public*/ virtual QString getLabelKey();
    /*public*/ virtual QWidget* getPreferencesComponent();
    /*public*/ virtual bool isPersistant();
    /*public*/ virtual QString getPreferencesTooltip();
    /*public*/ virtual void savePreferences();
    /*public*/ virtual bool isDirty();
    /*public*/ virtual bool isRestartRequired();
    /*public*/ bool isPreferencesValid();

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

   ConnectionConfig* ccCurrent;// = NULL;
   /**
    * Use "instance" to get one of these. That allows it to reconnect to
    * existing information in an existing ConnectionConfig object. It's
    * permitted to call this with a NULL argument, e.g. for when first
    * configuring the system.
    */
   /*private*/ JmrixConfigPane(ConnectionConfig* original, QWidget* parent = 0);
   void selection();

protected:
   JmrixConfigPane(QWidget *parent = 0) : QWidget(parent){}

   friend class ConnectionsPreferencesPanel;
};

#endif // JMRIXCONFIGPANE_H
