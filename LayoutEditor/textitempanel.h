#ifndef TEXTITEMPANEL_H
#define TEXTITEMPANEL_H
#include "itempanel.h"

class ItemPalette;
class DecoratorPanel;
class TextItemPanel : public ItemPanel
{
    Q_OBJECT
public:
    //explicit TextItemPanel(QWidget *parent = 0);
    /*public*/ TextItemPanel(ItemPalette* parentFrame, QString  type, QString family, Editor* editor, QWidget *parent);
    /*public*/ void init();

signals:

public slots:
private:
    DecoratorPanel* _decorator;

};

#endif // TEXTITEMPANEL_H
