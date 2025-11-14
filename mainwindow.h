#pragma once

#include <QMainWindow>
#include <QMap>
#include "hanoigame.h"

class QGraphicsView;
class QGraphicsScene;
class QGraphicsRectItem;
class QTimer;
class QPushButton;

/// Hauptfenster mit View + Steuerung.
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private slots:
    void onNewClicked();
    void onStartClicked();
    void onPauseClicked();
    void onQuitClicked();

    void onTimerTick();
    void updateStatusBar();

    void openSettings();

private:
    void setupUi();
    void setupMenu();
    void rebuildGraphics();
    void applyMove(const Move& move);

    HanoiGame m_game;
    GameState m_state = GameState::Ready;

    QGraphicsView* m_view = nullptr;
    QGraphicsScene* m_scene = nullptr;

    // Disk-ID -> Item
    QMap<int, QGraphicsRectItem*> m_diskItems;

    QTimer* m_timer = nullptr;
    int m_currentMoveIndex = 0;
    int m_movesDone = 0;
    int m_moveDurationMs = 800; // Standard-Zugdauer

    QPushButton* m_newButton = nullptr;
    QPushButton* m_startButton = nullptr;
    QPushButton* m_pauseButton = nullptr;
    QPushButton* m_quitButton = nullptr;
};
