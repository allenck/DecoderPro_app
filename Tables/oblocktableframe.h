#ifndef OBLOCKTABLEFRAME_H
#define OBLOCKTABLEFRAME_H
#include "beantableframe.h"

class OBlockTablePanel;
class OBlockTableFrame : public BeanTableFrame
{
    Q_OBJECT
public:
    OBlockTableFrame(OBlockTablePanel* panel, QString helpTarget, QWidget* parent = nullptr);
    /*public*/ void dispose();

private:
    OBlockTablePanel* oblockPanel;

};

#endif // OBLOCKTABLEFRAME_H
