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
 /*public*/ static bool contains(QVector<PropertyChangeListener*> listeners, /*@Nonnull*/ PropertyChangeListener* needle);

signals:

public slots:
private:
 static Logger* log;
};

#endif // BEANS_H
