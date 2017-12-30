#ifndef OPTIONPANEUI_H
#define OPTIONPANEUI_H

#include <QObject>
#include "joptionpane.h"

class OptionPaneUI : public QObject
{
 Q_OBJECT
public:
 explicit OptionPaneUI(QObject *parent = 0);
 /**
      * Requests the component representing the default value to have
      * focus.
      */
     /*public*/ /*abstract*/ virtual void selectInitialValue(JOptionPane* /*op*/) {}

     /**
      * Returns true if the user has supplied instances of Component for
      * either the options or message.
      */
     /*public*/ /*abstract*/ bool containsCustomComponents(JOptionPane* /*op*/) {return false;}
signals:

public slots:
};

#endif // OPTIONPANEUI_H
