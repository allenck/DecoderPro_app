#ifndef PROFILEMANAGERDIALOG_H
#define PROFILEMANAGERDIALOG_H
#include "jdialog.h"
#include "propertychangelistener.h"
#include "exceptions.h"
#include <QModelIndex>
#include <QPushButton>
#include "libpref_global.h"

class IndexedPropertyChangeEvent;
class ListSelectionEvent;
class Profile;
class WindowEvent;
class ActionEvent;
class JFrame;
class QScrollArea;
class QLabel;
class QListView;
class LIBPREFSHARED_EXPORT ProfileManagerDialog : public JDialog
{
    Q_OBJECT
public:
    //explicit ProfileManagerDialog(QWidget *parent = 0);
    /*public*/ ProfileManagerDialog(JFrame* parent, bool modal);
    /*public*/ static Profile* getStartingProfile(JFrame* f) throw (IOException);

signals:

public slots:
 void propertyChange(IndexedPropertyChangeEvent* evt);

private:
    /*private*/ QTimer* timer;
    /*private*/ int countDown;
    // Variables declaration - do not modify
    /*private*/ QPushButton* btnCreate;
    /*private*/ QPushButton* btnSelect;
    /*private*/ QPushButton* btnUseExisting;
    /*private*/ QLabel* countDownLbl;
//    /*private*/ QScrollArea* jScrollPane1;
    /*private*/ QLabel* listLabel;
    /*private*/ QListView* profiles;
    // End of variables declaration
    /*private*/ void initComponents();
    Logger* log;
private slots:
    /*private*/ void btnSelectActionPerformed(ActionEvent* /*evt*/ = 0);
    /*private*/ void btnCreateActionPerformed(ActionEvent* /*evt*/= 0);
    /*private*/ void btnUseExistingActionPerformed(ActionEvent* /*evt*/= 0);
    /*private*/ void profileNameChanged(Profile* p);
    /*private*/ void profilesValueChanged(QModelIndex);
    /*private*/ void profilesKeyPressed(QKeyEvent* evt);
    /*private*/ void formWindowOpened(QShowEvent* /*evt*/);
    void keyPressEvent(QKeyEvent *evt);
    void mousePressEvent(QMouseEvent *);
    void closeEvent(QCloseEvent *);
    void showEvent(QShowEvent *);
    void timeout();
};



#endif // PROFILEMANAGERDIALOG_H
