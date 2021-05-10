#ifndef ENDSCREENWIDGET_HH
#define ENDSCREENWIDGET_HH

#include <QWidget>

namespace Ui {
class EndscreenWidget;
}

class EndscreenWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EndscreenWidget(QWidget *parent = nullptr);
    ~EndscreenWidget();

private:
    Ui::EndscreenWidget *ui;
};

#endif // ENDSCREENWIDGET_HH
