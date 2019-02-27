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
    return QString(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)+ "/saveledge/diary/" + getDateString(date) + ".txt");
}
bool diary::isSaved(const QDate &date)
{
    return QFile(getFilename(date)).exists();
}

bool diary::saveDiary(const QDate &date, QString text)
{
    QString rootdir = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
    QString saveledgedir = rootdir+"/saveledge";
    QString diarydir = saveledgedir+"/diary";

    if(!QDir().exists(rootdir)) {
        QDir().mkdir(rootdir);
    }
    if(!QDir().exists(saveledgedir)) {
        QDir().mkdir(saveledgedir);
    }
    if(!QDir().exists(diarydir)) {
        QDir().mkdir(diarydir);
    }
    QFile file(getFilename(date));
    qDebug() << getFilename(date);
    qDebug() << QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
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

QStringList diary::getSavedDate()
{
    auto dir = QDir();
    dir.cd(QString(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)+ "/saveledge/diary/"));
    return dir.entryList(QDir::Filter::Files);
}
