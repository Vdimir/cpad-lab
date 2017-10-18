
#include <QtGui/QtGui>
#include <QMessageBox>
#include <QPainter>
#include <QPen>
#include "win_main.h"
#include "set_range_dialog.h"
#include <cmath>

float f(float x) {
    return x;
    return sin(x);
}

WinMain::WinMain(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow()), ctx(-1, 1, -1, 1)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_NoSystemBackground, true);
    QObject::connect(ui->action_Exit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void WinMain::on_action_About_triggered() {
    auto about_txt = QString::fromLocal8Bit("This Qt app displays plot for sine function.");
    auto title_txt = QString::fromLocal8Bit("About");
    QMessageBox::about(this, title_txt, about_txt);
}

void WinMain::on_actionPlot_range_triggered()
{
    SetRange_Dialog dialog(this, ctx);
    auto res = dialog.exec();
    if (res == QDialog::Accepted) {
        dialog.getData(ctx);
        calc_plot(m_Pixmap.size());
        this->repaint();
    }
}


void WinMain::resizeEvent(QResizeEvent *pEvent)
{
    calc_plot(pEvent->size());
}

void WinMain::paintEvent(QPaintEvent *pEvent)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_Pixmap);
}



void WinMain::calc_plot(QSize sz) {
    m_Pixmap = QPixmap(sz);
    m_Pixmap.fill(Qt::white);

    QPainter painter(&m_Pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);

    int w = sz.width();
    int h = sz.height();

    auto xa = ctx.xa;
    auto xb = ctx.xb;
    auto ya = ctx.ya;
    auto yb = ctx.yb;

    painter.translate(w / 2, h / 2);

    float x_scale = w/(xb-xa);
    float x_shift = -(xa+xb)*x_scale/2;

    float y_scale = h/(yb-ya);
    float y_shift = -(ya+yb)*y_scale/2;


    painter.drawLine(xa*x_scale+x_shift, y_shift, xb*x_scale+x_shift, y_shift);

    painter.drawLine(x_shift, ya*y_scale + y_shift, x_shift, yb*y_scale + y_shift);

    QFont font("Arial", 12);
    painter.setFont(font);
    auto label = QString::fromLocal8Bit("0");
    painter.drawText(QRectF(x_shift-10, y_shift, 100,100),label);

    QPen penHText(QColor("#00e0fc"));
    painter.setPen(penHText);
    float step = 1e-2;
    painter.scale(1,-1);

    while (xa < xb) {
        float xaa = xa + step;
        painter.drawLine(xa*x_scale+x_shift,
                         f(xa)*y_scale + y_shift,
                         (xaa)*x_scale+x_shift,
                         f(xaa)*y_scale + y_shift);
        xa = xaa;
    }
}


WinMain::~WinMain() {
    if (ui) delete ui;
}


