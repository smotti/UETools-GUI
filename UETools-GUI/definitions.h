#pragma once


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
	#define ACTOR_KIND

	Enables everything related to Actor Kind subsystem (e.g. Point Light Settings, Spot Light Settings, Pawn Actions...).
	It's disabled by default in order to avoid massive occurencies of incompatibility on older Engine versions.
*/