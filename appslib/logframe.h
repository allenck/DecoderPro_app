#ifndef LOGFRAME_H
#define LOGFRAME_H
#include "jmrijframe.h"

class LogFrame : public JmriJFrame
{
public:
 LogFrame(QWidget* parent = 0);
 /*public*/ void initComponents() throw (Exception);

};

#endif // LOGFRAME_H
