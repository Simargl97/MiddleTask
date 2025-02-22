#include <iostream>
#include <memory>
#include <vector>
#include <string>

// Предварительное объявление класса Enemy (используется в Builder)
class Enemy;

/////////////////// ФАБРИКА (Abstract Factory) /////////////////////////////

// Интерфейс для персонажей игры
class Character {
public:
    virtual void info() const = 0; // Вывод информации о персонаже
    virtual ~Character() {}
};

// Интерфейс для оружия
class Weapon {
public:
    virtual void info() const = 0; // Вывод информации об оружии
    virtual ~Weapon() {}
};

// Конкретный класс персонажа: Рыцарь
class Knight : public Character {
public:
    void info() const override {
        std::cout << "Knight" << std::endl;
    }
};

// Конкретный класс оружия: Меч
class Sword : public Weapon {
public:
    void info() const override {
        std::cout << "Sword" << std::endl;
    }
};

// Конкретный класс персонажа: Инопланетянин (для космического мира)
class Alien : public Character {
public:
    void info() const override {
        std::cout << "Инопланетянин" << std::endl;
    }
};

// Конкретный класс оружия: Лазерное оружие (для космического мира)
class LaserGun : public Weapon {
public:
    void info() const override {
        std::cout << "Лазерное оружие" << std::endl;
    }
};

// Абстрактная фабрика для создания персонажей и оружия
class ILevelFactory {
public:
    virtual std::unique_ptr<Character> CreateCharacter() = 0;
    virtual std::unique_ptr<Weapon> CreateWeapon() = 0;
    virtual ~ILevelFactory() {}
};

// Фабрика для Средневековья: создает рыцарей и мечи
class MedievalFactory : public ILevelFactory {
public:
    std::unique_ptr<Character> CreateCharacter() override {
        return std::make_unique<Knight>();
    }
    std::unique_ptr<Weapon> CreateWeapon() override {
        return std::make_unique<Sword>();
    }
};

// Фабрика для Космического мира: создает инопланетян и лазерное оружие
class SciFiFactory : public ILevelFactory {
public:
    std::unique_ptr<Character> CreateCharacter() override {
        return std::make_unique<Alien>();
    }
    std::unique_ptr<Weapon> CreateWeapon() override {
        return std::make_unique<LaserGun>();
    }
};

/////////////////// СТРОИТЕЛЬ (Builder) /////////////////////////////

// Класс, представляющий уровень игры
class Level {
public:
    void SetTerrain(const std::string& terrain) {  
        // Установка типа местности уровня (например, Dungeon)
        terrain_ = terrain;
    }
    void SetEnemies(const std::vector<std::unique_ptr<Enemy>>& enemies) {  
        // Установка врагов на уровне (логика может быть дополнена)
    }
private:
    std::string terrain_;
    // Другие данные уровня
};

// Абстрактный строитель уровня
class LevelBuilder {
public:
    virtual ~LevelBuilder() = default;
    virtual void BuildTerrain() = 0; // Построение местности
    virtual void BuildEnemies() = 0; // Добавление врагов
    virtual void BuildTraps() = 0;   // Добавление ловушек
    std::unique_ptr<Level> GetLevel() { return std::move(level); } // Получение готового уровня
protected:
    std::unique_ptr<Level> level = nullptr;
};

// Конкретный строитель для создания подземелий (Dungeon)
class DungeonBuilder : public LevelBuilder {
public:
    DungeonBuilder() { level = std::make_unique<Level>(); }
    void BuildTerrain() override { 
        level->SetTerrain("Dungeon"); // Установка подземельной местности
    }
    void BuildEnemies() override {  
        // Добавление врагов для подземелья (логика может быть дополнена)
    }
    void BuildTraps() override {  
        // Добавление ловушек в подземелье (логика может быть дополнена)
    }
};

// Директор, управляющий процессом строительства уровня
class LevelDirector {
public:
    void Construct(LevelBuilder* builder) {
        builder->BuildTerrain();
        builder->BuildEnemies();
        builder->BuildTraps();
    }
};

/////////////////// ПРОТОТИП (Prototype) /////////////////////////////

// Абстрактный класс врага с методом клонирования
class Enemy {
public:
    virtual ~Enemy() = default;
    virtual std::unique_ptr<Enemy> Clone() const = 0; // Метод для создания копии врага
    virtual void Attack() { /* Базовая реализация атаки */ }
};

// Конкретный класс врага: Гоблин
class Goblin : public Enemy {
public:
    Goblin() { /* Инициализация параметров гоблина */ }
    std::unique_ptr<Enemy> Clone() const override { 
        return std::make_unique<Goblin>(*this); // Создание копии объекта Гоблин
    }
    void Attack() override { 
        // Реализация атаки гоблина
        std::cout << "Goblin attacks!" << std::endl;
    }
};

/////////////////// ОДИНОЧКА (Singleton) /////////////////////////////

// Класс-одиночка для управления состоянием игры
class GameManager {
public:
    static GameManager& Instance() {
        static GameManager instance;
        return instance;
    }
    
    void StartGame() { 
        // Запуск игры 
        std::cout << "Game Started" << std::endl;
    }
    void EndGame() { 
        // Завершение игры 
        std::cout << "Game Ended" << std::endl;
    }
    
private:
    GameManager() {}
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;
};

int main()
{
    try {
        //// ФАБРИКА ////
        // Выбор конкретной фабрики (например, для Средневековья)
        std::unique_ptr<ILevelFactory> factory = std::make_unique<MedievalFactory>();
        
        // Создание объектов персонажа и оружия через фабрику
        auto hero = factory->CreateCharacter();
        auto weapon = factory->CreateWeapon();
        
        // Вывод информации о созданных объектах
        hero->info();  
        weapon->info(); 
        
        //// ОДИНОЧКА ////
        // Запуск игры через синглтон GameManager
        GameManager::Instance().StartGame();
    
        //// ПРОТОТИП ////
        // Создание оригинального врага и его клонирование
        std::unique_ptr<Enemy> original = std::make_unique<Goblin>();
        std::unique_ptr<Enemy> clone = original->Clone();
        clone->Attack(); // Выполнение атаки клона
    
        //// СТРОИТЕЛЬ ////
        // Создание строителя для подземелья
        std::unique_ptr<LevelBuilder> builder = std::make_unique<DungeonBuilder>();
        LevelDirector director;
        // Директор управляет процессом создания уровня
        director.Construct(builder.get());
        std::unique_ptr<Level> dungeonLevel = builder->GetLevel(); // Получение готового уровня
    
        // Дальнейшая логика игры...
    
        // Завершение игры
        GameManager::Instance().EndGame();
    }
    catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
    }
    
    return 0;
}



