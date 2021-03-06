#pragma once
#include "help_func.hpp"
#include "client_class.hpp"
#include "net_vars.h"
#include "move_type.hpp"

#include <string>



//实例类
class entity_class
{
public:
	//判断该实例是否是处于休眠状态
	constexpr bool is_dormant() noexcept
	{
		return call_virtual_method<bool>(this + 8, 9);
	}

	//获取该实例的客户数据类
	constexpr client_class_struct* get_client_class() noexcept
	{
		return call_virtual_method<client_class_struct*>(this + 8, 2);
	}

	//判断玩家是否死亡
	constexpr bool is_alive() noexcept
	{
		return call_virtual_method<bool>(this, 155) && get_health() > 0;
	}

	//根据句柄获取实例
	constexpr auto get_entity_from_handle(int handle) noexcept
	{
		return call_virtual_method<entity_class*, int>(this, 4, handle);
	}

	//设置模型索引
	constexpr void set_model_index(int index) noexcept
	{
		call_virtual_method<void, int>(this, 75, index);
	}

	//更新数据
	constexpr void pre_data_update(int updateType) noexcept
	{
		call_virtual_method<void, int>(this + 8, 6, updateType);
	}

	//获取当前的武器
	constexpr entity_class* get_active_weapon() noexcept
	{
		return call_virtual_method<entity_class*>(this, 267);
	}

	//获取武器的不正确率
	constexpr float get_inaccuracy() noexcept
	{
		return call_virtual_method<float>(this, 482);
	}

	//获取自瞄punch
	auto get_aim_punch() noexcept
	{
		self_vector_struct vec;
		call_virtual_method<void>(this, 345, std::ref(vec));
		return vec;
	}

	//是否是狙击枪
	constexpr bool is_sniper_rifle() noexcept
	{
		switch (get_client_class()->classId) 
		{
		case classId_enum::Ssg08:
		case classId_enum::Awp:
		case classId_enum::Scar20:
		case classId_enum::G3sg1:
			return true;
		default: return false;
		}
	}

	//判断是否是敌人
	bool is_enemy() noexcept;

	//判断玩家是否在视线中
	bool is_visiable(const self_vector_struct& position) noexcept;

	//获取人物视线方位
	self_vector_struct get_eye_position() noexcept;

	//获取骨骼的位置
	self_vector_struct get_bone_position(int bone = 8) noexcept;

	//初始化人物骨骼
	constexpr bool setup_bones(matrix3x4_class* out, int max_bones, int bone_mask, float current_time) noexcept;

public:

	NETVAR(get_origin, "CBaseEntity", "m_vecOrigin", self_vector_struct)//玩家的地图位置
	NETVAR(get_health, "CBasePlayer", "m_iHealth", int)//获取玩家血量
	NETVAR_OFFSET(get_index, "CBaseEntity", "m_bIsAutoaimTarget", 4, int)//获取索引
	NETVAR(get_weapons, "CBaseCombatCharacter", "m_hMyWeapons", int[48])//武器信息
	NETVAR(get_item_definition_index, "CBaseAttributableItem", "m_iItemDefinitionIndex", short)//获取武器定义索引
	NETVAR(get_item_id_high, "CBaseAttributableItem", "m_iItemIDHigh", int)//
	NETVAR(get_account_id, "CBaseAttributableItem", "m_iAccountID", int)//
	NETVAR(get_fallback_paint_kit, "CBaseAttributableItem", "m_nFallbackPaintKit", unsigned)//
	NETVAR(get_view_model, "CBasePlayer", "m_hViewModel[0]", int)//
	NETVAR(get_weapon, "CBaseViewModel", "m_hWeapon", int)//
	NETVAR(get_entity_quality, "CBaseAttributableItem", "m_iEntityQuality", int)//
	NETVAR(get_fallback_seed, "CBaseAttributableItem", "m_nFallbackSeed", unsigned)//
	NETVAR(get_fallback_stat_trak, "CBaseAttributableItem", "m_nFallbackStatTrak", unsigned)//
	NETVAR(get_fallback_wear, "CBaseAttributableItem", "m_flFallbackWear", float)//
	NETVAR(get_tick_base, "CBasePlayer", "m_nTickBase", int)//
	NETVAR(get_is_scoped, "CCSPlayer", "m_bIsScoped", bool)//判断玩家是否处于开镜状态
	NETVAR(get_next_attack, "CBaseCombatCharacter", "m_flNextAttack", float)//下一次攻击的时间
	NETVAR(get_flags, "CBasePlayer", "m_fFlags", int)//人物状态标识
	NETVAR_OFFSET(get_move_type, "CBaseEntity", "m_nRenderMode", 1, move_type_enum)//获取人物移动类型
	NETVAR(get_model_index, "CBaseEntity", "m_nModelIndex", unsigned)//
	NETVAR(get_weapon_world_model, "CBaseCombatWeapon", "m_hWeaponWorldModel", int)//
	NETVAR(is_gun_game_immunity, "CCSPlayer", "m_bGunGameImmunity", bool)//枪战免疫
	NETVAR(is_clip, "CBaseCombatWeapon", "m_iClip1", int)//不是枪械
	NETVAR(get_next_primary_attack, "CBaseCombatWeapon", "m_flNextPrimaryAttack", float)//下一次主要攻击

};