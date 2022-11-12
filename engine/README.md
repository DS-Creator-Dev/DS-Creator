# DSCEngine Tests list

This is a list of tests that DSCEngine should pass.

## Legend

✅ - ok, seems to work, but wouldn't hurt to double check it

🍦 - other things may break if this doesn't work. Assume it's correct, although it has not been thoroughly tested

⚠️ - not tested, proceed with caution

❌ - successfully fails

🔵 - not a concern

🔸 - to be implemented

## Tests List

| No.  | Related source file                  | Target                                 | Description                                                              | Passing |
|-----:|:-------------------------------------|----------------------------------------|--------------------------------------------------------------------------|:-------:|
|    1 |`debug/log.cpp`                       | `_logv()`                              | Check for incorrect parsings, index-out-of-bounds etc                    |✅| 
|    2 |`events/event.cpp`                    | `Event::trigger()`                     | Missed case: what if the EventHandler is null?                           |⚠️| 
|    3 |`resources/readonly_data.cpp`         | `ReadOnlyData::extract()`              | Possible "8-bit write to VRAM" error source                              |⚠️| 
|    4 |`resources/readonly_data.cpp`         | `ReadOnlyData::extract()`              | Extracting resources from file                                           |⚠️| 
|    5 |`resources/readonly_data.cpp`         | `ReadOnlyData::extract(v*,i,i)`        | Check requested data alignment                                           |✅| 
|    6 |`resources/asset_data.cpp`            | `*`                                    | It is assumed that provided AssetData sources are correctly created      |⚠️/🔵?| 
|    7 |`resources/asset_data.cpp`            | `*`                                    | Data access with compression enabled                                     |🔸| 
|    8 |`resources/asset_data.cpp`            | `AssetData::get_color_depth()`         | Detect incorrect color depth flag                                        |⚠️|
|    9 |`scenes/scene.cpp`                    | `Scene::run()`                         | Key events working                                                       |✅|
|   10 |`scenes/scene.cpp`                    | `SceneCom::next()`                     | Calling `close->next()` from within an event                             |⚠️|
|   11 |`scenes/generic_scene_256.cpp`   | `GenericScene256::solve_map_requirements_main()` | Assert encounter: `Map base exceeded`                                    |⚠️|
|   12 |`scenes/generic_scene_256.cpp`   | `GenericScene256::solve_map_requirements_main()` | Assert encounter: `Backgrounds 0,1 cannot be bitmaps`                    |⚠️|
|   13 |`scenes/generic_scene_256.cpp`   | `GenericScene256::solve_map_requirements_main()` | Assert encounter: `Main backgrounds data does not fit in allocated VRAM` |⚠️|
|   14 |`scenes/generic_scene_256.cpp`   | `GenericScene256::solve_map_requirements_main()` | Check if tile & map bases are computed correctly                         |⚠️|
|   15 |`scenes/generic_scene_256.cpp`   | `GenericScene256::solve_map_requirements_sub()`  | Same observations for the sub engine                                     |🔸|
|   16 |`scenes/generic_scene_256.cpp`   | `GenericScene256::load_assets()`| Assert encounter: `Palette allocation failed`                                             |⚠️/🔸|
|   17 |`scenes/generic_scene_256.cpp`       | `GenericScene256::require_tiledmap_4bpp()` | Checks for invalid data                                                    |⚠️|
|   18 |`scenes/generic_scene_256.cpp`       | `GenericScene256::require_tiledmap_8bpp()` | Checks for invalid data                                                    |⚠️|
|   19 |`scenes/generic_scene_256.cpp`       | `GenericScene256::require_tiledmap()` | Checks for invalid data                                                         |⚠️|
|   20 |`scenes/generic_scene_256.cpp`       | `GenericScene256::require_bitmap(i,i,i)` | Checks for invalid data                                                      |⚠️|
|   21 |`scenes/generic_scene_256.cpp`       | `GenericScene256::require_bitmap(i,cAD*)` | Checks for invalid data                                                     |⚠️|
|   22 |`scenes/generic_scene_256.cpp`       | `GenericScene256::require_bitmap_16bpp(i,i,i)` | Checks for invalid data                                                |⚠️|
|   23 |`scenes/generic_scene_256.cpp`       | `GenericScene256::require_bitmap_16bpp(i,cAD*)` | Checks for invalid data                                               |⚠️|
|   24 |`scenes/generic_scene_256.cpp`       | `GenericScene256::validate_bg_size()`           | Allowing individual map sizes: 128, 256, 512, 1024                    |🍦|
|   25 |`scenes/generic_scene_256.cpp`       | `GenericScene256::validate_bg_size()`           | Allowing right map size combination                                   |⚠️|
|   26 |`video/allocator.cpp`                | `Allocator::reserve()`           | Reserving memory zone                                                                |⚠️|
|   27 |`video/allocator.cpp`                | `Allocator::reserve()`           | Prevent overwriting                                                                  |⚠️|
|   28 |`video/allocator.cpp`                | `Allocator::reserve()`           | Desired-offset allocation                                                            |⚠️|
|   29 |`video/allocator.cpp`                | `Allocator::reserve()`           | Returning null on fail                                                               |⚠️|
|   30 |`video/allocator.cpp`                | `Allocator::reserve()`           | Allocate + Deallocate + Reallocate                                                   |⚠️|
|   31 |`video/allocator.cpp`                | `Allocator::release()`           | Freeing occupied segment                                                             |⚠️|
|   32 |`video/allocator.cpp`                | `Allocator::release()`           | Adjacent segments merging                                                            |⚠️|
|   33 |`video/allocator.cpp`                | `Allocator::release()`           | Freeing what resides at the start of the memory zone                                 |⚠️|
|   34 |`video/allocator.cpp`                | `Allocator::release()`           | Ignoring invalid addresses                                                           |⚠️|
|   35 |`video/measure.cpp`                  | `*`                              | Check the math, should be straight forward                                           |⚠️|
|   36 |`video/palette_manager.cpp`          | `validate_palette_manager_constructor_input()`| Maybe also allow shadow-palettes in WRAM?   |🔸|
|   37 |`video/palette_manager.cpp`          | `free_bit_pos()`| Check the math, should be straight forward                                                            |🍦|
|   38 |`video/palette_manager.cpp`          | `PaletteManager::reserve1()`| Reserve a new color index                                                                 |🍦|
|   39 |`video/palette_manager.cpp`          | `PaletteManager::reserve1()`| Prevents color duplicates                                                                 |🍦|
|   40 |`video/palette_manager.cpp`          | `PaletteManager::reserve1()`| Returns -1 on fail                                                                        |🍦|
|   41 |`video/palette_manager.cpp`          | `PaletteManager::unload1()` | Removes colors allocated one                                                              |🍦|
|   42 |`video/palette_manager.cpp`          | `PaletteManager::unload1()` | Keeps colors still in use                                                                 |🍦|
|   43 |`video/palette_manager.cpp`          | `PaletteManager::unload1()` | Ignores inexistent colors                                                                 |🍦|
|   44 |`video/palette_manager.cpp`          | `PaletteManager::reserve16()` | Reserves a new slot                                                                     |🍦|
|   45 |`video/palette_manager.cpp`          | `PaletteManager::reserve16()` | Prevents duplicates                                                                     |🍦|
|   46 |`video/palette_manager.cpp`          | `PaletteManager::reserve16()` | Returns -1 on fail                                                                      |🍦|
|   47 |`video/palette_manager.cpp`          | `PaletteManager::unload()`    | Removes palettes allocated once                                                         |🍦|
|   48 |`video/palette_manager.cpp`          | `PaletteManager::unload()`    | Keeps palettes still in use                                                             |🍦|
|   49 |`video/palette_manager.cpp`          | `PaletteManager::unload()`    | Ignores inexistent palettes                                                             |🍦|
|   50 |`video/palette_manager.cpp`          | `PaletteManager::try_load()`  | Error on 16-bit asset                                                                   |⚠️|
|   51 |`video/palette_manager.cpp`          | `PaletteManager::try_load()`  | Loads 4-bit asset                                                                       |⚠️|
|   52 |`video/palette_manager.cpp`          | `PaletteManager::try_load()`  | Loads 8-bit asset                                                                       |🍦|
|   53 |`video/palette_manager.cpp`          | `PaletteManager::unload()`    | Error on 16-bit asset                                                                   |⚠️|
|   54 |`video/palette_manager.cpp`          | `PaletteManager::unload()`    | Loads 4-bit asset                                                                       |⚠️|
|   55 |`video/palette_manager.cpp`          | `PaletteManager::unload()`    | Loads 8-bit asset                                                                       |🍦|
|   56 |`video/vram_loader.cpp`              | `VramLoader::load()`          | Copies without additional buffer (4bpp, 16bpp and 8bpp w/o) dynamic indices             |⚠️|
|   57 |`video/vram_loader.cpp`              | `VramLoader::load()`          | Copies with additional buffer 8bpp w/ dynamic palette indices                           |🍦|


## Related

See [DOCS.md](DOCS.md) for old docs.

For updated docs, see `docs/html/annotations.html`.