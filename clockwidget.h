#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H
#include <QApplication>
#include <QLabel>
#include <QTimer>
#include <QTime>
#include <QPainter>
#include <QPen>
#include <QBrush>


class ClockWidget : public QLabel {
public:
    ClockWidget(QWidget *parent = nullptr) : QLabel(parent) {
        setMinimumSize(200, 200);
        setText(""); // Очищаем текстовое содержимое

        // Создаем таймер для обновления времени каждые 50 миллисекунд
        m_timer.setInterval(50);
        connect(&m_timer, &QTimer::timeout, this, &ClockWidget::updateClock);
        m_timer.start();
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        int side = qMin(width(), height());
        int xCenter = width() / 2;
        int yCenter = height() / 2;

        painter.translate(xCenter, yCenter);
        painter.scale(side / 200.0, side / 200.0);

        drawClock(&painter);
    }

private slots:
    void updateClock() {
        // Пересчитываем углы поворота стрелок на основе текущего времени
        QTime currentTime = QTime::currentTime();
        m_hourAngle = 30.0 * (currentTime.hour() + currentTime.minute() / 60.0);
        m_minuteAngle = 6.0 * (currentTime.minute() + currentTime.second() / 60.0);
        m_secondAngle = 6.0 * currentTime.second();

        // Перерисовываем часы
        update();
    }

private:
    void drawClock(QPainter *painter) {
        painter->save();

        // Рисуем циферблат
        QPen outerCirclePen(Qt::black);
        outerCirclePen.setWidth(2);
        painter->setPen(outerCirclePen);
        painter->setBrush(Qt::white);
        painter->drawEllipse(-90, -90, 180, 180);

        // Рисуем деления
        QPen scalePen(Qt::black);
        scalePen.setWidth(2);
        for (int i = 0; i < 12; ++i) {
            painter->save();
            painter->rotate(i * 30.0);
            painter->drawLine(0, -80, 0, -70);
            painter->restore();
        }

        // Рисуем часовую стрелку
        painter->save();
        painter->rotate(m_hourAngle);
        painter->setBrush(Qt::black);
        painter->drawConvexPolygon(m_hourHand, 3);
        painter->restore();

        // Рисуем минутную стрелку
        painter->save();
        painter->rotate(m_minuteAngle);
        painter->setBrush(Qt::black);
        painter->drawConvexPolygon(m_minuteHand, 3);
        painter->restore();

        // Рисуем секундную стрелку
        painter->save();
        painter->rotate(m_secondAngle);
        painter->setBrush(Qt::red);
        painter->drawConvexPolygon(m_secondHand, 3);
        painter->restore();

        painter->restore();
    }

private:
    QTimer m_timer;
    qreal m_hourAngle;
    qreal m_minuteAngle;
    qreal m_secondAngle;

    QPointF m_hourHand[3] = {
        QPointF(-2, -2),
        QPointF(2, -2),
        QPointF(0, -40)
    };

    QPointF m_minuteHand[3] = {
        QPointF(-1, -1),
        QPointF(1, -1),
        QPointF(0, -60)
    };

    QPointF m_secondHand[3] = {
        QPointF(-1, -1),
        QPointF(1, -1),
        QPointF(0, -75)
    };
};
#endif // CLOCKWIDGET_H
