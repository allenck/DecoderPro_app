#ifndef ROSTERCONFIGPANE_H
#define ROSTERCONFIGPANE_H
#include "preferencespanel.h"
#include "libpref_global.h"

class QFileDialog;
class QLabel;
class JTextField;
class LIBPREFSHARED_EXPORT RosterConfigPane : public PreferencesPanel
{
    Q_OBJECT
public:
    explicit RosterConfigPane(QWidget *parent = 0);
    ~RosterConfigPane() {}
    RosterConfigPane(const RosterConfigPane&) : PreferencesPanel() {}
    /*public*/ QString getDefaultOwner();
    /*public*/ void setDefaultOwner(QString defaultOwner);
    /*public*/ QString getSelectedItem() ;
    /*public*/ QString getPreferencesItem();
    /*public*/ QString getPreferencesItemText();
    /*public*/ QString getTabbedPreferencesTitle() ;
    /*public*/ QString getLabelKey();
    /*public*/ QWidget* getPreferencesComponent();
    /*public*/ bool isPersistant() ;
    /*public*/ QString getPreferencesTooltip();
    /*public*/ void savePreferences();
    /*public*/ bool isDirty() ;
    /*public*/ bool isRestartRequired();

signals:

public slots:
    void On_b_clicked();
    void On_set_clicked();
private:
    QLabel* filename;
    JTextField* owner;// = new JTextField(20);
    QFileDialog* fc;
    /*private*/ bool isFileLocationChanged();

};

#endif // ROSTERCONFIGPANE_H
