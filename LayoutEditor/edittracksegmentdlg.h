#ifndef EDITTRACKSEGMENTDLG_H
#define EDITTRACKSEGMENTDLG_H

#include <QMainWindow>
#include "tracksegment.h"

namespace Ui {
class EditTrackSegmentDlg;
}

class EditTrackSegmentDlg : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit EditTrackSegmentDlg(TrackSegment* trackSegment, QWidget *parent);
    ~EditTrackSegmentDlg();
    
private:
    Ui::EditTrackSegmentDlg *ui;
    TrackSegment* trackSegment;
    QWidget *parent;
private slots:
    void on_edBlockName_textChanged(QString text);
    void on_pbDone_clicked();
    void on_pbCancel_clicked();
    void on_pbEditBlock_clicked();
    void on_chkHide_toggled(bool bChecked);
};

#endif // EDITTRACKSEGMENTDLG_H
