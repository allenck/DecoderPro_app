#ifndef MANAGERDEFAULTSCONFIGPANE_H
#define MANAGERDEFAULTSCONFIGPANE_H
#include "jmripanel.h"
#include <QRadioButton>
#include "libpref_global.h"
#include "preferencespanel.h"
#include "instancemanagerautodefault.h"

class Logger;
class PropertyChangeEvent;
class SystemConnectionMemo;
class QVBoxLayout;
class QGridLayout;
class QButtonGroup;
class LIBPREFSHARED_EXPORT ManagerDefaultsConfigPane : public JmriPanel, public PreferencesPanel,
  public InstanceManagerAutoDefault
{
    Q_OBJECT
    Q_INTERFACES(PreferencesPanel InstanceManagerAutoDefault)
public:
    Q_INVOKABLE explicit ManagerDefaultsConfigPane(QWidget *parent = 0);
    ~ManagerDefaultsConfigPane();
    ManagerDefaultsConfigPane(const ManagerDefaultsConfigPane&);
    /*public*/ void update();
    void reloadConnections(QObjectList connList);

    /*public*/ QString getPreferencesItem() override ;
     /*public*/ QString getPreferencesItemText() override;

    /*public*/ QString getTabbedPreferencesTitle() override;

    /*public*/ QString getLabelKey()  override;

    /*public*/ QWidget* getPreferencesComponent()  override;

    /*public*/ bool isPersistant()  override;

    /*public*/ QString getPreferencesTooltip() override ;

    /*public*/ void savePreferences() override ;

    /*public*/ bool isDirty() override;

    /*public*/ bool isRestartRequired() override;
    /*public*/ bool isPreferencesValid() override;


    /*public*/ QString className() override;
    /*public*/ QObject* ppself()  override{return (QObject*)this;}

signals:

public slots:
    void propertyChange(PropertyChangeEvent*);

private:
    /*private*/ bool dirty;// = false;
    QWidget* matrix;
    QVector<QButtonGroup*> groups;
    QVBoxLayout* thisLayout;
    QGridLayout* matrixLayout;
    /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("ManagerDefaultsConfigPane");

friend class SelectionButton;
};
Q_DECLARE_METATYPE(ManagerDefaultsConfigPane)

/**
 * Captive class to track changes
 */
/*static*/ class SelectionButton : public  QRadioButton
{
    Q_OBJECT
    QString name;
    QString managerClass;
    ManagerDefaultsConfigPane* pane;
public:
    /**
     *
     */
    //private static final long serialVersionUID = -2572336492673634333L;

    SelectionButton(QString name, QString managerClass, ManagerDefaultsConfigPane* pane);

    /*public*/ void setSelected(bool t);
public slots:
    void On_toggled(bool);
};
#endif // MANAGERDEFAULTSCONFIGPANE_H
