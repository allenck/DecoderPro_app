#ifndef SDFMACRO_H
#define SDFMACRO_H
#include "sdfconstants.h"

class Logger;
class SdfBuffer;
class SdfMacro : public QObject
{
 Q_OBJECT
public:
 explicit SdfMacro(QObject *parent = 0);
 /*abstract*/ /*public*/ virtual QString name();
 /*abstract*/ /*public*/ int length();
 /*abstract*/ /*public*/ QString toString();
 /*abstract*/ /*public*/ virtual QString oneInstructionString();
 /*abstract*/ /*public*/ virtual QString allInstructionString(QString indent);
 /*public*/ QList<SdfMacro*>* getChildren();
 /*public*/ int totalLength();
 /*public*/ void loadByteArray(SdfBuffer* buffer);
 static /*public*/ SdfMacro* decodeInstruction(SdfBuffer* buff);

signals:

public slots:
private:
 /**
  * Local member hold list of child (contained) instructions
  */
 QList<SdfMacro*>* children;// = null;  // not changed unless there are some!
 /**
  * Local method contains comment text associated with this instruction
  */
 QString comment;
 QString decodeFlags(int input, QVector<int> values, QVector<int> masks, QStringList labels);
 QString decodeState(int input, QVector<int> values, QStringList labels);
 Logger* log;
 friend class ChannelStart;
 friend class SkemeStart;
 friend class SkipOnTrigger;
 friend class InitiateSound;
 friend class Play;
 friend class LoadModifier;
};

#endif // SDFMACRO_H
