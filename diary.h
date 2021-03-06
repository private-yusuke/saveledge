#ifndef DIARY_H
#define DIARY_H

#include <QtWidgets>
#include <QStandardPaths>

class diary
{
public:
    static QString errorString;
    diary();
    static QString getDateString(const QDate &date);
    static QString getFilename(const QDate &date);
    static bool isSaved(const QDate &date);
    static bool saveDiary(const QDate &date, QString text);
    static QString getDiary(const QDate &date);
    static QStringList getSavedDate();
    static QString getDiaryFirstLine(const QDate &date);


};

#endif // DIARY_H
