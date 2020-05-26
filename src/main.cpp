// 3rdparty MCU headers
#include <imxrt1062.h>
#include <imxrt1062-memory.h>

// for delay() functions
#include "../include/chrono.h"

#include <vector>
#include <string>
#include <map>

int main(void)
{
    // enables the debug register for cycle counting (used in delay_ms())
    init_demcr();

    // Create a vector of 256 bytes -- proof we can use STL!
    std::vector<uint8_t> test_vector(256);

    // Create a map for the hell of it
    std::map<std::string, int> test_map;
    test_map["zero"] = 0;
    test_map["one"] = 1;

    std::vector<std::string> string_vec;
    string_vec.push_back("how many character is this, i don't know?");

    // Test our fast memset assembly function
    // by setting all the values in the vector to size of vector
    for (size_t i = 0; i < test_vector.size()/8; i++)
    {
        memset(test_vector.data() + i * 8, string_vec.size() * test_map["one"], test_vector.size()/8);
    }
    
    // Configure GPIO B0_03 (PIN 13) for output
    IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_03 = 5;
    IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_03 = IOMUXC_PAD_DSE(7);
    IOMUXC_GPR_GPR27 = 0xFFFFFFFF;
    GPIO7_GDIR |= (1 << 3);

    for(;;) {
        // Set PIN 13 HIGH
        GPIO7_DR_SET = (1 << 3);

        delay_ms(100);

        // Set PIN 13 LOW
        GPIO7_DR_CLEAR = (1 << 3);

        delay_ms(100);
    }

    return 0;
}