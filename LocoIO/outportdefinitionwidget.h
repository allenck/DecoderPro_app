#ifndef OUTPORTDEFINITIONWIDGET_H
#define OUTPORTDEFINITIONWIDGET_H

#include <QWidget>
#include "locoiodata.h"

namespace Ui {
class OutPortDefinitionWidget;
}

class OutPortDefinitionWidget : public QWidget
{
 Q_OBJECT
public:
 explicit OutPortDefinitionWidget(LocoIOData* data, QWidget *parent = 0);
 ~OutPortDefinitionWidget();
 void setBlinkSb(int rate);
public slots:
 void retranslateControls();

private:
 Ui::OutPortDefinitionWidget *ui;
 LocoIOData* data;
 bool bSetting;
private slots:
 void on_sbBlinkRate_valueChanged(int val);

};

#endif // OUTPORTDEFINITIONWIDGET_H
