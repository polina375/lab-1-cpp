#include "types.h"
#include "linear.h"
#include "dataset.h"
#include "evaluation.h"
#include "console.h"
#include <vector>

void test_dataset() {
    auto data = Dataset::generate(10, 0.5f, 1.0f);
    Console::info("Test: Dataset size");
    Console::value("Expected 10, got", static_cast<int>(data.size()));

    if (data.size() != 10) throw "Dataset size test failed";
}

void test_linear() {
    float transform[2][2] = { {1.0f, 0.1f},{0.0f,1.0f} };
    auto data = Dataset::generate(1, 0.0f, 0.0f);
    float oldX = data[0].x;
    float oldY = data[0].y;

    auto newVec = Linear::transform(transform, oldX, oldY);
    Console::info("Test: Linear transform applied");
    Console::value("Original X", oldX);
    Console::value("Transformed X", newVec.x);

    if (newVec.x == oldX && newVec.y == oldY) throw "Linear transform test failed";
}

void test_evaluation() {
    auto data = Dataset::generate(5, 1.0f, 0.0f);
    float error = Evaluation::meanAbsError(data, 1.0f, 0.0f);
    Console::info("Test: Mean Absolute Error");
    Console::value("Error", error);

    if (error < 0.0f) throw "Evaluation error test failed";
}

void test_save_csv() {
    auto data = Dataset::generate(5, 0.5f, 1.0f);
    bool saved = Dataset::saveCSV(data, "../test_points.csv");
    Console::info("Test: Save CSV");
    Console::value("Saved", saved);

    if (!saved) throw "CSV save test failed";
} // <-- вот здесь закрываем функцию

int main_test() {
    Console::info("Running Unit Tests...");

    bool all_passed = true;

    // Проверяем Dataset
    try {
        test_dataset();
    }
    catch (...) {
        Console::info("Dataset test failed!");
        all_passed = false;
    }

    // Проверяем Linear
    try {
        test_linear();
    }
    catch (...) {
        Console::info("Linear transform test failed!");
        all_passed = false;
    }

    // Проверяем Evaluation
    try {
        test_evaluation();
    }
    catch (...) {
        Console::info("Evaluation test failed!");
        all_passed = false;
    }

    // Проверяем CSV
    try {
        test_save_csv();
    }
    catch (...) {
        Console::info("CSV save test failed!");
        all_passed = false;
    }

    if (all_passed)
        Console::info("All tests passed successfully!");
    else
        Console::info("Some tests failed.");

    return all_passed ? 0 : 1;
}