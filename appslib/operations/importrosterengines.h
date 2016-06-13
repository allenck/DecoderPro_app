#ifndef IMPORTROSTERENGINES_H
#define IMPORTROSTERENGINES_H

#include <QObject>

class Logger;
class QLabel;
namespace Operations
{
 class EngineManager;
 class ImportRosterEngines : public QObject
 {
  Q_OBJECT
 public:
  explicit ImportRosterEngines(QObject *parent = 0);
 public slots:
  /*public*/ void process();

 signals:
  void finished(int);
  void progress(QString);

 public slots:

 private:
  EngineManager* manager;// = EngineManager.instance();
//  QLabel* textEngine;// = new javax.swing.JLabel();
//  QLabel* textId;//= new javax.swing.JLabel();
  /*private*/ static QString defaultEngineLength;// = tr("engineDefaultLength");
  /*private*/ static QString defaultEngineType;// = tr("engineDefaultType");
  /*private*/ static QString defaultEngineHp;// = tr("engineDefaultHp");
  Logger* log;
 };
}
#endif // IMPORTROSTERENGINES_H
