#ifndef MONITORINGLABEL_H
#define MONITORINGLABEL_H
#include "jtextarea.h"

class PropertyChangeEvent;
class MonitoringLabel : public JTextArea
{
 Q_OBJECT
public:
 //explicit MonitoringLabel(QWidget *parent = 0);
 /*public*/ MonitoringLabel(QWidget *parent = 0);
 /*public*/ MonitoringLabel(int row, int col, QWidget *parent = 0);

signals:

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* evt);

};

#endif // MONITORINGLABEL_H
