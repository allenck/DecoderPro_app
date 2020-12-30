#ifndef THROTTLESPREFERENCESPANE_H
#define THROTTLESPREFERENCESPANE_H

#include "preferencespanel.h"
#include "actionlistener.h"
#include "libpref_global.h"
class PropertyChangeEvent;
class ThrottlesPreferences;
class JFrame;
class QPushButton;
class QLabel;
class QCheckBox;
class LIBPREFSHARED_EXPORT ThrottlesPreferencesPane : public QWidget, public PreferencesPanel
{
    Q_OBJECT
 Q_INTERFACES(PreferencesPanel)

public:
    Q_INVOKABLE explicit ThrottlesPreferencesPane(QWidget *parent = 0);
    ~ThrottlesPreferencesPane() {}
    ThrottlesPreferencesPane(const ThrottlesPreferencesPane&);
    /*public*/ void setContainer(JFrame* f);
    /*public*/ QString getPreferencesItem();
    /*public*/ QString getPreferencesItemText();
    /*public*/ QString getTabbedPreferencesTitle();
    /*public*/ QString getLabelKey();
    /*public*/ QWidget* getPreferencesComponent();
    /*public*/ bool isPersistant();
    /*public*/ QString getPreferencesTooltip();
    /*public*/ void savePreferences();
    /*public*/ bool isDirty();
    /*public*/ bool isRestartRequired();
    /*public*/ QString className();
    /*public*/ QObject* self() {return (QObject*)this;}

signals:

public slots:
    /*public*/ void jbSaveActionPerformed(JActionEvent* evt = 0);
    /*public*/ void propertyChange(PropertyChangeEvent* evt);

private:
    /*private*/ QCheckBox* cbUseToolBar;
    /*private*/ QCheckBox* cbUseFunctionIcon;
    /*private*/ QCheckBox* cbResizeWinImg;
    /*private*/ QCheckBox* cbUseExThrottle;
    /*private*/ QCheckBox* cbUseRosterImage;
    /*private*/ QCheckBox* cbEnableRosterSearch;
    /*private*/ QCheckBox* cbEnableAutoLoad;
    /*private*/ QCheckBox* cbHideUndefinedButtons;
    /*private*/ QCheckBox* cbIgnoreThrottlePosition;
    /*private*/ QCheckBox* cbSaveThrottleOnLayoutSave;
    /*private*/ QLabel*	labelApplyWarning;
    /*private*/ QPushButton* jbApply;
    /*private*/ QPushButton* jbCancel;
    /*private*/ QPushButton* jbSave;
    /*private*/ JFrame* m_container;// = null;
    /*private*/ void initComponents();
    /*private*/ void setComponents(ThrottlesPreferences* tp);
private slots:
    /*private*/ void jbApplyActionPerformed(JActionEvent* evt = 0);
    /*private*/ ThrottlesPreferences* getThrottlesPreferences();
    /*private*/ void checkConsistancy(bool);
    /*private*/ void jbCancelActionPerformed(JActionEvent* evt = 0);
    void common();
};

#endif // THROTTLESPREFERENCESPANE_H
