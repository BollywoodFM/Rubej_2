#include <gtest/gtest.h>
#include "munition_h.cpp"
//std::unique_ptr<Weapon>&& weapon, std::unique_ptr<Vehicle>&& vehicle
#include <stdexcept>
TEST (Mu, change_weapon) {
  testing::internal::CaptureStdout();
  MunitionStore store2(std::make_unique<Knife>(), std::make_unique<Horse>());
  ChangeWeapon(store2, std::make_unique<Knife>());
  ChangeWeapon(store2, std::make_unique<Gun>());
  ChangeWeapon(store2, std::make_unique<Missile>());
  PrintStore(store2);
  const std::string o1 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(o1, "Change Weapon to Knife\nChange Weapon to Gun\nChange Weapon to Missile\n---- Infomation ----\nWeapon  : Missile\nVehicle : Horse\n--------------------\n");

}

TEST (Mu2, change_cahnge) {
  testing::internal::CaptureStdout();
  MunitionStore store3(std::make_unique<Knife>(), std::make_unique<Horse>());
  ChangeVehicle(store3, std::make_unique<Horse>());
  ChangeVehicle(store3, std::make_unique<Tank>());
  ChangeVehicle(store3, std::make_unique<Spaceship>());
  PrintStore(store3);
  const std::string o2 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(o2, "Change Vehicle to Horse\nChange Vehicle to Tank\nChange Vehicle to Spaceship\n---- Infomation ----\nWeapon  : Knife\nVehicle : Spaceship\n--------------------\n");
}

TEST (Mu3, print) {
  testing::internal::CaptureStdout();
  MunitionStore store4(std::make_unique<Knife>(), std::make_unique<Horse>());
  PrintStore(store4);
  const std::string o3 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(o3, "---- Infomation ----\nWeapon  : Knife\nVehicle : Horse\n--------------------\n");
}
