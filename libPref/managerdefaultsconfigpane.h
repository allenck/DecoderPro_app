#ifndef MANAGERDEFAULTSCONFIGPANE_H
#define MANAGERDEFAULTSCONFIGPANE_H
#include "jmripanel.h"
#include <QRadioButton>
#include "libpref_global.h"
#include "preferencespanel.h"

class Logger;
class PropertyChangeEvent;
class SystemConnectionMemo;
class QVBoxLayout;
class QGridLayout;
class QButtonGroup;
class LIBPREFSHARED_EXPORT ManagerDefaultsConfigPane : public JmriPanel, public PreferencesPanel
{
    Q_OBJECT
    Q_INTERFACES(PreferencesPanel)
public:
    Q_INVOKABLE explicit ManagerDefaultsConfigPane(QWidget *parent = 0);
    ~ManagerDefaultsConfigPane();
    ManagerDefaultsConfigPane(const ManagerDefaultsConfigPane&);
    /*public*/ void update();
    void reloadConnections(QObjectList connList);
    virtual
    /*public*/ QString getPreferencesItem() ;
    virtual /*public*/ QString getPreferencesItemText();
    virtual
    /*public*/ QString getTabbedPreferencesTitle();
    virtual
    /*public*/ QString getLabelKey() ;
    virtual
    /*public*/ QWidget* getPreferencesComponent() ;
    virtual
    /*public*/ bool isPersistant() ;
    virtual
    /*public*/ QString getPreferencesTooltip() ;
    virtual
    /*public*/ void savePreferences() ;
    virtual
    /*public*/ bool isDirty();
    virtual
    /*public*/ bool isRestartRequired();

    /*public*/ QString className();
    /*public*/ QObject* self() {return (QObject*)this;}

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
    virtual
    /*public*/ void setSelected(bool t);
public slots:
    void On_toggled(bool);
};
#endif // MANAGERDEFAULTSCONFIGPANE_H
