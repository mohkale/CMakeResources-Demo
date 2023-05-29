#include <algorithm>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace testing;

std::optional<std::string> readId(const std::string &resourceGroup) {
    return resourceGroup.substr(3, 1);
}

TEST(foo, bar) {
    EXPECT_THAT(std::getenv("CTEST_RESOURCE_GROUP_COUNT"), StrEq("1"));
    EXPECT_THAT(std::getenv("CTEST_RESOURCE_GROUP_0"), StrEq("portoffset"));
    const char* portOffsetResourceGroup = std::getenv("CTEST_RESOURCE_GROUP_0_PORTOFFSET");
    ASSERT_THAT(portOffsetResourceGroup, Ne(nullptr));
    const auto portOffsetOpt = readId(portOffsetResourceGroup);
    ASSERT_THAT(portOffsetOpt.has_value(), IsTrue());
    const int portOffset = std::stoi(*portOffsetOpt);

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    ASSERT_THAT(fd, Gt(0)) << "Failed to create network socket";

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(portOffset + 10'000);

    std::cout << "Binding to port=" << portOffset + 10'000 << '\n';
    int rc = bind(fd, (struct sockaddr *)&address, sizeof(address));
    ASSERT_THAT(rc, Eq(0));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}
