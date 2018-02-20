#include <opencv/cv.hpp>
#include <QPainter>
#include <QPixmap>
#include <QFileDialog>
#include <QDebug>
#include <vector>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imgoperate.h"
#include "dragablelabel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    label = new DragableLabel(this);
    label->imgop = &imgop;
    ui->verticalLayout->addWidget(label);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_loadButton_clicked() {
   QString fileName = QFileDialog::getOpenFileName(this,"Select a picture",".","JPEG Files(*.jpg);;PNG Files(*.png)");
   if (!fileName.isNull()) {
       imgop.LoadMainImage(fileName);
       label->setPixmap(imgop.GetCanvas());
       label->points = imgop.CurrentSquare();
       label->update();
   }
}

void MainWindow::on_nextButton_clicked() {
    if (!imgop.IsEmpty()) {
        label->points = imgop.NextSquare();
        label->setPixmap(imgop.GetCanvas());
        label->update();
    }
}

void MainWindow::on_replaceButton_clicked() {
    if (!imgop.IsEmpty()) {
        QString fileName = QFileDialog::getOpenFileName(this,"Select a picture",".","JPEG Files(*.jpg);;PNG Files(*.png)");
        if (!fileName.isNull()) {
            imgop.LoadReplaceImage(fileName);
            label->setPixmap(imgop.GetCanvas());
            label->update();
        }
    }
}

void MainWindow::on_prevButton_clicked() {
    if (!imgop.IsEmpty()) {
        label->points = imgop.PreviousSquare();
        label->setPixmap(imgop.GetCanvas());
        label->update();
    }
}

void MainWindow::on_saveButton_clicked() {
    if (!imgop.IsEmpty()) {
        QString fileName = QFileDialog::getSaveFileName(this,"Save",".","JPEG Files(*.jpg);;PNG Files(*.png)");
        if (!fileName.isNull()) {
            imgop.SaveImage(fileName);
        }
    }
}
