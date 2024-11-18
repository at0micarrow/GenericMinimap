# Generic Minimap Plugin

This plugin provides a modular minimap system for Unreal Engine. It includes support for both minimap and world map functionality, dynamic markers, battle royale-style zones, and tools for creating accurate top-view textures.

## Installation

### Downloading the Plugin
- Download the plugin from the GitHub repository. 
- This is a **C++ plugin**, so it requires a C++ project to compile.
- For convenience, a **compiled branch** based on specific Unreal Engine versions is also available.

### Adding the Plugin to Your Project
1. Clone or download the plugin into your project's `Plugins` folder.
2. Right-click the `.uproject` file in your project directory and select **Generate Visual Studio project files**.  
   > This step ensures that Unreal Engine detects the plugin and properly integrates it into the project.
3. Open your Unreal Engine project. The plugin will automatically compile if your project is set up correctly.
4. Enable the plugin in the **Plugins** menu inside Unreal Engine.

## Usage

### 1. Setting Up the Minimap Manager
The **Minimap Manager** class defines the playable area for your minimap. Here's how to set it up:

1. Place the **Minimap Manager** actor from the plugin's content folder into your level.
2. Adjust the **Playable Area Size**:
   - Use the variable **Playable Area Size** float to define the bounds of your minimap.
   - This is in meters. The Grid material helps to see your bounds in the level.
   
---

### 2. Minimap and World Map Widgets
- **Minimap Widget**: Inherit from the premade minimap widget for quick setup. Add it to your UMG UI and customize it as needed.
- **World Map Widget**: Use the provided world map widget for full-screen maps, supporting dynamic markers and zones.

---

### 3. Creating a Minimap Texture
1. Place the **Minimap2d_capture** actor from the plugin's content folder into your level.
2. Set the **Minimap2d_capture** to the same world location as your minimap manager.
3. Set the **Capture Size** to match the **playable area size** of your map. This is in centimeter (Playable Area Size * 100).
4. Open the **MinimapCaptureTarget** render target in the plugin's content folder Art->Texture
4. Adjust the Z value of the **Minimap2d_capture** actor in the world to capture all of your actors in the world. 
5. Right-click the assigned **Render Target** and select **Create Static Texture**.
6. Use the generated texture as the minimap's background image.

---

### 4. Battle Royale Zone System
The plugin includes a prototype **Zone System** for dynamic zones.

#### Image Zone Component
- Add the **Image Zone** component to your minimap or world map widget.
- Customize the material instance (e.g., colors, opacity).
- Update zone properties via Blueprint:
  - **Current Zone Radius**
  - **Current Zone Location**
  - **Next Zone Radius**
  - **Next Zone Location**

---

### 5. Example Content
- **World Map Example**: Demonstrates marker and zone functionality.
- **Dynamic Zone Example**: A sample implementation for shrinking zones in a battle royale setting.

---

## Support
For issues, feature requests, or questions, please open an issue on the [GitHub repository](#).
