# Farmomatica

[![Ask DeepWiki](https://devin.ai/assets/askdeepwiki.png)](https://deepwiki.com/waffle0823/Farmomatica)

**Farmomatica** is a 2D isometric, open-world farming adventure with deep automation, dynamic economy, and procedural dungeon exploration. Built with **C#** on the **MonoGame** framework, the project uses a shared core library to support cross-platform releases across desktop and mobile.

---

## Game Overview

* **Genre:** Farming Sim • Sandbox • Action-Adventure
* **Perspective:** 2D Isometric
* **Core Pillars:** Automation, Economy, Exploration, Dungeons & Mining

Grow crops, build automated production lines, react to a living market shaped by weather and seasons, and venture into mines and dungeons to secure rare resources that power your farm’s expansion.

---

## Gameplay Features

### 🌱 Automated Farming

* Plant, irrigate, harvest, and process crops using placeable machines
* Upgrade automation for speed, range, and efficiency
* Design production layouts for optimal throughput

### 💹 Dynamic Economy

* Crop prices fluctuate based on **weather**, **seasons**, **random events**, and **supply & demand**
* Decide when to sell, store, or process goods for maximum profit
* Trading and market timing are key strategic choices

### 🌍 Open World Exploration

* Seamless 2D isometric world with chunk-based streaming
* Discover biomes, points of interest, and expansion areas

### ⛏️ Mining & Dungeons

* Procedurally generated mines and dungeons
* PvE encounters, loot, and rare resources
* Crafting materials unlock advanced machines and upgrades

---

## Technical Features

While gameplay systems are actively under development, Farmomatica already includes a robust technical foundation:

* **Cross-Platform Architecture:** Build targets from a single codebase:

  * Windows (DirectX & OpenGL)
  * Linux (OpenGL)
  * macOS (OpenGL)
  * Android
  * iOS

---

## Project Structure

The repository is organized to support scalable, cross-platform development:

* `Farmomatica.Core` — Shared game logic, world systems, automation, economy, utilities
* `Farmomatica.DesktopGL` — Desktop entry point using OpenGL (Windows/macOS/Linux)
* `Farmomatica.WindowsDX` — Windows entry point using DirectX
* `Farmomatica.Android` — Android platform entry point
* `Farmomatica.iOS` — iOS platform entry point

---

## Getting Started

### Prerequisites

* [.NET 9 SDK](https://dotnet.microsoft.com/download/dotnet/9.0)

### Build & Run

1. **Clone the repository**

   ```sh
   git clone https://github.com/waffle0823/Farmomatica.git
   cd Farmomatica
   ```

2. **Restore .NET tools**

   ```sh
   dotnet tool restore
   ```

3. **Build the solution**

   ```sh
   dotnet build Farmomatica.sln
   ```

4. **Run (Desktop OpenGL)**

   ```sh
   dotnet run --project Farmomatica.DesktopGL/Farmomatica.DesktopGL.csproj
   ```

---

## License

**All Rights Reserved.**
Copyright (c) 2025 Waffle0823.
See the [LICENSE](LICENSE) file for details.
