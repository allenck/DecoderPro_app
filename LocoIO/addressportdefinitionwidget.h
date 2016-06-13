#ifndef ADDRESSPORTDEFINITION_H
#define ADDRESSPORTDEFINITION_H

#include <QWidget>
#include "locoiodata.h"

namespace Ui {
class AddressPortDefinitionWidget;
}

class AddressPortDefinitionWidget : public QWidget
{
 Q_OBJECT
    
public:
 explicit AddressPortDefinitionWidget(LocoIOData* data, QWidget *parent = 0);
 ~AddressPortDefinitionWidget();
public slots:
 void retranslateControls();

private:
 Ui::AddressPortDefinitionWidget *ui;
 LocoIOData* data;

};

#endif // ADDRESSPORTDEFINITION_H
