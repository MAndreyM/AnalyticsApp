#include "dummy_controller.hpp"

DummyController::DummyController(QObject* parent) 
    : QObject(parent) {
}

void DummyController::dummySlot() {
    emit dummySignal();
}
