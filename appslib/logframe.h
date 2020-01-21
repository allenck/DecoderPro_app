#ifndef LOGFRAME_H
#define LOGFRAME_H
#include "jmrijframe.h"

class LogFrame : public JmriJFrame
{
public:
 LogFrame(QWidget* parent = 0);
 /*public*/ void initComponents() throw (Exception);
 /*public*/ QString getClassName();

};

#endif // LOGFRAME_H
