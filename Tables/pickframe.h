#ifndef PICKFRAME_H
#define PICKFRAME_H
#include "../LayoutEditor/jmrijframe.h"

class PickFrame : public JmriJFrame
{
    Q_OBJECT
public:
    //explicit PickFrame(QWidget *parent = 0);
    /*public*/ PickFrame(QString _title, QWidget *parent= 0);

signals:

public slots:
private:
    /*private*/ void makeMenus();

};

#endif // PICKFRAME_H
