#ifndef USERMESSAGEPREFERENCESPANE_H
#define USERMESSAGEPREFERENCESPANE_H
#include "preferencespanel.h"
#include "libpref_global.h"

class QComboBox;
class QCheckBox;
class UserPreferencesManager;
class LIBPREFSHARED_EXPORT UserMessagePreferencesPane : public PreferencesPanel
{
    Q_OBJECT
public:
    explicit UserMessagePreferencesPane(QWidget *parent = 0);
    ~UserMessagePreferencesPane() {}
    UserMessagePreferencesPane(const UserMessagePreferencesPane&) : PreferencesPanel() {}
    /*public*/ QString getPreferencesItem();
    /*public*/ QString getPreferencesItemText();
    /*public*/ QString getTabbedPreferencesTitle();
    /*public*/ QString getLabelKey() ;
    /*public*/ QWidget* getPreferencesComponent();
    /*public*/ bool isPersistant();
    /*public*/ QString getPreferencesTooltip();
    /*public*/ void savePreferences();
    /*public*/ bool isDirty() ;
    /*public*/ bool isRestartRequired();
    /*public*/ void updateManager();

signals:

public slots:
    void propertyChange(PropertyChangeEvent* e);
private:
    UserPreferencesManager* p;
    QTabWidget* tab;// = new QTabWidget();

    /*static*/ class ListItems
    {

        QString strClass;
        QString item;
        bool included;// = false;
    public:
        ListItems(QString strClass, QString item);
        QString getClassName();
        QString getItem();
        bool isIncluded() ;
        void isIncluded(bool boo);
    };
    /*private*/ QMap<QComboBox*, ListItems*> _comboBoxes;// = new HashMap<JComboBox<Object>, ListItems>();
    /*private*/ QMap<QCheckBox*, ListItems*> _checkBoxes;// = new HashMap<>();
    bool updating;// = false;
    /*private*/ void setMinimumMessagePref();
    /*private*/ void newMessageTab();
    /*private*/ void refreshOptions();



};

#endif // USERMESSAGEPREFERENCESPANE_H
