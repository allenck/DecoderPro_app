#include "hardcopywriter.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QFont>
#include <QFontMetrics>
#include <QFrame>
#include <QDateTime>
#include "jframe.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QToolBar>
#include <QToolButton>
#include <QPushButton>
#include <QLabel>
#include <QIcon>
//#include "../../LayoutEditor/jlabel.h"
#include "imageicon.h"
#include <QPixmap>
#include <QPainter>
#include <QTextDocument>
#include <QTextEdit>
#include <QTextLayout>

//HardCopyWriter::HardCopyWriter(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * This is from Chapter 12 of the O'Reilly Java book by David Flanagan with the alligator on the front.
 *
 * @author David Flanagan
 * @version $Revision: 28013 $
 */
// /*public*/ class HardcopyWriter extends Writer {



// constructor modified to add print preview parameter
/*public*/ HardcopyWriter::HardcopyWriter(JFrame* frame, QString jobname, int fontsize, double leftmargin, double rightmargin,  double topmargin, double bottommargin, bool preview, QObject* parent)
    : QObject(parent) /*throw(HardcopyWriter::PrintCanceledException)*/
{
 common();
 hardcopyWriter(frame, jobname, fontsize, leftmargin, rightmargin, topmargin, bottommargin, preview);
}

// constructor modified to add default printer name and page orientation
/*public*/ HardcopyWriter::HardcopyWriter(JFrame* frame, QString jobname, int fontsize, double leftmargin, double rightmargin, double topmargin, double bottommargin, bool preview, QString printerName, bool landscape,
        bool printHeader, QSize pagesize, QObject* parent) /*throws HardcopyWriter.PrintCanceledException*/
    : QObject(parent)
{
 common();
 // print header?
 this->printHeader = printHeader;

 // set default print name
 jobAttributes->setPrinterName(printerName);
 if (landscape)
 {
  //pageAttributes.setOrientationRequested(PageAttributes.OrientationRequestedType.LANDSCAPE);
  jobAttributes->setOrientation(QPrinter::Landscape);
  if (preview)
    this->pagesize = QSize(792, 612);
 }
 else if (preview && !pagesize.isNull())
 {
  this->pagesize = pagesize;
 }

 hardcopyWriter(frame, jobname, fontsize, leftmargin, rightmargin, topmargin, bottommargin, preview);
}

void HardcopyWriter::common()
{
 log = new Logger("HardcopyWriter");
 last_char_was_return = false;
 jobAttributes = new QPrinter();
// jobAttributes->setFullPage(true);
 page = NULL;
 pagesize = QSize(612, 792);
 pagedpi = 72;
 fontName = "Monospace";
 fontStyle = QFont::StyleNormal;
 fontWeight = QFont::Normal;
 pagenum = 0;
 prFirst = 1;
 color = QColor(Qt::black);
 printHeader = true;
 pageCount = new QLabel();
 totalPages = new QLabel();
 pageImages = QVector<QImage*>();
 //	/*protected*/ ImageIcon previewIcon = new ImageIcon();
 previewLabel = new QLabel();
 previewIcon = QPixmap();
 charnum = 0, linenum = 0;
 charoffset = 0;
 previewToolBar = new QToolBar();
// headermetrics = NULL;
// metrics = NULL;
 previewImage = new QImage();
 cancelled = false;
}

