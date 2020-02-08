#ifndef DCS240USBMODESELECTPANE_H
#define DCS240USBMODESELECTPANE_H
#include "pr3selectpane.h"

class Dcs240UsbModeSelectPane : public Pr3SelectPane
{
 Q_OBJECT
public:
 Dcs240UsbModeSelectPane(QWidget *parent = nullptr);
 ~Dcs240UsbModeSelectPane() {}
 Dcs240UsbModeSelectPane(const Dcs240UsbModeSelectPane&) : Pr3SelectPane() {}
 /*public*/ QString getHelpTarget();
 /*public*/ QString getTitle();
};
Q_DECLARE_METATYPE(Dcs240UsbModeSelectPane)
#endif // DCS240USBMODESELECTPANE_H
