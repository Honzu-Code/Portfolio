#include <chrono>
#include <thread>
#include "Server.h"

using std::cout;

int main() {

    if(!std::numeric_limits<float>::is_iec559){
        std::cout << "System Float encoding is not fine.";
        return 1;
    }
    Server server(9000);
    while(true){
        auto sleepFor = std::chrono::milliseconds(40);

        auto start = std::chrono::high_resolution_clock::now();
        server.loop();
        auto finish = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> elapsed = finish - start;
       // std::cout << "loop => " << elapsed.count() << "\n";

        std::this_thread::sleep_for (sleepFor - elapsed);
    }


}
