#ifndef DECODER3ACTION_H
#define DECODER3ACTION_H

#include "jmriabstractaction.h"

class WindowInterface;
class DecoderPro3Window;
class Decoder3Action : public JmriAbstractAction
{
 Q_OBJECT
public:
 //explicit Decoder3Action(QObject *parent = 0);
 /*public*/ Decoder3Action(QString s, WindowInterface* wi);
 /*public*/ Decoder3Action(QString s, QIcon i, WindowInterface* wi);
 /*public*/ Decoder3Action(QString pName, bool allowQuit, QObject *parent);

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* event = 0);

private:
 DecoderPro3Window* mainFrame;
 bool allowQuit;// = true;
 void common();
};

#endif // DECODER3ACTION_H
