#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int GetPin1R();
    int GetPin1G();
    int GetPin1B();

    int GetPin2R();
    int GetPin2G();
    int GetPin2B();

    void Set1RGB(int R, int G, int B);
    void Set2RGB(int R, int G, int B);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
