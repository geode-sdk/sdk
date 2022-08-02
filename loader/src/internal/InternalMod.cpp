#include "InternalMod.hpp"
#include "about.hpp"

static ModInfo getInternalModInfo() {
    ModInfo info;
    
    info.m_id          = "geode.loader";
    info.m_name        = "Geode";
    info.m_developer   = "Geode Team";
    info.m_description = "Internal representation";
    info.m_details     = LOADER_ABOUT_MD;
    info.m_version     = LOADER_VERSION;
    info.m_supportsDisabling = false;
    info.m_spritesheets = {
        "geode.loader_LogoSheet",
        "geode.loader_APISheet",
        "geode.loader_BlankSheet"
    };

    return info;
}

InternalMod::InternalMod() : Mod(getInternalModInfo()) {}

InternalMod::~InternalMod() {}

InternalMod* InternalMod::get() {
    static auto g_mod = new InternalMod;
    return g_mod;
}