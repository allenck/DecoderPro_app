#ifndef BEANS_H
#define BEANS_H

#include <QObject>

class Logger;
class PropertyChangeListener;
class Beans : public QObject
{
 Q_OBJECT
public:
 explicit Beans(QObject *parent = nullptr);
 /*public*/ static void setIndexedProperty(QObject* bean, QString key, int index, QVariant value);
 /*public*/ static void setIntrospectedIndexedProperty(QObject *bean, QString key, int index, QVariant value);
 /*public*/ static QVariant getIndexedProperty(QObject* bean, QString key, int index);
 /*public*/ static QVariant getIntrospectedIndexedProperty(QObject* bean, QString key, int index);
 /*public*/ static void setProperty(QObject* bean, QString key, QVariant value);
 /*public*/ static void setIntrospectedProperty(QObject* bean, QString key, QVariant value);
 /*public*/ static QVariant getProperty(QObject* bean, QString key);
 /*public*/ static QVariant getIntrospectedProperty(QObject* bean, QString key);
 /*public*/ static bool hasProperty(QObject* bean, QString key) ;
 /*public*/ static bool hasIndexedProperty(QObject* bean, QString key);
 /*public*/ static bool hasIntrospectedProperty(QObject* bean, QString key);
 /*public*/ static bool hasIntrospectedIndexedProperty(QObject* bean, QString key);
 /*public*/ static QSet<QString> getPropertyNames(QObject* bean);
 /*public*/ static QSet<QString> getIntrospectedPropertyNames(QObject* bean);
 /*public*/ static bool implementsBeanInterface(QObject* bean);
 /*public*/ static bool contains(QVector<PropertyChangeListener*> listeners, /*@Nonnull*/ PropertyChangeListener* needle);

signals:

public slots:
private:
 static Logger* log;
};

#endif // BEANS_H
