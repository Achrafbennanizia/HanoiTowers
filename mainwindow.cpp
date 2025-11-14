#include "mainwindow.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QStatusBar>
#include <QMenuBar>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QAction>

#include "settingsdialog.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setupUi();
    setupMenu();

    connect(&m_game, &HanoiGame::gameChanged, this, &MainWindow::rebuildGraphics);

    rebuildGraphics();
    updateStatusBar();
}

MainWindow::~MainWindow() = default;

void MainWindow::setupUi()
{
    setWindowTitle("Türme von Hanoi");

    auto* central = new QWidget(this);
    auto* mainLayout = new QVBoxLayout(central);

    m_scene = new QGraphicsScene(this);
    m_view = new QGraphicsView(m_scene, central);
    m_view->setRenderHint(QPainter::Antialiasing);
    mainLayout->addWidget(m_view);

    auto* buttonLayout = new QHBoxLayout();
    m_newButton = new QPushButton("Neu", central);
    m_startButton = new QPushButton("Start", central);
    m_pauseButton = new QPushButton("Pause", central);
    m_quitButton = new QPushButton("Beenden", central);

    buttonLayout->addWidget(m_newButton);
    buttonLayout->addWidget(m_startButton);
    buttonLayout->addWidget(m_pauseButton);
    buttonLayout->addWidget(m_quitButton);
    buttonLayout->addStretch();

    mainLayout->addLayout(buttonLayout);

    setCentralWidget(central);

    // Statusleiste
    statusBar();

    // Timer für „Schritt-für-Schritt“-Animation
    m_timer = new QTimer(this);
    m_timer->setInterval(m_moveDurationMs);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::onTimerTick);

    // Button-Signale
    connect(m_newButton, &QPushButton::clicked, this, &MainWindow::onNewClicked);
    connect(m_startButton, &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(m_pauseButton, &QPushButton::clicked, this, &MainWindow::onPauseClicked);
    connect(m_quitButton, &QPushButton::clicked, this, &MainWindow::onQuitClicked);

    setMinimumSize(800, 600);
}

void MainWindow::setupMenu()
{
    auto* optionsMenu = menuBar()->addMenu("Optionen");

    auto* settingsAction = new QAction("Einstellungen...", this);
    connect(settingsAction, &QAction::triggered, this, &MainWindow::openSettings);

    optionsMenu->addAction(settingsAction);
}

void MainWindow::rebuildGraphics()
{
    m_scene->clear();
    m_diskItems.clear();

    const int pegBaseY = 400;
    const int pegSpacing = 200;
    const int pegWidth = 10;
    const int pegHeight = 250;

    // Pflöcke zeichnen
    for (int i = 0; i < 3; ++i) {
        int x = 200 + i * pegSpacing;
        m_scene->addRect(x - pegWidth / 2, pegBaseY - pegHeight,
                         pegWidth, pegHeight,
                         QPen(Qt::black), QBrush(Qt::darkGray));
    }

    const auto& pegs = m_game.pegs();
    const auto& disks = m_game.disks();

    // Scheiben zeichnen gemäß aktuellem Modellzustand
    for (int pegIndex = 0; pegIndex < 3; ++pegIndex) {
        const auto& stack = pegs[pegIndex].disks();
        int xCenter = 200 + pegIndex * pegSpacing;

        for (int level = 0; level < static_cast<int>(stack.size()); ++level) {
            int diskId = stack[level];
            const Disk& d = disks[diskId];

            int w = d.width();
            int h = 20;
            int y = pegBaseY - h * (stack.size() - level); // unten = größter y

            auto* item = m_scene->addRect(
                xCenter - w / 2,
                y - h,
                w,
                h,
                QPen(Qt::black),
                QBrush(d.color())
                );
            m_diskItems[diskId] = item;
        }
    }

    // Szene-Ausschnitt anpassen
    m_scene->setSceneRect(0, 0, 800, 500);
}

void MainWindow::updateStatusBar()
{
    QString stateText;
    switch (m_state) {
    case GameState::Ready:    stateText = "bereit"; break;
    case GameState::Running:  stateText = "läuft"; break;
    case GameState::Paused:   stateText = "pausiert"; break;
    case GameState::Finished: stateText = "fertig"; break;
    }

    int totalMoves = m_game.moves().size();
    statusBar()->showMessage(
        QString("Scheiben: %1 | Züge: %2 / %3 | Status: %4")
            .arg(m_game.diskCount())
            .arg(m_movesDone)
            .arg(totalMoves)
            .arg(stateText)
        );
}

void MainWindow::onNewClicked()
{
    m_timer->stop();
    m_state = GameState::Ready;
    m_currentMoveIndex = 0;
    m_movesDone = 0;

    m_game.reset(m_game.diskCount()); // gleiche Scheibenzahl erneut
    rebuildGraphics();
    updateStatusBar();
}

void MainWindow::onStartClicked()
{
    if (m_state == GameState::Finished || m_state == GameState::Ready) {
        m_currentMoveIndex = 0;
        m_movesDone = 0;

        // Modell neu aufbauen, falls es verändert wurde
        m_game.reset(m_game.diskCount());
        rebuildGraphics();
    }

    m_state = GameState::Running;
    m_timer->start(m_moveDurationMs);
    updateStatusBar();
}

void MainWindow::onPauseClicked()
{
    if (m_state == GameState::Running) {
        m_state = GameState::Paused;
        m_timer->stop();
    } else if (m_state == GameState::Paused) {
        m_state = GameState::Running;
        m_timer->start(m_moveDurationMs);
    }
    updateStatusBar();
}

void MainWindow::onQuitClicked()
{
    close();
}

void MainWindow::applyMove(const Move& move)
{
    // Logisches Modell aktualisieren
    auto& pegs = m_game.pegs();
    if (pegs[move.fromPeg].empty())
        return;

    int diskId = pegs[move.fromPeg].pop();
    pegs[move.toPeg].push(diskId);

    // Für diese einfache Version: Grafik vollständig neu zeichnen
    rebuildGraphics();
}

void MainWindow::onTimerTick()
{
    const auto& moves = m_game.moves();
    if (m_currentMoveIndex >= moves.size()) {
        m_timer->stop();
        m_state = GameState::Finished;
        updateStatusBar();
        return;
    }

    applyMove(moves[m_currentMoveIndex]);
    ++m_currentMoveIndex;
    ++m_movesDone;

    updateStatusBar();
}

void MainWindow::openSettings()
{
    m_timer->stop();
    m_state = GameState::Ready;

    SettingsDialog dlg(m_game.diskCount(), m_moveDurationMs, this);
    if (dlg.exec() == QDialog::Accepted) {
        m_moveDurationMs = dlg.moveDurationMs();
        m_game.reset(dlg.diskCount());
        m_currentMoveIndex = 0;
        m_movesDone = 0;
        rebuildGraphics();
    }

    updateStatusBar();
}
