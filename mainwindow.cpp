#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPalette>
#include <QPushButton>

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

int MainWindow::GetPin1R() {  return ui->label->palette().color(QPalette::Window).red(); }
int MainWindow::GetPin1G() {  return ui->label->palette().color(QPalette::Window).green(); }
int MainWindow::GetPin1B() {  return ui->label->palette().color(QPalette::Window).blue(); }
void MainWindow::Set1RGB(int R, int G, int B)
{
    QPalette p(ui->label->palette());
    p.setColor(QPalette::Window, QColor(R, G, B));
    ui->label->setPalette(p);
    ui->label->setText(QString("%1 %2 %3").arg(R).arg(G).arg(B));
    ui->label->repaint();
}

int MainWindow::GetPin2R() {  return ui->label_2->palette().color(QPalette::Window).red(); }
int MainWindow::GetPin2G() {  return ui->label_2->palette().color(QPalette::Window).green(); }
int MainWindow::GetPin2B() {  return ui->label_2->palette().color(QPalette::Window).blue(); }
void MainWindow::Set2RGB(int R, int G, int B)
{
    QPalette p(ui->label_2->palette());
    p.setColor(QPalette::Window, QColor(R, G, B));
    ui->label_2->setPalette(p);
    ui->label_2->setText(QString("%1 %2 %3").arg(R).arg(G).arg(B));
    ui->label_2->repaint();
}
