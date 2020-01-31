#ifndef WIFICONSISTFILE_H
#define WIFICONSISTFILE_H

#include "consistfile.h"

class Logger;
class WiFiConsistFile : public ConsistFile
{
public:
 WiFiConsistFile(AbstractConsistManager *cm);

private:
     /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("WiFiConsistFile");
 /*private*/ void loadStoredConsistFile(QString fileName);

};

#endif // WIFICONSISTFILE_H
