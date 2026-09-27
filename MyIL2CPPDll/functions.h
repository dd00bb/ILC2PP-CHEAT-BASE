#pragma once
#include "includes.h"
namespace Functions
{
	#pragma region Hooks

	void(UNITY_CALLING_CONVENTION StartAuthentication_o)(void*);
	void StartAuthentication_hk(void* this_ptr)
	{
		if (!vars::ptr)
		{
			vars::ptr = this_ptr;
			printf("StartAuthentication Found ptr: %p\n", vars::ptr);
		}

		return StartAuthentication_o(this_ptr);
	}

	#pragma endregion

	#pragma region Game Functions

	void UnlockAchievement(void* this_ptr, int id, void* callback)
	{
		void (UNITY_CALLING_CONVENTION u)(void*, int, void*);
		return reinterpret_cast<decltype(u)>(offsets::UnlockAchievement)(this_ptr,id,callback);
	}

	#pragma endregion

	#pragma region Custom Functions
	
	#pragma endregion
}