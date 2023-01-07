#ifndef PROGRAMMERCONFIGPANE_H
#define PROGRAMMERCONFIGPANE_H

#include "preferencespanel.h"
#include "libpref_global.h"
class QCheckBox;
class QComboBox;
class LIBPREFSHARED_EXPORT ProgrammerConfigPane : public QWidget, public PreferencesPanel, public InstanceManagerAutoDefault
{
    Q_OBJECT
 Q_INTERFACES(PreferencesPanel InstanceManagerAutoDefault)

public:
    Q_INVOKABLE explicit ProgrammerConfigPane(QWidget *parent = 0);
    ~ProgrammerConfigPane() {}
    ProgrammerConfigPane(const ProgrammerConfigPane&);
    /*public*/ QString getSelectedItem();
    /*public*/ QWidget* getAdvancedPanel() ;
    /*public*/ bool getShowEmptyTabs() ;
    /*public*/ bool getShowCvNums();
    /*public*/ virtual QString getPreferencesItem()  override;
    /*public*/ virtual QString getPreferencesItemText() override;
    /*public*/ virtual QString getTabbedPreferencesTitle() override;
    /*public*/ virtual QString getLabelKey() override;
    /*public*/ virtual QWidget* getPreferencesComponent() override;
    /*public*/ virtual bool isPersistant() override;
    /*public*/ virtual QString getPreferencesTooltip() override;
    /*public*/ virtual void savePreferences() override;
    /*public*/ virtual bool isDirty() override;
    /*public*/ virtual bool isRestartRequired() override;
    /*public*/ bool isPreferencesValid() override;
    /*public*/ QString className();
    /*public*/ QObject* ppself() override{return (QObject*)this;}

signals:

public slots:
private:
    QComboBox* programmerBox;
    QWidget* advancedPanel;
    QCheckBox* showEmptyTabs;
    QCheckBox* ShowCvNums;
    void common();
};
#endif // PROGRAMMERCONFIGPANE_H
