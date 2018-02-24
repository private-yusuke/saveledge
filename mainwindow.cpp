#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);
    ui->dateLabel->setText(diary::getTodayDateString());
    ui->textEdit->setPlainText(diary::getDiary());
    //ui->actionSave->setShortcut(QKeySequence::Save);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveDiary()
{
    if(!diary::isSavedToday()) {
        QMessageBox::information(this, tr("Good job!"), tr("This will be the first time you write your diary today!"));
    }
    if(!diary::saveDiary(ui->textEdit->toPlainText())) {
        QMessageBox::warning(this, tr("error"), diary::errorString);
        ui->statusBar->showMessage(tr("Unable to save today's diary."));
    } else ui->statusBar->showMessage(tr("Saved!"), 5*1000);
    //QMessageBox::information(this, tr("error"), QFileInfo(diary::getTodayDateString()).absoluteFilePath());
}
void MainWindow::on_saveButton_clicked()
{
    saveDiary();
}

void MainWindow::on_actionSave_triggered()
{
    saveDiary();
}
