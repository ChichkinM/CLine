#include "cline.h"

void CLine::registerComponents() {
    qmlRegisterType<CLine>("CLine", 1, 0, "CLine");
    qmlRegisterType<CGuiPoint>("CPoint", 1, 0, "CPoint");

}

QQmlListProperty<CGuiPoint> CLine::points() {
    return QQmlListProperty<CGuiPoint>(this, m_points);
}

int CLine::pointsCount() const {
    return m_points.count();
}

CGuiPoint *CLine::point(int index) const {
    return m_points.at(index);
}

CGuiPoint *CLine::correctPosition(const CGuiPoint *pointStart, const CGuiPoint *pointEnd) const
{
    Direction dir;
    int x0 = pointStart->x();
    int y0 = pointStart->y();
    int x1 = pointEnd->x();
    int y1 = pointEnd->y();

    if (x0 == x1 || y0 == y1) {
        if (x0 == x1 && y0 > y1) dir = UP;
        if (x0 == x1 && y0 < y1) dir = DOWN;
        if (x0 > x1 && y0 == y1) dir = LEFT;
        if (x0 < x1 && y0 == y1) dir = RIGHT;
    }
    else
        dir = OTHER;

    CGuiPoint *result = new CGuiPoint;
    switch (dir) {
    case UP:
        result->setY(y0 - penWidth() / 2, false);
        result->setX(x0, false);
        break;
    case DOWN:
        result->setY(y0 + penWidth() / 2, false);
        result->setX(x0, false);
        break;
    case LEFT:
        result->setX(x0 = x0 - penWidth() / 2, false);
        result->setY(y0, false);
        break;
    case RIGHT:
        result->setX(x0 = x0 + penWidth() / 2, false);
        result->setY(y0, false);
        break;
    default:
        result->setX(x0);
        result->setY(y0);
    }

    return result;
}

void CLine::updateSize() {
    setHeight(height_);
    setWidth(width_);
    setX(x_);
    setY(y_);

    updatePolish();
}

void CLine::resizeByPoints() {
    int preX = pointMinX_->x() - penWidth() / 2;
    int preY = pointMinY_->y() - penWidth() / 2;
    int preHeight = pointMaxY_->y() - pointMinY_->y() + penWidth();
    int preWidth = pointMaxX_->x() - pointMinX_->x() + penWidth();

    if (m_clipType & CLIP_TOP) {
        preY = pointMinY_->y();
        preHeight = pointMaxY_->y() - pointMinY_->y() + penWidth() / 2;
    }

    if (m_clipType & CLIP_LEFT) {
        preX = pointMinX_->x();
        preWidth = pointMaxX_->x() - pointMinX_->x() + penWidth() / 2;
    }

    if (m_clipType & CLIP_BOTTOM) {
        preHeight -= penWidth() / 2;
    }

    if (m_clipType & CLIP_RIGHT) {
        preWidth -= penWidth() / 2;
    }

    if (m_clipType & NO_CLIP) {
        preX = pointMinX_->x() - penWidth() / 2;
        preY = pointMinY_->y() - penWidth() / 2;
        preHeight = pointMaxY_->y() - pointMinY_->y() + penWidth();
        preWidth = pointMaxX_->x() - pointMinX_->x() + penWidth();
    }

    x_ = preX;
    y_ = preY;
    height_ = preHeight;
    width_ = preWidth;

    updateSize();
}

void CLine::setPointsForResize() {
    pointMaxX_ = m_points.at(0);
    pointMaxY_ = m_points.at(0);
    pointMinX_ = m_points.at(0);
    pointMinY_ = m_points.at(0);

    for(CGuiPoint *p : m_points) {
        if (p->x() > pointMaxX_->x())
            pointMaxX_ = p;
        if (p->x() < pointMinX_->x())
            pointMinX_ = p;
        if (p->y() > pointMaxY_->y())
            pointMaxY_ = p;
        if (p->y() < pointMinY_->y())
            pointMinY_ = p;
    }

    if (!pointSignalsIsConnectToSlots_) {
        connect(pointMaxX_, SIGNAL(xChanged(int)), this, SLOT(update()));
        connect(pointMaxY_, SIGNAL(yChanged(int)), this, SLOT(update()));
        connect(pointMinX_, SIGNAL(xChanged(int)), this, SLOT(update()));
        connect(pointMinY_, SIGNAL(yChanged(int)), this, SLOT(update()));
        pointSignalsIsConnectToSlots_ = true;
    }
}

void CLine::paint(QPainter *painter) {
    setPointsForResize();
    resizeByPoints();

    CGuiPoint *newStart = correctPosition(m_points.at(0), m_points.at(1));
    CGuiPoint *newEnd = correctPosition(m_points.at(m_points.count() - 1), m_points.at(m_points.count() - 2));

    QPainterPath path;
    path.moveTo(newStart->x() - x_, newStart->y() - y_);
    for(int i = 1; i < m_points.count() - 1; i++)
        path.lineTo(m_points.at(i)->x() - x_, m_points.at(i)->y() - y_);
    path.lineTo(newEnd->x() - x_, newEnd->y() - y_);

    painter->setPen(*pen_);
    painter->drawPath(path);
}


