//
//  patternScanner.h
//  osxGlow
//
//  Created by TheArmKing on 21/09/21.
//

#ifndef patternScanner_h
#define patternScanner_h

#include <mach-o/dyld.h>
#include <sys/stat.h>

//pattern scanner
uintptr_t scan(const char* module, unsigned char* sig, const char* mask) {
    //thanks https://github.com/scen/libembryo
    unsigned int count = _dyld_image_count();
    for (int i = 0; i < count; i++) {
        const char* image = _dyld_get_image_name(i);
        if (!strstr(image, module))
            continue;
            
        struct stat sb;
        if (stat(image, &sb))
            continue;
            
        mach_header_64* header = (mach_header_64*)_dyld_get_image_header(i);
        uintptr_t address = (uintptr_t)header;
        std::size_t size = sb.st_size;
        
        //thanks https://github.com/AimTuxOfficial/AimTux/
        auto compare = [](const unsigned char* data, const unsigned char* sig, const char* mask) {
            for (; *mask; ++mask, ++data, ++sig) {
                if (*mask == 'x' && *data != *sig)
                    return false;
            }
            
            return (*mask) == 0;
        };
        
        for (uintptr_t i = 0; i < size; i++) {
            if (compare((unsigned char*)(address + i), sig, mask))
                return (uintptr_t)(address + i);
        }
    }
    
    return 0;
}

#endif /* patternScanner_h */
