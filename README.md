![Geode Logo](https://github.com/geode-sdk.png?size=80) 

# Geode SDK

**Geode** is a [Geometry Dash](https://store.steampowered.com/app/322170/Geometry_Dash/) **mod loader** and **modding SDK** with a modern approach towards mod development. Unlike previous mod loaders, which merely inject the DLLs and let devs handle the rest, Geode aims to be a more comprehensive project, which manages loaded mods & hooks itself. Geode has been built to ensure performance, compatibility, portability and ease of use. For devs, Geode means **easy development and portability**; for end users, Geode means **an uniform and easy experience** using mods.

## Why Geode?

There's nothing worse than having to read thousands of words just to see what some library's code actually looks like, so instead, here's a **Hello World** in Geode right off the bat:

```cpp
#include <Geode.hpp>

USE_GEODE_NAMESPACE();

class $modify(MenuLayer) {
	void onMoreGames(CCObject*) {
		FLAlertLayer::create(
			"Geode",
			"Hello World from my Custom Mod!",
			"OK"
		)->show();
	}
};
```

This code hooks the "More Games" button in Geometry Dash, and makes it show a different popup when clicked. Compared to traditional modding methods such as MinHook, we would argue that this is **much easier to write, understand & maintain**.

Geode is in many ways a **declarative framework**; you tell it what you want, not how to accomplish it. Geode has been built to let modders focus on what mod they want to make, not how exactly to build it. Its goal is to **abstract away** unnecessary details, while still enabling developers have **precise control** over their mod.

One of our main design goals with Geode has been to make a framework so good that **after using it once, you never want to go back**.

## Documentation

Detailed documentation, tutorials, and references on using the Geode SDK can be found [here](https://geode-sdk.github.io/docs/).

## Contribution

You can contribute to Geode by opening a [Pull Request](https://github.com/geode-sdk/geode/pulls)!

## Questions, help, etc.

If you have any further questions, need help, or just want to share your love for catgirls, be sure to join [our Discord server](https://discord.gg/9e43WMKzhp)!
