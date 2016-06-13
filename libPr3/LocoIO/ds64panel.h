#ifndef DS64PANEL_H
#define DS64PANEL_H
#include "abstractboardprogpanel.h"
#include <QCheckBox>
#include "libPr3_global.h"

class QCheckBox;
class LIBPR3SHARED_EXPORT DS64Panel : public AbstractBoardProgPanel
{
 Q_OBJECT
public:
 explicit DS64Panel(QWidget *parent = 0);
 ~DS64Panel() {}
 DS64Panel(const DS64Panel&) : AbstractBoardProgPanel() {}
 /*public*/ DS64Panel(int boardNum, QWidget* parent);
 /*public*/ QString getHelpTarget();
 /*public*/ QString getTitle();

signals:

public slots:

private:
 void common(int boardNum);
 QCheckBox* opsw1;// = new QCheckBox("OpSw 01: Static Output Type (Pulse if off)");
 QCheckBox* opsw2;// = new QCheckBox("OpSw 02: Pulse Timeout  200ms");
 QCheckBox* opsw3;// = new QCheckBox("OpSw 03: Pulse Timeout  400ms");
 QCheckBox* opsw4;// = new QCheckBox("OpSw 04: Pulse Timeout  800ms");
 QCheckBox* opsw5;// = new QCheckBox("OpSw 05: Pulse Timeout 1600ms");
 QCheckBox* opsw6;// = new QCheckBox("OpSw 06: Output Power Management - Wait for 1st command");
 QCheckBox* opsw7;// = new QCheckBox("OpSw 07: Reset Functions to Factory Default");
 QCheckBox* opsw8;// = new QCheckBox("OpSw 08: Double normal startup delay");
 QCheckBox* opsw9;// = new QCheckBox("OpSw 09: Turn off static outputs after 16sec");
 QCheckBox* opsw10;// = new QCheckBox("OpSw 10: DS64 accepts computer commands only");
 QCheckBox* opsw11;// = new QCheckBox("OpSw 11: Routes work from input lines");
 QCheckBox* opsw12;// = new QCheckBox("OpSw 12: Either input high causes toggle");
 QCheckBox* opsw13;// = new QCheckBox("OpSw 13: All eight inputs send sensor messages");
 QCheckBox* opsw14;// = new QCheckBox("OpSw 14: Switch commands from track only");
 QCheckBox* opsw15;// = new QCheckBox("OpSw 15: Outputs ignore inputs");
 QCheckBox* opsw16;// = new QCheckBox("OpSw 16: Disable routes");
 QCheckBox* opsw17;// = new QCheckBox("OpSw 17: Output 1 is crossing gate");
 QCheckBox* opsw18;// = new QCheckBox("OpSw 18: Output 2 is crossing gate");
 QCheckBox* opsw19;// = new QCheckBox("OpSw 19: Output 3 is crossing gate");
 QCheckBox* opsw20;// = new QCheckBox("OpSw 20: Output 4 is crossing gate");
 QCheckBox* opsw21;// = new QCheckBox("OpSw 21: Send turnout sensor messages (general sensor messages if off)");
 Logger* log;

protected:
 /*protected*/ void copyToOpsw();
 /*protected*/ void updateDisplay();
 /*protected*/ int nextState(int state);

};
Q_DECLARE_METATYPE(DS64Panel)
#endif // DS64PANEL_H