/*private*/ void HardcopyWriter::hardcopyWriter(JFrame* frame, QString jobname, int fontsize, double leftmargin, double rightmargin,double topmargin, double bottommargin, bool preview) /*throws HardcopyWriter.PrintCanceledException*/
{
 printHeader = true;

 isPreview = preview;
 this->frame = frame;

 // set default to color
 //pageAttributes.setColor(PageAttributes.ColorType.COLOR);
 //jobAttributes->setColorMode(QPrinter::GrayScale);
 jobAttributes->setDocName(jobname);
 jobAttributes->setFullPage(true);

 // skip printer selection if preview
 if (!isPreview)
 {
//        Toolkit toolkit = frame.getToolkit();

//        job = toolkit.getPrintJob(frame, jobname, jobAttributes, pageAttributes);

//        if (job == NULL)
//            throw new PrintCanceledException("User cancelled print request");
//        pagesize = job.getPageDimension();
//        pagedpi = job.getPageResolution();
//        // determine if user selected a range of pages to print out, note that page becomes NULL if range
//        // selected is less than the total number of pages, that's the reason for the page NULL checks
//        if (jobAttributes.getDefaultSelection().equals(DefaultSelectionType.RANGE)) {
//            prFirst = jobAttributes.getPageRanges()[0][0];
//        }
  QPrintDialog dialog(jobAttributes, this->frame);
  dialog.setWindowTitle(tr("Print Document"));
//  if (editor->textCursor().hasSelection())
   dialog.addEnabledOption(QAbstractPrintDialog::PrintSelection);
  if (dialog.exec() != QDialog::Accepted)
  {
   emit printCancelled("User cancelled print request");
   cancelled = true;
   return;
  }
 }

 // Bug workaround
// if (System.getProperty("os.name").regionMatches(true, 0, "windows", 0, 7))
// {
//        //
// }

 x0 = (int) (leftmargin * pagedpi);
 y0 = (int) (topmargin * pagedpi);
 width = pagesize.width() - (int) ((leftmargin + rightmargin) * pagedpi);
 height = pagesize.height() - (int) ((topmargin + bottommargin) * pagedpi);

 // get body font and font size
 font = QFont(fontName, fontsize, QFont::Normal, fontStyle==QFont::StyleItalic);
 font.setStyleHint(QFont::TypeWriter);

 frame->setFont(font);
 metrics =  new QFontMetrics(frame->font());
 lineheight = metrics->height();
 lineascent = metrics->ascent();
 charwidth = metrics->width('m');

 // compute lines and columns within margins
 chars_per_line = width / charwidth;
 lines_per_page = height / lineheight;

 // header font info
 headerfont = QFont("SansSerif", fontsize,QFont::Normal ,true);
 headermetrics =  new QFontMetrics(frame->font());
 headery = y0 - (int) (0.125 * pagedpi) - headermetrics->height() + headermetrics->ascent();

 // compute date/time for header
// DateFormat df = DateFormat.getDateTimeInstance(DateFormat.LONG, DateFormat.SHORT);
// df.setTimeZone(TimeZone.getDefault());
 time = QDateTime::currentDateTime().toString();

 this->jobname = jobname;
 this->fontsize = fontsize;

 if (isPreview)
 {
  previewFrame = new JFrame("Print Preview: " + jobname);
  QWidget* contentPane = new QWidget;
  previewFrame->setCentralWidget(contentPane);
  QVBoxLayout* layout = new QVBoxLayout;
  previewFrame->centralWidget()->setLayout(layout); //(new BorderLayout());
  toolBarInit();
//  previewToolBar.setFloatable(false);
  layout->addWidget(previewToolBar, 0,Qt::AlignTop);
  previewPanel = new QWidget();
  previewPanelLayout = new QVBoxLayout;
  previewPanel->setLayout(previewPanelLayout);
  previewPanel->resize(pagesize.width(), pagesize.height());
  previewPanel->setMinimumSize(500,600);
  // add the panel to the frame and make visible, otherwise creating the image will fail.
  // use a scroll pane to handle print images bigger than the window
  QScrollArea* scrollArea;
  layout->addWidget(scrollArea = new QScrollArea());//,0,  Qt::AlignVCenter);
  QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
  scrollArea->setSizePolicy(sizePolicy);
  scrollArea->setWidget(previewPanel);
  // page width 660 for portrait
  previewFrame->resize(pagesize.width() + 48, pagesize.height() + 100);
  previewFrame->setVisible(true);
 }
}

/**
 * Creates a print preview toolbar added by Dennis Miller
 */
/*protected*/ void HardcopyWriter::toolBarInit()
{
 previousButton = new QPushButton("Previous Page");
 previewToolBar->addWidget(previousButton);
//    previousButton.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent actionEvent) {
//            pagenum--;
//            displayPage();
//        }
//    });
 connect(previousButton, SIGNAL(clicked()), this, SLOT(On_previousButton_clicked()));
    nextButton = new QPushButton("Next Page");
    previewToolBar->addWidget(nextButton);
//    nextButton.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent actionEvent) {
//            pagenum++;
//            displayPage();
//        }
//    });
    connect(nextButton, SIGNAL(clicked()), this, SLOT(On_nextButton_clicked()));
    previewToolBar->addWidget(new QLabel("    Page "));
    previewToolBar->addWidget(pageCount);
    previewToolBar->addWidget(new QLabel(" of "));
    previewToolBar->addWidget(totalPages);
    closeButton = new QPushButton(" Close ");
    previewToolBar->addWidget(closeButton);
//    closeButton.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent actionEvent) {
//            if (page != NULL)
//                page.dispose();
//            previewFrame.dispose();
//        }
//    });
    connect(closeButton, SIGNAL(clicked()), this, SLOT(On_close_clicked()));
}
void HardcopyWriter::On_previousButton_clicked()
{
 pagenum--;
 displayPage();
}
void HardcopyWriter::On_nextButton_clicked()
{
 pagenum++;
 displayPage();
}
void HardcopyWriter::On_close_clicked()
{
 if(page != NULL)
   page->end();
 previewFrame->close();
}

