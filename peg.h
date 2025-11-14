#pragma once
#include <vector>

/// Ein Pflock (Stapel von Scheiben-IDs).
class Peg {
public:
    void push(int diskId) {
        m_disks.push_back(diskId);
    }

    int pop() {
        int id = m_disks.back();
        m_disks.pop_back();
        return id;
    }

    bool empty() const { return m_disks.empty(); }
    const std::vector<int>& disks() const { return m_disks; }
    std::vector<int>& disks() { return m_disks; }

private:
    std::vector<int> m_disks; ///< IDs der Scheiben, oben = letztes Element
};
