#ifndef _SCENE_H_
#define _SCENE_H_

#include "common.h"
#include "light.h"
#include "mesh_node.h"
#include "skybox.h"


namespace scene {

// misc
extern skybox_t skybox;
inline vec3_t GetAmbientColor() { return vec3_t( 0.1, 0.05, 0.05 )*1; }

extern void UpdateAllWorldStuff();
extern void UpdateAllSkeletonNodes();


// container_t
/// entities container class
template<typename type_t> class container_t: public vec_t<type_t*>
{
	protected:
		typedef typename vector<type_t*>::iterator iterator_t; ///< Just to save me time from typing

		/**
		 * Register x in this container only. Throw error if its already registered
		 * @param x pointer to the object we want to register
		 */
		void RegisterMe( type_t* x )
		{
			DEBUG_ERR( Search( x ) ); // the obj must not be already loaded

			vec_t<type_t*>::push_back( x );
		}


		/**
		 * Unregister x from this container only
		 * @param x pointer to the object we want to unregister
		 */
		void UnregisterMe( type_t* x )
		{
			uint i;
			for( i=0; i<vec_t<type_t*>::size(); i++ )
			{
				if( (*this)[i] == x )
					break;
			}

			if( i==vec_t<type_t*>::size() )
			{
				ERROR( "Entity is unregistered" );
				return;
			}

			vec_t<type_t*>::erase( vec_t<type_t*>::begin() + i );
		}

	public:
		container_t() {};
		virtual ~container_t() {};

		/**
		 * Search in container by pointer
		 * @param x pointer to the object
		 */
		bool Search( type_t* x )
		{
			for( iterator_t it=vec_t<type_t*>::begin(); it<vec_t<type_t*>::end(); it++ )
			{
				if( x == *it ) return true;
			}
			return false;
		}


		/**
		 * Search in container by name
		 * @param name The name of the resource object
		 */
		type_t* Search( const char* name )
		{
			for( iterator_t it=vec_t<type_t*>::begin(); it<vec_t<type_t*>::end(); it++ )
			{
				if( strcmp( name, (*it)->GetName() ) == 0 )
				return *it;
			}
			return NULL;
		}


		/**
		 * Register x in this container and register it to more containers if needed. Thats why its abstract.
		 * @param: x pointer to an object
		 */
		virtual void Register( type_t* x ) = 0;

		/**
		 * See Register
		 * @param: x pointer to an object
		 */
		virtual void Unregister( type_t* x ) = 0;

}; // end class container_t



// conaiteners
class container_node_t: public container_t<node_t>
{
	public:
		void Register( node_t* x );
		void Unregister( node_t* x );
};

class container_light_t: public container_t<light_t>
{
	public:
		void Register( light_t* x );
		void Unregister( light_t* x );
};

class container_camera_t: public container_t<camera_t>
{
	public:
		void Register( camera_t* x );
		void Unregister( camera_t* x );
};

class container_mesh_node_t: public container_t<mesh_node_t>
{
	public:
		void Register( mesh_node_t* x );
		void Unregister( mesh_node_t* x );
};

class container_skel_node_t: public container_t<skel_node_t>
{
	public:
		void Register( skel_node_t* x );
		void Unregister( skel_node_t* x );
};


extern container_node_t       nodes;
extern container_light_t      lights;
extern container_camera_t     cameras;
extern container_mesh_node_t  mesh_nodes;
extern container_skel_node_t  skel_nodes;


} // end namespace
#endif