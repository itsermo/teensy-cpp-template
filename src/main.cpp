// 3rdparty MCU headers
#include <imxrt1062.h>
#include <imxrt1062-memory.h>

// for delay() functions
#include <imxrt1062-chrono.h>

#include <vector>
#include <string>
#include <map>

#include "morse-code.hpp"

int main(void)
{
    // enables the debug register for cycle counting, used in function delay_ms()
    init_demcr();
    
    std::string morse_str{"SO"};
    const auto morse_sequence = morse::convert_string_to_morse_binary_sequence(morse_str);

    // Configure GPIO B0_03 (PIN 13) for output
    IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_03 = 5;
    IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_03 = IOMUXC_PAD_DSE(7);
    IOMUXC_GPR_GPR27 = 0xFFFFFFFF;
    GPIO7_GDIR |= (1 << 3);

    for(;;) {

        for (const auto & s : morse_sequence)
        {
            if(s) {
                GPIO7_DR_SET = (1 << 3);
            }
            else {
                GPIO7_DR_CLEAR = (1 << 3);
            }

            delay_ms(300);
        }
    }

    return 0;
}