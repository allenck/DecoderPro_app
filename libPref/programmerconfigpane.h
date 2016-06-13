#ifndef PROGRAMMERCONFIGPANE_H
#define PROGRAMMERCONFIGPANE_H

#include "preferencespanel.h"
#include "libpref_global.h"
class QCheckBox;
class QComboBox;
class LIBPREFSHARED_EXPORT ProgrammerConfigPane : public PreferencesPanel
{
    Q_OBJECT
public:
    explicit ProgrammerConfigPane(QWidget *parent = 0);
    ~ProgrammerConfigPane() {}
    ProgrammerConfigPane(const ProgrammerConfigPane&);
    /*public*/ QString getSelectedItem();
    /*public*/ QWidget* getAdvancedPanel() ;
    /*public*/ bool getShowEmptyTabs() ;
    /*public*/ bool getShowCvNums();
    /*public*/ virtual QString getPreferencesItem() ;
    /*public*/ virtual QString getPreferencesItemText();
    /*public*/ virtual QString getTabbedPreferencesTitle();
    /*public*/ virtual QString getLabelKey();
    /*public*/ virtual QWidget* getPreferencesComponent();
    /*public*/ virtual bool isPersistant();
    /*public*/ virtual QString getPreferencesTooltip();
    /*public*/ virtual void savePreferences();
    /*public*/ virtual bool isDirty();
    /*public*/ virtual bool isRestartRequired();
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
