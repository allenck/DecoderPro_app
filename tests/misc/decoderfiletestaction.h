#ifndef DECODERFILETESTACTION_H
#define DECODERFILETESTACTION_H

#include <abstractaction.h>

class Logger;
class DecoderFileTestAction : public AbstractAction
{
 Q_OBJECT
public:
 DecoderFileTestAction(QObject *parent);

public slots:
 void actionPerformed();

private:
 static Logger * log;
};

#endif // DECODERFILETESTACTION_H
