#include "indicatortrackpaths.h"
#include "editor.h"
#include "oblock.h"

//IndicatorTrackPaths::IndicatorTrackPaths(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * A utility class replacing common methods formerly implementing the
 * IndicatorTrack interface.
 * <P>
 *
 * @author Pete Cressman Copyright (c) 2012
 * @version $Revision: 1 $
 */
//class IndicatorTrackPaths  {

/*protected*/ QStringList _paths;      // list of paths that this icon displays
/*protected*/ bool _showTrain; 		// this track icon should display _loco when occupied
/*private*/ LocoLable* _loco = NULL;

/*protected*/ IndicatorTrackPaths::IndicatorTrackPaths(QObject *parent) : QObject(parent)
{
 _loco = NULL;
 log = new Logger("IndicatorTrackPaths");
}

/*protected*/ IndicatorTrackPaths* IndicatorTrackPaths::deepClone() {
    IndicatorTrackPaths* p = new IndicatorTrackPaths();
    if (!_paths.isEmpty()) {
        p->_paths = QStringList();
        for (int i=0; i<_paths.size(); i++) {
            p->_paths.append(_paths.at(i));
        }
    }
    p->_showTrain = _showTrain;
    return p;
}

/*protected*/ QStringList IndicatorTrackPaths::getPaths() {
    return _paths;
}
/*protected*/ void IndicatorTrackPaths::setPaths(QStringList paths) {
    if (paths.isEmpty()) {
        _paths = paths;
    } else {
        _paths = QStringList();
        for (int i=0; i<paths.size(); i++) {
            _paths.append(paths.at(i).trimmed());
        }
    }
}

/*protected*/ void IndicatorTrackPaths::addPath(QString path) {
    if (!_paths.isEmpty()) {
        _paths =  QStringList();
    }
    if (path!=NULL && path.length()>0) {
        path = path.trimmed();
        if (!_paths.contains(path)) {
            _paths.append(path);
        }
    }
    if (log->isDebugEnabled()) log->debug("addPath \""+path+"\" #paths= "+QString::number(_paths.size()));
}
/*protected*/ void IndicatorTrackPaths::removePath(QString path) {
    if (!_paths.isEmpty()) {
        if (path!=NULL && path.length()>0) {
            path = path.trimmed();
            _paths.removeAt(_paths.indexOf(path));
        }
    }
}

/*protected*/ void IndicatorTrackPaths::setShowTrain(bool set) {
    _showTrain = set;
}
/*protected*/ bool IndicatorTrackPaths::showTrain() {
    return _showTrain;
}
/*protected*/ QString IndicatorTrackPaths::setStatus(OBlock* block, int state) {
    QString pathName = block->getAllocatedPathName();
    QString status;
    removeLocoIcon();
    if ((state & OBlock::TRACK_ERROR)!=0) {
        status = "ErrorTrack";
    } else if ((state & OBlock::OUT_OF_SERVICE)!=0) {
        status = "DontUseTrack";
    } else if ((state & OBlock::ALLOCATED)!=0) {
        if (!_paths.isEmpty() && _paths.contains(pathName)) {
            if ((state & OBlock::RUNNING)!=0) {
                status = "PositionTrack";
            } else {
                status = "AllocatedTrack";
            }
        } else {
            status = "ClearTrack";     // icon not on path
        }
    } else if ((state & OBlock::OCCUPIED)!=0) {
        status = "OccupiedTrack";
    } else if ((state & Sensor::UNKNOWN)!=0) {
        status = "DontUseTrack";
    } else {
        status = "ClearTrack";
    }
    return status;
}

/*private*/ void IndicatorTrackPaths::removeLocoIcon() {
    if (_loco!=NULL) {
//        _loco->remove();
        _loco = NULL;
    }
}

/*protected*/ void IndicatorTrackPaths::setLocoIcon(QString trainName, QPoint /*pt*/, QSize /*size*/, Editor* /*ed*/) {
    if (!_showTrain) {
        return;
    }
    if (trainName==NULL) {
        removeLocoIcon();
        return;
    }
    if (_loco!=NULL) {
        return;
    }
    trainName = trainName.trimmed();
#if 0
    _loco = new LocoLable(ed);
    FontMetrics metrics = ed.getFontMetrics(ed.getFont());
    int width = metrics.stringWidth(trainName);
    int height = metrics.getHeight();
    _loco.setLineWidth(1);
    _loco.setLineColor(Color.RED);
    _loco.setAlpha(150);
    _loco.setFillColor(Color.WHITE);
    _loco.setText(trainName);
    _loco.setWidth(width+height/2);
    _loco.setHeight(height);
    _loco.setCornerRadius(height/2);
    _loco.makeShape();
    _loco.setDisplayLevel(Editor::MARKERS);
    _loco.updateSize();
    pt.x = pt.x + (size.width - _loco.maxWidth())/2;
    pt.y = pt.y + (size.height - _loco.maxHeight())/2;
    _loco.setLocation(pt);
    ed.putItem(_loco);
#endif
}

/*protected*/ QString IndicatorTrackPaths::setStatus(int state) {
    QString status;
    if (state==Sensor::ACTIVE) {
        status = "OccupiedTrack";
    } else if (state==Sensor::INACTIVE) {
        status = "ClearTrack";
    } else if (state==Sensor::UNKNOWN) {
        status = "DontUseTrack";
    } else {
        status = "ErrorTrack";
    }
    return status;
}
#if 0
static class LocoLable extends PositionableRoundRect {

    QString _text;

    /*public*/ LocoLable(Editor editor) {
        super(editor);
    }

    /*public*/ LocoLable(Editor editor, Shape shape) {
        super(editor, shape);
    }

    /*public*/ void setText(QString text) {
        _text = text;
    }

    /*public*/ void paint(Graphics g) {
        super.paint(g);
        Graphics2D g2d = (Graphics2D)g;
        if (_transform!=NULL ) {
            g2d.transform(_transform);
        }
        g2d.setFont(getFont().deriveFont(Font.BOLD));
        int textWidth = getFontMetrics(getFont()).stringWidth(_text);
        int textHeight = getFontMetrics(getFont()).getHeight();
        int hOffset = Math.max((maxWidth()-textWidth)/2, 0);
        int vOffset = Math.max((maxHeight()-textHeight)/2, 0) + getFontMetrics(getFont()).getAscent();
        g2d.setColor(Color.BLACK);
        g2d.drawString(_text, hOffset, vOffset);
    }
};
  #endif
