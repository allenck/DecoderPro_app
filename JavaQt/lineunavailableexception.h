#ifndef LINEUNAVAILABLEEXCEPTION_H
#define LINEUNAVAILABLEEXCEPTION_H
#include "exceptions.h"

class LineUnavailableException : public Exception
{
 public:
  /*public*/ LineUnavailableException();

  /**
   * Constructs a <code>LineUnavailableException</code> that has
   * the specified detail message.
   *
   * @param message a string containing the error detail message
   */
  /*public*/ LineUnavailableException(QString message);
};
#endif // LINEUNAVAILABLEEXCEPTION_H
