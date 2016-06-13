#ifndef SPEEDPROFILEFRAME_H
#define SPEEDPROFILEFRAME_H
#include "jmrijframe.h"

class QPushButton;
class SpeedProfilePanel;
class SpeedProfileFrame : public JmriJFrame
{
 Q_OBJECT
public:
 explicit SpeedProfileFrame(QWidget *parent = 0);
 /*public*/ void initComponents() /*throws Exception*/;

signals:

public slots:
private:
 QPushButton* sendButton;
 SpeedProfilePanel* spPanel;

};

#endif // SPEEDPROFILEFRAME_H