/**
 * Method to display a page image in the preview pane Not in original class but added later by Dennis Miller
 */
/*protected*/ void HardcopyWriter::displayPage()
{
 // limit the pages to the actual range
 if (pagenum > pageImages.size())
  pagenum = pageImages.size();
 if (pagenum < 1)
  pagenum = 1;
 // enable/disable the previous/next buttons as appropriate
 previousButton->setEnabled(true);
 nextButton->setEnabled(true);
 if (pagenum == pageImages.size())
  nextButton->setEnabled(false);
 if (pagenum == 1)
  previousButton->setEnabled(false);
 previewImage = pageImages.at(pagenum - 1);
 previewFrame->setVisible(false);
 previewIcon = QPixmap::fromImage(*previewImage);
 previewLabel->setPixmap(previewIcon);
 // put the label in the panel (already has a scroll pane)
 previewPanelLayout->addWidget(previewLabel);
 // set the page count info
 pageCount->setText(QString::number(pagenum));
 totalPages->setText(QString::number(pageImages.size()) + "     ");
 // repaint the frame but don't use pack() as we don't want resizing
// previewFrame->invalidate();
//    previewFrame.validate();
 previewFrame->setVisible(true);
}

/**
 * write method, implemented by all Write subclasses
 */
/*public*/ void HardcopyWriter::write(QString buffer, int index, int len)
{
 //    synchronized (this.lock) {
 // loop through all characters passed to us
 line = "";
 for (int i = index; i < index + len; i++)
 {
  // if we haven't begun a new page, do that now
  if (page == NULL)
   newpage();

  QChar c = buffer.at(i);
  // if the character is a line terminator, begin a new line
  // unless its \n after \r
  if (buffer.at(i) == '\n')
  {
   if (!last_char_was_return)
   {
    newline();
   }
   continue;
  }
  if (buffer.at(i) == '\r')
  {
   newline();
   last_char_was_return = true;
   continue;
  }
  else
   last_char_was_return = false;

  if (buffer.at(i) == '\f')
    pageBreak();

  // if some other non-printing char, ignore it
  if (Character::isWhitespace(buffer.at(i)) && !Character::isSpaceChar(buffer.at(i)) && (buffer.at(i) != '\t'))
   continue;
  // if no more characters will fit on the line, start new line
  if (charoffset >= width)
  {
   newline();
   // also start a new page if needed
   if (page == NULL)
    newpage();
  }

  // now print the page
  // if a space, skip one space
  // if a tab, skip the necessary number
  // otherwise print the character
  // We need to position each character one-at-a-time to
  // match the FontMetrics

  if (buffer[i] == '\t')
  {
   int tab = 8 - (charnum % 8);
   charnum += tab;
   charoffset = charnum * metrics->width('m');
   for (int t = 0; t < tab; t++)
   {
    line += " ";
   }
  }
  else
  {
   line += buffer[i];
   charnum++;
   charoffset += metrics->width(buffer[i]);
  }
 }
 if (page != NULL && pagenum >= prFirst)
  page->drawText(x0, y0 + (linenum * lineheight) +    lineascent,line);
 }
// }
//}
#if 1
/**
 * Write the String with the desired color. Returns the text color back to the default after the string is written.
 *
 * @param c
 *            the color desired for this String
 * @param s
 *            the String
 * @throws IOException
 */
/*public*/ void HardcopyWriter::write(QColor c, QString s) throw (IOException)
{
 if (page != NULL)
 {
  //page->setColor(c);
  page->setPen(c);
  }
  //write(s);
  write(s, 0, s.length());
  // note that the above write(s) can cause the page to become NULL!
  if (page != NULL)
  {
   //page->setColor(color); // reset color
   page ->setPen(color);
  }
}

/*public*/ void HardcopyWriter::flush() throw (IOException) {
}
#endif
/** method modified by Dennis Miller to add preview capability */
/*public*/ void HardcopyWriter::close() throw (IOException)
{
//    synchronized (this.lock) {
 if (isPreview)
 {
  pageImages.append(previewImage);
  // set up first page for display in preview frame
  // to get the image displayed, put it in an icon and the icon in a label
  pagenum = 1;
  displayPage();
 }
 if (page != NULL)
  page->end();
//        if (job != NULL)
//            job.end();
//    }
}

