## Code: C — Doxygen

- `/** ... */` block directly above the declaration, in the header for public symbols (`include/`), above the definition for file-local (`static`) ones. First sentence is the `@brief`; imperative or third person, one line.
- Tags: `@brief`, `@param name description` (add `[in]`/`[out]` only for pointers), `@return` (omit for `void`), `@note` for hardware constraints (VRAM timing, bank switching, ROM bank), `@warning` for pitfalls.
- File header `/** @file name.c @brief ... */` once per file.
- Document every non-static function, struct/enum/typedef and macro constant in headers; group related macros with `@name`/`@{ @}`.
- Comments inside functions explain why, never what. Match the repo's formatting: no line over 100 columns.

```c
/**
 * @brief Move the player one tile and update its sprite.
 * @param dir Direction to move (DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT).
 * @return 1 if the tile was walkable, 0 if blocked.
 */
uint8_t player_move(uint8_t dir);
```

## Project — minimal

Files, and their sections in order. Each section only when it has content.

- `README.md`: one-line purpose; **Install**; **Run** (exact commands); **Test** (exact commands); **Configuration** (env vars and config files, as a table `name | default | effect`); **Layout** (table `module | path | one line`, one row per module). No badges, no feature marketing, no contributing boilerplate unless asked.
- `docs/architecture.md`, only with 3 or more modules: **Modules** (how they depend on each other, as a Mermaid `flowchart` or an indented list); **Data flow** (one request or job end to end, by module); **Decisions** (each: the decision, the reason, the alternative rejected, in one line). One page.
- `<module>/README.md`, only for modules whose map row says `big: yes`: purpose; **Entry points** (`file` and what starts there); **Gotchas**. Never restate what the code docs say; link to the symbol instead.

## Not covered

- Languages other than C (none in the repo).
- Assembly or generated asset data tables beyond a one-line file header.
