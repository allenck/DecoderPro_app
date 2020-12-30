#ifndef ADDPROFILEDIALOG_H
#define ADDPROFILEDIALOG_H
#include "jdialog.h"

class QFrame;
class JActionEvent;
class Profile;
class Logger;
class QPushButton;
class JSeparator;
class QLabel;
class JTextField;
class AddProfileDialog : public JDialog
{
 Q_OBJECT
public:
 //explicit AddProfileDialog(QWidget *parent = 0);
 /*public*/ AddProfileDialog(QFrame* parent, bool modal, bool setNextProfile);
 AddProfileDialog(QWidget* parent, bool modal, bool setNextProfile);
 // <editor-fold defaultstate="collapsed" desc="Generated Code">
 void setSourceProfile(Profile* profile);

signals:

public slots:
private:
 // Variables declaration - do not modify
 /*private*/ QPushButton* btnBrowse;
 /*private*/ QPushButton* btnCancel;
 /*private*/ QPushButton* btnOk;
 /*private*/ JSeparator*  jSeparator1;
 /*private*/ JSeparator*  jSeparator2;
 /*private*/ QLabel*  lblProfileFolder;
 /*private*/ QLabel*  lblProfileLocation;
 /*private*/ QLabel*  lblProfileName;
 /*private*/ QLabel*  lblProfileNameAndLocation;
 /*private*/ JTextField*  profileFolder;
 /*private*/ JTextField*  profileLocation;
 /*private*/ JTextField*  profileName;
 // End of variables declaration
 /*private*/ static /*final*/ Logger* log;// = LoggerFactory::getLogger("AddProfileDialog");
// /*private*/ static final long serialVersionUID = -2838864019793309792L;
 /*private*/ QString profileId;
 /*private*/ bool setNextProfile;// = false;
 /*private*/ Profile* source;// = null;
 /*private*/ void initComponents();

private slots:
 /*private*/ void profileNameActionPerformed(JActionEvent* evt = 0);
 /*private*/ void btnBrowseActionPerformed(JActionEvent* evt = 0);
 /*private*/ void profileFolderActionPerformed(JActionEvent* evt = 0);
 /*private*/ void profileLocationActionPerformed(JActionEvent* evt = 0);
 /*private*/ void btnCancelActionPerformed(JActionEvent* evt = 0);
 /*private*/ void btnOkActionPerformed(JActionEvent* evt = 0);

};

#endif // ADDPROFILEDIALOG_H
