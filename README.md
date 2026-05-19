# OpenBLAS Interface Tests

Интерфейсные тесты для библиотеки OpenBLAS, покрывающие функционал Level 1 BLAS.

## Описание

Проект содержит интерфейсные тесты для следующих функций CBLAS:

### Single Precision (float)
- `cblas_saxpy` - vector update: y = αx + y
- `cblas_sdot` - dot product
- `cblas_snrm2` - Euclidean norm
- `cblas_scopy` - copy vector
- `cblas_sscal` - scale vector
- `cblas_sasum` - sum of absolute values
- `cblas_isamax` - index of maximum absolute value
- `cblas_sswap` - swap two vectors

### Double Precision (double)
- `cblas_daxpy` - vector update: y = αx + y
- `cblas_ddot` - dot product
- `cblas_dnrm2` - Euclidean norm
- `cblas_dcopy` - copy vector
- `cblas_dscal` - scale vector
- `cblas_dasum` - sum of absolute values
- `cblas_idamax` - index of maximum absolute value
- `cblas_dswap` - swap two vectors
- `cblas_drotg` - generate Givens rotation
- `cblas_drot` - apply Givens rotation

## Покрытие тестами

Тесты покрывают:
- Базовую функциональность всех функций
- Граничные случаи (нулевые значения, единичные векторы)
- Отрицательные значения
- Различные значения параметров stride (incX, incY)
- Оба типа данных (float и double)

## Требования

- CMake >= 3.14
- C++ компилятор с поддержкой C++17
- OpenBLAS или совместимая библиотека BLAS
- Google Test (загружается автоматически)

## Установка зависимостей

### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install -y cmake build-essential libopenblas-dev
```

### Fedora/RHEL
```bash
sudo dnf install cmake gcc-c++ openblas-devel
```

### macOS
```bash
brew install cmake openblas
```

## Сборка и запуск

```bash
# Клонировать репозиторий
git clone <repository-url>
cd openblas-interface-tests

# Создать директорию для сборки
mkdir build
cd build

# Конфигурация
cmake ..

# Сборка
cmake --build .

# Запуск тестов
./cblas_interface_tests

# Или через CTest
ctest --output-on-failure
```

## Сборка с покрытием кода

```bash
mkdir build-coverage
cd build-coverage
cmake -DENABLE_COVERAGE=ON ..
cmake --build .
./cblas_interface_tests

# Генерация отчета о покрытии
lcov --capture --directory . --output-file coverage.info
lcov --remove coverage.info '/usr/*' --output-file coverage.info
lcov --list coverage.info
genhtml coverage.info --output-directory coverage_html
```

## Структура проекта

```
openblas-interface-tests/
├── CMakeLists.txt          # Конфигурация сборки
├── README.md               # Документация
├── include/
│   └── test_utils.h        # Утилиты для тестов
├── tests/
│   ├── test_level1_float.cpp   # Тесты для float (single precision)
│   ├── test_level1_double.cpp  # Тесты для double (double precision)
│   └── test_main.cpp           # Main функция для тестов
└── build/                  # Директория сборки (создается)
```

## Результаты тестов

При успешном выполнении всех тестов вы увидите вывод вида:

```
[==========] Running X tests from Y test suites.
[----------] Global test environment set-up.
[----------] Z tests from CBlasLevel1FloatTest
[ RUN      ] CBlasLevel1FloatTest.SaxpyBasic
[       OK ] CBlasLevel1FloatTest.SaxpyBasic (0 ms)
...
[==========] X tests from Y test suites ran. (Z ms total)
[  PASSED  ] X tests.
```

## Дополнительная информация

### Классификация тестов

Согласно диаграмме классификации тестирования, данные тесты относятся к:
- **По запуску кода на исполнение**: Динамическое тестирование
- **По доступу к коду и архитектуре**: Метод черного ящика (тестирование интерфейса)
- **По степени автоматизации**: Автоматизированное
- **По моменту выполнения**: На основе тест-кейсов

### Тестируемые аспекты

1. **Функциональность**: Корректность вычислений
2. **Совместимость**: Работа с разными типами данных
3. **Граничные условия**: Поведение при крайних значениях
4. **Параметры stride**: Корректная работа с разными шагами по массиву

## Лицензия

Этот проект создан в образовательных целях для тестирования библиотеки OpenBLAS.
