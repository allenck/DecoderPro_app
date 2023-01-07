#ifndef ROSTERCONFIGPANE_H
#define ROSTERCONFIGPANE_H
#include "preferencespanel.h"
#include "libpref_global.h"

class QFileDialog;
class QLabel;
class JTextField;
class LIBPREFSHARED_EXPORT RosterConfigPane : public QWidget, public PreferencesPanel, public InstanceManagerAutoDefault
{
    Q_OBJECT
 Q_INTERFACES(PreferencesPanel InstanceManagerAutoDefault)

public:
   Q_INVOKABLE  explicit RosterConfigPane(QWidget *parent = 0);
    ~RosterConfigPane() {}
    RosterConfigPane(const RosterConfigPane&) : QWidget() {}
    /*public*/ QString getDefaultOwner();
    /*public*/ void setDefaultOwner(QString defaultOwner);
    /*public*/ QString getSelectedItem() ;
    /*public*/ QString getPreferencesItem() override;
    /*public*/ QString getPreferencesItemText() override;
    /*public*/ QString getTabbedPreferencesTitle()  override;
    /*public*/ QString getLabelKey() override;
    /*public*/ QWidget* getPreferencesComponent() override;
    /*public*/ bool isPersistant()  override;
    /*public*/ QString getPreferencesTooltip() override;
    /*public*/ void savePreferences() override;
    /*public*/ bool isDirty() override ;
    /*public*/ bool isRestartRequired() override;
    /*public*/ bool isPreferencesValid() override;
    /*public*/ QString className() override;

    /*public*/ QObject* ppself() override {return (QObject*)this;}


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
