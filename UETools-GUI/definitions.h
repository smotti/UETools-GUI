#pragma once






// =======================
// |  RENDERING SECTION  |
// =======================

/*
	#define INACTIVE_ZERO_SIZE

	Sets overlay window to { 0, 0 } size when menu isn't active or target window isn't in focus.
	Should only be used as an emergency solution for Windows 24H2+ black screen glitch as it disables all of background rendering features.
*/




// ======================
// |  FEATURES SECTION  |
// ======================

/*
	#define UE5

	When targeting Unreal Engine 5 based titles, it's recommended to uncomment that define;
	In many cases that action alone would be enough to adapt entirity of solution for newer engine.
*/

/*
	#define ACTOR_TRACE

	The way Line Tracing work often differ from Engine to Engine (e.g. 4.25 -> 4.27),
	it's disabled by default in order to avoid a potential set of compilation errors.
*/

/*
	#define SOFT_PATH

	Enables everything related to soft path (e.g. Actor Summon & Widget Construct).
	It's disabled by default in order to avoid massive occurencies of incompatibility on older Engine versions.
*/

/*
	#define ACTORS_TRACKING

	Enables everything related to Actors tracking (e.g. Enable Tracking).
	It's disabled by default in order to avoid massive occurencies of incompatibility on older Engine versions.
*/

/*
	#define COLLISION_VISUALIZER

	Enables everything related to collision visualization (e.g. Draw Collision).
	It's disabled by default in order to avoid massive occurencies of incompatibility on older Engine versions.
*/

/*
	#define ACTOR_KIND

	Enables everything related to Actor Kind subsystem (e.g. Point Light Settings, Spot Light Settings, Pawn Actions...).
	It's disabled by default in order to avoid massive occurencies of incompatibility on older Engine versions.
*/

/*
	#define LEVEL_SEQUENCE

	Enables everything related to Level Sequences.
	It's disabled by default in order to avoid massive occurencies of incompatibility on different from baseline Engine versions.
*/