/** Dispose added so that a preview can be canceled */
/*public*/ void HardcopyWriter::dispose()
{
//    synchronized (this.lock) {
 if (page != NULL)
  page->end();
  previewFrame->dispose();
//        if (job != NULL)
//            job.end();
//    }
}

/*public*/ void HardcopyWriter::setFontStyle(QFont::Style style) {
//    synchronized (this.lock) {
//        // try to set a new font, but restore current one if it fails
//        Font current = font;
//        try {
//            font = new Font(fontName, style, fontsize);
//            fontStyle = style;
//        } catch (Exception e) {
//            font = current;
//        }
//        // if a page is pending, set the new font, else newpage() will
//        if (page != NULL)
//            page.setFont(font);
//    }
  QFont font = page->font();
  font = QFont(font.family(), font.pointSize(),font.weight(),style== QFont::StyleItalic);
  page->setFont(font);
}
void HardcopyWriter::setFontWeight(QFont::Weight w)
{
 QFont font = page->font();
 font = QFont(font.family(), font.pointSize(),w ,font.style() == QFont::StyleItalic);
 page->setFont(font);
}

/*public*/ int HardcopyWriter::getLineHeight() {
    return this->lineheight;
}

/*public*/ int HardcopyWriter::getFontSize() {
    return this->fontsize;
}

/*public*/ int HardcopyWriter::getCharWidth() {
    return this->charwidth;
}

/*public*/ int HardcopyWriter::getLineAscent() {
    return this->lineascent;
}
#if 1
/*public*/ void HardcopyWriter::setFontName(QString name)
{
//    synchronized (this.lock) {
 // try to set a new font, but restore current one if it fails
 QFont current = font;
 try
 {
  font = QFont(name, fontsize, fontWeight, fontStyle);
  fontName = name;
  font.setStyleHint(QFont::TypeWriter);
  if(page != NULL)
   page->setFont(font);

  QFontMetrics* fm = new QFontMetrics(font);
  if(page != NULL)
  {
   QFontMetrics pm = page->fontMetrics();
   metrics = &pm;
  }
  lineheight = metrics->height();
  lineascent = metrics->ascent();
  charwidth = metrics->width('m');

  // compute lines and columns within margins
  chars_per_line = width / charwidth;
  lines_per_page = height / lineheight;
 }
 catch (Exception e)
 {
  font = current;
 }
 // if a page is pending, set the new font, else newpage() will
 if (page != NULL)
  page->setFont(font);
//    }
}
#endif
/**
 * sets the default text color
 *
 * @param c
 *            the new default text color
 */
/*public*/ void HardcopyWriter::setTextColor(QColor c)
{
 color = c;
}

/** End the current page. Subsequent output will be on a new page */
/*public*/ void HardcopyWriter::pageBreak()
{
//    synchronized (this.lock) {
 if (isPreview)
  pageImages.append(previewImage);
 else
  jobAttributes->newPage();
 if (pagenum != 0)
   page->end();
 page = NULL;
 //jobAttributes->newPage();
//    }
}

/** Return the number of columns of characters that fit on a page */
/*public*/ int HardcopyWriter::getCharactersPerLine()
{
 return this->chars_per_line;
}

/** Return the number of lines that fit on a page */
/*public*/ int HardcopyWriter::getLinesPerPage() {
    return this->lines_per_page;
}
/**
 * Internal method begins a new line method modified by Dennis Miller to add preview capability
 */
/*protected*/ void HardcopyWriter::newline()
{
 if (page != NULL && pagenum >= prFirst)
  page->drawText(x0, y0 + (linenum * lineheight) + lineascent, line);
 line = "";
 charnum = 0;
 charoffset = 0;
 linenum++;
 if (linenum >= lines_per_page)
 {
  if (isPreview)
   pageImages.append(previewImage);
  if (page != NULL)
   page->end();
  page = NULL;
  newpage();
 }
}

/**
 * Internal method beings a new page and prints the header method modified by Dennis Miller to add preview
 * capability
 */
