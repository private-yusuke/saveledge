#include "diary.h"

QString diary::errorString;

diary::diary()
{

}

QString diary::getTodayDateString()
{
    return QDateTime::currentDateTime().toString("yyyy-MM-dd");
}
QString diary::getTodayFilename()
{
    return QString(QCoreApplication::applicationDirPath() + "/diary/" + getTodayDateString() + ".txt");
}
bool diary::isSavedToday()
{
    return QFile(getTodayFilename()).exists();
}

bool diary::saveDiary(QString text)
{
    QDir rootdir("diary");
    if(!QDir().exists("diary")) {
        QDir().mkdir("diary");
    }
    QFile file(getTodayFilename());
    qDebug() << getTodayFilename();
    if(!file.open(QIODevice::WriteOnly)) {
        errorString = file.errorString();
        return false;
    }
    QTextStream out(&file);
    out << text;
    return true;
}

QString diary::getDiary()
{
    QFile file(getTodayFilename());
    if(!file.open(QIODevice::ReadOnly)) return "";
    return file.readAll();
}
