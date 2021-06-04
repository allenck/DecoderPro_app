#ifndef VALIDATION_H
#define VALIDATION_H
#include <qobject.h>

class JInputValidatorPreferences;
class Validation : public QObject
{
  Q_OBJECT
 public:
  enum Type
  {
   NONE, UNKNOWN, INFORMATION, SUCCESS, WARNING, DANGER

  };
  Q_ENUM(Type)

  /*public*/ Validation(Type type, QString message);
  /*public*/ Validation(Type type, QString string, /*@javax.annotation.Nonnull*/ JInputValidatorPreferences* jivp);
  /*public*/ Type getType();
  /*public*/ QString getMessage();
  /*public*/ QString getIcon();
  /*public*/ QColor getColor();
  /*public*/ QFont getFont();

 private:
  Type type;
  QString message;
  /*private*/ JInputValidatorPreferences* preferences = nullptr;
  void setPreferences(/*@Nonnull*/ JInputValidatorPreferences* preferences);
};

#endif // VALIDATION_H