/*protected*/ void HardcopyWriter::newpage()
{
 pagenum++;
 linenum = 0;
 charnum = 0;
 // get a page graphics or image graphics object depending on output destination
 if (page == NULL)
 {
  if (!isPreview)
  {
   if (pagenum >= prFirst)
   {
    //page = job.getGraphics();
    page = new QPainter();
    page->setFont(font);
    page->setPen(color);
    page->begin(jobAttributes);
   }
   else
   {
    // The job.getGraphics() method will return NULL if the number of pages requested is greater than
    // the number the user selected. Since the code checks for a NULL page in many places, we need to
    // create a "dummy" page for the pages the user has decided to skip.
//    JFrame* f = new JFrame();
//    f->pack();
//    page = f->createImage(pagesize.width(), pagesize.height()).getGraphics();
    previewImage = new QImage(pagesize,QImage::Format_RGB32);
    page = new QPainter();
    page->begin(previewImage);
   }
  }
  else
  { // Preview
   //previewImage = previewPanel.createImage(pagesize.width, pagesize.height);
   previewImage = new QImage(pagesize, QImage::Format_RGB32);
   page = new QPainter();
   if(!page->begin(previewImage))
   {
    log->error(QString("Error creating painter for page %1").arg(pagenum));
   }
   //page = previewImage.getGraphics();
   //page->setColor(new QBrush(QColor(Qt::white)));
   page->fillRect(0, 0, previewImage->width(), previewImage->height(),QColor(Qt::white));
   //page.setColor(color);
   page->setBrush( QBrush(color));
  }
 }
 if (printHeader && page != NULL && pagenum >= prFirst)
 {
  page->setFont(headerfont);
  page->drawText(x0, headery, jobname);

  QString s = "- " + QString::number(pagenum) + " -"; // print page number centered
  int w = headermetrics->width(s);
  page->drawText(x0 + (this->width - w) / 2, headery, s);
  w = headermetrics->width(time);
  page->drawText(x0 + width - w, headery, time);

  // draw a line under the header
  int y = headery + headermetrics->descent() + 1;
  page->drawLine(x0, y, x0 + width, y);
 }
 // set basic font
 if (page != NULL)
  page->setFont(font);
}

/**
 * Write a graphic to the printout.
 * <P>
 * This was not in the original class, but was added afterwards by Bob Jacobsen. Modified by D Miller.
 * <P>
 * The image is positioned on the right side of the paper, at the current height.
 */
/*public*/ void HardcopyWriter::write(QImage c, QWidget* i)
{
 // if we haven't begun a new page, do that now
 if (page == NULL)
  newpage();

 // D Miller: Scale the icon slightly smaller to make page layout easier and
 // position one character to left of right margin
 QRect source = QRect(0,0,c.width(), c.height());
 int x = x0 + width - (c.width() * 2 / 3 + charwidth);
 int y = y0 + (linenum * lineheight) + lineascent;
 int w = c.width() * 2 / 3;
 int h = c.height() * 2 /3;
 QRect target = QRect(x, y, w, h);

 if (/*page != NULL &&*/ pagenum >= prFirst)
  //page.drawImage(c, x, y, c.getWidth(NULL) * 2 / 3, c.getHeight(NULL) * 2 / 3, NULL);
 //page->drawImage(x,y,c);
 page->drawImage(target, c, source);
}

/**
 * Write a graphic to the printout.
 * <P>
 * This was not in the original class, but was added afterwards by Kevin Dickerson. it is a copy of the write, but
 * without the scaling.
 * <P>
 * The image is positioned on the right side of the paper, at the current height.
 */
/*public*/ void HardcopyWriter::writeNoScale(QImage c, QWidget* i)
{
 // if we haven't begun a new page, do that now
 if (page == NULL)
  newpage();

 int x = x0 + width - (c.width() + charwidth);
 int y = y0 + (linenum * lineheight) + lineascent;

 if (page != NULL && pagenum >= prFirst)
  page->drawImage(x, y, c, c.width(), c.height(), NULL);
}
/**
 * Writes a string.
 *
 * @param  str
 *         String to be written
 *
 * @throws  IOException
 *          If an I/O error occurs
 */
/*public*/ void HardcopyWriter::write(QString str) /*throws IOException*/ {
    write(str, 0, str.length());
}

/*public*/ void HardcopyWriter::writeHtml(QString str) /*throws IOException*/
{
//  QTextDocument doc;
//  doc.setHtml(str);
//  doc.print(jobAttributes);
// QTextEdit ed;
// ed.setHtml(str);
// ed.print(jobAttributes);
// QTextLayout lo;
// lo.setText(str);
// lo.draw(page,QPoint(2,50));
 int x = x0 ;
 int y = y0 + (linenum * lineheight) + lineascent;

 QLabel* lbl  = new QLabel;
 lbl->setFont(font);
 lbl->setTextFormat(Qt::RichText);
 lbl->setText(str);
 lbl->setWordWrap(true);
 lbl->render(page,QPoint(x,y),QRegion(),QWidget::DrawChildren);
}

