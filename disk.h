#pragma once
#include <QColor>

/// Logische Repräsentation einer Scheibe.
class Disk {
public:
    Disk(int id, int width, const QColor& color)
        : m_id(id), m_width(width), m_color(color) {}

    int id() const { return m_id; }
    int width() const { return m_width; }
    QColor color() const { return m_color; }

private:
    int m_id;       ///< eindeutige ID der Scheibe
    int m_width;    ///< Breite in Pixeln (für die Darstellung)
    QColor m_color; ///< Farbe der Scheibe
};
