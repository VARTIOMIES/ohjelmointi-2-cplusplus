#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // Normally this member should be in private part of the
    // class, but due to the automated tests it must be more
    // accessible.
    QTimer* timer;

private slots:
    // Add your slots here

    void on_stopButton_clicked();

    void on_startButton_clicked();

    void on_resetButton_clicked();

    void one_second_passed();

private:
    Ui::MainWindow *ui;
    // Add other necessary members here
    int seconds;
    int minutes;
    void update_displays();
};

#endif // MAINWINDOW_HH
