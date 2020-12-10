#ifndef LOCKEDROUTESMANAGER_H
#define LOCKEDROUTESMANAGER_H

#include <QObject>

class LockedRoutesManager : public QObject
{
  Q_OBJECT
 public:
  explicit LockedRoutesManager(QObject *parent = nullptr);

 signals:

 public slots:
};

#endif // LOCKEDROUTESMANAGER_H