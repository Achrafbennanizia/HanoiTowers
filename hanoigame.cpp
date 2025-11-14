#include "hanoigame.h"
#include <QColor>

HanoiGame::HanoiGame(QObject* parent)
    : QObject(parent)
{
    reset(m_diskCount);
}

void HanoiGame::reset(int diskCount)
{
    m_diskCount = diskCount;
    m_moves.clear();

    // drei Pflöcke
    m_pegs.assign(3, Peg{});

    // Scheiben erzeugen (id 0 = größte, id n-1 = kleinste)
    m_disks.clear();
    for (int i = 0; i < diskCount; ++i) {
        int width = 40 + (diskCount - i) * 20;           // simple Breitenberechnung
        QColor color = QColor::fromHsv((i * 40) % 360, 200, 250);
        m_disks.emplace_back(i, width, color);
        m_pegs[0].push(i);                               // alle Scheiben auf linken Pflock
    }

    generateMoves();
    emit gameChanged();
}

void HanoiGame::generateMoves()
{
    m_moves.clear();
    solveRecursive(m_diskCount, 0, 1, 2);
}

void HanoiGame::solveRecursive(int n, int from, int aux, int to)
{
    if (n <= 0) return;

    // bewege n-1 Scheiben von from nach aux
    solveRecursive(n - 1, from, to, aux);

    // große Scheibe von from nach to
    m_moves.push_back(Move{from, to});

    // bewege n-1 Scheiben von aux nach to
    solveRecursive(n - 1, aux, from, to);
}
