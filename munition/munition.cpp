#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Weapon
{
public:
    virtual ~Weapon() = default;
    virtual std::string Name() const = 0; 
    virtual std::unique_ptr<Weapon> Clone() const = 0;
};

class Knife : public Weapon
{
public:
    std::string Name() const override { return "Knife"; }
    std::unique_ptr<Weapon> Clone() const override { return std::make_unique<Knife>(*this); }
};
class Gun : public Weapon
{
public:
    std::string Name() const override { return "Gun"; }
    std::unique_ptr<Weapon> Clone() const override { return std::make_unique<Gun>(*this); }
};
class Missile : public Weapon
{
public:
    std::string Name() const override { return "Missile"; }
    std::unique_ptr<Weapon> Clone() const override { return std::make_unique<Missile>(*this); }
};

class Vehicle
{
public:
    virtual ~Vehicle() = default;
    virtual std::string Name() const = 0;
    virtual std::unique_ptr<Vehicle> Clone() const = 0;
};

class Horse : public Vehicle
{
public:
    std::string Name() const override { return "Horse"; }
    std::unique_ptr<Vehicle> Clone() const override { return std::make_unique<Horse>(*this); }
};
class Tank : public Vehicle
{
public:
    std::string Name() const override { return "Tank"; }
    std::unique_ptr<Vehicle> Clone() const override { return std::make_unique<Tank>(*this); }
};
class Spaceship : public Vehicle
{
public:
    std::string Name() const override { return "Spaceship"; }
    std::unique_ptr<Vehicle> Clone() const override { return std::make_unique<Spaceship>(*this); }
};

class MunitionStore
{
public:
    MunitionStore(std::unique_ptr<Weapon>&& weapon, std::unique_ptr<Vehicle>&& vehicle)
        : weapon_(std::move(weapon)), vehicle_(std::move(vehicle))
    {}

    void RegisterWeapon(std::unique_ptr<Weapon>&& weapon) { weapon_ = std::move(weapon); }
    void RegisterVehicle(std::unique_ptr<Vehicle>&& vehicle) { vehicle_ = std::move(vehicle); }

    std::unique_ptr<Weapon> MakeWeapon() const { return weapon_->Clone(); }
    std::unique_ptr<Vehicle> MakeVehicle() const { return vehicle_->Clone(); }

private:
    std::unique_ptr<Weapon> weapon_;
    std::unique_ptr<Vehicle> vehicle_;
};

void PrintStore(MunitionStore const& store)
{
    std::cout << "---- Infomation ----" << std::endl;
    std::cout << "Weapon  : " << store.MakeWeapon()->Name() << std::endl;
    std::cout << "Vehicle : " << store.MakeVehicle()->Name() << std::endl;
    std::cout << "--------------------" << std::endl;
}

void ChangeWeapon(MunitionStore& store, std::unique_ptr<Weapon>&& weapon)
{
    std::cout << "Change Weapon to " << weapon->Name() << std::endl;
    store.RegisterWeapon(std::move(weapon));
}

void ChangeVehicle(MunitionStore& store, std::unique_ptr<Vehicle>&& vehicle)
{
    std::cout << "Change Vehicle to " << vehicle->Name() << std::endl;
    store.RegisterVehicle(std::move(vehicle));
}

int main()
{
    MunitionStore store(std::make_unique<Knife>(), std::make_unique<Horse>());

    std::cout << "==== Munition Store ====" << std::endl;
    PrintStore(store);

    ChangeWeapon(store, std::make_unique<Gun>());
    PrintStore(store);

    ChangeVehicle(store, std::make_unique<Tank>());
    PrintStore(store);

    ChangeWeapon(store, std::make_unique<Missile>());
    ChangeVehicle(store, std::make_unique<Spaceship>());
    PrintStore(store);
}
