#ifndef PORTDEFINITIONWIDGET_H
#define PORTDEFINITIONWIDGET_H

#include <QWidget>

namespace Ui {
class InPortDefinitionWidget;
}

class InPortDefinitionWidget : public QWidget
{
 Q_OBJECT
    
public:
 explicit InPortDefinitionWidget(QWidget *parent = 0);
 ~InPortDefinitionWidget();
 void setServoOpt();

public slots:
 void retranslateControls();

private:
    Ui::InPortDefinitionWidget *ui;
};

#endif // PORTDEFINITIONWIDGET_H
