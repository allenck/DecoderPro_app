#ifndef SERVERREGISTERSWIDGET_H
#define SERVERREGISTERSWIDGET_H

#include <QWidget>
#include "registerswidget.h"

namespace Ui {
class ServoRegistersWidget;
}

class ServoRegistersWidget : public QWidget
{
 Q_OBJECT
    
public:
 explicit ServoRegistersWidget(QWidget *parent = 0);
 ~ServoRegistersWidget();
 void addWidget(RegistersWidget* rw);
public slots:
 void retranslateControls();
private:
 Ui::ServoRegistersWidget *ui;
};

#endif // SERVERREGISTERSWIDGET_H
