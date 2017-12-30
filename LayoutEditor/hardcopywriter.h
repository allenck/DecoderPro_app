#ifndef HARDCOPYWRITER_H
#define HARDCOPYWRITER_H

#include <QObject>
#include <QSize>
#include <QFont>
#include <QFontMetrics>
#include <QColor>
#include <QImage>
#include <QVector>
#include <QPixmap>
#include <QPainter>
#include "logger.h"
#include "exceptions.h"
#include "javaqt_global.h"

class JFrame;
class IOException;
class QMainWindow;
class QPixmap;
class QVBoxLayout;
class JLabel;
class QIcon;
class QToolBar;
class QImage;
class QPushButton;
class QLabel;
class QColor;
//class JmriJFrame;
//class QFontMetrics;
class QSize;
class QFont;
class QPrinter;
class QFrame;
class JAVAQTSHARED_EXPORT HardcopyWriter : public QObject
{
    Q_OBJECT
public:
    //explicit HardCopyWriter(QObject *parent = 0);
    /*public*/ HardcopyWriter(JFrame* frame, QString jobname, int fontsize, double leftmargin, double rightmargin, double topmargin, double bottommargin, bool preview, QObject* parent = 0); /*throw(HardcopyWriter::PrintCanceledException)*/
    /*public*/ HardcopyWriter(JFrame* frame, QString jobname, int fontsize, double leftmargin, double rightmargin, double topmargin, double bottommargin, bool preview, QString printerName, bool landscape, bool printHeader, QSize pagesize, QObject* parent = 0); /*throws HardcopyWriter.PrintCanceledException*/
    /*public*/ int getCharactersPerLine();
    /*public*/ int getLinesPerPage();
    /*public*/ void setFontStyle(QFont::Style);
    /*public*/ void setFontWeight(QFont::Weight);
    /*public*/ void write(QString buffer, int index, int len);
    /*public*/ void writeBorders();
    /*public*/ int getCurrentLineNumber();
    /*public*/ void write(QString str) /*throws IOException*/;
    /*public*/ void write(int rowStart, int colStart, int rowEnd, int colEnd);
    /*public*/ void write(QImage c, QWidget* i);
    /*public*/ int getLineHeight();
    /*public*/ int getFontSize() ;
    /*public*/ int getCharWidth();
    /*public*/ int getLineAscent();
    /*public*/ void writeNoScale(QImage c, QWidget* i);
    /*public*/ void pageBreak();
    /*public*/ void setTextColor(QColor c);
    /*public*/ void increaseLineSpacing(int percent);
    /*public*/ void setFontName(QString name);
    /*public*/ void close() throw (IOException);
    /*public*/ void dispose();
    /*public*/ void write(QMainWindow* jW);
    /*public*/ void write(QColor c, QString s) throw (IOException);
    /*public*/ void flush() throw (IOException);
    /*public*/ void writeHtml(QString str);
    bool isCancelled();

signals:
 void printCancelled(QString);

public slots:
    void On_previousButton_clicked();
    void On_nextButton_clicked();
    void On_close_clicked();

private:
    void common();
    // save state between invocations of write()
    /*private*/ bool last_char_was_return;// = false;


    // A static variable to hold prefs between print jobs
    // private static Properties printprops = new Properties();

    // Job and Page attributes
    QPrinter* jobAttributes;// = new JobAttributes();
//	PageAttributes pageAttributes = new PageAttributes();
    /*private*/ void hardcopyWriter(JFrame* frame, QString jobname, int fontsize, double leftmargin, double rightmargin, double topmargin, double bottommargin, bool preview);
    Logger* log;
    bool cancelled;

protected:
    // instance variables
//	/*protected*/ PrintJob job;
    /*protected*/ QPainter* page;
    /*protected*/ QString jobname;
    /*protected*/ QString line;
    /*protected*/ int fontsize;
    /*protected*/ QString time;
    /*protected*/ QSize pagesize;// = new Dimension(612, 792);
    /*protected*/ int pagedpi;// = 72;
    /*protected*/ QFont font, headerfont;
    /*protected*/ QString fontName;// = "Monospaced";
    /*protected*/ QFont::Style fontStyle;// = QFont::styleNormal;
                  QFont::Weight fontWeight;// = QFont::Normal;
    /*protected*/ QFontMetrics* metrics;
    /*protected*/ QFontMetrics* headermetrics;
    /*protected*/ int x0, y0;
    /*protected*/ int height, width;
    /*protected*/ int headery;
    /*protected*/ int charwidth;
    /*protected*/ int lineheight;
    /*protected*/ int lineascent;
    /*protected*/ int chars_per_line;
    /*protected*/ int lines_per_page;
    /*protected*/ int charnum/*= 0*/ , linenum;// = 0;
    /*protected*/ int charoffset;// = 0;
    /*protected*/ int pagenum;// = 0;
    /*protected*/ int prFirst;// = 1;
    /*protected*/ QColor color;// = Color.black;
    /*protected*/ bool printHeader;// = true;

    /*protected*/ bool isPreview;
////	/*protected*/ Graphics previewedPage;
    /*protected*/ QImage* previewImage;
////	/*protected*/ Graphics previewImagegr;
    /*protected*/ QVector<QImage*> pageImages;// = new QVector<QImage>(3, 3);
    /*protected*/ JFrame* previewFrame;
    /*protected*/ QWidget* previewPanel;
    /*protected*/ QPixmap previewIcon;// = new ImageIcon();
    /*protected*/ QLabel* previewLabel;// = new JLabel();
    /*protected*/ QToolBar* previewToolBar;// = new JToolBar();
    /*protected*/ JFrame* frame;
    /*protected*/ QPushButton* nextButton;
    /*protected*/ QPushButton* previousButton;
    /*protected*/ QPushButton* closeButton;
    /*protected*/ QLabel* pageCount;// = new JLabel();
    /*protected*/ QLabel* totalPages;// = new JLabel();
    /*protected*/ void toolBarInit();
    /*protected*/ void displayPage();
    QVBoxLayout* previewPanelLayout;
    /*protected*/ void newpage();
    /*protected*/ void newline();

};
class Character
{
 public:
    static bool isWhitespace(QChar c);
    static bool isSpaceChar(QChar c);
};

#endif // HARDCOPYWRITER_H
