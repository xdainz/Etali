# Etali - Copilot Instructions

## Project Overview

Etali is a C++ CLI tool for fetching Magic: The Gathering card data from the [Scryfall API](https://scryfall.com/docs/api). Named after the MTG card "Etali, Primal Conqueror", it currently supports fetching random commander cards.

## Architecture

```
main.cpp          → Entry point, CLI argument handling, orchestrates flow
fetch/            → HTTP layer (libcurl) - Scryfall API communication
parse/            → JSON parsing (jsoncpp) - Response deserialization
model/            → Data structures (ScryfallCard) and display formatting
cli/              → CLI help and usage display
```

**Data Flow:** `main.cpp` → `fetch_random_commander()` → `parse_json()` → `card_to_string()` → stdout

## Build & Run

```bash
make          # Build the etali binary (requires libcurl, libjsoncpp)
make clean    # Remove compiled binary and object files
./etali       # Fetch random commander
./etali -h    # Show help
./etali -v    # Show version
```

**Dependencies:** `libcurl`, `jsoncpp` - Link flags: `-lcurl -ljsoncpp`

## Code Patterns

### Error Handling
Errors are returned as strings with `ERROR:` prefix (see [fetch/fetch.cpp](fetch/fetch.cpp#L24)):
```cpp
return std::string("ERROR:") + std::to_string((int)res);
```
Check errors with: `raw.rfind("ERROR:", 0) == 0`

### Adding New API Endpoints
1. Add fetch function in `fetch/fetch.cpp` using `BASE_URL` + endpoint path
2. Parse response in `parse/parse_json.cpp`, returning appropriate model struct
3. Wire up in `main.cpp` with CLI argument handling

### Header Guards
Use `#ifndef FILENAME_H` / `#define FILENAME_H` pattern (see [fetch/fetch.hpp](fetch/fetch.hpp))

### Model Layer
- [model/card.h](model/card.h) contains `ScryfallCard` struct, `parse_card()`, and `card_to_string()`
- Static helper functions are defined directly in headers
- JSON parsing uses conditional member checks: `if(v.isMember("field"))`

### CLI Commands
Add commands in [cli/help.cpp](cli/help.cpp) using the `Command` struct, then wire logic in `main.cpp`

## Scryfall API

- Base URL: `https://api.scryfall.com/cards/`
- Random commander endpoint: `random?q=is%3Acommander`
- User-Agent header: `Etali/0.1`
- Response format: JSON with `"object": "card"` for valid cards
