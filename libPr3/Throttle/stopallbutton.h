#ifndef STOPALLBUTTON_H
#define STOPALLBUTTON_H
#include <QPushButton>

class ActionEvent;
class StopAllButton : public QPushButton
{
 Q_OBJECT
public:
 StopAllButton();
public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0) ;

};

#endif // STOPALLBUTTON_H
