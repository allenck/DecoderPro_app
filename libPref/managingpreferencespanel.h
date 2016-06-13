#ifndef MANAGINGPREFERENCESPANEL_H
#define MANAGINGPREFERENCESPANEL_H
#include "preferencespanel.h"
#include "libpref_global.h"

class LIBPREFSHARED_EXPORT ManagingPreferencesPanel : public PreferencesPanel
{
 Q_OBJECT
public:
 explicit ManagingPreferencesPanel(QWidget *parent = 0);
 ~ManagingPreferencesPanel() {}
 ManagingPreferencesPanel(const ManagingPreferencesPanel&) : PreferencesPanel() {}
 /*public*/ /*abstract*/virtual  QList<PreferencesPanel*>* getPreferencesPanels();

signals:

public slots:

};

#endif // MANAGINGPREFERENCESPANEL_H
