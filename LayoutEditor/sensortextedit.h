#ifndef SENSORTEXTEDIT_H
#define SENSORTEXTEDIT_H

#include <QDialog>
#include "exceptions.h"
#include "sensoricon.h"
#include "jmrijframe.h"

namespace Ui {
class SensorTextEdit;
}


class SensorTextEdit : public QDialog
{
 Q_OBJECT

public:
 explicit SensorTextEdit(QWidget *parent = 0);
 ~SensorTextEdit();
 /*public*/ void initComponents(SensorIcon* l, QString name) throw (Exception);

private:
 Ui::SensorTextEdit *ui;
 SensorIcon* pl;
 QString oldInactive;
 QString oldActive;
 QString oldIncon;
 QString oldUnknown;
 static QString INIT;
private slots:
 void on_okButtonClicked();
 void on_CancelButtonClicked();

};

#endif // SENSORTEXTEDIT_H
