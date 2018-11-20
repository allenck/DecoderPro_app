#ifndef EDITCONNECTIONPREFERENCESDIALOG_H
#define EDITCONNECTIONPREFERENCESDIALOG_H
#include "jdialog.h"

class EditConnectionPreferences;
class EditConnectionPreferencesDialog : public JDialog
{
public:
 EditConnectionPreferencesDialog(QWidget* parent = nullptr);
 /*public*/ QString getTitle();
 /*public*/ bool isMultipleInstances();
 /*public*/ static bool showDialog();
 /*public*/ void gotoPreferenceItem(QString item, QString sub);
 /*public*/ void windowClosing(QCloseEvent* e);

private:
 /*final*/ EditConnectionPreferences* editConnectionPreferences;
 bool restartProgram = false;

};

#endif // EDITCONNECTIONPREFERENCESDIALOG_H
