#ifndef JTITLEDSEPARATOR_H
#define JTITLEDSEPARATOR_H

#include "jpanel.h"

class QHBoxLayout;
class QLabel;
class JTitledSeparator : public JPanel
{
    Q_OBJECT
public:
    //explicit JTitledSeparator(QWidget *parent = 0);
    /*public*/ JTitledSeparator(QString title, QWidget* parent = 0);
    /*public*/ QString getTitle();
    /*public*/ void setTitle(QString title);
    /*public*/ void updateUI();


signals:

public slots:
private:
    /*private*/ /*final*/ QLabel* label;// = new QLabel();
    QHBoxLayout* layout;
    /*private*/ void adjustLook();
 class WestPanel : public QWidget
 {
  JTitledSeparator* parent;

 public:
  WestPanel(JTitledSeparator* parent);
  /*public*/ void setBounds(int x, int y, int w, int h);
  QHBoxLayout* layout;
 };

 class SeparatorPane : public JPanel
 {
   JTitledSeparator* parent;
   //QHBoxLayout* layout;
  public:
   SeparatorPane(JTitledSeparator* parent);
   /*public*/ virtual void setBounds(int x, int y, int w, int h);
 };
};

#endif // JTITLEDSEPARATOR_H
