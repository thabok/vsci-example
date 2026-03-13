// 1) Interface
class IFlashPort {
public:
  virtual ~IFlashPort() = default;
  virtual int Read(uint32_t addr, uint8_t* data, size_t len) = 0;
  virtual int Write(uint32_t addr, const uint8_t* data, size_t len) = 0;
};

// 2) Echte Implementierung der Dependency
extern "C" int flash_read(uint32_t, uint8_t*, size_t);
extern "C" int flash_write(uint32_t, const uint8_t*, size_t);

class FlashPort : public IFlashPort {
public:
  int Read(uint32_t addr, uint8_t* data, size_t len) override {
    return flash_read(addr, data, len);
  }
  int Write(uint32_t addr, const uint8_t* data, size_t len) override {
    return flash_write(addr, data, len);
  }
};

// 3) Mock für Unit Tests
class MockFlashPort : public IFlashPort {
public:
  MOCK_METHOD(int, Read, (uint32_t addr, uint8_t* data, size_t len), (override));
  MOCK_METHOD(int, Write, (uint32_t addr, const uint8_t* data, size_t len), (override));
};

// 4) Zu testendes Modul
class Storage {
public:
  explicit Storage(IFlashPort& flash) : flash_(flash) {}

  bool Save(const uint8_t* buf, size_t len) {
    return flash_.Write(0x1000, buf, len) == 0;
  }

private:
  IFlashPort& flash_;
};

// 5) Unit Test
TEST(StorageTest, Save_WritesToFlash) {
  MockFlashPort flash;
  Storage sut(flash);

  uint8_t data[4] = {1,2,3,4};

  EXPECT_CALL(flash, Write(0x1000, _, 4))
      .WillOnce(Return(0));

  EXPECT_TRUE(sut.Save(data, 4));
}
