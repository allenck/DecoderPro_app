#ifndef RPSMENU_H
#define RPSMENU_H
#include <QMenu>

class RpsSystemConnectionMemo;
class RpsMenu : public QMenu
{
public:
 RpsMenu(QWidget* parent = nullptr);
 /*public*/ RpsMenu(QString name, QWidget* parent = nullptr);
 /*public*/ RpsMenu(RpsSystemConnectionMemo* memo, QWidget* parent= nullptr);

private:
 void common();
 /*private*/ RpsSystemConnectionMemo* _memo = nullptr;
};

#endif // RPSMENU_H
