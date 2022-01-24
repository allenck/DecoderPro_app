#ifndef JDESKTOPPANE_H
#define JDESKTOPPANE_H

#include <QStackedWidget>

class JInternalFrame;
class DesktopManager;
class JDesktopPane : public QStackedWidget
{
 Q_OBJECT
public:
 explicit JDesktopPane(QWidget *parent = 0);
// /*public*/ DesktopPaneUI getUI();
 /*public*/ static /*final*/ int LIVE_DRAG_MODE;// = 0;
 /*public*/ static /*final*/ int OUTLINE_DRAG_MODE;// = 1;
  /*public*/ QList<JInternalFrame*> getAllFrames();
  /*public*/ void putClientProperty(QString, QString) {}
  /*public*/ void setBackground(QColor);
signals:

public slots:
private:
 /*private*/ static /*final*/ QString uiClassID;// = "DesktopPaneUI";
 /*transient*/ DesktopManager* desktopManager;

 /*private*/ /*transient*/ JInternalFrame* selectedFrame;// = null;
 /*private*/ int dragMode;// = LIVE_DRAG_MODE;
 /*private*/ bool dragModeSet;// = false;
 /*private*/ /*transient*/ QList<JInternalFrame*> framesCache;
 /*private*/ bool componentOrderCheckingEnabled;// = true;
 /*private*/ bool componentOrderChanged;// = false;
 /*private*/ static QList<JInternalFrame*> getAllFrames(JDesktopPane* parent);

};

#endif // JDESKTOPPANE_H
