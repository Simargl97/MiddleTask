#include <iostream>
#include <vector>
#include <memory>
#include <string>

///////////////////////////////////////  ФАСАД ///////////////////////////////////////

// Подсистема 1: Рендеринг
class Renderer {
public:
    void init() { std::cout << "Renderer initialized.\n"; }
    void renderScene() { std::cout << "Rendering scene...\n"; }
};

// Подсистема 2: Звуковая система
class SoundSystem {
public:
    void init() { std::cout << "Sound system initialized.\n"; }
    void playSound() { std::cout << "Playing sound...\n"; }
};

// Подсистема 3: Физический движок
class PhysicsEngine {
public:
    void init() { std::cout << "Physics engine initialized.\n"; }
    void updatePhysics() { std::cout << "Updating physics...\n"; }
};

// Фасад, объединяющий работу всех подсистем
class GameEngineFacade {
private:
    Renderer renderer;
    SoundSystem soundSystem;
    PhysicsEngine physicsEngine;
public:
    // Инициализация всех подсистем
    void initialize() {
        renderer.init();
        soundSystem.init();
        physicsEngine.init();
    }
    
    // Запуск игрового цикла с использованием подсистем
    void startGame() {
        std::cout << "Starting game...\n";
        renderer.renderScene();
        soundSystem.playSound();
        physicsEngine.updatePhysics();
    }
};

/////////////////////////////////////// ЗАМЕСТИТЕЛЬ ///////////////////////////////////////

// Интерфейс текстуры
class ITexture {
public:
    virtual void display() = 0;
    virtual ~ITexture() = default;
};

// Реальная текстура, которая загружается с диска
class RealTexture : public ITexture {
private:
    std::string filename;
public:
    RealTexture(const std::string& file) : filename(file) {
        loadFromDisk();
    }
    void loadFromDisk() {
        std::cout << "Загрузка текстуры с диска: " << filename << std::endl;
    }
    void display() override {
        std::cout << "Отображение текстуры: " << filename << std::endl;
    }
};

// Прокси, контролирующий доступ к реальной текстуре с использованием умного указателя
class TextureProxy : public ITexture {
private:
    std::string filename;
    std::unique_ptr<RealTexture> realTexture;
public:
    TextureProxy(const std::string& file) : filename(file), realTexture(nullptr) {}
    
    void display() override {
        if (!realTexture) {
            // Ленивая инициализация реальной текстуры
            realTexture = std::make_unique<RealTexture>(filename);
        }
        realTexture->display();
    }
};

/////////////////////////////////////// КОМПОНОВЩИК ///////////////////////////////////////

// Абстрактный компонент
class Component {
public:
    virtual void operation() const = 0;
    virtual ~Component() = default;
};

// Листовой элемент (например, простой игровой объект)
class Leaf : public Component {
private:
    std::string name;
public:
    Leaf(const std::string& n) : name(n) {}
    void operation() const override {
        std::cout << "Leaf: " << name << std::endl;
    }
};

// Композит, который может содержать как листья, так и другие композиты
class Composite : public Component {
private:
    std::vector<std::unique_ptr<Component>> children;
    std::string name;
public:
    Composite(const std::string& n) : name(n) {}
    
    // Добавление компонента в составной объект
    void add(std::unique_ptr<Component> component) {
        children.push_back(std::move(component));
    }
    
    void operation() const override {
        std::cout << "Composite: " << name << std::endl;
        for (const auto& child : children) {
            child->operation();
        }
    }
};

/////////////////////////////////////// АДАПТЕР ///////////////////////////////////////

// Новый интерфейс, ожидаемый клиентским кодом
class IGame {
public:
    virtual void play() = 0;
    virtual ~IGame() = default;
};

// Устаревший класс с несовместимым интерфейсом
class OldGame {
public:
    void startGame(const std::string& gameName) {
        std::cout << "Запуск старой игры: " << gameName << std::endl;
    }
};

// Адаптер, который преобразует интерфейс OldGame в IGame с использованием умного указателя
class GameAdapter : public IGame {
private:
    std::unique_ptr<OldGame> oldGame;
    std::string gameName;
public:
    GameAdapter(const std::string& name)
        : gameName(name), oldGame(std::make_unique<OldGame>()) {}

    void play() override {
        // Адаптация вызова метода: вызывается метод старого класса
        oldGame->startGame(gameName);
    }
};


int main()
{
    /////////////////////////////////////// ФАСАД ///////////////////////////////////////
    
    GameEngineFacade game;
    game.initialize(); // Инициализация всех систем
    game.startGame();  // Запуск игры

    /////////////////////////////////////// ЗАМЕСТИТЕЛЬ ///////////////////////////////////////

    auto texture = std::make_unique<TextureProxy>("texture.png");
    std::cout << "Прокси для текстуры создан." << std::endl;
    
    std::cout << "Первый запрос на отображение текстуры:" << std::endl;
    texture->display(); // Создаётся и отображается реальная текстура
    
    std::cout << "Повторный запрос на отображение текстуры:" << std::endl;
    texture->display(); // Повторное использование уже загруженной текстуры

    /////////////////////////////////////// КОМПОНОВЩИК ///////////////////////////////////////
    
    // Создаем корневой композит
    auto root = std::make_unique<Composite>("Root");
    
    // Добавляем листовые элементы
    root->add(std::make_unique<Leaf>("Leaf A"));
    root->add(std::make_unique<Leaf>("Leaf B"));
    
    // Создаем подкомпозит
    auto subComposite = std::make_unique<Composite>("SubComposite");
    subComposite->add(std::make_unique<Leaf>("Leaf C"));
    subComposite->add(std::make_unique<Leaf>("Leaf D"));
    
    // Добавляем подкомпозит в корневой композит
    root->add(std::move(subComposite));
    
    // Выполнение операции для всей структуры
    root->operation();

    /////////////////////////////////////// АДАПТЕР ///////////////////////////////////////
    
    // Клиентский код работает с интерфейсом IGame
    auto tetris = std::make_unique<GameAdapter>("Tetris");
    tetris->play();
    
    return 0;
}




