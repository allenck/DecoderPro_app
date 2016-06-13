#ifndef SLIPTURNOUTTEXTEDIT_H
#define SLIPTURNOUTTEXTEDIT_H
#include "jmrijframe.h"

class QLabel;
class QPushButton;
class JTextField;
class SlipTurnoutIcon;
class SlipTurnoutTextEdit : public JmriJFrame
{
    Q_OBJECT
public:
    explicit SlipTurnoutTextEdit(QWidget *parent = 0);
    /*public*/ void initComponents(SlipTurnoutIcon* l, QString name); //throw (Exception);
    /*public*/ void closeEvent(QCloseEvent* e);

signals:

public slots:
private:
    SlipTurnoutIcon* pl; 	// layout positional label tracked by this frame
    static /*final*/ QString INIT;// = "";
    QString oldLWUE;// = INIT;
    QString oldUWLE;// = INIT;
    QString oldLWLE;// = INIT;
    QString oldUWUE;// = INIT;

    // member declarations
    QLabel* lableName;// = new QLabel();
    QLabel* nameText;// = new QLabel();
    QLabel* textLWUE;// = new QLabel();
    QLabel* textUWLE;// = new QLabel();
    QLabel* textLWLE;// = new QLabel();
    QLabel* textUWUE;// = new QLabel();

    // buttons
    QPushButton* okButton;// = new QPushButton();
    QPushButton* cancelButton;// = new QPushButton();

    // text field
    JTextField* UWLETextField;// = new JTextField(15);
    JTextField* LWUETextField;// = new JTextField(15);
    JTextField* LWLETextField;// = new JTextField(15);
    JTextField* UWUETextField;// = new JTextField(15);

    // for padding out panel
    QLabel* space1;// = new QLabel();
    QLabel* space2;// = new QLabel();

    /*private*/ void addItem(QWidget* c, int x, int y);

  private slots:
    void on_okButton();
    void on_cancelButton();
};

#endif // SLIPTURNOUTTEXTEDIT_H
