#ifndef BEANSELECTPANEL_H
#define BEANSELECTPANEL_H

#include <jpanel.h>
#include <QObject>
#include "namedbeancombobox.h"
#include "namedbean.h"
#include "manager.h"

class BeanSelectPanel : public JPanel
{
  Q_OBJECT
 public:
  //BeanSelectPanel(QWidget* parent = nullptr);
  /*public*/  BeanSelectPanel(/*@Nonnull*/ Manager/*<E>*/* manager, NamedBean* selection, QWidget* parent = nullptr) ;
  /*public*/  BeanSelectPanel(/*@Nonnull*/ Manager/*<E>*/* manager, NamedBean* selection,NamedBean:: DisplayOptions display, QWidget* parent=nullptr);
  /*public*/  BeanSelectPanel(/*@Nonnull*/ Manager/*<E>*/* manager,NamedBean* selection, NamedBean::DisplayOptions display, bool maxRows);
  /*public*/  NamedBeanComboBox* getBeanCombo();
  /*public*/ NamedBean* getNamedBean();
  /*public*/  void setDefaultNamedBean(NamedBean* nBean);
  /*public*/  bool isEmpty();
  /*public*/  void dispose();

 private:
  NamedBean*_selection;
  NamedBeanComboBox/*<E>*/* _beanComboBox;
  NamedBean::DisplayOptions _display;
  void common(Manager* manager, NamedBean* selection, NamedBean::DisplayOptions display, bool maxRows);

};

#endif // BEANSELECTPANEL_H
