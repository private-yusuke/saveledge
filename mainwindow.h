#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <diary.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void saveDiary(const QDate &date);
    void loadDiary(const QDate &date);
    void initCalendar();
    QDate editingDate;
    bool isEdited;
    QTextCharFormat editedDateFormat;

private slots:
    void on_saveButton_clicked();

    void on_actionSave_triggered();

    void on_calendarWidget_activated(const QDate &date);

    void on_textEdit_textChanged();

    void on_actionExit_triggered();

    void on_actionChange_Controller_triggered();

    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    int checkSaved();
};

#endif // MAINWINDOW_H
