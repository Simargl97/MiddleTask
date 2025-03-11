#include <iostream>
#include <vector>
#include <memory>

using namespace std;

///////////////////////////////////////  КОМАНДА ///////////////////////////////////////

// Базовый интерфейс команды
class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
    virtual void undo() = 0;
};

// Класс игрока (получатель команд)
class Players
{
public:
    void jump() { cout << "Персонаж прыгает!" << endl; }
    void attack() { cout << "Персонаж атакует мечом!" << endl; }
};

// Конкретные команды
class JumpCommand : public Command {
    Players* player;
public:
    JumpCommand(Players* p) : player(p) {}
    void execute() override { player->jump(); }
    void undo() override { cout << "Отмена прыжка - возврат на землю" << endl; }
};

class AttackCommand : public Command {
    Players* player;
public:
    AttackCommand(Players* p) : player(p) {}
    void execute() override { player->attack(); }
    void undo() override { cout << "Отмена атаки - меч возвращен в ножны" << endl; }
};

// Обработчик ввода (инициатор команд)
class InputHandler {
    Command* buttonX;
    Command* buttonY;
    vector<Command*> history;
public:
    InputHandler(Command* x, Command* y) : buttonX(x), buttonY(y) {}

    void pressX() {
        buttonX->execute();
        history.push_back(buttonX);
    }

    void pressY() {
        buttonY->execute();
        history.push_back(buttonY);
    }

    void undoLastCommand() {
        if (!history.empty()) {
            history.back()->undo();
            history.pop_back();
        }
    }
};
/////////////////////////////////////// СОСТОЯНИЕ ///////////////////////////////////////
// Forward declaration
class CharacterState;
class IdleState;
class RunningState;
class JumpingState;

// Контекст (персонаж)
class Character {
private:
    std::unique_ptr<CharacterState> state;
public:
    Character();
    void setState(std::unique_ptr<CharacterState> newState);
    void handleInput(char input);
};

// Абстрактный класс состояния
class CharacterState {
public:
    virtual ~CharacterState() = default;
    virtual void handleInput(Character& character, char input) = 0;
};

// Конкретные состояния
class IdleState : public CharacterState {
public:
    void handleInput(Character& character, char input) override;
};

class RunningState : public CharacterState {
public:
    void handleInput(Character& character, char input) override;
};

class JumpingState : public CharacterState {
public:
    void handleInput(Character& character, char input) override;
};

// Реализация методов состояния
void IdleState::handleInput(Character& character, char input) {
    if (input == 'w') {
        std::cout << "Персонаж прыгает!\n";
        character.setState(std::make_unique<JumpingState>());
    } else if (input == 'd') {
        std::cout << "Персонаж начинает бежать!\n";
        character.setState(std::make_unique<RunningState>());
    }
}

void RunningState::handleInput(Character& character, char input) {
    if (input == 'e') {
        std::cout << "Персонаж останавливается.\n";
        character.setState(std::make_unique<IdleState>());
    } else if (input == 'w') {
        std::cout << "Персонаж прыгает во время бега!\n";
        character.setState(std::make_unique<JumpingState>());
    }
}

void JumpingState::handleInput(Character& character, char input) {
    std::cout << "Персонаж приземлился.\n";
    character.setState(std::make_unique<IdleState>());
}

// Реализация методов персонажа
Character::Character() : state(std::make_unique<IdleState>()) {}

void Character::setState(std::unique_ptr<CharacterState> newState) {
    state = std::move(newState);
}

void Character::handleInput(char input) {
    state->handleInput(*this, input);
}

/////////////////////////////////////// ПОСЕТИТЕЛЬ ///////////////////////////////////////

// Forward declaration
class Gamer;
class Enemy;
class AttackVisitor;

// Базовый класс для всех персонажей
class BaseCharacter {
public:
    virtual ~BaseCharacter() = default;
    virtual void accept(AttackVisitor& visitor) = 0; // Метод для посетителя
};

// Базовый класс "Посетитель"
class AttackVisitor {
public:
    virtual ~AttackVisitor() = default;
    virtual void visit(Gamer& player) = 0;
    virtual void visit(Enemy& enemy) = 0;
};

// Конкретные классы персонажей
class Gamer : public BaseCharacter {
public:
    void accept(AttackVisitor& visitor) override {
        visitor.visit(*this);
    }
};

class Enemy : public BaseCharacter {
public:
    void accept(AttackVisitor& visitor) override {
        visitor.visit(*this);
    }
};

// Конкретные атаки (посетители)
class FireAttack : public AttackVisitor {
public:
    void visit(Gamer& player) override {
        std::cout << "Огонь поджигает игрока! -10 HP\n";
    }
    void visit(Enemy& enemy) override {
        std::cout << "Огонь наносит врагу критический урон! -20 HP\n";
    }
};

