#include <QtCore/QCoreApplication>
#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QTextStream>
#include <QtCore/QRegExp>
#include <iostream>
#include <QDateTime>

const char* const pHelp = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"\
                          "~ AutoIncreaseBuildNr is a tool to increase the build number of a version file.~\n"\
                          "~ The file has to contain a line like the following:                           ~\n"\
                          "~ #define VER_BUILDNR 1                                                        ~\n"\
                          "~ the file is read completly and is written again with the number after        ~\n"\
                          "~ VER_BUILDNR increased.                                                       ~\n"\
                          "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"\
                          "~ call the app with:                                                           ~\n"\
                          "~     AutoIncreaseBuildNr <versionfile>                                        ~\n"\
                          "~ or for help with                                                             ~\n"\
                          "~     AutoIncreaseBuildNr -h                                                   ~\n"\
                          "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QStringList szArgs = app.arguments();

    // 1.) extract arguments
    if(szArgs.count() != 2)
    {
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        std::cout << "Command line errors: " << std::endl;
        std::cout << "the tool was called with an invalid set of arguments." << std::endl;
        std::cout << pHelp << std::endl;
        return 1;
    }

    if((0 == szArgs.at(1).compare(QLatin1String("-h"), Qt::CaseInsensitive)) ||
       (0 == szArgs.at(1).compare(QLatin1String("/h"), Qt::CaseInsensitive)) ||
       (0 == szArgs.at(1).compare(QLatin1String("-?"), Qt::CaseInsensitive)) ||
       (0 == szArgs.at(1).compare(QLatin1String("/?"), Qt::CaseInsensitive)) ||
       (0 == szArgs.at(1).compare(QLatin1String("-help"), Qt::CaseInsensitive)) ||
       (0 == szArgs.at(1).compare(QLatin1String("/help"), Qt::CaseInsensitive)))
    {
        std::cout << pHelp << std::endl;
        return 0;
    }

    if(!QFile::exists(szArgs.at(1)))
    {
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        std::cout << "File not found: " << szArgs.at(1).toLatin1().constData() << std::endl;
        std::cout << pHelp << std::endl;
        return 2;
    }

    // 2.) read version file
    QFile versionFile(szArgs.at(1));
    if(!versionFile.open(QFile::ReadOnly))
    {
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        std::cout << "Error opening the version file for reading: " << szArgs.at(1).toLatin1().constData() << std::endl;
        std::cout << "Error: " << versionFile.errorString().toLatin1().constData() << std::endl;
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        return 3;
    }

    QStringList szContent;
    QStringList szOut;
    QTextStream stream(&versionFile);
    while(!stream.atEnd())
    {
     szContent.append(stream.readLine());
    }
    versionFile.close();
    int nBuildNumber = 0;
    int iDateIndex = -1;

    // 3.) change build nr
    for(int i = 0; i < szContent.count(); ++i)
    {
     QString& rszLine = szContent[i];
     if(rszLine.startsWith("<<<<")) continue;
     if(rszLine.startsWith("====")) continue;
     if(rszLine.startsWith(">>>>")) continue;

     if(rszLine.contains(QLatin1String("#define")) && rszLine.contains(QLatin1String("VER_BUILDNR")))
     {
      rszLine = rszLine.trimmed();
      QStringList szWordsOfLine = rszLine.split(QRegExp("\\s"),
                                                      QString::SkipEmptyParts);
      if(3 == szWordsOfLine.count() &&
               szWordsOfLine.at(0) == "#define" &&
               szWordsOfLine.at(1) == "VER_BUILDNR")
      {
       int n = szWordsOfLine.at(2).toInt();
       if(n < nBuildNumber) continue;
       std::cout << "Old version was " << n << " and is now incremented by 1." << std::endl;
       nBuildNumber = n;
       nBuildNumber++;
       if(iDateIndex == -1)
       {
        iDateIndex = szOut.count();

        szWordsOfLine[2] = QString::number(nBuildNumber);
        rszLine = szWordsOfLine.join(" ");
        szOut.append(rszLine);

        QString newDate = (QDateTime::currentDateTime().toString("yyyyMMdd"));
        rszLine = "#define VER_DATE " + newDate;
        szOut.append(rszLine);

        QString newHour = (QDateTime::currentDateTime().toString("h"));
        rszLine = "#define VER_HOUR " + newHour;
        szOut.append(rszLine);

        QString newMinute = (QDateTime::currentDateTime().toString("m"));
        rszLine = "#define VER_MINUTE " + newMinute;
        szOut.append(rszLine);

        QString newSecond = (QDateTime::currentDateTime().toString("s"));
        rszLine = "#define VER_SECOND " + newSecond;
        szOut.append(rszLine);
       }
       else
       {
        szWordsOfLine[2] = QString::number(nBuildNumber);
        rszLine = szWordsOfLine.join(" ");
        szOut.replace(iDateIndex, rszLine);
       }
      }
     }
     if(rszLine.contains(QLatin1String("#define")) && rszLine.contains(QLatin1String("VER_DATE")))
     {
//            rszLine = rszLine.trimmed();
//            QStringList szWordsOfLine = rszLine.split(QRegExp("\\s"),
//                                                      QString::SkipEmptyParts);
//            if(3 == szWordsOfLine.count() &&
//               szWordsOfLine.at(0) == "#define" &&
//               szWordsOfLine.at(1) == "VER_DATE")
//            {
//                int nBuildDate = szWordsOfLine.at(2).toInt();
//                QString newDate = (QDateTime::currentDateTime().toString("yyyyMMdd"));
//                std::cout << "Old date was " << nBuildDate << " and is now " << newDate.toInt() << std::endl;
//                //nBuildDate = QDateTime::currentDateTime().toString("YYYYMMdd").toInt();
//                szWordsOfLine[2] = newDate;
//                rszLine = szWordsOfLine.join(" ");
//                //break;
//            }
      continue;
     }
     if(rszLine.contains(QLatin1String("#define")) && rszLine.contains(QLatin1String("VER_HOUR")))
     {
//            rszLine = rszLine.trimmed();
//            QStringList szWordsOfLine = rszLine.split(QRegExp("\\s"),
//                                                      QString::SkipEmptyParts);
//            if(3 == szWordsOfLine.count() &&
//               szWordsOfLine.at(0) == "#define" &&
//               szWordsOfLine.at(1) == "VER_HOUR")
//            {
//                int nBuildTime = szWordsOfLine.at(2).toInt();
//                QString newHour = (QDateTime::currentDateTime().toString("h"));
//                std::cout << "Old time was " << nBuildTime << " and is now " << newHour.toInt() << std::endl;
//                //nBuildDate = QDateTime::currentDateTime().toString("YYYYMMdd").toInt();
//                szWordsOfLine[2] = newHour ;
//                rszLine = szWordsOfLine.join(" ");
//                //break;
//            }
      continue;
     }
     if(rszLine.contains(QLatin1String("#define")) && rszLine.contains(QLatin1String("VER_MINUTE")))
     {
//            rszLine = rszLine.trimmed();
//            QStringList szWordsOfLine = rszLine.split(QRegExp("\\s"),
//                                                      QString::SkipEmptyParts);
//            if(3 == szWordsOfLine.count() &&
//               szWordsOfLine.at(0) == "#define" &&
//               szWordsOfLine.at(1) == "VER_MINUTE")
//            {
//                int nBuildTime = szWordsOfLine.at(2).toInt();
//                QString newMinute = (QDateTime::currentDateTime().toString("m"));
//                std::cout << "Old time was " << nBuildTime << " and is now " << newMinute.toInt() << std::endl;
//                //nBuildDate = QDateTime::currentDateTime().toString("YYYYMMdd").toInt();
//                szWordsOfLine[2] = newMinute ;
//                rszLine = szWordsOfLine.join(" ");
//                //break;
//            }
      continue;
     }
     if(rszLine.contains(QLatin1String("#define")) && rszLine.contains(QLatin1String("VER_SECOND")))
     {
//            rszLine = rszLine.trimmed();
//            QStringList szWordsOfLine = rszLine.split(QRegExp("\\s"),
//                                                      QString::SkipEmptyParts);
//            if(3 == szWordsOfLine.count() &&
//               szWordsOfLine.at(0) == "#define" &&
//               szWordsOfLine.at(1) == "VER_SECOND")
//            {
//                int nBuildTime = szWordsOfLine.at(2).toInt();
//                QString newSecond = (QDateTime::currentDateTime().toString("s"));
//                std::cout << "Old time was " << nBuildTime << " and is now " << newSecond.toInt() << std::endl;
//                //nBuildDate = QDateTime::currentDateTime().toString("YYYYMMdd").toInt();
//                szWordsOfLine[2] = newSecond ;
//                rszLine = szWordsOfLine.join(" ");
//                //break;
//            }
            continue;
     }
     szOut.append(rszLine);
    }

    // 4.) write version file again.
    if(!versionFile.open(QFile::WriteOnly))
    {
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        std::cout << "Error opening the version file for writing: " << szArgs.at(1).toLatin1().constData() << std::endl;
        std::cout << "Error: " << versionFile.errorString().toLatin1().constData() << std::endl;
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        return 4;
    }

    QTextStream writeStream(&versionFile);
    for(int i = 0; i < szOut.count(); ++i)
    {
        writeStream << szOut.at(i) << "\n" << flush;
    }

    std::cout << "version file written" << std::endl;
    return 0;
}
