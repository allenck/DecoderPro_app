#ifndef EXCEPTIONCONTEXT_H
#define EXCEPTIONCONTEXT_H

#include <QObject>
#include "exceptions.h"
#include "system.h"

class ExceptionContext : public QObject
{
  Q_OBJECT
 public:
  explicit /*public*/  ExceptionContext(Exception* ex, QString operation, QString hint, QObject* parent = nullptr);

  /*public*/  Exception* getException();
  /*public*/  QString getPreface();
  /*public*/  QString getOperation();
  /*public*/  QString getHint();
  /*public*/  QString getTitle();
  /*public*/  QString getSummary();

 signals:

 protected:
  /*protected*/ Exception* _exception;
  // Used to give a more friendly message
  // This may be replaced in derived classes
  /*protected*/ QString _preface = "An error occurred during the following operation."; // NOI18N
  // What was happening when the exception occurred
  /*protected*/ QString _operation;
  // A suggestion to the user to correct the problem.
  /*protected*/ QString _hint = "No hint"; // NOI18N
  // The system appropriate newline separator, used to format messages for
  // display.
  /*protected*/ QString _nl = System::getProperty("line.separator"); // NOI18N

};

#endif // EXCEPTIONCONTEXT_H
