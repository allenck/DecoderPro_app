#ifndef JPANEL_H
#define JPANEL_H
#include <QFrame>
#include "border.h"

class JPanel : public QFrame
{
 Q_OBJECT
public:
 JPanel(QWidget* parent = 0);
 /*public*/ void setBorder(Border* border);

};
#endif // JPANEL_H
