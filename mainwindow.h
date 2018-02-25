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
    QDate editingDate;
    bool isEdited;

private slots:
    void on_saveButton_clicked();

    void on_actionSave_triggered();

    void on_calendarWidget_activated(const QDate &date);

    void on_textEdit_textChanged();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
