#ifndef EXTRAOPCODEDEFINITIONWIDGET_H
#define EXTRAOPCODEDEFINITIONWIDGET_H

#include <QWidget>

namespace Ui {
class ExtraOpcodeDefinitionWidget;
}

class ExtraOpcodeDefinitionWidget : public QWidget
{
 Q_OBJECT
    
public:
 explicit ExtraOpcodeDefinitionWidget(int extra, QWidget *parent = 0);
 ~ExtraOpcodeDefinitionWidget();
public slots:
 void retranslateControls();

private:
 Ui::ExtraOpcodeDefinitionWidget *ui;
 void paintEvent(QPaintEvent *);
};

#endif // EXTRAOPCODEDEFINITIONWIDGET_H
