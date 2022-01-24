#ifndef TURNOUTWIDGET_H
#define TURNOUTWIDGET_H

#include <QWidget>
#include "turnouttablewidget.h"
#include "actionlistener.h"
#include "libtables_global.h"

namespace Ui {
class TurnoutWidget;
}

class UserPreferencesManager;
class JTextField;
class JmriJFrame;
class UserPreferencesManager;
class JActionEvent;
class LIBTABLESSHARED_EXPORT TurnoutWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit TurnoutWidget(QWidget *parent = 0);
    ~TurnoutWidget();
    QVector<QString>* getSpeedListClosed();
    QVector<QString>* getSpeedListThrown();
public slots:
    void on_defaultSpeeds_triggered();
    void on_automation_triggered();

private slots:
    void on_chkFeedback_toggled(bool bState);
    void on_chkLockInfo_toggled(bool bState);
    void on_chkSpeedDetails_toggled(bool bState);
//    void on_btnAdd_clicked();
    void on_chkAuto_toggled(bool bState);
    /*private*/ void canAddRange(JActionEvent* e = 0);
    void okPressed(JActionEvent* e = 0);

private:
    Ui::TurnoutWidget *ui;
    TurnoutTableWidget* tableWidget1;
    TurnoutTableWidget* tableWidget2;
    TurnoutTableWidget* tableWidget3;
    QString defaultClosedSpeedText;
    QString defaultThrownSpeedText;
    QString useBlockSpeed;    ProxyTurnoutManager* turnManager;
    QVector<QString>* speedListClosed;
    QVector<QString>* speedListThrown;
    QVector<QString> _speedMap;
    UserPreferencesManager* p;
    JmriJFrame* addFrame;
    QComboBox* prefixBox;
    JTextField* sysName;// = new JTextField(40);
    JTextField* userName;// = new JTextField(40);
    QCheckBox* range;// = new JCheckBox("Add a range");
    JTextField* numberToAdd;// = new JTextField(5);
    Logger * log;
    bool noWarn;
    QString systemSelectionCombo;// = this.getClass().getName()+".SystemSelected";
    QString userNameError;// = this.getClass().getName()+".DuplicateUserName";
    void handleCreateException(QString sysName);
    QString showFeedbackInfo;
    QString showLockInfo;
    QString autoRetry;
    QString showSpeedDetails;

protected:
    /*protected*/ void setDefaultSpeeds(QWidget* _who);
protected slots:
    /*protected*/ void addPressed(JActionEvent* e = 0);
 friend class RangeActionListener;
 friend class OkButtonActionListener;
};
class OkButtonActionListener : public ActionListener
{
 Q_OBJECT
 TurnoutWidget* widget;
public:
 OkButtonActionListener(TurnoutWidget* widget);
public slots:
 void actionPerformed(JActionEvent *e = 0);
};

class CancelButtonActionListener : public ActionListener
{
 Q_OBJECT
 TurnoutWidget* widget;
public:
 CancelButtonActionListener(TurnoutWidget* widget);
public slots:
 void actionPerformed(JActionEvent *e = 0);
};

class RangeActionListener : public ActionListener
{
 Q_OBJECT
 TurnoutWidget* widget;
public:
 RangeActionListener(TurnoutWidget* widget);
public slots:
 void actionPerformed(JActionEvent *e = 0);
};

#endif // TURNOUTWIDGET_H
