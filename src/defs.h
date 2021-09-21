//
//  defs.h
//  osxGlow
//
//  Created by TheArmKing on 21/09/21.
//

#ifndef defs_h
#define defs_h

class Vector
{
    public:
        float x, y, z;
        Vector(float X, float Y, float Z) {
            x = X; y = Y; z = Z;
        };
};

//https://github.com/perilouswithadollarsign/cstrike15_src/blob/29e4c1fda9698d5cebcdaf1a0de4b829fa149bf8/game/client/glow_outline_effect.h#L23
enum GlowRenderStyle_t
{
    GLOWRENDERSTYLE_DEFAULT = 0,
    GLOWRENDERSTYLE_RIMGLOW3D,
    GLOWRENDERSTYLE_EDGE_HIGHLIGHT,
    GLOWRENDERSTYLE_EDGE_HIGHLIGHT_PULSE,
    GLOWRENDERSTYLE_COUNT,
};

#define RGB(x,y,z) { x / 255.0f, y / 255.0f, z / 255.0f }
#import "keyCodes.h"
#import "detourHook.h"
#import "patternScanner.h"
detour hooker;
id monitor;
uintptr_t m_iTeamNum = 0x12C;

// Customizations
bool shouldGlow = true;
bool shouldGlowTeam = true;

int toggleGlowKey = kVK_RightArrow;
int toggleTeamKey = kVK_LeftArrow;

Vector enemyColor = RGB(242,117,117);
float enemyAlpha = 1.0f;
GlowRenderStyle_t enemyStyle = GLOWRENDERSTYLE_DEFAULT;

Vector teamColor = RGB(117,242,165);
float teamAlpha = 0.6f;
GlowRenderStyle_t teamStyle = GLOWRENDERSTYLE_DEFAULT;

#endif /* defs_h */
