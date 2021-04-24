#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <fstream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_findPushButton_clicked();

    void on_keyLineEdit_editingFinished();

    void on_fileLineEdit_editingFinished();

private:
    Ui::MainWindow *ui;

    QString filename_ = "<name>";
    QString what_to_find_ = "<string>";
};
#endif // MAINWINDOW_HH
