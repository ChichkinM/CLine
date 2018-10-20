#include "cpainter.h"

CPainter::CPainter(QQuickPaintedItem *parent) :
    QQuickPaintedItem(parent),
    m_color(Qt::black), m_penWidth(1),
    m_penStyle(Qt::SolidLine), m_scale(1)
{
    pen_ = new QPen();
    pen_->setJoinStyle(Qt::MiterJoin);
    setFlag(QQuickPaintedItem::ItemHasContents, true);

    setAntialiasing(true);
    setAcceptedMouseButtons(Qt::AllButtons );
}


void CPainter::setColor(const QColor &color) {
    if(m_color == color) return;
    m_color = color;
    emit colorChanged();
    pen_->setColor(color);
    update();
}

void CPainter::setPenWidth(int newWidth) {
    if(m_penWidth == newWidth) return;
    m_penWidth = newWidth;
    emit penWidthChanged();
    pen_->setWidth(newWidth);
    update();
}

void CPainter::setStyle(const Qt::PenStyle &newStyle) {
    if(m_penStyle == newStyle) return;
    m_penStyle = newStyle;
    emit styleChanged();
    pen_->setStyle(newStyle);
    update();
}

void CPainter::setScale(double scale) {
    if(m_scale == scale) return;
    m_scale = scale;
    emit scaleChanged();
    update();
}


