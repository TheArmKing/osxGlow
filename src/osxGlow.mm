//
//  osxGlow.mm
//  osxGlow
//
//  Created by TheArmKing on 20/09/21.
//
#include <thread> // for std::thread
#import <AppKit/AppKit.h> // for NSEvent
#import "defs.h"

//hook
//https://www.unknowncheats.me/forum/counterstrike-global-offensive/427787-easy-alternative-internal-glow-basically-3-lines.html
bool hooked_GlowEffectSpectator(void* thisPlayer, void* pLocalPlayer, GlowRenderStyle_t& glowStyle, Vector& glowColor, float& alphaStart, float& alpha, float& timeStart, float& timeTarget, bool& animate) {
    
    if (!pLocalPlayer) {
        return false;
    }

    if(shouldGlow && thisPlayer) {
        if(*(int*)((uintptr_t)thisPlayer + m_iTeamNum) != *(int*)((uintptr_t)pLocalPlayer + m_iTeamNum)) {
            glowColor = enemyColor;
            alpha = enemyAlpha;
            glowStyle = enemyStyle;
        } else if(shouldGlowTeam) {
            glowColor = teamColor;
            alpha = teamAlpha;
            glowStyle = teamStyle;
        }
    }
    
    return true;
}

int __attribute__((constructor)) start() {
    std::thread mainThread([](){
        /* Alternative: (in case sig changes)
        search string '%.2f Aborting fadeout' or 'Killer replay stuck waiting for tick message for %.2fs'
        go to pseudocode -> first BL in this function -> pseudocode -> last BL in the function -> the other xref*/
        uintptr_t func_addr = scan("osx64/client.dylib", (unsigned char*)"\x55\x48\x89\xE5\x41\x57\x41\x56\x41\x55\x41\x54\x53\x48\x83\xEC\x38\x4C\x89\xC3\x49\x89\xF4", "xxxxxxxxxxxxxxxxxxxxxxx");
        
        if (func_addr) {
            hooker.hook((void*)func_addr, (void*)hooked_GlowEffectSpectator);
        }
    });
    mainThread.detach();
    
    // monitoring keystrokes
    monitor = [NSEvent addLocalMonitorForEventsMatchingMask:NSEventMaskKeyDown handler:^NSEvent *(NSEvent *event) {
         if (event.keyCode == toggleGlowKey) {
             shouldGlow = !shouldGlow;
         } else if(event.keyCode == toggleTeamKey) {
             shouldGlowTeam = !shouldGlowTeam;
         }
         return event;
     }];

    return 0;
}

void __attribute__((destructor)) shutdown() {
    [NSEvent removeMonitor:monitor];
    hooker.unhook();
}
