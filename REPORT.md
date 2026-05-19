# Отчет по интерфейсному тестированию OpenBLAS

**Выполнил:** Студент  
**Дата:** 06.04.2026  
**Тема:** Интерфейсное тестирование библиотеки линейной алгебры OpenBLAS

---

## 1. Цель работы

Создать интерфейсные тесты для проверки корректности реализации функций библиотеки OpenBLAS (CBLAS интерфейс), продемонстрировать успешное прохождение тестов с корректной библиотекой и падение тестов с некорректной реализацией.

---

## 2. Описание задания

### 2.1 Основные требования

1. Скачать дистрибутив OpenBLAS
2. Создать интерфейсные тесты для CBLAS функционала
3. Запустить тесты с OpenBLAS и продемонстрировать успешное прохождение
4. Продемонстрировать полноту покрытия

### 2.2 Дополнительное задание (+20 баллов)

1. Создать библиотеку с неправильным интерфейсом
2. Запустить тесты с созданной библиотекой
3. Продемонстрировать ожидаемые падения тестов

---

## 3. Выбранный функционал для тестирования

Для тестирования был выбран **Level 1 BLAS** - векторные операции с вычислительной сложностью O(n).

### 3.1 Тестируемые функции (Single Precision - float)

| Функция | Описание | Операция |
|---------|----------|----------|
| `cblas_saxpy` | Vector update | y = αx + y |
| `cblas_sdot` | Dot product | result = x·y |
| `cblas_snrm2` | Euclidean norm | result = \\|x\\|₂ |
| `cblas_scopy` | Copy vector | y = x |
| `cblas_sscal` | Scale vector | x = αx |
| `cblas_sasum` | Sum of absolute values | result = Σ\\|xᵢ\\| |
| `cblas_isamax` | Index of max absolute value | result = argmax\\|xᵢ\\| |
| `cblas_sswap` | Swap vectors | x ↔ y |

### 3.2 Тестируемые функции (Double Precision - double)

| Функция | Описание | Операция |
|---------|----------|----------|
| `cblas_daxpy` | Vector update | y = αx + y |
| `cblas_ddot` | Dot product | result = x·y |
| `cblas_dnrm2` | Euclidean norm | result = \\|x\\|₂ |
| `cblas_dcopy` | Copy vector | y = x |
| `cblas_dscal` | Scale vector | x = αx |
| `cblas_dasum` | Sum of absolute values | result = Σ\\|xᵢ\\| |
| `cblas_idamax` | Index of max absolute value | result = argmax\\|xᵢ\\| |
| `cblas_dswap` | Swap vectors | x ↔ y |
| `cblas_drotg` | Generate Givens rotation | Генерация вращения |
| `cblas_drot` | Apply Givens rotation | Применение вращения |

---

## 4. Классификация тестов

Согласно диаграмме классификации тестирования, созданные тесты относятся к:

### По запуску кода на исполнение
- ✅ **Динамическое тестирование** - код выполняется

### По доступу к коду и архитектуре приложения
- ✅ **Метод черного ящика** - тестируется только внешний интерфейс

### По степени автоматизации
- ✅ **Автоматизированное** - тесты выполняются автоматически через Google Test

### По моменту выполнения
- ✅ **На основе тест-кейсов** - используются заранее подготовленные сценарии

### По целям и задачам
- ✅ **Функциональное тестирование** - проверка корректности вычислений
- ✅ **Позитивное** - проверка корректной работы с валидными данными
- ✅ **Негативное** - проверка граничных случаев (нули, отрицательные значения)

---

## 5. Структура проекта

```
openblas-interface-tests/
├── CMakeLists.txt              # Конфигурация сборки
├── README.md                   # Документация проекта
├── include/
│   └── test_utils.h           # Утилиты для сравнения чисел с плавающей точкой
├── tests/
│   ├── test_level1_float.cpp  # 20 тестов для float (single precision)
│   ├── test_level1_double.cpp # 23 теста для double (double precision)
│   └── test_main.cpp          # Главная функция для запуска тестов
└── build/                      # Директория сборки

fake-blas-lib/
├── CMakeLists.txt              # Конфигурация для "поломанной" библиотеки
├── README.md                   # Документация поломанной библиотеки
├── fake_blas.c                 # Намеренно неправильные реализации
└── build/                      # Директория сборки
```

---

## 6. Покрытие тестами

### 6.1 Типы тестовых сценариев

Для каждой функции реализованы следующие типы тестов:

1. **Базовая функциональность** - проверка основной работы функции
2. **Граничные случаи**:
   - Нулевые векторы
   - Единичные векторы
   - Нулевые коэффициенты (α = 0)
