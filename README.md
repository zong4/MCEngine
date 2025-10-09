# Minecraft Engine

A game engine created for Minecraft-like games.

![Minecraft Engine Editor](./Assets/Editor.png)

## Why is it

As I said, it's a game engine created for Minecraft-like games which means it wouldn't support some amazing features that other game engines support like Unity or Unreal Engine. So I can more focus on improving the performance of the engine and make it more suitable for Minecraft-like games.

## What I do

### Graphics

Support rendering squares and cubes with OpenGL with Blinn-Phong lighting model.

## How to use

1. Clone the repository
   ```bash
   git clone https://github.com/zong4/MinecraftEngine.git
   ```
2. Download and install [XMake](https://xmake.io/guide/quick-start.html)
3. Build and run the project 
   ```bash
   cd MinecraftEngine
   xmake run -y
   ```

## What we plan

- [ ] Support rendering other basic shapes like sphere, cylinder, cone, etc.
- [ ] Provide some generation algorithms like Perlin Noise, Simplex Noise, etc.
- [ ] Provide some world generation algorithms like Chunked LOD, Greedy Meshing, etc.

## References:
- [OpenGL](https://learnopengl.com)
- [Game Engine Architecture](https://github.com/TheCherno/Hazel)