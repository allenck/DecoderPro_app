#ifndef DEFAULTMALEDIGITALEXPRESSIONSOCKETSWING_H
#define DEFAULTMALEDIGITALEXPRESSIONSOCKETSWING_H

#include "abstractmalesocketswing.h"

class DefaultMaleDigitalExpressionSocketSwing : public AbstractMaleSocketSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit DefaultMaleDigitalExpressionSocketSwing(QObject *parent = nullptr);
    ~DefaultMaleDigitalExpressionSocketSwing() {}
    DefaultMaleDigitalExpressionSocketSwing(const DefaultMaleDigitalExpressionSocketSwing&) : AbstractMaleSocketSwing() {}
  /*public*/ void updateObjectForSubPanel(/*@Nonnull*/ Base* object);

    QObject* sself() override {return this;}

 private:
  /*private*/ JPanel* _panel;
  /*private*/ /*final*/ JLabel* _listenLabel = new JLabel(tr("Listen"));
  /*private*/ JCheckBox* _listenCheckBox;

 protected:
  /*protected*/ JPanel* getSubPanel(/*@CheckForNull*/ Base* object);

};
Q_DECLARE_METATYPE(DefaultMaleDigitalExpressionSocketSwing)
#endif // DEFAULTMALEDIGITALEXPRESSIONSOCKETSWING_H
