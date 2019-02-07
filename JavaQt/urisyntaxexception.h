#ifndef URISYNTAXEXCEPTION_H
#define URISYNTAXEXCEPTION_H
#include "exceptions.h"

class URISyntaxException : public Exception
{
public:
 URISyntaxException(QString input, QString reason, int index);
 /*public*/ URISyntaxException(QString input, QString reason);
 /*public*/ QString getInput();
 /*public*/ QString getReason();
 /*public*/ int getIndex();
 /*public*/ QString getMessage();

private:
 /*private*/ QString input;
 /*private*/ int index;

};

#endif // URISYNTAXEXCEPTION_H
