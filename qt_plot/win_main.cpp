
#include <QtGui/QtGui>
#include <QMessageBox>
#include <QPainter>
#include <QPen>
#include "win_main.h"
#include "set_range_dialog.h"
#include <cmath>
#include "function_to_plot.h"

// note std::clamp avaliable in c++17
double clamp(double val, double lo, double hi) {
    return std::max(lo, std::min(val, hi));
}

WinMain::WinMain(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow()), ctx(-4, 4, -1.2, 1.2)
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
    painter.scale(1,-1);

    float x_scale = w/(xb-xa);
    float x_shift = -(xa+xb)*x_scale/2;

    float y_scale = h/(yb-ya);
    float y_shift = -(ya+yb)*y_scale/2;


    painter.drawLine(xa*x_scale+x_shift, y_shift, xb*x_scale+x_shift, y_shift);

    painter.drawLine(x_shift, ya*y_scale + y_shift, x_shift, yb*y_scale + y_shift);

    QFont font("Arial", 12);
    painter.setFont(font);

    float axis_zero_x = x_shift;
    bool is_x_axis_in_range = (-w/2 <= axis_zero_x && axis_zero_x <= w/2);
    if (!is_x_axis_in_range) {
        axis_zero_x = -w/2 + 10;
    }

    float axis_zero_y = -y_shift;
    bool is_y_axis_in_range = (-h/2 <= axis_zero_y && axis_zero_y <= h/2);
    if (!is_y_axis_in_range) {
        axis_zero_y = h/2 - 20;
    }


    painter.scale(1,-1);
    int n_point_coords = 6;
    double coord_step = (xb-xa)/n_point_coords;
    double x = xa;
    while (x <= xb)
    {
        if (std::abs(x) < 1e-5) x = 0;
        auto label = QString::number(x, 'g', 2);
        double margin = x == xa ? 0 : -10;
        painter.drawText(QRectF(x*x_scale+x_shift + margin, axis_zero_y, 100, 100), label);
        x += coord_step;
    }

    n_point_coords = 6;
    coord_step = (yb-ya)/n_point_coords;
    double y = ya;
    while (y <= yb)
    {
        if (std::abs(y) < 1e-5) {
            y += coord_step;
            continue;
        }
        auto label = QString::number(y, 'g', 2);
        double margin = y == ya ? 0 : 20;
        painter.drawText(QRectF(axis_zero_x, -y*y_scale-y_shift + margin,  100, 100), label);
        y += coord_step;
    }

    painter.scale(1,-1);
    QPen penMain(QColor("#00e0fc"));
    QPen penSecond(QColor("#000000"));
    painter.setPen(penMain);
    auto b = QBrush(QColor("#FF2255"));
    painter.setBrush(b);

    float step = 1e-3;

    float f_max = ya-1;
    float f_min = yb+1;
    std::vector<QPoint> max_ponts;
    std::vector<QPoint> min_ponts;
    float prev_x = xa - 1;
    while (xa < xb) {
        float xaa = xa + step;
        if (std::abs(f(xa)) < 1e-3) {
            painter.drawEllipse(xa*x_scale+x_shift -4 ,
                                f(xa)*y_scale + y_shift -4 ,
                                8, 8);
        }
        painter.drawLine(xa*x_scale+x_shift,
                         f(xa)*y_scale + y_shift,
                         (xaa)*x_scale+x_shift,
                         f(xaa)*y_scale + y_shift);

        auto y = f(xa);
        if ( y > f_max) {
            f_max = y;
            max_ponts.clear();
        }
        if (std::abs(y - f_max) < 1e-5) {
            if (std::abs(prev_x - xa) > step*5) {
                prev_x = xa;
                max_ponts.push_back(QPoint(xa*x_scale+x_shift, f(xa)*y_scale + y_shift));
            }
        }

        if ( y < f_min) {
            f_min = y;
            min_ponts.clear();
        }
        if (std::abs(y - f_min) < 1e-5) {
            if (std::abs(prev_x - xa) > step*5) {
                prev_x = xa;
                min_ponts.push_back(QPoint(xa*x_scale+x_shift, f(xa)*y_scale + y_shift));
            }
        }

        xa = xaa;
    }

    for (auto it = max_ponts.begin(); it != max_ponts.end(); ++it) {
        auto p =(*it) - QPoint(2,2);
        painter.drawEllipse( p, 4, 4);

        painter.scale(1,-1);
        auto label = QString::number(f_max, 'g', 2);
        painter.setPen(penSecond);
        painter.drawText(QRectF(p.x(), -p.y(),  100, 100), label);
        painter.setPen(penMain);
        painter.scale(1,-1);

    }

    for (auto it = min_ponts.begin(); it != min_ponts.end(); ++it) {
        auto p =(*it) - QPoint(2,2);
        painter.drawEllipse( p, 4, 4);
        painter.scale(1,-1);
        auto label = QString::number(f_min, 'g', 2);
        painter.setPen(penSecond);
        painter.drawText(QRectF(p.x(), -p.y(),  100, 100), label);
        painter.setPen(penMain);
        painter.scale(1,-1);
    }
}


WinMain::~WinMain() {
    if (ui) delete ui;
}


