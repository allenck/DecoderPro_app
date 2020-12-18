#ifndef CTCEXCEPTIONBUFFER_H
#define CTCEXCEPTIONBUFFER_H

#include <QObject>

class ExceptionBufferRecord;
class CTCExceptionBuffer : public QObject
{
  Q_OBJECT
 public:
  /*public*/ enum ExceptionBufferRecordSeverity {
      INFO = 0,
      WARN = 1,
      ERROR = 2     // Order: The more severe, the HIGHER the number.  See function "getHighestExceptionBufferRecordSeverity" for why.
  };
  Q_INVOKABLE /*public*/ CTCExceptionBuffer();
  ~CTCExceptionBuffer() {}
  CTCExceptionBuffer(const CTCExceptionBuffer&) : QObject(){}
  /*public*/ void logString(ExceptionBufferRecordSeverity exceptionBufferRecordSeverity, QString string);
  /*public*/ bool isEmpty();
  /*public*/ void clear();
  /**
   * You SHOULD call "isEmpty()" first, because this routine returns by default "INFO"
   * IF there are NO entries in the list.
   *
   * It's purpose is to give the user an idea of the worst case scenario in the errors.
   *
   * @return The highest level of severity in our list.
   */
  /*public*/ ExceptionBufferRecordSeverity getHighestExceptionBufferRecordSeverity();
  /*public*/ QString getAllMessages();


 signals:

 public slots:
 private:
  QList<ExceptionBufferRecord*> _mArrayListOfExceptionBufferRecords = QList<ExceptionBufferRecord*>();

};
/*private*/ /*static*/ class ExceptionBufferRecord : public QObject{
 public:
    /*public*/ /*final*/ CTCExceptionBuffer::ExceptionBufferRecordSeverity _mExceptionBufferRecordSeverity;
    /*public*/ /*final*/ QString _mMessage;
    /*public*/ ExceptionBufferRecord(CTCExceptionBuffer::ExceptionBufferRecordSeverity exceptionBufferRecordSeverity, QString message) {
        _mExceptionBufferRecordSeverity = exceptionBufferRecordSeverity;
        switch(exceptionBufferRecordSeverity) {
            case CTCExceptionBuffer::ERROR:
                _mMessage = tr("ERROR") + message;  // NOI18N
                break;
            case CTCExceptionBuffer::WARN:
                _mMessage = tr("WARN") + message;  // NOI18N
                break;
            default:    // INFO too
                _mMessage = tr("INFO") + message;  // NOI18N
                break;
        }
    }
};
Q_DECLARE_METATYPE(CTCExceptionBuffer)
#endif // CTCEXCEPTIONBUFFER_H
