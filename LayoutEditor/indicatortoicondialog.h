#ifndef INDICATORTOICONDIALOG_H
#define INDICATORTOICONDIALOG_H
#include "icondialog.h"

class JPanel;
class IndicatorTOItemPanel;
class IndicatorTOIconDialog : public IconDialog
{
 Q_OBJECT
public:
 /*public*/ IndicatorTOIconDialog(QString type, QString family, IndicatorTOItemPanel* parent, QString key,
         QMap<QString, NamedIcon*>* iconMap);

private:
 static Logger* log;
 QString _key;
 /*private*/ void addFamilySet();
 /*private*/ void createNewStatusSet();
 /*private*/ void deleteFamilySet();
 /*private*/ bool addFamilySet(QString family, QMap<QString, NamedIcon*>* iconMap, QString subFamily);

protected:
 /*protected*/ void makeAddIconButtonPanel(JPanel* buttonPanel, QString addTip, QString deleteTip);
 /*protected*/ bool doDoneAction();

};

#endif // INDICATORTOICONDIALOG_H
