#ifndef SMALLPOWERMANAGERBUTTON_H
#define SMALLPOWERMANAGERBUTTON_H
#include "powermanagerbutton.h"

class SmallPowerManagerButton : public PowerManagerButton
{
    Q_OBJECT
public:
    explicit SmallPowerManagerButton(QWidget *parent = 0);

signals:

public slots:
private:
    void loadIcons();

};

#endif // SMALLPOWERMANAGERBUTTON_H
