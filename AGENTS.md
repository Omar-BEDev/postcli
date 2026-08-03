# AGENTS.md

Last updated: 2026-08-03 (postcli project)

## Project
`postcli` — a small C CLI that parses log history. `src/` is pure C; headers use `extern "C"` guards for C++ test compatibility.

## What was done today (2026-08-03)

1. Installed googletest via `pkg install googletest` (1.17.0, termux).
2. Added `extern "C"` guards to all 8 headers (header-only; **no `src/*.c` code was modified**):
   - `src/core/date-compare.h`, `src/core/history/history.h`, `src/core/history/search.h`,
     `src/utils/dynamic-array.h`, `src/core/start/before-start.h`, `src/core/start/start.h`,
     `src/io/logs/logs.h`, `src/utils/file-check.h`
3. Added a `test` target to the `makefile`:
   - Compiles all `src/*.c` EXCEPT `src/main.c`, plus `test/*.cpp`, links `-lgtest -pthread`, runs `test/run_tests`.
   - `make test` runs the suite. `make clean` also removes `test/*.o` and `test/run_tests`.
4. Created `test/` folder with GoogleTest suites covering every function:
   - `crash_guard.h` — `EXPECT_NO_CRASH(...)` fork/waitpid helper: catches SIGSEGV as a failed test instead of killing the runner.
   - `test_main.cpp`, `test_date.cpp`, `test_dynamic_array.cpp`, `test_search.cpp`,
     `test_file.cpp`, `test_logs.cpp`, `test_before_start.cpp`, `test_start.cpp`
5. Result: **52 tests, 46 PASSED, 6 FAILED** (all 6 failures are genuine bugs in `src/`; none were fixed per user request).
6. Main `postcli` binary still builds and runs OK.

## KNOWN BUGS FOUND BY EDGE-CASE TESTS (NOT FIXED — user requested tests only)

1. **SIGSEGV — `first_history_index` on empty/NULL array** — `src/core/history/search.c:38`
   Dereferences `history[match]` (index 0) after the loop when no match exists.
2. **SIGSEGV — `last_history_index` on empty/NULL array** — `src/core/history/search.c:74`
   Same NULL dereference.
3. **`search_history_indexes` leaves `indexes` uninitialized on empty array** — `src/core/history/history.c:13`
   Returns after printing `error: logs not found` without setting `indexes[0]/[1]` to `-1`.
4. **`read_file_logs` stores stale `date` for empty lines** — `src/io/logs/logs.c:60`
   `date[11]` never cleared between lines; an empty line re-uses the previous date (bogus duplicate entry).
5. **`read_file_logs` reads uninitialized memory for short lines** — `src/io/logs/logs.c:60`
   Line shorter than 10 chars → partial data + uninitialized stack garbage stored as the date (UB).
6. **SIGSEGV — `read_file_logs`/`extract_logs` crash unless caller wires function pointer** — `src/io/logs/logs.c:81`
   Calls `history_arr->add_history_log(...)` which is a NULL function pointer. **No code in `src/` ever assigns the `add_history_log`/`remove_history_log` struct pointers**, so this path crashes in production too. Tests must set `arr.add_history_log = add_history_log` first.

## Notes
- The `HistoryArray` struct has function-pointer members `add_history_log`/`remove_history_log` that must be wired by the caller before calling `extract_logs`/`read_file_logs`.
- `json_parsee.c` and `network/http_client.cpp` are empty (0 bytes) — no functions to test.
- `.gitignore` now ignores `test/run_tests`.
