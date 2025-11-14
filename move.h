#pragma once

/// Repräsentiert einen einzelnen Zug im Türme-von-Hanoi-Spiel.
struct Move {
    int fromPeg;  ///< Index des Quell-Pfocks (0 = links, 1 = Mitte, 2 = rechts)
    int toPeg;    ///< Index des Ziel-Pfocks
};
