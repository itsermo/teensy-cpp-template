#pragma once
#ifndef MORSE_CODE_HPP

#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <algorithm>
#include <cctype>

namespace morse {
    enum symbol {
        dot = 0,
        dash = 1
    };

    using morse_map = std::map<char, std::vector<symbol>>;

    inline std::vector<bool> convert_string_to_morse_binary_sequence(std::string & str){
            const morse_map MORSE_ALPHABET_MAP {
            // A-Z Alphabet
            { 'A', { dot , dash             } }, // A .-
            { 'B', { dash, dot , dot , dot  } }, // B -...
            { 'C', { dash, dot , dash, dot  } }, // C -.-.
            { 'D', { dash, dot , dot        } }, // D -..
            { 'E', { dot                    } }, // E .
            { 'F', { dot , dot , dash, dot  } }, // F ..-.
            { 'G', { dash, dash, dot        } }, // G --.
            { 'H', { dot , dot , dot , dot  } }, // H ....
            { 'I', { dot , dot              } }, // I ..
            { 'J', { dot , dash, dash, dash } }, // J .---
            { 'K', { dash, dot , dash       } }, // K -.-
            { 'L', { dot , dash, dot , dot  } }, // L .-..
            { 'M', { dash, dash             } }, // M --
            { 'N', { dash, dot              } }, // N -.
            { 'O', { dash, dash, dash       } }, // O ---
            { 'P', { dot , dash, dash, dot  } }, // P .--.
            { 'Q', { dash, dash, dot , dash } }, // Q --.-
            { 'R', { dot , dash, dot        } }, // R .-.
            { 'S', { dot , dot , dot        } }, // S ...
            { 'T', { dash                   } }, // T -
            { 'U', { dot , dot , dash       } }, // U ..-
            { 'V', { dot , dot , dot , dash } }, // V ...-
            { 'W', { dot , dash, dash       } }, // W .--
            { 'X', { dash, dot , dot , dash } }, // X -..-
            { 'Y', { dash, dot , dash, dash } }, // Y -.--
            { 'Z', { dash, dash, dot , dot  } }, // Z --..

            // 0-9 Numerics
            { '0', { dash, dash, dash, dash, dash } }, // 0 -----
            { '1', { dot , dash, dash, dash, dash } }, // 1 .----
            { '2', { dot , dot , dash, dash, dash } }, // 2 ..---
            { '3', { dot , dot , dot , dash, dash } }, // 3 ...--
            { '4', { dot , dot , dot , dot , dash } }, // 4 ....-
            { '5', { dot , dot , dot , dot , dot  } }, // 5 .....
            { '6', { dash, dot , dot , dot , dot  } }, // 6 -....
            { '7', { dash, dash, dot , dot , dot  } }, // 7 --...
            { '8', { dash, dash, dash, dot , dot  } }, // 8 ---..
            { '9', { dash, dash, dash, dash, dot  } }, // 9 ----.
        };

        // reserve 2 bits for each unit
        // up to 5 symbols (dot or dash) per letter
        // worst case is 5 dashes
        // 5 dashes is 4 * (3 + 1)
        // and 3 units of blank space between letters
        // therefore max sequence can be num_letters * (4 * 3 * 2 + 1 + 3)
        std::vector<bool> sequence;
        sequence.reserve(str.size() * (4 * 3 * 2 + 1 + 3));
        
        for(size_t i = 0; i < str.size(); i++){
            auto & c = str[i];
            const bool is_alpha = std::isalpha(c);
            const bool is_digit = is_alpha ? false : std::isdigit(c) ? true : false;
            char cc = is_alpha ? std::toupper(c) : is_digit ? c : ' ';

            if(cc == ' ')
            {
                // 7 units between letters, or a "whitespace"
                sequence.push_back(0);
                sequence.push_back(0);
                sequence.push_back(0);
                sequence.push_back(0);
                sequence.push_back(0);
                sequence.push_back(0);
                sequence.push_back(0);
            }
            else
            {
                auto m = MORSE_ALPHABET_MAP.at(cc);
                for(size_t j = 0; j < m.size(); j++){
                    if(m[j] == dot){
                        // Dot is one unit
                        sequence.push_back(1);
                    } else {
                        // Dash is three units
                        sequence.push_back(1);
                        sequence.push_back(1);
                        sequence.push_back(1);
                    }
                    
                    // Space between parts of the letter (one unit)
                    sequence.push_back(0);
                }
                
                // Three units between letters
                if(i < str.size() - 1){
                    sequence.push_back(0);
                    sequence.push_back(0);
                    sequence.push_back(0);
                }
            }

            c = cc;
        }

        return sequence;
    }
}

#endif
