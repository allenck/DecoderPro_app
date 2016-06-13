#ifndef BOOSTERPANEL_H
#define BOOSTERPANEL_H

#include <QWidget>

namespace Ui {
class BoosterPanel;
}

class BoosterPanel : public QWidget
{
    Q_OBJECT
    
public:
    explicit BoosterPanel(QWidget *parent = 0);
    ~BoosterPanel();
public slots:
 void retranslateControls();

private:
    Ui::BoosterPanel *ui;
};

#endif // BOOSTERPANEL_H
