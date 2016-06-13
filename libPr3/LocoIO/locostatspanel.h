#ifndef LOCOSTATSPANEL_H
#define LOCOSTATSPANEL_H
#include "lnpanel.h"
#include "logger.h"
#include "lnnamedpaneaction.h"
#include "QMetaType"
#include "libPr3_global.h"

class LocoNetMessage;
class JTextField;
class QPushButton;
class LIBPR3SHARED_EXPORT LocoStatsPanel : public LnPanel
{
 Q_OBJECT
public:
 explicit LocoStatsPanel(QWidget *parent = 0);
 ~LocoStatsPanel() {}
 LocoStatsPanel(const LocoStatsPanel&) : LnPanel() {}
 /*public*/ QString getHelpTarget();
 /*public*/ QString getTitle();
 // /*public*/ LocoStatsPanel();
 /*public*/ void initComponents();
 /*public*/ void initComponents(LocoNetSystemConnectionMemo* memo);
 /*public*/ void dispose();

signals:

public slots:
 /*public*/ void message(LocoNetMessage* msg);
 /*public*/ void requestUpdate();

private:
 Logger* log;
 /**
  *
  */
 //private static final long serialVersionUID = -5940710123873302443L;
 QWidget* lb2Panel;
 QWidget* rawPanel;
 QWidget* pr2Panel;
 QWidget* ms100Panel;
 JTextField* r1;// = new JTextField(5);
 JTextField* r2;// = new JTextField(5);
 JTextField* r3;// = new JTextField(5);
 JTextField* r4;// = new JTextField(5);
 JTextField* r5;// = new JTextField(5);
 JTextField* r6;// = new JTextField(5);
 JTextField* r7;// = new JTextField(5);
 JTextField* r8;// = new JTextField(5);

 JTextField* serial;// = new JTextField(6);
 JTextField* status;// = new JTextField(5);
 JTextField* current;// = new JTextField(4);
 JTextField* hardware;// = new JTextField(2);
 JTextField* software;// = new JTextField(3);

 JTextField* goodMsgCnt;// = new JTextField(5);
 JTextField* badMsgCnt;// = new JTextField(5);
 JTextField* ms100status;// = new JTextField(6);

 JTextField* version;// = new JTextField(8);
 JTextField* breaks;// = new JTextField(6);
 JTextField* errors;// = new JTextField(6);

 bool updatePending;// = false;
 void report(QString msg);
 QPushButton* updateButton;// = new JButton("Update");

 void revalidate() {}
};
#if 0

/**
 * Nested class to create one of these using old-style defaults
 */
/*static*/ /*public*/ class Default : public LnNamedPaneAction
{
 Q_OBJECT
    /**
     *
     */
//    private static final long serialVersionUID = -5534308120479708337L;
public:
    /*public*/ Default();
};
#endif
Q_DECLARE_METATYPE(LocoStatsPanel)
#endif // LOCOSTATSPANEL_H
