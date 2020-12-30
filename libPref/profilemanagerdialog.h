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
class JActionEvent;
class JFrame;
class QScrollArea;
class QLabel;
class JList;
class LIBPREFSHARED_EXPORT ProfileManagerDialog : public JDialog
{
    Q_OBJECT
public:
    //explicit ProfileManagerDialog(QWidget *parent = 0);
    /*public*/ ProfileManagerDialog(JFrame* parent, bool modal);
    /*public*/ static Profile* getStartingProfile(JFrame* f) throw (IOException);

signals:

public slots:
 //void propertyChange(IndexedPropertyChangeEvent* evt);

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
    /*private*/ JList* profiles = nullptr;
    // End of variables declaration
    /*private*/ void initComponents();
    Logger* log;
private slots:
    /*private*/ void btnSelectActionPerformed(JActionEvent* /*evt*/ = 0);
    /*private*/ void btnCreateActionPerformed(JActionEvent* /*evt*/= 0);
    /*private*/ void btnUseExistingActionPerformed(JActionEvent* /*evt*/= 0);
    /*private*/ void profileNameChanged(Profile* p);
    /*private*/ void profilesValueChanged(QModelIndex);
    /*private*/ void profilesKeyPressed(QKeyEvent* evt);
    /*private*/ void formWindowOpened(QShowEvent* /*evt*/);
    void keyPressEvent(QKeyEvent *evt);
    void mousePressEvent(QMouseEvent *);
    void closeEvent(QCloseEvent *);
    void showEvent(QShowEvent *);
    void timeout();
    friend class PMDPropertyChangeListener1;
    friend class PMDPropertyChangeListener2;
};

class PMDPropertyChangeListener1 : public PropertyChangeListener
{
 Q_OBJECT
 ProfileManagerDialog* dlg;
public:
 PMDPropertyChangeListener1(ProfileManagerDialog* dlg) {this->dlg = dlg;}
public slots:
 void propertyChange(PropertyChangeEvent* evt);
};

class PMDPropertyChangeListener2 : public PropertyChangeListener
{
 Q_OBJECT
 ProfileManagerDialog* dlg;
public:
 PMDPropertyChangeListener2(ProfileManagerDialog* dlg) {this->dlg = dlg;}
public slots:
 void propertyChange(PropertyChangeEvent*evt);
};


#endif // PROFILEMANAGERDIALOG_H
