#ifndef POSITIONABLEICON_H
#define POSITIONABLEICON_H
#include "positionablelabel.h"

class NamedIcon;
class LayoutEditor;
class Positionable;
class PositionableIcon : public PositionableLabel
{
    Q_OBJECT
public:
    explicit PositionableIcon(QWidget *parent = 0);
    /*public*/ PositionableIcon(Editor* editor, Positionable *parent);
    /*public*/ PositionableIcon(NamedIcon* s, Editor* editor, Positionable *parent);
    /*public*/ PositionableIcon(QString s, Editor* editor, Positionable *parent);
    /*public*/ Positionable* finishClone(Positionable* p) override;
    /**
    * Get icon by its bean state name key found in jmri.NamedBeanBundle.properties
    * Get icon by its localized bean state name
    */
    /*public*/ NamedIcon* getIcon(QString state);
    /*public*/ QString getFamily();
    /*public*/ void setFamily(QString family);
    /*public*/ QStringListIterator getIconStateNames();
    /*public*/ int maxHeight() override;
    /*public*/ int maxWidth() override;
    /*public*/ virtual void displayState(int state);
    /*public*/ void setScale(double s) override;
    /*public*/ int getDegrees() override;
    /*public*/ void rotate(int deg) override;
    Positionable* parent;
    void invalidate();

signals:
    
public slots:
    
private:
 Logger log;
 void common(Editor* editor, Positionable* parent);
protected:
 /*protected*/ QMap<QString, NamedIcon*>* _iconMap;
 /*protected*/ QString  _iconFamily;
 /*protected*/ double _scale;// = 1.0;			// getScale, come from net result found in one of the icons
 /*protected*/ int _rotate;// = 0;
 /*protected*/ void rotateOrthogonal() override;
 /*protected*/ static QMap<QString, NamedIcon*>* cloneMap(QMap<QString, NamedIcon*>* map, PositionableLabel* pos);
 friend class PortalItemPanel;
};

#endif // POSITIONABLEICON_H
