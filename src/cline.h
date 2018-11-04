#ifndef CLINE_H
#define CLINE_H

#include "cpainter.h"

class CGuiPoint : public QObject {
    Q_OBJECT
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
public:
    CGuiPoint(QObject *parent = 0) : QObject(parent), m_x(0), m_y(0) { }

    int x() const { return m_x; }
    int y() const { return m_y; }

    void setX(int value, bool emitSignal = true) { m_x = value; if (emitSignal) emit xChanged(value); }
    void setY(int value, bool emitSignal = true) { m_y = value; if (emitSignal) emit yChanged(value); }

private:
    int m_x;
    int m_y;

signals:
    void xChanged(int value);
    void yChanged(int value);
};



class CLine : public CPainter
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<CGuiPoint> points READ points)
    Q_PROPERTY(int clipType READ clipType WRITE setClipType)
    Q_PROPERTY(int radius READ radius WRITE setRadius)
    Q_PROPERTY(bool clickable READ clickable WRITE setClickable)


public:
    CLine();
    ~CLine() { }

    void  mousePressEvent (QMouseEvent *event) override;
    void paint(QPainter *painter) override;

    QQmlListProperty<CGuiPoint> points();
    int pointsCount() const;
    CGuiPoint *point(int index) const;

    enum ClipType { NO_CLIP = 1, CLIP_TOP = 2, CLIP_BOTTOM = 4, CLIP_RIGHT = 8, CLIP_LEFT = 16 };
    Q_ENUMS(ClipType)

    void setClipType(int newClipType)   { m_clipType = newClipType; }
    void setClickable(bool clickable)   { m_clickable = clickable; }
    void setRadius(int newRadius)       { m_radius = newRadius; }

    int radius()        { return m_radius; }
    bool clickable()    { return m_clickable; }
    int clipType()      { return m_clipType; }

    static void registerComponents();


protected:
    enum Direction { LEFT, RIGHT, DOWN, UP, OTHER };
    QList<CGuiPoint*> m_points;

    CGuiPoint *correctPosition(const CGuiPoint *pointStart, const CGuiPoint *pointEnd) const;

    void updateSize();


private:
    int x_ = 0;
    int y_ = 0;
    int width_ = 1;
    int height_ = 1;

    CGuiPoint *pointMaxX_ = nullptr;
    CGuiPoint *pointMaxY_ = nullptr;
    CGuiPoint *pointMinX_ = nullptr;
    CGuiPoint *pointMinY_ = nullptr;

    int m_clipType = NO_CLIP;
    int m_radius = 0;
    bool m_clickable = false;

    bool pointSignalsIsConnectToSlots_ = false;

    void resizeByPoints();
    void setPointsForResize();

    QPainterPath path;


private slots:    
    void resize();

signals:
    //TODO: мб возможно получить готовые сигналы действия мыши не прописывая в ручную их
    void clicked();

};

#endif // CLINE_H
