#ifndef TREEVIEWER_H
#define TREEVIEWER_H

#include <jmrijframe.h>

class AbstractFemaleSocket;
class TreePane;
class TreeViewer : public JmriJFrame
{
  Q_OBJECT
 public:
  TreeViewer(AbstractFemaleSocket *femaleRootSocket, QWidget* parent = nullptr);
  /*public*/ /*final*/ TreePane* _treePane = nullptr;
  /*public*/ void initComponents()override;
  /*public*/ void initMinimumSize(QSize dimension);
  /*public*/ bool getRootVisible();
  /*public*/ void setRootVisible(bool rootVisible);
  /*public*/ void dispose()override;

  QWidget* jself() override {return this;}
 private:
  /*private*/ static /*final*/ int panelWidth;// = 500;
  /*private*/ static /*final*/ int panelHeight;// = 300;
  /*private*/ bool _rootVisible = true;



};

#endif // TREEVIEWER_H
