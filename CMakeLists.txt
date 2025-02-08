cmake_minimum_required(VERSION 3.15)
project(ShovelKnightShovelOfHope)

add_subdirectory(Engine)

add_executable(Game
   Source/main.cpp
   Source/pch.cpp

   Source/Background.cpp
   Source/Beeto.cpp
   Source/Blorb.cpp
   Source/Boneclang.cpp
   Source/Bubble.cpp
   Source/Camera.cpp
   Source/CheckPoint.cpp
   Source/Clod.cpp
   Source/Destructive.cpp
   Source/DestructiveBlock.cpp
   Source/DigClod.cpp
   Source/DigPile.cpp
   Source/DigPile.cpp
   Source/DirtBlock.cpp
   Source/DirtBlockSmall.cpp
   Source/Divedrake.cpp
   Source/Dozedrake.cpp
   Source/DynamicCollider.cpp
   Source/FX.cpp
   Source/Game.cpp
   Source/GameObject.cpp
   Source/GameObjectManager.cpp
   Source/HitBox.cpp
   Source/HUD.cpp
   Source/HurtBox.cpp
   Source/InputManager.cpp
   Source/Interactable.cpp
   Source/Interactor.cpp
   Source/KinematicCollider.cpp
   Source/Ladder.cpp
   Source/LevelManager.cpp
   Source/MovingPlatform.cpp
   Source/Particle.cpp
   Source/Pickupable.cpp
   Source/Pickupper.cpp
   Source/Platter.cpp
   Source/Rigidbody.cpp
   Source/ShovelKnight.cpp
   Source/SimpleSprite.cpp
   Source/Skull.cpp
   Source/SoundManager.cpp
   Source/Spike.cpp
   Source/SpriteAnimator.cpp
   Source/SVGDeathZone.cpp
   Source/SVGMap.cpp
   Source/SVGPolygon.cpp)

target_link_libraries(Game PRIVATE Engine)

target_precompile_headers(Game PRIVATE Source/pch.h)

add_custom_command(TARGET Game
   POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
   ${CMAKE_SOURCE_DIR}/Resources
   $<TARGET_FILE_DIR:Game>)