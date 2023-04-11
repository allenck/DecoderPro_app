#ifndef UIDEFAULTS_H
#define UIDEFAULTS_H

#include <QObject>
#include <QMap>
#include <QVariant>

class UIDefaults : public QObject
{
    Q_OBJECT
public:
    explicit UIDefaults(QObject *parent = nullptr);
    /*public*/ QVariant get(QString key);
    /*public*/ QColor getColor(QString key);
    /*public*/ QFont getFont(QString key);
    /*public*/ QFont getFont(QString key, QLocale l);

signals:

private:
    QMap<QString, QVariant> hashtable;

};

#endif // UIDEFAULTS_H
