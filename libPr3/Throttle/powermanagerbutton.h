#ifndef POWERMANAGERBUTTON_H
#define POWERMANAGERBUTTON_H

#include <QToolButton>
#include "loggerfactory.h"

class PropertyChangeEvent;
class NamedIcon;
class PowerPane;
class PowerManager;
class PowerManagerButton : public QToolButton
{
    Q_OBJECT
public:
    explicit PowerManagerButton(QWidget *parent = 0);
    /*public*/ PowerManagerButton(bool fullText, QWidget *parent = 0);
    /*public*/ void dispose();
    /*abstract*/ virtual void loadIcons();

signals:

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* evt);
    void OnClicked();
    void init();
private:
    void common(bool fullText);
    /*private*/ PowerPane* powerControl;// = new PowerPane();
    /*private*/ PowerManager* powerMgr;// = NULL;
    /*private*/ bool fullText;// = false;
    /*protected*/ QIcon powerXIcon;
    /*protected*/ QIcon powerOffIcon;
    /*protected*/ QIcon powerOnIcon;
    /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("PowerManagerButton");

protected:
 /*protected*/ void setPowerIcons();
friend class SmallPowerManagerButton;
friend class LargePowerManagerButton;
};

#endif // POWERMANAGERBUTTON_H
