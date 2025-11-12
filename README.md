# NECROEngine

# PROJECT MOVED TO NECROMMO: https://github.com/silvematt/NECRO-MMO

Isometric Game Engine written in C++ and SDL2

<img width="1441" alt="thum1" src="https://github.com/silvematt/NECROEngine/assets/20478938/fa632904-6105-4b7a-8d44-ad700113e6fb">


# Features
* __GPU-based Rendering__ done on RenderTargets (Game, Debug, UI, ...), to allow rendering on different textures and join them to compose the final image.
* __Camera__ with Zoom, Free-Look and Follow Player mode.
* __Dynamic Assets Manager__ that allows the load of assets (images, prefabs, animators, etc) only when strictly needed.
* __Prefabs__ to dynamically create and modify entities from files (.nprfb).
* __Animators__ with AnimStates that allow defining settings for each animation, defined in files (.nanim).
* __Worldspace and Cells__ rendered and updated only in the visible Camera space.
* __Basic Entities__ with a component-oriented architecture.
* __Lighting__ flat and dynamic (raycasting).
* __Player__ movements, interactions with entities, and aim-mode.
* __Collision checking and resolution__.
* __Entity-Occlusion check__ (if set) when an entity occludes the player the entity will be drawn transparent.
* __Input System__
