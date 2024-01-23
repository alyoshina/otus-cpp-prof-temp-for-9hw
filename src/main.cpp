#include <iostream>

#include "async.h"

#include <chrono>

int main(int, char *[]) {
    std::size_t bulk = 5;
    auto h = async::connect(bulk);
    auto h2 = async::connect(bulk);
    
    async::receive(h, "9", 1);

    async::receive(h, "9", 1);
    async::receive(h, "9", 1);
    async::receive(h, "1111", 4);

    async::receive(h2, "1\n", 2);

    async::receive(h2, "8", 1);
    async::receive(h2, "8", 1);
    async::receive(h2, "777\n", 4);

    async::receive(h, "\n2\n3\n4\n5\n6\n{\na\n", 15);
    async::receive(h, "b\nc\nd\n}\n89\n", 11);

    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "+++++++++sleep+++++++++++++" << std::endl;
        async::receive(h, "9", 1);

    async::receive(h, "9", 1);
    async::receive(h, "9", 1);
    async::receive(h, "1111", 4);

    async::receive(h2, "1\n", 2);

    async::receive(h2, "8", 1);
    async::receive(h2, "8", 1);
    async::receive(h2, "777\n", 4);

    async::receive(h, "\n2\n3\n4\n5\n6\n{\na\n", 15);
    async::receive(h, "b\nc\nd\n}\n89\n", 11);

    async::disconnect(h);
    async::disconnect(h2);

    return 0;
}