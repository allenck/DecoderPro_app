#ifndef DUALDECODERSELECTFRAME_H
#define DUALDECODERSELECTFRAME_H
#include "jmrijframe.h"
#include "appslib_global.h"

class APPSLIBSHARED_EXPORT DualDecoderSelectFrame : public JmriJFrame
{
 Q_OBJECT
public:
 //explicit DualDecoderSelectFrame(QWidget *parent = 0);
 /*public*/ DualDecoderSelectFrame(QString title = tr("Multi-Decoder Control"), QWidget *parent = 0);
 /*public*/ QString getClassName();

signals:

public slots:

};

#endif // DUALDECODERSELECTFRAME_H
