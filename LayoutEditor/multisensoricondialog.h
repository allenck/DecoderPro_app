#ifndef MULTISENSORICONDIALOG_H
#define MULTISENSORICONDIALOG_H
#include "icondialog.h"
#include "familyitempanel.h"

class MultiSensorIconDialog : public IconDialog
{
public:
 /*public*/ MultiSensorIconDialog(QString type, QString family, FamilyItemPanel* parent,
         QHash<QString, NamedIcon*>* iconMap);


public slots:
 void onAddSensor_clicked();
 void onDeleteSensor_clicked();

private:
     /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("MultiSensorIconDialog");

protected:
 /*protected*/ QString getIconName();
 /*protected*/ void makeAddIconButtonPanel(QWidget* buttonPanel, QString addTip, QString deleteTip);
 /*protected*/ bool doDoneAction();
 /*protected*/ bool addNewIcon(QString name);

 /*protected*/ bool deleteIcon();

};

#endif // MULTISENSORICONDIALOG_H
