#ifndef LOCONETEXCEPTION_H
#define LOCONETEXCEPTION_H

#include "jmriexception.h"

class LocoNetException : public JmriException
{
 public:
  LocoNetException(QString m);
};

#endif // LOCONETEXCEPTION_H
