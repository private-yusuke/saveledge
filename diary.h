#ifndef DIARY_H
#define DIARY_H

#include <QtWidgets>

class diary
{
public:
    diary();
    static QString getTodayDateString();
    static QString getTodayFilename();
    static bool isSavedToday();
    static bool saveDiary(QString text);
    static QString getDiary();
};

#endif // DIARY_H
