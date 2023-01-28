#ifndef JAVATOQT_H
#define JAVATOQT_H
#include <QtCore>

class JavaToQt
{
 private:
  JavaToQt();
 public:
  static QString getQtName(QString cClass);

 private:
  static QMap<QString, QString> map;
};

#endif // JAVATOQT_H
