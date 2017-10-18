#ifndef WINMAIN_H
#define WINMAIN_H

#include <QMainWindow>
#include "ui_main_window.h"
#include "context.h"


class WinMain : public QMainWindow
{
    Q_OBJECT
public:
    explicit WinMain(QWidget* parent = 0);

    ~WinMain();

protected:
    void paintEvent(QPaintEvent *pEvent);
    void resizeEvent(QResizeEvent *pEvent);
    void calc_plot(QSize sz);

private:
    QPixmap m_Pixmap;
    Ui::MainWindow *ui;
    RangeContext ctx;

private slots:
    void on_action_About_triggered();
    void on_actionPlot_range_triggered();
};
#endif // WINMAIN_H
