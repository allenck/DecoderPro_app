#ifndef IMPORTLOGIXACTION_H
#define IMPORTLOGIXACTION_H

#include <abstractaction.h>

class ImportLogixFrame;
class ImportLogixAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit ImportLogixAction(QObject *parent = nullptr);
  /*public*/  ImportLogixAction(QString s, QObject* parent);
public slots:
  /*public*/  void actionPerformed(JActionEvent* e =0)override;

 private:
  static ImportLogixFrame* importLogixFrame;// = nullptr;

};

#endif // IMPORTLOGIXACTION_H