/**
 * A Method to allow a JWindow to print itself at the current line position
 * <P>
 * This was not in the original class, but was added afterwards by Dennis Miller.
 * <P>
 * Intended to allow for a graphic printout of the speed table, but can be used to print any window. The JWindow is
 * passed to the method and prints itself at the current line and aligned at the left margin. The calling method
 * should check for sufficient space left on the page and move it to the top of the next page if there isn't enough
 * space.
 */

/*public*/ void HardcopyWriter::write(QMainWindow* jW)
{
 // if we haven't begun a new page, do that now
 if (page == NULL)
  newpage();
 if (page != NULL && pagenum >= prFirst)
 {
  int x = x0;
  int y = y0 + (linenum * lineheight);
  // shift origin to current printing position
  page->translate(x, y);
  // Window must be visible to print
  jW->setVisible(true);
  // Have the window print itself
  //jW->printAll(page);
  jW->render(page);
  // Make it invisible again
  jW->setVisible(false);
  // Get rid of the window now that it's printed and put the origin back where it was
  jW->close();
  page->translate(-x, -y);
 }
}

/**
 * Draw a line on the printout.
 * <P>
 * This was not in the original class, but was added afterwards by Dennis Miller.
 * <P>
 * colStart and colEnd represent the horizontal character positions. The lines actually start in the middle of the
 * character position to make it easy to draw vertical lines and space them between printed characters.
 * <P>
 * rowStart and rowEnd represent the vertical character positions. Horizontal lines are drawn underneath the row
 * (line) number. They are offset so they appear evenly spaced, although they don't take into account any space
 * needed for descenders, so they look best with all caps text
 */
/*public*/ void HardcopyWriter::write(int rowStart, int colStart, int rowEnd, int colEnd)
{
 // if we haven't begun a new page, do that now
 if (page == NULL)
    newpage();
 int xStart = x0 + (colStart - 1) * charwidth + charwidth / 2;
 int xEnd = x0 + (colEnd - 1) * charwidth + charwidth / 2;
 int yStart = y0 + rowStart * lineheight + (lineheight - lineascent) / 2;
 int yEnd = y0 + rowEnd * lineheight + (lineheight - lineascent) / 2;
 if (pageCount != 0 && pagenum >= prFirst)
  page->drawLine(xStart, yStart, xEnd, yEnd);
}

/**
 * Get the current linenumber.
 * <P>
 * This was not in the original class, but was added afterwards by Dennis Miller.
 */
/*public*/ int HardcopyWriter::getCurrentLineNumber()
{
 return this->linenum;
}

/**
 * Print vertical borders on the current line at the left and right sides of the page at character positions 0 and
 * chars_per_line + 1. Border lines are one text line in height
 * <P>
 * This was not in the original class, but was added afterwards by Dennis Miller.
 */
/*public*/ void HardcopyWriter::writeBorders()
{
 write(this->linenum, 0, this->linenum + 1, 0);
 write(this->linenum, this->chars_per_line + 1, this->linenum + 1, this->chars_per_line + 1);
}

/**
 * Increase line spacing by a percentage
 * <P>
 * This method should be invoked immediately after a new HardcopyWriter is created.
 * <P>
 * This method was added to improve appearance when printing tables
 * <P>
 * This was not in the original class, added afterwards by DaveDuchamp.
 */
/*public*/ void HardcopyWriter::increaseLineSpacing(int percent) {
    int delta = (lineheight * percent) / 100;
    lineheight = lineheight + delta;
    lineascent = lineascent + delta;
    lines_per_page = height / lineheight;
}
#if 0
/*public*/ static class PrintCanceledException extends Exception {
    /**
     *
     */
    private static final long serialVersionUID = -281738262906826412L;

    /*public*/ PrintCanceledException(String msg) {
        super(msg);
    }
};

#endif
bool Character::isWhitespace(QChar c)
{
 if(c.isSpace())
  return true;
 if((c == '\n') || (c == '\t') || (c == '\r') || (c == '\f'))
  return true;
 else
  return false;
}
bool Character::isSpaceChar(QChar c)
{
 return c==' ';
}
bool HardcopyWriter::isCancelled() {return cancelled;}
