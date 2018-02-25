#include "diary.h"

QString diary::errorString;

diary::diary()
{

}

QString diary::getDateString(const QDate &date)
{
    return date.toString("yyyy-MM-dd");
}
QString diary::getFilename(const QDate &date)
{
    return QString(QCoreApplication::applicationDirPath() + "/diary/" + getDateString(date) + ".txt");
}
bool diary::isSaved(const QDate &date)
{
    return QFile(getFilename(date)).exists();
}

bool diary::saveDiary(const QDate &date, QString text)
{
    QString rootdir = QCoreApplication::applicationDirPath() + "/diary";
    if(!QDir().exists(rootdir)) {
        QDir().mkdir(rootdir);
    }
    QFile file(getFilename(date));
    qDebug() << getFilename(date);
    if(!file.open(QIODevice::WriteOnly)) {
        errorString = file.errorString();
        return false;
    }
    QTextStream out(&file);
    out << text;
    return true;
}

QString diary::getDiary(const QDate &date)
{
    QFile file(getFilename(date));
    if(!file.open(QIODevice::ReadOnly)) return "";
    return file.readAll();
}
