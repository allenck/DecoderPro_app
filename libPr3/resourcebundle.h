#ifndef RESOURCEBUNDLE_H
#define RESOURCEBUNDLE_H

#include <QObject>
#include <QMap>
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT ResourceBundle : public QObject
{
    Q_OBJECT
public:
    explicit ResourceBundle(QObject *parent = 0);
    ResourceBundle* getBundle(QString filename);
    QString getString(QString key);
    QStringList keys();

signals:

private:
/*private*/ QMap<QString, QString>* bundleMap;
    void initDCS51();
    void initDefault();
    void initLocoBuffer();

};

#endif // RESOURCEBUNDLE_H
