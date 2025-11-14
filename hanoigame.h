#pragma once

#include <QObject>
#include <QVector>
#include <vector>
#include "peg.h"
#include "disk.h"
#include "move.h"

/// Zustände des Spiels / der Animation.
enum class GameState {
    Ready,
    Running,
    Paused,
    Finished
};

/// Model-Klasse für das Türme-von-Hanoi-Spiel.
class HanoiGame : public QObject {
    Q_OBJECT
public:
    explicit HanoiGame(QObject* parent = nullptr);

    /// Setzt das Spiel mit neuer Scheibenzahl zurück.
    void reset(int diskCount);

    /// Rückgabe der generierten Zugfolge (bereits berechnet nach reset()).
    const QVector<Move>& moves() const { return m_moves; }

    /// Aktueller Zustand der Pflöcke.
    const std::vector<Peg>& pegs() const { return m_pegs; }
    std::vector<Peg>& pegs() { return m_pegs; }

    /// Liste der Scheiben.
    const std::vector<Disk>& disks() const { return m_disks; }

    int diskCount() const { return m_diskCount; }

signals:
    /// Wird emittiert wenn das Spiel neu aufgebaut wurde.
    void gameChanged();

private:
    void generateMoves();
    void solveRecursive(int n, int from, int aux, int to);

    int m_diskCount = 3;
    std::vector<Peg> m_pegs;
    std::vector<Disk> m_disks;
    QVector<Move> m_moves;
};
