#ifndef SIGNALHEADICONDIALOG_H
#define SIGNALHEADICONDIALOG_H
#include "icondialog.h"

class SignalHeadIconDialog : public IconDialog
{
 Q_OBJECT

public:
 /*public*/ SignalHeadIconDialog(QString type, QString family, FamilyItemPanel* parent, QMap<QString, NamedIcon*>* iconMap);

private:
 static Logger* log;
protected:
 /*protected*/ void makeDoneButtonPanel(JPanel *buttonPanel, QMap<QString, NamedIcon*>* iconMap);

};

#endif // SIGNALHEADICONDIALOG_H
