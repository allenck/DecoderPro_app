#ifndef ADDPROFILEDIALOG_H
#define ADDPROFILEDIALOG_H
#include "jdialog.h"

class QFrame;
class ActionEvent;
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
//    /*private*/ static final Logger log = LoggerFactory.getLogger(AddProfileDialog.class);
 Logger * log;
// /*private*/ static final long serialVersionUID = -2838864019793309792L;
 /*private*/ QString profileId;
 /*private*/ bool setNextProfile;// = false;
 /*private*/ Profile* source;// = null;
 /*private*/ void initComponents();
 void setSourceProfile(Profile* profile);

private slots:
 /*private*/ void profileNameActionPerformed(ActionEvent* evt = 0);
 /*private*/ void btnBrowseActionPerformed(ActionEvent* evt = 0);
 /*private*/ void profileFolderActionPerformed(ActionEvent* evt = 0);
 /*private*/ void profileLocationActionPerformed(ActionEvent* evt = 0);
 /*private*/ void btnCancelActionPerformed(ActionEvent* evt = 0);
 /*private*/ void btnOkActionPerformed(ActionEvent* evt = 0);

};

#endif // ADDPROFILEDIALOG_H
