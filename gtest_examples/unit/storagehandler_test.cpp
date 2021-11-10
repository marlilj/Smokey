////////////////////////////////////////////////
// NOLINTs allowed:
// protected class member unit_test since gtest standard is non private class members
// every TEST_F since they throw warning regarding 'testing::internal::TestFactoryBase *' with a newly created
// 'gsl::owner<>' [cppcoreguidelines-owning-memory]
////////////////////////////////////////////////

#include <gtest/gtest.h>

#include "mock_ps_posix.hpp"
#include "ps_posix.h"
#include "ps_types.h"
#include "storage_handler.hpp"

constexpr int EXIT_TRANSLATION_FAILURE = 2;
using namespace ::testing;

class StorageHandlerTest : public Test {
protected:
  const std::string mode_storage_ = "carmodeps.storage";
  const std::string crash_storage_ = "crashmodeps.storage";
  const std::string service_storage_ = "servicemodeps.storage";
  const std::string cm_normal_ = "kNormal";
  const std::string cm_transport_ = "kTransport";
  const std::string cm_factory_ = "kFactory";
  const std::string cm_dyno_ = "kDyno";
  const std::string cm_show_ = "kShow";
  static constexpr int storage_size_ = 32;
  vehiclemodesprovider::StorageHandler unit_test;  // NOLINT
  void SetUp() override {
    EXPECT_CALL(MockPsPosix::Get(), PS_Resize(_, _)).WillRepeatedly(Return(Ps_ReturnCode_t::PS_SUCCESS));
    EXPECT_CALL(MockPsPosix::Get(), PS_Seek(_, 0, PsSeekDirection::kBegin, _))
        .WillRepeatedly(Return(Ps_ReturnCode_t::PS_SUCCESS));
    EXPECT_CALL(MockPsPosix::Get(), PS_Read(_, _, storage_size_, _))
        .WillRepeatedly(Return(Ps_ReturnCode_t::PS_SUCCESS));
    EXPECT_CALL(MockPsPosix::Get(), PS_Close(_)).WillRepeatedly(Return(Ps_ReturnCode_t::PS_SUCCESS));
  }
  void TearDown() override {}
};

