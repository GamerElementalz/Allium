#pragma once

// -----------------------------------------------------------------------------
// TEMPORARY SHIM: EditorTabAPI.hpp ported to the Geode v6 event export macro.
//
// The upstream header (alphalaneous.editortab_api v2.1.x) was written for
// Geode 5 and uses the old two-argument form of GEODE_EVENT_EXPORT /
// GEODE_EVENT_EXPORT_NORES. Geode v6.0.0-alpha.1 changed the macro to
//
//     GEODE_EVENT_EXPORT(returnType, name, (params), (args))
//
// and removed the *_NORES variants (use `void` as the return type instead).
//
// This copy lives in third_party/ so that it is found before the header that
// the Geode CLI downloads into build/geode-deps. Delete this file once
// EditorTab API publishes a header that supports Geode v6.
//
// NOTE: at runtime Allium still needs an EditorTab API build made for Geode v6
// (compiled from this same header) to be installed.
// -----------------------------------------------------------------------------

#include <Geode/cocos/base_nodes/CCNode.h>
#include <Geode/utils/ZStringView.hpp>
#include <Geode/binding/EditButtonBar.hpp>
#include <Geode/loader/Event.hpp>
#include <Geode/loader/Dispatch.hpp>

#include <functional>
#include <span>
#include <string>
#include <vector>

#ifdef MY_MOD_ID
    #undef MY_MOD_ID
#endif
#define MY_MOD_ID "alphalaneous.editortab_api"
#undef DELETE

namespace alpha::editor_tabs {
    static const std::string BUILD = "robtop.geometry-dash/build";
    static const std::string EDIT = "robtop.geometry-dash/edit";
    static const std::string DELETE = "robtop.geometry-dash/delete";

    using CreateTab = std::function<cocos2d::CCNode*()>;
    using CreateTabIcon = std::function<cocos2d::CCNode*()>;
    using ToggleTab = std::function<void(bool, cocos2d::CCNode*)>;
    using ReloadTab = std::function<void(int, int, cocos2d::CCNode*)>;

    GEODE_EVENT_EXPORT(void, addTab,
        (geode::ZStringView tabID, geode::ZStringView modeID, CreateTab&& createTab, CreateTabIcon&& createIcon, ToggleTab&& toggleTab = nullptr, ReloadTab&& reloadTab = nullptr),
        (tabID, modeID, std::move(createTab), std::move(createIcon), std::move(toggleTab), std::move(reloadTab)));

    GEODE_EVENT_EXPORT(void, switchMode,
        (geode::ZStringView modeID),
        (modeID));

    GEODE_EVENT_EXPORT(void, switchTab,
        (geode::ZStringView tabID),
        (tabID));

    GEODE_EVENT_EXPORT(void, changeModeSprites,
        (bool enabled),
        (enabled));

    GEODE_EVENT_EXPORT(void, addModeSwitchCallback,
        (geode::Function<void(geode::ZStringView id)>&& callback, geode::Mod* mod = geode::Mod::get()),
        (std::move(callback), mod));

    GEODE_EVENT_EXPORT(void, addTabSwitchCallback,
        (geode::Function<void(geode::ZStringView id)>&& callback, geode::Mod* mod = geode::Mod::get()),
        (std::move(callback), mod));

    GEODE_EVENT_EXPORT(geode::Result<std::vector<cocos2d::CCNode*>>, getAllTabs,
        (),
        ());

    GEODE_EVENT_EXPORT(geode::Result<geode::ZStringView>, getCurrentMode,
        (),
        ());

    GEODE_EVENT_EXPORT(geode::Result<geode::ZStringView>, getCurrentTab,
        (),
        ());

    GEODE_EVENT_EXPORT(geode::Result<int>, getTabIndex,
        (geode::ZStringView tabID),
        (tabID));

    GEODE_EVENT_EXPORT(geode::Result<geode::ZStringView>, getTabMode,
        (geode::ZStringView tabID),
        (tabID));

    GEODE_EVENT_EXPORT(geode::Result<geode::Ref<cocos2d::CCNode>>, nodeForTab,
        (geode::ZStringView tabID),
        (tabID));

    GEODE_EVENT_EXPORT(geode::Result<int>, indexForTab,
        (cocos2d::CCNode* tab),
        (tab));

    GEODE_EVENT_EXPORT(geode::Result<geode::Ref<cocos2d::CCNode>>, tabForIndex,
        (int index, geode::ZStringView modeID),
        (index, modeID));

    GEODE_EVENT_EXPORT(geode::Result<geode::ZStringView>, idForTab,
        (cocos2d::CCNode* tab),
        (tab));

    GEODE_EVENT_EXPORT(geode::Result<geode::ZStringView>, idForTabIndex,
        (int index, geode::ZStringView modeID),
        (index, modeID));

    GEODE_EVENT_EXPORT(geode::Result<geode::Ref<CCMenuItemToggler>>, togglerForTab,
        (geode::ZStringView tabID),
        (tabID));

    GEODE_EVENT_EXPORT(EditButtonBar*, createEditButtonBar,
        (std::span<geode::Ref<cocos2d::CCNode>> nodes),
        (nodes));

    GEODE_EVENT_EXPORT(void, removeTab,
        (geode::ZStringView tabID),
        (tabID));

    GEODE_EVENT_EXPORT(void, updateTabMenu,
        (),
        ());
};
