#ifndef LOCOSELTREEPANE_H
#define LOCOSELTREEPANE_H
#include "combinedlocoseltreepane.h"

class QLabel;
class JToggleButton;
class QWidget;
class LocoSelTreePane : public CombinedLocoSelTreePane
{
    Q_OBJECT
public:
    explicit LocoSelTreePane(QWidget *parent = 0);
    /*public*/ LocoSelTreePane(QLabel* s, ProgModeSelector* selector, QWidget *parent = 0);

signals:

public slots:
private:
    JToggleButton* addDecoderIdentButton();

protected:
    /*protected*/ virtual QWidget* layoutRosterSelection();
    /*protected*/ virtual QWidget* layoutDecoderSelection();

};

#endif // LOCOSELTREEPANE_H
