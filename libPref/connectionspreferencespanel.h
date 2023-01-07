#ifndef CONNECTIONPREFERENCESPANEL_H
#define CONNECTIONPREFERENCESPANEL_H
#include "managingpreferencespanel.h"
#include "logger.h"
#include "actionlistener.h"
#include "libpref_global.h"
#include <QEvent>
#include <QToolButton>
#include "jbutton.h"
#include "propertychangelistener.h"
#include "jtabbedpane.h"
#include "instancemanagerautodefault.h"

class PropertyChangeEvent;
class JButton;
class QCheckBox;
class TabbedPreferences;
class ImageIcon;
class JmrixConfigPane;

class LIBPREFSHARED_EXPORT ConnectionsPreferencesPanel : public JTabbedPane, public /*ManagingPreferencesPanel*/PreferencesPanel,
  public PropertyChangeListener, public InstanceManagerAutoDefault
{
  Q_OBJECT
  Q_INTERFACES (/*ManagingPreferencesPanel*/PreferencesPanel PropertyChangeListener InstanceManagerAutoDefault)
public:
    Q_INVOKABLE explicit ConnectionsPreferencesPanel(QWidget *parent = 0);
//    /*public*/ ConnectionsPreferencesPanel(TabbedPreferences* preference, QWidget* parent=0);
    ~ConnectionsPreferencesPanel()  {}
    ConnectionsPreferencesPanel(const ConnectionsPreferencesPanel &);  //: PreferencesPanel(parent)
    /*public*/ QString getPreferencesItem() override;
    /*public*/ QString getPreferencesItemText() override;
    /*public*/ QString getTabbedPreferencesTitle() override;
    /*public*/ QString getLabelKey() override;
    /*public*/ QWidget* getPreferencesComponent()  override;
    /*public*/ bool isPersistant() override;
    /*public*/ QString getPreferencesTooltip()  override;
    /*public*/ void savePreferences() override ;
    /*public*/ bool isDirty() override ;
    /*public*/ bool isRestartRequired() override;
    /*public*/ bool isPreferencesValid() override ;
    /*public*/ QList<PreferencesPanel *> getPreferencesPanels() /*override*/;
    /*public*/ QString className() override;

    QObject* pself() override {return this;}
    QObject* ppself() override {return this;}
    QWidget* jself() override {return this;}

signals:

public slots:
    void On_currentChanged(int);
    void propertyChange(PropertyChangeEvent*evt) override;

private:
    //MyTabWidget* tabWidget;
//    /*private*/ /*final*/ TabbedPreferences* preferences;
    /*private*/ /*final*/ QIcon deleteIcon;
    /*private*/ /*final*/ QIcon deleteIconRollOver;
    /*private*/ /*final*/ QSize deleteButtonSize;
    /*private*/ QIcon addIcon;
    /*private*/ bool restartRequired = false;

    /*private*/ QList<JmrixConfigPane*> configPanes = QList<JmrixConfigPane*>();
    void common();
    /*private*/ void activeTab();
    /*private*/ void addConnection(int tabPosition, /*final*/ JmrixConfigPane* configPane);
    void addConnectionTab();
    /*private*/ void newConnectionTab() ;
    /*private*/ void removeTab(/*ActionEvent* e,*/ int x);
    static Logger* log;
    int indexOfTab(QString text);
    bool bDeleteFlag;
 friend class CloseButtonListener;
};
Q_DECLARE_METATYPE(ConnectionsPreferencesPanel);

class DisableCheckboxListener : public QObject, public ActionListener
{
    Q_OBJECT
    Q_INTERFACES(ActionListener)
    JmrixConfigPane* configPane;
    QCheckBox* checkBox;
public:
    DisableCheckboxListener(JmrixConfigPane* configPane, QCheckBox* checkBox);
    QObject* self() override {return (QObject*)this;}
public slots:
    void actionPerformed(JActionEvent * = 0)override;
};

class CloseButtonListener : public QObject, public ActionListener
{
    Q_OBJECT
    Q_INTERFACES(ActionListener)
    int index;
    ConnectionsPreferencesPanel* parent;
public:
    CloseButtonListener(int index, ConnectionsPreferencesPanel* parent);
    QObject* self() override {return (QObject*)this;}
public slots:
    void actionPerformed(JActionEvent * = 0) override;
};
#endif // CONNECTIONPREFERENCESPANEL_H
