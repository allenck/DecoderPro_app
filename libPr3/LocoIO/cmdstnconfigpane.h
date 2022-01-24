#ifndef CMDSTNCONFIGPANE_H
#define CMDSTNCONFIGPANE_H
#include "lnpanel.h"
#include "logger.h"
#include "libPr3_global.h"

class ResourceBundle;
class LocoNetMessage;
class JActionEvent;
class QLabel;
class QPushButton;
class QRadioButton;
class QCheckBox;
class LIBPR3SHARED_EXPORT CmdStnConfigPane : public LnPanel
{
    Q_OBJECT
public:
   Q_INVOKABLE explicit CmdStnConfigPane(QWidget *parent = 0);
 ~CmdStnConfigPane() {}
 CmdStnConfigPane(const CmdStnConfigPane&) : LnPanel() {}
    /*public*/ QString getHelpTarget();
    /*public*/ QString getTitle();
    /*public*/ void initComponents(LocoNetSystemConnectionMemo* memo);
    /*public*/ void start();
    /*public*/ void dispose();

signals:

public slots:
    void updateVisibility(bool show);
    /*public*/ void readButtonActionPerformed(JActionEvent* e = 0);
    /*public*/ void writeButtonActionPerformed(JActionEvent* e = 0);
    /*public*/ void message(LocoNetMessage* msg);

private:
    int CONFIG_SLOT;// = 127 ;
    int MIN_OPTION;// = 1 ;
    int MAX_OPTION;// = 72 ;
    QString LabelT;// = "T";
    QString LabelC;// = "C";
    QString LabelTop;// = "Configure Command Station";

    QString read;// = "Read";
    QString write;// = "Write";

    QVector<int> oldcontent;// = new int[10];

    QCheckBox* optionBox;
    // internal members to hold widgets
    QPushButton* readButton;
    QPushButton* writeButton;

    QVector<QRadioButton*> closedButtons;// = new JRadioButton[MAX_OPTION];
    QVector<QRadioButton*> thrownButtons;// = new JRadioButton[MAX_OPTION];
    QVector<QLabel*> labels;// = new JLabel[MAX_OPTION];
    QVector<bool> isReserved;// = new boolean[MAX_OPTION];
    QVector<QWidget*> p2Widgets;
    Logger* log;
    void initDCS51();
    ResourceBundle* rb;
};
#if 0
class ResourceBundle : public QObject
{
 Q_OBJECT
    QMap<QString, QString>* map;
    void initDCS51();
    void initDefault();
    void initLocoBuffer();
 Logger* log;
 public:
    ResourceBundle();
    void getBundle(QString);
    QString getString(QString);
};
#endif
Q_DECLARE_METATYPE(CmdStnConfigPane)
#endif // CMDSTNCONFIGPANE_H
