//---------------------
// Ivan Chetverin M3113 - ICHetverin
// Реализация TestRunner
// Содержит систему для запуска и проверки unit-тестов
//---------------------

#pragma once
#include <functional>
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <stdexcept>

class TestCase {
public:
    TestCase(const std::string& name, std::function<void()> test, bool shouldFail = false)
        : name(name), test(test), shouldFail(shouldFail) {}

    void run() const {
        try {
            test();
            if (!shouldFail) {
                std::cout << "[PASS] " << name << "\n";
            } else {
                throw std::runtime_error("Expected failure but passed");
            }
        } catch (const std::exception& e) {
            if (shouldFail) {
                std::cout << "[PASS] " << name << ": " << e.what() << "\n";
            } else {
                throw std::runtime_error(std::string("Test '") + name + "' failed: " + e.what());
            }
        }
    }

    std::string name;
    std::function<void()> test;
    bool shouldFail;
};

class TestRunner {
public:
    static TestRunner& instance() {
        static TestRunner instance;
        return instance;
    }

    void addTest(const TestCase& testCase) {
        tests.push_back(testCase);
    }

    void runAll() {
        std::cout << "Running " << tests.size() << " tests...\n";
        size_t passed = 0;

        for (const auto& test : tests) {
            try {
                test.run();
                passed++;
            } catch (const std::exception& e) {
                std::cout << "[FAIL] " << e.what() << "\n";
            }
        }

        std::cout << "\nResults: " << passed << "/" << tests.size()
                  << " tests passed\n";
    }

private:
    std::vector<TestCase> tests;
};
