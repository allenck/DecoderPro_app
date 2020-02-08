#ifndef DCS52USBMODESELECTPANE_H
#define DCS52USBMODESELECTPANE_H
#include "pr3selectpane.h"

class Dcs52UsbModeSelectPane : public Pr3SelectPane
{
public:
 Dcs52UsbModeSelectPane(QWidget *parent = nullptr);
 ~Dcs52UsbModeSelectPane() {}
 Dcs52UsbModeSelectPane(const Dcs52UsbModeSelectPane&) : Pr3SelectPane() {}
 /*public*/ QString getHelpTarget();
 /*public*/ QString getTitle();
 /*public*/ QObject* self() {return (QObject*)this;}
};
Q_DECLARE_METATYPE(Dcs52UsbModeSelectPane)
#endif // DCS52USBMODESELECTPANE_H
