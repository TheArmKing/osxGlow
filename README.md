# osxGlow
A small internal CSGO glowhack for macOS. Works on M1 as well. \
Based on https://github.com/fakePh0e/osxGlow. His credits are provided in the code \
I have simply done the following:
- Switched to `Objective-C++`
- Added team unlink using `iTeam_Num`
- Added keybinds (Right arrow to toggle full glow and left arrow to toggle only team glow)
- Restructured the code

# Usage
Launch `CSGO` and then run `load.command` in terminal. (It will ask for password). The compiled dylib must be in the same folder as the `load.command` file. A pre-compiled `osxGlow.dylib` is provided in the `main` folder along with `load.command` (to inject) and `unload.command` (to de-inject) the dylib.


**You will probably need xcode command line tools installed. To do that run `xcode-select --install` in terminal.**


# Customizations
Scroll down in `src/defs.h` to customize the glow options.
```cpp
// Customizations

// Default behaviour of whether these should be turned on upon injection
bool shouldGlow = true;
bool shouldGlowTeam = true;

// Keybinds for toggling the glow
int toggleGlowKey = kVK_RightArrow;
int toggleTeamKey = kVK_LeftArrow;

// Enemy glow customizations
Vector enemyColor = RGB(242,117,117);
float enemyAlpha = 1.0f;
GlowRenderStyle_t enemyStyle = GLOWRENDERSTYLE_DEFAULT;

// Team glow customizations
Vector teamColor = RGB(117,242,165);
float teamAlpha = 0.6f;
GlowRenderStyle_t teamStyle = GLOWRENDERSTYLE_DEFAULT;
```


# Building from source
If you want to make any changes then you can use `build.command` provided in the `src` folder to build the dylib using gcc. It will automatically handle building x86_64 on an M1 Mac as well. All the other files must also be in the same folder as the build.command for it to work. 

# Showcase


https://user-images.githubusercontent.com/41083078/134171556-b9ee83a7-3d6d-4dda-8077-b4c6005372f2.mp4


