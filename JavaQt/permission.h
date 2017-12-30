#ifndef PERMISSION_H
#define PERMISSION_H

#include <QObject>

class Permission : public QObject
{
 Q_OBJECT
public:
 //explicit Permission(QObject *parent = 0);
 /*public*/ Permission(QString name);
 /*public*/ /*abstract*/ virtual bool implies(Permission* permission);
 /*public*/ /*abstract*/ virtual bool equals(QObject* obj);
 /*public*/ /*final*/ QString getName();
 /*public*/ /*abstract*/ virtual QString getActions();
 /*public*/ QString toString();

signals:

public slots:

private:
 /*private*/ QString name;

};

#endif // PERMISSION_H
