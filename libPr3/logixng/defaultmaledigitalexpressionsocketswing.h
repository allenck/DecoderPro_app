#ifndef DEFAULTMALEDIGITALEXPRESSIONSOCKETSWING_H
#define DEFAULTMALEDIGITALEXPRESSIONSOCKETSWING_H

#include "abstractmalesocketswing.h"

class DefaultMaleDigitalExpressionSocketSwing : public AbstractMaleSocketSwing
{
  Q_OBJECT
 public:
  explicit DefaultMaleDigitalExpressionSocketSwing(QObject *parent = nullptr);
  /*public*/ void updateObjectForSubPanel(/*@Nonnull*/ Base* object);

 private:
  /*private*/ JPanel* _panel;
  /*private*/ /*final*/ JLabel* _listenLabel = new JLabel(tr("Listen"));
  /*private*/ JCheckBox* _listenCheckBox;

 protected:
  /*protected*/ JPanel* getSubPanel(/*@CheckForNull*/ Base* object);

};

#endif // DEFAULTMALEDIGITALEXPRESSIONSOCKETSWING_H
