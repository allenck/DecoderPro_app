#ifndef BORDERFACTORY_H
#define BORDERFACTORY_H

#include <QObject>
#include "border.h"
#include "matteborder.h"
#include <QIcon>
#include <QColor>
#include "lineborder.h"
#include "titledborder.h"
#include "etchedborder.h"
#include "compoundborder.h"

class BorderFactory : QObject
{
 Q_OBJECT
public:
 /*public*/ static Border* createLineBorder(QColor color);
 /*public*/ static Border* createLineBorder(QColor color, int thickness);
 /*public*/ static Border* createLineBorder(QColor color, int thickness, bool rounded);
 /*public*/ static MatteBorder* createMatteBorder(int top, int left, int bottom, int right,
                                             QColor color);
 /*public*/ static MatteBorder* createMatteBorder(int top, int left, int bottom, int right,
                                             QIcon tileIcon);
 /*public*/ static TitledBorder* createTitledBorder(QString title);
 /*public*/ static TitledBorder* createTitledBorder(Border* border);
 /*public*/ static TitledBorder* createTitledBorder(Border* border,  QString title);
 /*public*/ /*static*/ TitledBorder* createTitledBorder(Border* border,
                     QString title,
                     int titleJustification,
                     int titlePosition);
 /*public*/ /*static*/ TitledBorder* createTitledBorder(Border* border,
                     QString title,
                     int titleJustification,
                     int titlePosition,
                     QFont* titleFont);
 /*public*/ /*static*/ TitledBorder* createTitledBorder(Border* border,
                     QString title,
                     int titleJustification,
                     int titlePosition,
                     QFont *titleFont,
                     QColor titleColor);
 /*public*/ static Border* createEmptyBorder();
 /*public*/ static Border* createEmptyBorder(int top, int left, int bottom, int right);
 /*public*/ static CompoundBorder* createCompoundBorder();
 /*public*/ static CompoundBorder* createCompoundBorder(Border* outsideBorder,
                                              Border* insideBorder);

#if 1
 static /*final*/ Border* sharedEtchedBorder;// = new EtchedBorder();
 /*private*/ static Border* sharedRaisedEtchedBorder;

 /*public*/ static Border* createEtchedBorder();
 /*public*/ static Border* createEtchedBorder(QColor highlight, QColor shadow);
 /*public*/ static Border* createEtchedBorder(int type);
 /*public*/ static Border* createEtchedBorder(int type, QColor highlight,
                                             QColor shadow);
#endif

private:
 BorderFactory(QObject* parent = 0);
 /*final*/ static Border* emptyBorder;// = new EmptyBorder(0, 0, 0, 0);

};

#endif // BORDERFACTORY_H
