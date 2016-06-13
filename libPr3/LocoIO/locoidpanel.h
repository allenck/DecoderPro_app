#ifndef LOCOIDPANEL_H
#define LOCOIDPANEL_H
#include "lnpanel.h"
#include "libPr3_global.h"

class LnTrafficController;
class LocoNetMessage;
class QPushButton;
class JTextArea;
class QComboBox;
class LIBPR3SHARED_EXPORT LocoIdPanel : public LnPanel
{
 Q_OBJECT
public:
 explicit LocoIdPanel(QWidget *parent = 0);
 ~LocoIdPanel() {}
 LocoIdPanel(const LocoIdPanel&) : LnPanel() {}
 /*public*/ void initComponents() /*throws Exception*/;
 /*public*/ QString getHelpTarget();
 /*public*/ QString getTitle();
 /*public*/ void initComponents(LocoNetSystemConnectionMemo* memo);
 /*public*/ void dispose();

signals:

public slots:
 /*public*/ void setButtonActionPerformed();
 /*public*/ void readButtonActionPerformed();
 /*public*/ void message(LocoNetMessage* m);
 /*public*/ void connectTc(LnTrafficController* t);

private:
 // member declarations
 QPushButton* readButton;
 QPushButton* setButton;
 JTextArea* value;

 QComboBox* idBox;
 QStringList IDValues;//[] = {"-", "0", "1", "2", "3", "4", "5", "6", "7"};
 LocoNetMessage* createReadPacket();
 LocoNetMessage* createSetPacket(QString s);


};
Q_DECLARE_METATYPE(LocoIdPanel)
#endif // LOCOIDPANEL_H
