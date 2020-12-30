#ifndef SIMPLETURNOUTCTRLFRAME_H
#define SIMPLETURNOUTCTRLFRAME_H
#include "jmrijframe.h"
#include "liblayouteditor_global.h"

class Exception;
class AbstractTurnout;
class JActionEvent;
class QLabel;
class QPushButton;
class JTextField;
class Turnout;
class LIBLAYOUTEDITORSHARED_EXPORT SimpleTurnoutCtrlFrame : public JmriJFrame
{
    Q_OBJECT
public:
    explicit SimpleTurnoutCtrlFrame(QWidget *parent = 0);
 /*public*/ QString getClassName();

signals:

public slots:
    /*public*/ void closeButtonActionPerformed(JActionEvent* e = 0);
    /*public*/ void throwButtonActionPerformed(JActionEvent* e = 0);
    /*public*/ void lockButtonActionPerformed(JActionEvent* e = 0);
    /*public*/ void lockPushButtonActionPerformed(JActionEvent* e = 0);
    /*public*/ void propertyChange(PropertyChangeEvent* e);

private:
    // GUI member declarations
    JTextField* adrTextField;// = new JTextField(8);

    QPushButton* throwButton;// = new QPushButton();
    QPushButton* closeButton;// = new QPushButton();

    QLabel* nowStateLabel;// = new QLabel();

    QLabel* nowFeedbackLabel;// = new QLabel();

    QLabel* lockButtonLabel;// = new QLabel();
    QPushButton* lockButton;// = new QPushButton();

    QLabel* lockPushButtonLabel;// = new QLabel();
    QPushButton* lockPushButton;// = new QPushButton();

    AbstractTurnout* turnout;// = null;
    QString newState;// = "";
    /*private*/ static /*final*/ QString LOCKED;// = "Locked";
    /*private*/ static /*final*/ QString UNLOCKED;// = "Normal";
    /*private*/ void updateTurnoutStatusFields();
    Logger* log;
    void invalidTurnout(QString name, Exception ex);
private slots:
    void on_adrTextField_textEdited(QString);
    void on_adrTextField_editingFinished();
};

#endif // SIMPLETURNOUTCTRLFRAME_H
