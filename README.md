# Generic Minimap Plugin

This plugin provides a modular minimap system for Unreal Engine. It includes support for minimaps, world maps, dynamic markers, battle royale-style zones, and tools for creating accurate top-view textures.

---

## Installation

### Downloading the Plugin
- Download the plugin from the GitHub repository.
- This is a **C++ plugin**, so it requires a C++ project to compile.
- A **compiled branch** based on specific Unreal Engine versions is also available for convenience.

### Adding the Plugin to Your Project
1. Clone or download the plugin into your project's `Plugins` folder.
2. Right-click the `.uproject` file in your project directory and select **Generate Visual Studio project files**.  
3. Open your Unreal Engine project. The plugin will automatically compile if your project is set up correctly.
4. Enable the plugin in the **Plugins** menu inside Unreal Engine.

---

## Usage

### 1. Setting Up the Minimap Manager
The **Minimap Manager** class defines the playable area for your minimap.

1. Place the **Minimap Manager** actor from the plugin's content folder into your level.
2. Adjust the **Playable Area Size**:
   - Use the **Playable Area Size** variable to define the bounds of your minimap in meters.
   - The Grid material helps visualize these bounds.

---

### 2. Adding the Actor Component
To display a player marker or other markers, you need to register the actor to the minimap system.

1. Add the `ACGenericMinimap` **Actor Component** to any actor you want to appear on the minimap.
2. On Begin Play call the **SpawnAndRegister** function.
3. The spawned marker will automatically follow the actor's position.
> This will be more modular in the future. For now I recommend using this function for Pawn class.

---

### 3. Minimap and World Map Widgets
- **Minimap Widget**: Inherit from the premade minimap widget for quick setup. Add it to your UMG UI and customize as needed.
- **World Map Widget**: Use the provided world map widget for full-screen maps with dynamic markers and zones.

---

### 4. Creating a Minimap Texture
1. Place the **Minimap2D_Capture** actor from the plugin's content folder into your level.
2. Set the **Minimap2D_Capture** to the same world location as your Minimap Manager.
3. Set the **Capture Size** to match the **Playable Area Size** of your map in centimeters (Playable Area Size * 100).
4. Open the **MinimapCaptureTarget** render target in the plugin's content folder (`Art -> Texture`).
5. Adjust the Z value of the **Minimap2D_Capture** actor in the world to ensure it captures all actors in the playable area.
6. Right-click the assigned **Render Target** and select **Create Static Texture**.
![](Resources\minimap_capture_target01.webp)
7. Use the generated texture as the minimap's background image.

---

### 5. Battle Royale Zone System
The plugin includes a prototype **Zone System** for dynamic zones.

#### Adding an Image Zone
- Add the **Image Zone** component to your minimap or world map widget.
- Customize the material instance (e.g., colors, opacity).
- Update zone properties via Blueprint:
  - **Current Zone Radius**
  - **Current Zone Location**
  - **Next Zone Radius**
  - **Next Zone Location**

---

### 6. Example Content
- **World Map Example**: Demonstrates marker and zone functionality.
- **Dynamic Zone Example**: A sample implementation for shrinking zones in a battle royale setting.

---

## Support
For issues, feature requests, or questions, please open an issue on the [GitHub repository](#).
