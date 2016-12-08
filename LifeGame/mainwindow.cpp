#include <QInputDialog>
#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "resizefielddialog.h"
#include "fieldwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::stepNClicked()
{
    bool ok;

    int N = QInputDialog::getInt(this,
                                 tr("N Steps"),
                                 tr("Enter number of steps:"),
                                 previousNStepsCount,
                                 1, 1000000000,
                                 1, &ok);

    if (ok)
    {
        previousNStepsCount = N;
        ui->fieldWidget->stepN(N);
    }
}

void MainWindow::resizeFieldClicked()
{
    ResizeFieldDialog dialog(this);

    dialog.setInputWidth(ui->fieldWidget->getFieldWidth());
    dialog.setInputHeight(ui->fieldWidget->getFieldHeight());

    if (dialog.exec() == QDialog::Accepted)
    {
        int width = dialog.getInputWidth();
        int height = dialog.getInputHeight();

        ui->fieldWidget->resizeField(width, height);
    }
}

void MainWindow::loadClicked()
{
    QString s = QFileDialog::getOpenFileName(this,
                                 tr("Open bitmap field"),
                                 "",
                                 tr("Bitmaps (*.bmp)"));

    if(s != nullptr)
    {
        ui->fieldWidget->LoadField(s);
    }
}

void MainWindow::saveClicked()
{
    QString s = QFileDialog::getSaveFileName(this,
                                 tr("Save field as bitmap"),
                                 "",
                                 tr("Bitmaps (*.bmp)"));

    if(s != nullptr)
    {
        ui->fieldWidget->SaveField(s);
    }
}
