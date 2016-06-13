#ifndef POSITIONALLABEL_H
#define POSITIONALLABEL_H

#include <QLabel>
#include "editor.h"


class PositionableLabel : public QLabel
{
    Q_OBJECT
public:
    //explicit PositionalLabel(QObject *parent = 0);
/*public*/ PositionableLabel(QString s, Editor* editor, QObject *parent = 0);
/*public*/ PositionableLabel(NamedIcon s, Editor* editor) ;
/*public*/ /*final*/ bool isIcon();
/*public*/ /*final*/ bool isText();
/*public*/ /*final*/ bool isControl();
/*public*/ Editor* getEditor();
/*public*/ void setEditor(Editor ed);
/***************** Positionable methods **********************/

/*public*/ void setPositionable(bool enabled);
/*public*/ /*final*/ bool isPositionable();
/*public*/ void setEditable(bool enabled) ;
/*public*/ bool isEditable();

/*public*/ void setViewCoordinates(bool enabled);
/*public*/ bool getViewCoordinates();

/*public*/ void setControlling(bool enabled);
/*public*/ bool isControlling();

/*public*/ void setHidden(bool hide);
/*public*/ bool isHidden();
/*public*/ void showHidden();
/**
* Delayed setDisplayLevel for DnD
*/
/*public*/ void setLevel(int l);
/*public*/ void setDisplayLevel(int l);
/*public*/ int getDisplayLevel();
/*public*/ void setShowTooltip(bool set);
/*public*/ bool showTooltip();
/*public*/ void setTooltip(ToolTip tip);
/*public*/ ToolTip getTooltip();

/*public*/ QString getNameQString();
/*public*/ Positionable* deepClone();

/**
 * When text is rotated or in an icon mode, the return of getText() may be
 * null or some other value
 * @return original defining text set by user
 */
/*public*/ QString getUnRotatedText();

signals:
    
public slots:
private:
/*private*/ int _degrees;

protected:
/*protected*/ Editor* _editor;

/*private*/ bool debug = false;
/*protected*/ bool _icon = false;
/*protected*/ bool _text = false;
/*protected*/ bool _control = false;
/*protected*/ NamedIcon* _namedIcon;

/*protected*/ ToolTip* _tooltip;
/*protected*/ bool _showTooltip =true;
/*protected*/ bool _editable = true;
/*protected*/ bool _positionable = true;
/*protected*/ bool _viewCoordinates = true;
/*protected*/ bool _controlling = true;
/*protected*/ bool _hidden = false;
/*protected*/ int _displayLevel;

/*protected*/ QString _unRotatedText;
/*protected*/ bool _rotateText = false;

};

#endif // POSITIONALLABEL_H
