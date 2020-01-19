#ifndef MANAGINGPREFERENCESPANEL_H
#define MANAGINGPREFERENCESPANEL_H
#include "preferencespanel.h"
#include "libpref_global.h"
#include "jtabbedpane.h"

class QToolButton;
class LIBPREFSHARED_EXPORT ManagingPreferencesPanel : public JTabbedPane, public PreferencesPanel
{
 Q_OBJECT
 Q_INTERFACES(PreferencesPanel)
public:
 explicit ManagingPreferencesPanel(QWidget *parent = 0);
 ~ManagingPreferencesPanel() {}
 ManagingPreferencesPanel(const ManagingPreferencesPanel&) : JTabbedPane() {}
 /*public*/ /*abstract*/virtual  QList<PreferencesPanel*>* getPreferencesPanels();
 /*public*/ QString className();
 /*public*/ QObject* self() {return (QObject*)this;}

signals:

public slots:

};
Q_DECLARE_METATYPE(ManagingPreferencesPanel)
#endif // MANAGINGPREFERENCESPANEL_H
