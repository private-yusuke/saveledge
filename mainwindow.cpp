#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QMessageBox>

QDate editingDate;
bool isEdited = false;
QTextCharFormat editedDateFormat;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);
    this->editingDate = QDate::currentDate();
    ui->dateLabel->setText(diary::getDateString(this->editingDate));
    ui->textEdit->setPlainText(diary::getDiary(this->editingDate));
    this->isEdited = false;
    editedDateFormat = QTextCharFormat();
    editedDateFormat.setUnderlineStyle(QTextCharFormat::SingleUnderline);

    this->ui->actionChange_Controller->setText(tr("Change Controller"));
    initCalendar();
}

void MainWindow::initCalendar()
{
    auto *model = new QStringListModel();
    QStringList qlist;

    foreach(auto v, diary::getSavedDate()) {
        v.chop(4);
        auto date = QDate::fromString(v, "yyyy-MM-dd");
        qDebug() << "format: " << date;
        if(!date.isValid()) continue;
        this->ui->calendarWidget->setDateTextFormat(date, editedDateFormat);
        qlist << QString(date.toString("yyyy/MM/dd") + " " + diary::getDiaryFirstLine(date));
    }
    if(qlist.isEmpty()) qlist << QString(tr("Let's write your diary!"));
    model->setStringList(qlist);
    this->ui->listView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveDiary(const QDate &date)
{
    if(!diary::isSaved(date)) {
        QMessageBox::information(this, tr("Good job!"), tr("This will be the first time you write your diary on %1.").arg(diary::getDateString(this->editingDate)));

    }
    if(!diary::saveDiary(this->editingDate, ui->textEdit->toPlainText())) {
        QMessageBox::warning(this, tr("error"), diary::errorString);
        ui->statusBar->showMessage(tr("Unable to save today's diary."));
    } else {
        ui->statusBar->showMessage(tr("Saved!"), 5*1000);
        this->isEdited = false;
        ui->calendarWidget->setDateTextFormat(date, editedDateFormat);
    }
    initCalendar();
    //QMessageBox::information(this, tr("error"), QFileInfo(diary::getTodayDateString()).absoluteFilePath());
}
void MainWindow::on_saveButton_clicked()
{
    saveDiary(this->editingDate);
    this->isEdited = false;
}

void MainWindow::on_actionSave_triggered()
{
    saveDiary(this->editingDate);
    this->isEdited = false;
}

int MainWindow::checkSaved()
{
    if(this->isEdited) {
        QMessageBox msgBox(this);
        msgBox.setText(tr("Changes you made may not be saved. Do you want to save your changes?"));
        msgBox.setWindowTitle(tr("Are you sure?"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setButtonText(QMessageBox::Yes, tr("Yes"));
        msgBox.setButtonText(QMessageBox::No, tr("No"));
        msgBox.setButtonText(QMessageBox::Cancel, tr("Cancel"));
        msgBox.setIcon(QMessageBox::Warning);

        int res = msgBox.exec();
        if(res == QMessageBox::Yes) saveDiary(this->editingDate);
        return res;
    }
    return QMessageBox::Ok;
}

void MainWindow::on_calendarWidget_activated(const QDate &date)
{
    checkSaved();
    loadDiary(date);
}

void MainWindow::loadDiary(const QDate &date)
{
    if(!date.isValid()) return;
    this->ui->dateLabel->setText(diary::getDateString(date));
    this->editingDate = date;
    this->ui->textEdit->setText(diary::getDiary(date));
    this->isEdited = false;
}

void MainWindow::on_textEdit_textChanged()
{
    this->isEdited = true;
}

void MainWindow::on_actionExit_triggered()
{
    if(checkSaved() != QMessageBox::Cancel) QApplication::exit();
}

void MainWindow::on_actionChange_Controller_triggered()
{
    this->ui->stackedWidget->setCurrentIndex(this->ui->stackedWidget->currentIndex() ^ 1);
}

void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    if(checkSaved() == QMessageBox::Cancel) return;
    auto str = this->ui->listView->model()->data(index).toString().left(10);
    loadDiary(QDate::fromString(str, "yyyy/MM/dd"));
}
