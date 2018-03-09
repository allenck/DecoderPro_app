#ifndef SPROGREPLY_H
#define SPROGREPLY_H
#include "abstractmrreply.h"
#include "sprogconstants.h"

namespace Sprog
{
class SprogReply : public AbstractMRReply
{
public:
 SprogReply(QObject *parent = 0);
 static /*public*/ /*final*/ int maxSize;// = 515;
 /*public*/ void setId(int id);
 /*public*/ int getId();
 /*public*/ SprogReply(SprogReply* m, QObject *parent = 0);
 /*public*/ SprogReply(QString replyString, bool isBoot, QObject *parent = 0);
 /*public*/ SprogReply(QString replyString, QObject *parent = 0);
 /*public*/ bool isOverload();
 /*public*/ bool isError();
 /*public*/ bool strip();
 /*public*/ bool getChecksum();
 //@Override
 /*public*/ QString toString();
 /*public*/ int value();
 /*public*/ int match(QString s);
 /*public*/ bool endNormalReply();
 /*public*/ bool endBootReply();
 /*public*/ bool endBootloaderReply(SprogConstants::SprogState sprogState);


private:
     /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("SprogReply");
 /*private*/ bool _isBoot;// = false;
 /*private*/ int skipEqual(int index);


protected:
 /*protected*/ int _id;// = -1;
 /*protected*/ int skipPrefix(int index);

};
}
#endif // SPROGREPLY_H