3. **Специальные значения**:
   - Отрицательные значения
   - Дробные коэффициенты
   - Ортогональные векторы (для dot product)
4. **Параметры stride** (incX, incY):
   - Базовые случаи с stride = 1
   - Случаи с stride > 1 (проверка корректной работы с подвекторами)

### 6.2 Статистика покрытия

| Тип данных | Функций | Тестов | Тестовых сценариев на функцию |
|------------|---------|--------|-------------------------------|
| float      | 8       | 20     | 2-3                           |
| double     | 10      | 23     | 2-3                           |
| **Всего**  | **18**  | **43** | **~2.4 в среднем**            |

---

## 7. Результаты тестирования

### 7.1 Тестирование с OpenBLAS (корректная библиотека)

**Команда запуска:**
```bash
cd /home/claude/openblas-interface-tests/build
./cblas_interface_tests
```

**Результат:**
```
[==========] Running 43 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 20 tests from CBlasLevel1FloatTest
...все тесты прошли успешно...
[----------] 20 tests from CBlasLevel1FloatTest (0 ms total)

[----------] 23 tests from CBlasLevel1DoubleTest
...все тесты прошли успешно...
[----------] 23 tests from CBlasLevel1DoubleTest (0 ms total)

[----------] Global test environment tear-down
[==========] 43 tests from 2 test suites ran. (1 ms total)
[  PASSED  ] 43 tests.
```

✅ **Все 43 теста прошли успешно** - OpenBLAS корректно реализует интерфейс CBLAS.

### 7.2 Тестирование с Fake BLAS (некорректная библиотека)

**Команда запуска:**
```bash
cd /home/claude/openblas-interface-tests/build-fake
./cblas_interface_tests
```

**Результат:**
```
[==========] Running 43 tests from 2 test suites.
...
[  FAILED  ] 36 tests из 43
[  PASSED  ] 7 tests
```

❌ **36 тестов упали** - некорректная реализация была успешно обнаружена тестами.

### 7.3 Примеры обнаруженных ошибок

#### Пример 1: cblas_saxpy
```
[ RUN      ] CBlasLevel1FloatTest.SaxpyBasic
/home/claude/openblas-interface-tests/tests/test_level1_float.cpp:31: Failure
Value of: vectors_almost_equal(y, expected)
  Actual: false
Expected: true
[  FAILED  ] CBlasLevel1FloatTest.SaxpyBasic (0 ms)
```
**Причина:** Функция ничего не делает вместо выполнения y = αx + y

#### Пример 2: cblas_sdot
```
[ RUN      ] CBlasLevel1FloatTest.SdotBasic
/home/claude/openblas-interface-tests/tests/test_level1_float.cpp:72: Failure
Value of: almost_equal(result, 35.0f)
  Actual: false
Expected: true
[  FAILED  ] CBlasLevel1FloatTest.SdotBasic (0 ms)
```
**Причина:** Функция возвращает 0 вместо корректного скалярного произведения (35.0)

#### Пример 3: cblas_snrm2
```
[ RUN      ] CBlasLevel1FloatTest.Snrm2Basic
/home/claude/openblas-interface-tests/tests/test_level1_float.cpp:101: Failure
Value of: almost_equal(result, expected)
  Actual: false
Expected: true
[  FAILED  ] CBlasLevel1FloatTest.Snrm2Basic (0 ms)
```
**Причина:** Функция возвращает 999.0 вместо корректной нормы

---

## 8. Технические детали реализации

### 8.1 Используемые технологии

- **Язык:** C++ (стандарт C++17)
- **Фреймворк тестирования:** Google Test 1.12.1
- **Система сборки:** CMake 3.28.3
- **Библиотека BLAS:** OpenBLAS 0.3.26
- **Компилятор:** GCC 13.3.0
- **ОС:** Ubuntu 24.04

### 8.2 Работа с числами с плавающей точкой

Для корректного сравнения float/double значений используется функция с учетом погрешности:

```cpp
template<typename T>
bool almost_equal(T a, T b, T tolerance = get_tolerance<T>()) {
    return std::abs(a - b) <= tolerance * std::max(T(1.0), 
                                                    std::max(std::abs(a), 
                                                             std::abs(b)));
}
```

Где `tolerance = std::numeric_limits<T>::epsilon() * 100`

### 8.3 Организация тестов

Используется подход **Test Fixture** для группировки связанных тестов:

```cpp
class CBlasLevel1FloatTest : public ::testing::Test {
protected:
    void SetUp() override {
        x = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
        y = {5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
        n = static_cast<int>(x.size());
    }
    
    std::vector<float> x, y;
    int n;
};
```

---

## 9. Типы обнаруженных дефектов в Fake BLAS

### 9.1 Классификация дефектов