class IceAttack : public AttackVisitor {
public:
    void visit(Gamer& player) override {
        std::cout << "Лёд замедляет игрока! -5 HP и -50% скорость\n";
    }
    void visit(Enemy& enemy) override {
        std::cout << "Лёд замораживает врага! -15 HP\n";
    }
};


/////////////////////////////////////// НАБЛЮДАТЕЛЬ ///////////////////////////////////////

// Интерфейс наблюдателя (тот, кто следит за событиями)
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(int health) = 0;
};

// Интерфейс субъекта (тот, за кем следят)
class Subject {
private:
    std::vector<Observer*> observers;
public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }
    
    void removeObserver(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyObservers(int health) {
        for (auto observer : observers) {
            observer->update(health);
        }
    }
};

// Класс игрока (является субъектом)
class PlayerBase : public Subject {
private:
    int health;
public:
    PlayerBase(int hp) : health(hp) {}

    void takeDamage(int damage) {
        health -= damage;
        std::cout << "Игрок получил " << damage << " урона! Текущее здоровье: " << health << "\n";
        notifyObservers(health);
    }
};

// Конкретные наблюдатели
class HealthUI : public Observer {
public:
    void update(int health) override {
        std::cout << "[UI] Обновление интерфейса: здоровье = " << health << "\n";
    }
};

class SoundEffect : public Observer {
public:
    void update(int health) override {
        std::cout << "[Звук] Проигрываем звук получения урона!\n";
    }
};


/////////////////////////////////////// ШАБЛОННЫЙ МЕТОД ///////////////////////////////////////


// Базовый класс врага с шаблонным методом
class EnemyBase {
public:
    void attack() { // Шаблонный метод
        approachTarget();
        performAttack();
        retreat();
    }

protected:
    virtual void approachTarget() {
        std::cout << "Враг приближается к цели...\n";
    }

    virtual void performAttack() = 0; // Чистая виртуальная функция (обязательно переопределять)

    virtual void retreat() {
        std::cout << "Враг отступает после атаки.\n";
    }

    virtual ~EnemyBase() = default;
};

// Орк атакует дубиной
class Orc : public EnemyBase {
protected:
    void performAttack() override {
        std::cout << "Орк размахивает дубиной! -15 HP\n";
    }
};

// Дракон дышит огнем
class Dragon : public EnemyBase {
protected:
    void approachTarget() override {
        std::cout << "Дракон летит к жертве...\n";
    }

    void performAttack() override {
        std::cout << "Дракон извергает огонь! -50 HP\n";
    }

    void retreat() override {
        std::cout << "Дракон взмывает в небо!\n";
    }
};

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    /////////////////////////////////////// КОМАНДА ///////////////////////////////////////
    Players player;
    JumpCommand jumpCmd(&player);
    AttackCommand attackCmd(&player);

    InputHandler input(&jumpCmd, &attackCmd);

    // Игровой ввод
    cout << "Игрок нажимает X:" << endl;
    input.pressX();
    
    cout << "\nИгрок нажимает Y:" << endl;
    input.pressY();
    
    cout << "\nОтмена последних действий:" << endl;
    input.undoLastCommand(); // Отмена атаки
    input.undoLastCommand(); // Отмена прыжка



    
    /////////////////////////////////////// СОСТОЯНИЕ ///////////////////////////////////////
    
    Character character;

    std::cout << "Введите команду (d - бежать, w - прыгнуть, пробел - остановиться):\n";
    char inputs;
    while (std::cin >> inputs) {
        character.handleInput(inputs);
    }


    
    /////////////////////////////////////// ПОСЕТИТЕЛЬ ///////////////////////////////////////
    
    std::vector<std::unique_ptr<BaseCharacter>> characters;
    characters.push_back(std::make_unique<Gamer>());
    characters.push_back(std::make_unique<Enemy>());

    FireAttack fire;
    IceAttack ice;

    std::cout << "Атака огнём:\n";
    for (auto& characterOne : characters) {
        characterOne->accept(fire);
    }

    std::cout << "\nАтака льдом:\n";
    for (auto& characterOne : characters) {
        characterOne->accept(ice);
    }

    /////////////////////////////////////// НАБЛЮДАТЕЛЬ ///////////////////////////////////////

    PlayerBase playerBase(100);
    HealthUI ui;
    SoundEffect sound;

    playerBase.addObserver(&ui);
    playerBase.addObserver(&sound);

    playerBase.takeDamage(20); // Урон - интерфейс и звук обновляются
    playerBase.takeDamage(50);


    /////////////////////////////////////// ШАБЛОННЫЙ МЕТОД ///////////////////////////////////////
    ///
    Orc orc;
    Dragon dragon;

    std::cout << "Орк атакует:\n";
    orc.attack();

    std::cout << "\nДракон атакует:\n";
    dragon.attack();
    
    return 0;
}