// NOLINTNEXTLINE
TEST_F(StorageHandlerTest, WriteReadCarModeNormal) {
  // initialize variable to send to function
  vehiclemodesprovider::types::CarModes car_mode{vehiclemodesprovider::types::CarModes::kNormal};
  // write kNormal to persistant storage
  EXPECT_CALL(MockPsPosix::Get(), PS_Open(StrEq(mode_storage_), PsOpenMode::kWrite, _))
      .WillOnce(Return(Ps_ReturnCode_t::PS_SUCCESS));
  EXPECT_CALL(MockPsPosix::Get(), PS_Write(_, StrEq(cm_normal_), cm_normal_.size(), _))
      .WillOnce(Return(Ps_ReturnCode_t::PS_SUCCESS));
  auto result = unit_test.WritePersistentStorageCarmode(car_mode);
  EXPECT_EQ(EXIT_SUCCESS, result);
  // set car mode to something else
  // to make sure result is set from read function
  car_mode = vehiclemodesprovider::types::CarModes::kTransport;
  EXPECT_CALL(MockPsPosix::Get(), PS_Open(StrEq(mode_storage_), PsOpenMode::kRead, _))
      .WillOnce(Return(Ps_ReturnCode_t::PS_SUCCESS));
  result = unit_test.ReadPersistentStorageCarmode(&car_mode);
  EXPECT_EQ(EXIT_TRANSLATION_FAILURE, result);  // Reason: Due to mocking we only test persistent storage as expected
}
// NOLINTNEXTLINE
TEST_F(StorageHandlerTest, WriteReadCarModeTransport) {
  // initialize variable to send to function
  vehiclemodesprovider::types::CarModes car_mode{vehiclemodesprovider::types::CarModes::kTransport};
  // write kNormal to persistant storage
  EXPECT_CALL(MockPsPosix::Get(), PS_Open(StrEq(mode_storage_), PsOpenMode::kWrite, _))
      .WillOnce(Return(Ps_ReturnCode_t::PS_SUCCESS));
  EXPECT_CALL(MockPsPosix::Get(), PS_Write(_, StrEq(cm_transport_), cm_transport_.size(), _))
      .WillOnce(Return(Ps_ReturnCode_t::PS_SUCCESS));
  auto result = unit_test.WritePersistentStorageCarmode(car_mode);
  EXPECT_EQ(EXIT_SUCCESS, result);
  // set car mode to something else
  // to make sure result is set from read function
  car_mode = vehiclemodesprovider::types::CarModes::kNormal;
  EXPECT_CALL(MockPsPosix::Get(), PS_Open(StrEq(mode_storage_), PsOpenMode::kRead, _))
      .WillOnce(Return(Ps_ReturnCode_t::PS_SUCCESS));
  result = unit_test.ReadPersistentStorageCarmode(&car_mode);
  EXPECT_EQ(EXIT_TRANSLATION_FAILURE, result);
}
// NOLINTNEXTLINE
TEST_F(StorageHandlerTest, WriteReadCarModeDyno) {
  // initialize variable to send to function
  vehiclemodesprovider::types::CarModes car_mode{vehiclemodesprovider::types::CarModes::kDyno};
  // write kNormal to persistant storage
  EXPECT_CALL(MockPsPosix::Get(), PS_Open(StrEq(mode_storage_), PsOpenMode::kWrite, _))
      .WillOnce(Return(Ps_ReturnCode_t::PS_SUCCESS));
  EXPECT_CALL(MockPsPosix::Get(), PS_Write(_, StrEq(cm_dyno_), cm_dyno_.size(), _))
      .WillOnce(Return(Ps_ReturnCode_t::PS_SUCCESS));
  auto result = unit_test.WritePersistentStorageCarmode(car_mode);
  EXPECT_EQ(EXIT_SUCCESS, result);
  // set car mode to something else
  // to make sure result is set from read function
  car_mode = vehiclemodesprovider::types::CarModes::kShow;
  EXPECT_CALL(MockPsPosix::Get(), PS_Open(StrEq(mode_storage_), PsOpenMode::kRead, _))
      .WillOnce(Return(Ps_ReturnCode_t::PS_SUCCESS));
  result = unit_test.ReadPersistentStorageCarmode(&car_mode);
  EXPECT_EQ(EXIT_TRANSLATION_FAILURE, result);
}
// NOLINTNEXTLINE
TEST_F(StorageHandlerTest, WriteReadCarModeShow) {
  // initialize variable to send to function
  vehiclemodesprovider::types::CarModes car_mode{vehiclemodesprovider::types::CarModes::kShow};
  // write kNormal to persistant storage
  EXPECT_CALL(MockPsPosix::Get(), PS_Open(StrEq(mode_storage_), PsOpenMode::kWrite, _))
      .WillOnce(Return(Ps_ReturnCode_t::PS_SUCCESS));
  EXPECT_CALL(MockPsPosix::Get(), PS_Write(_, StrEq(cm_show_), cm_show_.size(), _))
      .WillOnce(Return(Ps_ReturnCode_t::PS_SUCCESS));
  auto result = unit_test.WritePersistentStorageCarmode(car_mode);
  EXPECT_EQ(EXIT_SUCCESS, result);
  // set car mode to something else
  // to make sure result is set from read function
  car_mode = vehiclemodesprovider::types::CarModes::kDyno;
  EXPECT_CALL(MockPsPosix::Get(), PS_Open(StrEq(mode_storage_), PsOpenMode::kRead, _))
      .WillOnce(Return(Ps_ReturnCode_t::PS_SUCCESS));
  result = unit_test.ReadPersistentStorageCarmode(&car_mode);
  EXPECT_EQ(EXIT_TRANSLATION_FAILURE, result);
}
// NOLINTNEXTLINE
TEST_F(StorageHandlerTest, WriteReadCarModeFactory) {
  // initialize variable to send to function
  vehiclemodesprovider::types::CarModes car_mode{vehiclemodesprovider::types::CarModes::kFactory};
  // write kNormal to persistant storage
  EXPECT_CALL(MockPsPosix::Get(), PS_Open(StrEq(mode_storage_), PsOpenMode::kWrite, _))
      .WillOnce(Return(Ps_ReturnCode_t::PS_SUCCESS));
  EXPECT_CALL(MockPsPosix::Get(), PS_Write(_, StrEq(cm_factory_), cm_factory_.size(), _))
      .WillOnce(Return(Ps_ReturnCode_t::PS_SUCCESS));
  auto result = unit_test.WritePersistentStorageCarmode(car_mode);
  EXPECT_EQ(EXIT_SUCCESS, result);
  // set car mode to something else
  // to make sure result is set from read function
  car_mode = vehiclemodesprovider::types::CarModes::kTransport;
  EXPECT_CALL(MockPsPosix::Get(), PS_Open(StrEq(mode_storage_), PsOpenMode::kRead, _))
      .WillOnce(Return(Ps_ReturnCode_t::PS_SUCCESS));
  result = unit_test.ReadPersistentStorageCarmode(&car_mode);
  EXPECT_EQ(EXIT_TRANSLATION_FAILURE, result);
}
// NOLINTNEXTLINE
TEST_F(StorageHandlerTest, WriteReadServicemode) {
  // initialize variable to send to function
  bool service_mode = true;
  // write service mode activated to persistant storage
  EXPECT_CALL(MockPsPosix::Get(), PS_Open(StrEq(service_storage_), PsOpenMode::kWrite, _))
      .WillOnce(Return(Ps_ReturnCode_t::PS_SUCCESS));
  EXPECT_CALL(MockPsPosix::Get(), PS_Write(_, StrEq("true"), 4, _)).WillOnce(Return(Ps_ReturnCode_t::PS_SUCCESS));
  auto result = unit_test.WritePersistentStorageServicemode(service_mode);
  EXPECT_EQ(EXIT_SUCCESS, result);
  // set service mode to something else
  // to make sure result is set from read function
  service_mode = false;
  EXPECT_CALL(MockPsPosix::Get(), PS_Open(StrEq(service_storage_), PsOpenMode::kRead, _))
      .WillOnce(Return(Ps_ReturnCode_t::PS_SUCCESS));
  result = unit_test.ReadPersistentStorageServicemode(&service_mode);
  EXPECT_EQ(EXIT_TRANSLATION_FAILURE, result);

  // Test scenario when service mode is "unset"
  service_mode = false;
  // write service mode activated to persistant storage
  EXPECT_CALL(MockPsPosix::Get(), PS_Open(StrEq(service_storage_), PsOpenMode::kWrite, _))
      .WillOnce(Return(Ps_ReturnCode_t::PS_SUCCESS));
  EXPECT_CALL(MockPsPosix::Get(), PS_Write(_, StrEq("false"), 5, _)).WillOnce(Return(Ps_ReturnCode_t::PS_SUCCESS));
  result = unit_test.WritePersistentStorageServicemode(service_mode);
  EXPECT_EQ(EXIT_SUCCESS, result);
  // set service mode to something else
  // to make sure result is set from read function
  service_mode = true;
  EXPECT_CALL(MockPsPosix::Get(), PS_Open(StrEq(service_storage_), PsOpenMode::kRead, _))
      .WillOnce(Return(Ps_ReturnCode_t::PS_SUCCESS));
  result = unit_test.ReadPersistentStorageServicemode(&service_mode);
  EXPECT_EQ(EXIT_TRANSLATION_FAILURE, result);
}
// NOLINTNEXTLINE
TEST_F(StorageHandlerTest, WriteReadCrashmode) {
  // initialize variable to send to function
  bool crash_mode = true;
  // write service mode activated to persistant storage
  EXPECT_CALL(MockPsPosix::Get(), PS_Open(StrEq(crash_storage_), PsOpenMode::kWrite, _))
      .WillOnce(Return(Ps_ReturnCode_t::PS_SUCCESS));
  EXPECT_CALL(MockPsPosix::Get(), PS_Write(_, StrEq("true"), 4, _)).WillOnce(Return(Ps_ReturnCode_t::PS_SUCCESS));
  auto result = unit_test.WritePersistentStorageCrashmode(crash_mode);
  EXPECT_EQ(EXIT_SUCCESS, result);
  // set service mode to something else
  // to make sure result is set from read function
  crash_mode = false;
  EXPECT_CALL(MockPsPosix::Get(), PS_Open(StrEq(crash_storage_), PsOpenMode::kRead, _))
      .WillOnce(Return(Ps_ReturnCode_t::PS_SUCCESS));
  result = unit_test.ReadPersistentStorageCrashmode(&crash_mode);
  EXPECT_EQ(EXIT_TRANSLATION_FAILURE, result);

  // Test scenario when crash mode is "unset"
  crash_mode = false;
  // write service mode activated to persistant storage
  EXPECT_CALL(MockPsPosix::Get(), PS_Open(StrEq(crash_storage_), PsOpenMode::kWrite, _))
      .WillOnce(Return(Ps_ReturnCode_t::PS_SUCCESS));
  EXPECT_CALL(MockPsPosix::Get(), PS_Write(_, StrEq("false"), 5, _)).WillOnce(Return(Ps_ReturnCode_t::PS_SUCCESS));
  result = unit_test.WritePersistentStorageCrashmode(crash_mode);
  EXPECT_EQ(EXIT_SUCCESS, result);
  // set service mode to something else
  // to make sure result is set from read function
  crash_mode = true;
  EXPECT_CALL(MockPsPosix::Get(), PS_Open(StrEq(crash_storage_), PsOpenMode::kRead, _))
      .WillOnce(Return(Ps_ReturnCode_t::PS_SUCCESS));
  result = unit_test.ReadPersistentStorageCrashmode(&crash_mode);
  EXPECT_EQ(EXIT_TRANSLATION_FAILURE, result);
}