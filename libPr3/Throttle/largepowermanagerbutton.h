#ifndef LARGEPOWERMANAGERBUTTON_H
#define LARGEPOWERMANAGERBUTTON_H
#include "powermanagerbutton.h"

class LargePowerManagerButton : public PowerManagerButton
{
    Q_OBJECT
public:
    explicit LargePowerManagerButton(QWidget *parent = 0);
    /*public*/ LargePowerManagerButton(bool fullText, QWidget *parent = 0);
private:
    void loadIcons();
signals:

public slots:

};

#endif // LARGEPOWERMANGERBUTTON_H
