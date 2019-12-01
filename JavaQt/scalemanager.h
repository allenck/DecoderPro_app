#ifndef SCALEMANAGER_H
#define SCALEMANAGER_H

#include <QObject>

class Scale;
class Logger;
class ScaleManager : public QObject
{
 Q_OBJECT
public:
 explicit ScaleManager(QObject *parent = nullptr);
 /*public*/ static void addScale(QString scaleName, QString userName, double scaleRatio);
 /*public*/ static Scale *getScale(/*@Nonnull*/ QString name);
 /*public*/ static QList<Scale *> getScales();
 /*public*/ static Scale* getScaleByName(/*@Nonnull*/ QString name);

signals:

public slots:

private:
 /*private*/ static QMap<QString, Scale*> _scaleMap;// = QMap<QString, Scale>();
 /*private*/ static void fillMap();
 static Logger* log;
};

#endif // SCALEMANAGER_H
