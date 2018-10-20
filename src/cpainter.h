#ifndef CPAINTER_H
#define CPAINTER_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QList>
#include <QPoint>



class CPainter : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(int penWidth READ penWidth WRITE setPenWidth NOTIFY penWidthChanged)
    Q_PROPERTY(Qt::PenStyle style READ style WRITE setStyle NOTIFY styleChanged)
    Q_PROPERTY(double scale READ scale WRITE setScale NOTIFY scaleChanged)
    Q_PROPERTY(bool antialiasing READ antialiasing WRITE setAntialiasing)

public:
    CPainter(QQuickPaintedItem *parent = 0);
    ~CPainter() { delete pen_; }



    QColor color() const       { return m_color; }
    int penWidth() const       { return m_penWidth; }
    Qt::PenStyle style() const { return m_penStyle; }
    double scale() const       { return m_scale; }


    void setColor(const QColor &color);
    void setPenWidth(int newWidth);
    void setStyle(const Qt::PenStyle &NewStyle);
    void setScale(double scale);

signals:
    void colorChanged();
    void penWidthChanged();
    void styleChanged();
    void scaleChanged();


protected:
    QColor m_color;
    int m_penWidth;
    Qt::PenStyle m_penStyle;
    double m_scale;
    QPen *pen_;

};

#endif // CPAINTER_H
