#include "checkforupdateaction.h"
#include "loggerfactory.h"
#include "jmriabstractaction.h"
#include "jmrijframe.h"
#include "jtextarea.h"
#include "version.h"
#include "jbutton.h"
#include "qtextstream.h"

/**
 * Swing action to check for more recent JMRI version. Checks a jmri.org URL for
 * information.
 *
 * @author Bob Jacobsen Copyright (C) 2007, 2014
 * @author Matt Harris Copyright (C) 2008
 *
 */
// /*public*/ class CheckForUpdateAction extends jmri.util.swing.JmriAbstractAction {

    /*public*/ CheckForUpdateAction::CheckForUpdateAction(/*@Nonnull*/  QString s, /*@Nonnull*/  WindowInterface* wi) : JmriAbstractAction(s, wi) {
        //super(s, wi);
    }

    /*public*/ CheckForUpdateAction::CheckForUpdateAction(/*@Nonnull*/  QString s, /*@Nonnull*/  QIcon i, /*@Nonnull*/  WindowInterface* wi)
     : JmriAbstractAction(s, i, wi)
    {
        //super(s, i, wi);
    }

    /*public*/ CheckForUpdateAction::CheckForUpdateAction(QWidget* parent): JmriAbstractAction(tr("Update"), parent) {
        //super(Bundle.getMessage("Update"));
    }

    //@Override
    /*public*/ void CheckForUpdateAction::actionPerformed(JActionEvent* ev) {

        /*final*/ JFrame* frame = new JmriJFrameX(tr("Update"), false, false);
        frame->setLayout(new QVBoxLayout());//frame.getContentPane(), BoxLayout.Y_AXIS));

        JTextArea* text = new JTextArea();
        text->setEditable(false);
        frame->layout()->addWidget(text);

        QString productionrelease = "";
        QString testrelease = "";
#if 0
        QTextStream* in = nullptr;
        try {
            QString urlname = "http://jmri.org/releaselist";
            URL url = new URL(urlname);
            in = url.openConnection().getInputStream();
            BufferedReader reader = new BufferedReader(new InputStreamReader(in));

            // search for releases
            QString line;
            while ((line = reader.readLine()) != "") {
                if (line.startsWith("production")) {
                    productionrelease = getNumber(reader);
                }
                if (line.startsWith("test")) {
                    testrelease = getNumber(reader);
                }
            }
        } catch (MalformedURLException e) {
            log->error("Unexpected failure in URL parsing", e);
            return;
        } catch (FileNotFoundException e) {
            log->debug(tr("Unable to get version info from web%1").arg(e.getMessage()));
        } catch (IOException e) {
            log->debug(tr("Unexpected failure during reading%1").arg(e.getMessage()));
        } /*finally*/ {
            try {
                if (in != nullptr) {
                    in.close();
                }
            } catch (IOException e1) {
                log->error("Exception closing input stream", e1);
            }
        }
#endif
        // add content
        text->append(tr("Most recent production release: %1").arg(productionrelease) + "\n");
        text->append(tr("Most recent test release: %1").arg(testrelease) + "\n");
        text->append(tr("You have: %1").arg(Version::name()) + "\n"); // cleaner form is getCanonicalVersion()

        JPanel* p = new JPanel();
        p->setLayout(new FlowLayout());

        JButton* go = new JButton(tr("Open JMRI Download Page"));
#if 0
//        go.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent event) {
        connect(go, &JButton::actionPerformed, [=]{
                try {
                    Desktop.getDesktop().browse(new URI("http://jmri.org/download"));
                } catch (URISyntaxException e) {
                    log->error("Invalid page requested", e);
                } catch (IOException e) {
                    log->error("Could no load page", e);
                }
//            }
        });
#endif
        p->layout()->addWidget(go);

        JButton* close = new JButton(tr("Close"));
//        close.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent event) {
        connect(close, &JButton::actionPerformed, [=]{
                frame->setVisible(false);
                frame->dispose();
//            }
        });
        p->layout()->addWidget(close);

        frame->layout()->addWidget(p);
        frame->pack();

        // show
        frame->setVisible(true);

    }

    /*@Nonnull*/  QString getNumber(/*@Nonnull*/  /*BufferedReader*/QTextStream* reader) throw (IOException) {
        reader->readLine();  // skip a line
        QString line = reader->readLine();
        if (line == "") return "";
        return line.mid(0, line.length() - 1);  // drop trailing :
    }

    // never invoked, because we overrode actionPerformed above
    //@Override
    /*public*/ JmriPanel* CheckForUpdateAction::makePanel() {
        throw IllegalArgumentException("Should not be invoked");
    }

    /*private*/ /*final*/ /*static*/ Logger* CheckForUpdateAction::log = LoggerFactory::getLogger("CheckForUpdateAction");

