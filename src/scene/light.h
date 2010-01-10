#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "common.h"
#include "texture.h"
#include "node.h"
#include "camera.h"

/*
LIGHTING MODEL

Final intensity:                If = Ia + Id + Is
Ambient intensity:              Ia = Al * Am
Ambient intensity of light:     Al
Ambient intensity of material:  Am
Defuse intensity:               Id = Dl * Dm * LambertTerm
Defuse intensity of light:      Dl
Defuse intensity of material:   Dm
LambertTerm:                    max( Normal dot Light, 0.0 )
Specular intensity:             Is = Sm x Sl x pow( max(R dot E, 0.0), f )
Specular intensity of light:    Sl
Specular intensity of material: Sm
*/


/// light_t (A)
class light_t: public node_t
{
	public:
		enum types_e { LT_POINT, LT_SPOT };

	PROPERTY_RW( vec3_t, diffuse_color, GetDiffuseColor, SetDiffuseColor );
	PROPERTY_RW( vec3_t, specular_color, GetSpecularColor, SetSpecularColor );
	PROPERTY_R( types_e, type, GetType );

	friend class point_light_t;
	friend class spot_light_t;



	public:
		light_t( types_e type_ ): node_t(NT_LIGHT), type(type_) {}
};


/// point_light_t
class point_light_t: public light_t
{
	public:
		float radius;

		point_light_t(): light_t(LT_POINT) {}
		void Render();
};


/// spot_light_t
class spot_light_t: public light_t
{
	public:
		camera_t camera;
		texture_t* texture;
		bool casts_shadow;

		spot_light_t(): light_t(LT_SPOT), texture(NULL), casts_shadow(false) { AddChild( &camera ); }
		float GetDistance() const { return camera.GetZFar(); }
		void  SetDistance( float d ) { camera.SetZFar(d); }
		void Render();
};


#endif