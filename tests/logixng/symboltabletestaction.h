#ifndef SYMBOLTABLETESTACTION_H
#define SYMBOLTABLETESTACTION_H

#include <abstractaction.h>
#include <QObject>

class Logger;
class SymbolTableTestAction : public AbstractAction
{
    Q_OBJECT
public:
    explicit SymbolTableTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // SYMBOLTABLETESTACTION_H