| Тип дефекта | Количество | Примеры функций |
|-------------|------------|-----------------|
| Не выполняет операцию | 4 | saxpy, daxpy, sswap, dswap, drot |
| Возвращает константу вместо вычисления | 6 | sdot, ddot, snrm2, dnrm2, sasum, dasum |
| Неправильный алгоритм | 4 | sscal, dscal, scopy, dcopy |
| Неправильный индекс | 2 | isamax, idamax |
| Неправильные параметры | 1 | drotg |

### 9.2 Прошедшие тесты (ложные срабатывания)

Некоторые тесты прошли случайно из-за специфики ошибочной реализации:
- `SaxpyZeroAlpha` - прошел, т.к. при α=0 ничего не должно происходить
- `SdotZeroVector` - прошел, т.к. результат должен быть 0
- `DaxpyZeroAlpha` - прошел по той же причине
- `DdotZeroVector` - прошел по той же причине
- И еще 3 теста

Это показывает важность **разнообразия тестовых сценариев**.

---

## 10. Сборка и запуск проекта

### 10.1 Установка зависимостей

```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install -y cmake build-essential libopenblas-dev
```

### 10.2 Сборка и запуск с OpenBLAS

```bash
# Клонирование репозитория
git clone <repository-url>
cd openblas-interface-tests

# Сборка
mkdir build && cd build
cmake ..
cmake --build .

# Запуск тестов
./cblas_interface_tests

# Или через CTest
ctest --output-on-failure
```

### 10.3 Сборка и запуск с Fake BLAS

```bash
# Сборка fake библиотеки
cd fake-blas-lib
mkdir build && cd build
cmake ..
cmake --build .

# Сборка тестов с fake библиотекой
cd ../../openblas-interface-tests
mkdir build-fake && cd build-fake
cmake -DBLAS_LIBRARIES=/home/claude/fake-blas-lib/build/libopenblas.so ..
cmake --build .

# Запуск (ожидаем падения)
./cblas_interface_tests
```

---

## 11. Выводы

### 11.1 Достигнутые результаты

1. ✅ Создано 43 интерфейсных теста для 18 функций CBLAS Level 1
2. ✅ Тесты покрывают базовую функциональность, граничные случаи и различные параметры
3. ✅ Все тесты успешно проходят с библиотекой OpenBLAS
4. ✅ Создана библиотека с намеренно неправильной реализацией
5. ✅ 36 из 43 тестов корректно обнаруживают ошибки в fake библиотеке

### 11.2 Эффективность интерфейсного тестирования

Проект демонстрирует эффективность интерфейсного тестирования:

- **Обнаружение нарушений контракта** - тесты проверяют соответствие спецификации BLAS
- **Независимость от реализации** - тесты работают с любой библиотекой, реализующей интерфейс CBLAS
- **Автоматизация** - все проверки выполняются автоматически
- **Быстрое выполнение** - 43 теста выполняются за 1 мс

### 11.3 Практическая значимость

Интерфейсные тесты критически важны для:
- Проверки совместимости различных реализаций BLAS
- Регрессионного тестирования при обновлении библиотеки
- Валидации оптимизаций (убедиться, что оптимизация не нарушила корректность)
- Портирования на новые платформы

---

## 12. Ссылки на репозитории

- **Тесты:** `/home/claude/openblas-interface-tests`
- **Fake BLAS:** `/home/claude/fake-blas-lib`

---

## 13. Приложения

### Приложение A: Полный список тестов

**Float Tests (20):**
1. SaxpyBasic, SaxpyZeroAlpha, SaxpyNegativeAlpha, SaxpyWithIncrement
2. SdotBasic, SdotZeroVector, SdotWithIncrement
3. Snrm2Basic, Snrm2ZeroVector, Snrm2UnitVector
4. ScopyBasic, ScopyWithIncrement
5. SscalBasic, SscalZeroAlpha, SscalNegativeAlpha
6. SasumBasic, SasumNegativeValues
7. IsamaxBasic, IsamaxNegativeValues
8. SswapBasic

**Double Tests (23):**
1. DaxpyBasic, DaxpyZeroAlpha, DaxpyNegativeAlpha, DaxpyWithIncrement
2. DdotBasic, DdotZeroVector, DdotOrthogonalVectors
3. Dnrm2Basic, Dnrm2ZeroVector, Dnrm2UnitVector
4. DcopyBasic, DcopyWithIncrement
5. DscalBasic, DscalZeroAlpha, DscalFractionalAlpha
6. DasumBasic, DasumMixedValues
7. IdamaxBasic, IdamaxNegativeValues, IdamaxFirstElement
8. DswapBasic
9. DrotgBasic, DrotBasic

---

**Конец отчета**
