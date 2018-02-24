#ifndef PREVIEWDIALOG_H
#define PREVIEWDIALOG_H

#include "jdialog.h"
#include "logger.h"

class QTableWidget;
class QScrollArea;
class QGridLayout;
class ActionListener;
class JFrame;
class QLabel;
class QDir;
class PreviewDialog : public JDialog
{
    Q_OBJECT
public:
    //explicit PreviewDialog(QWidget *parent = 0);
    /*public*/ PreviewDialog(JFrame* frame, QString title, QDir* dir, QStringList filter );
    /*public*/ void init(ActionListener* addAction, ActionListener* moreAction,
                     ActionListener* lookAction, ActionListener* cancelAction,
                     int startNum, JFrame* waitDialog);
    /*public*/ int getNumFilesShown();
    /*public*/ void dispose();

signals:

public slots:
    void whiteButton_clicked();
    void darkButton_clicked();
    void grayButton_clicked();
private:
    QWidget*          _selectedImage;
    static QColor    _grayColor;// = new Color(235,235,235);
    QColor           _currentBackground;// = _grayColor;

    QLabel*          _previewLabel;// = new JLabel();
    //QWidget*          _preview;
    QTableWidget*    _preview;

    int _cnt;           // number of files displayed when setIcons() method runs
    int _startNum;      // total number of files displayed from a directory

    QDir* _currentDir;   // current FS directory
    QStringList _filter;   // file extensions of types to display
    QPushButton* _addButton;
    QPushButton* _moreButton;
    bool _noMemory;// = false;
    Logger* log;
    void resetPanel();
    /*private*/ QWidget* setupPanel();
    /*private*/ void setBackground(QColor color);
    static const int CHUNK = 500000;
    /*private*/ bool setIcons(int startNum); /*throws OutOfMemoryError*/
    /*private*/ long availableMemory();
    QGridLayout* gridbag;
    QScrollArea* js;
};

#endif // PREVIEWDIALOG_H
