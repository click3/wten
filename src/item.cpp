#include "stdafx.h"

namespace wten {

Item::Item(boost::shared_ptr<const ItemInfo> info, CONDITION condition) :
	info(info), condition(condition)
{
	BOOST_ASSERT(info);
}

Item::~Item() {
}

bool Item::IsUncertain() const {
	return (GetCondition() < CONDITION_NORMAL);
}

bool Item::IsEquip() const {
	switch(GetCondition()) {
		case CONDITION_UNCERTAIN_EQUIP:
		case CONDITION_UNCERTAIN_EQUIP_CURSE:
		case CONDITION_EQUIP:
		case CONDITION_EQUIP_CURSE:
			break;
		default:
			return false;
	}
	return true;
}

boost::shared_ptr<const std::string> Item::GetName() const {
	BOOST_ASSERT(info);
	if(IsUncertain()) {
		return info->GetUncertaintyName();
	}
	return info->GetName();
}

boost::optional<boost::shared_ptr<const std::string> > Item::GetDescription() const {
	BOOST_ASSERT(info);
	if(IsUncertain()) {
		return boost::none;
	}
	return info->GetDescription();
}

unsigned int Item::GetSalePrice() const {
	BOOST_ASSERT(info);
	return info->GetSalePrice();
}

unsigned int Item::GetPrice() const {
	BOOST_ASSERT(info);
	return info->GetPrice();
}

ItemInfo::ITEM_TYPE Item::GetItemType() const {
	BOOST_ASSERT(info);
	return info->GetItemType();
}

std::vector<unsigned int> Item::CalcAtkDamage(unsigned int hit_count) const {
	BOOST_ASSERT(info);
	return info->CalcAtkDamage(hit_count);
}

unsigned int Item::GetHit() const {
	BOOST_ASSERT(info);
	unsigned int result = info->GetHit();
	if(IsUncertain()) {
		result -= 1;
	}
	return result;
}

unsigned int Item::GetHitCount() const {
	BOOST_ASSERT(info);
	return info->GetHitCount();
}

int Item::GetAC() const {
	BOOST_ASSERT(info);
	unsigned int result = info->GetAC();
	if(IsUncertain()) {
		result += 1;
	}
	return result;
}

bool Item::IsEquipPossible(boost::shared_ptr<const Job> job) const {
	BOOST_ASSERT(info);
	return info->IsEquipPossible(job);
}

Item::CONDITION Item::GetCondition() const {
	return condition;
}

boost::optional<boost::shared_ptr<Error> > Item::UseBattle(boost::shared_ptr<CharData> charcter, boost::shared_ptr<PTData> pt, boost::shared_ptr<EnemyPTData> enemy_pt) {
	// TODO;
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > Item::UseField(boost::shared_ptr<CharData> charcter, boost::shared_ptr<PTData> pt) {
	// TODO
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > Item::EquipStatus(boost::shared_ptr<CharData> charcter) const {
	// TODO
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > Item::PossessionStatus(boost::shared_ptr<CharData> charcter) const {
	// TODO
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > Item::OnEquip(boost::shared_ptr<CharData> charcter) {
	switch(GetCondition()) {
		case CONDITION_UNCERTAIN_BROKEN:
		case CONDITION_BROKEN:
			return CREATE_ERROR(ERROR_CODE_ITEM_BROKEN);
		case CONDITION_UNCERTAIN_EQUIP:
		case CONDITION_UNCERTAIN_EQUIP_CURSE:
		case CONDITION_UNCERTAIN_ADHESION_CURSE:
		case CONDITION_EQUIP:
		case CONDITION_EQUIP_CURSE:
			return CREATE_ERROR(ERROR_CODE_ITEM_EQUIPED);
		case CONDITION_UNCERTAIN:
			condition = CONDITION_UNCERTAIN_EQUIP;
			break;
		case CONDITION_UNCERTAIN_CURSE:
			condition = CONDITION_UNCERTAIN_EQUIP_CURSE;
			break;
		case CONDITION_NORMAL:
			condition = CONDITION_EQUIP;
			break;
		case CONDITION_CURSE:
			condition = CONDITION_EQUIP_CURSE;
			break;
		default:
			BOOST_ASSERT(false);
			return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > Item::OnDetach() {
	switch(GetCondition()) {
		case CONDITION_UNCERTAIN_BROKEN:
		case CONDITION_BROKEN:
			return CREATE_ERROR(ERROR_CODE_ITEM_BROKEN);
		case CONDITION_UNCERTAIN_EQUIP_CURSE:
		case CONDITION_UNCERTAIN_ADHESION_CURSE:
		case CONDITION_EQUIP_CURSE:
			return CREATE_ERROR(ERROR_CODE_ITEM_CURSE);
		case CONDITION_UNCERTAIN:
		case CONDITION_UNCERTAIN_CURSE:
		case CONDITION_NORMAL:
		case CONDITION_CURSE:
			return CREATE_ERROR(ERROR_CODE_ITEM_NONE_EQUIPED);
		case CONDITION_UNCERTAIN_EQUIP:
			condition = CONDITION_UNCERTAIN;
			break;
		case CONDITION_EQUIP:
			condition = CONDITION_NORMAL;
			break;
		default:
			BOOST_ASSERT(false);
			return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > Item::OnIdentification(boost::shared_ptr<CharData> charcter) {
	switch(GetCondition()) {
		case CONDITION_NORMAL:
		case CONDITION_CURSE:
		case CONDITION_EQUIP:
		case CONDITION_EQUIP_CURSE:
		case CONDITION_BROKEN:
			return CREATE_ERROR(ERROR_CODE_ITEM_CERTAIN);
		case CONDITION_UNCERTAIN_EQUIP:
		case CONDITION_UNCERTAIN_EQUIP_CURSE:
		case CONDITION_UNCERTAIN_ADHESION_CURSE:
			return CREATE_ERROR(ERROR_CODE_ITEM_EQUIPED);
		case CONDITION_UNCERTAIN:
		case CONDITION_UNCERTAIN_CURSE:
		case CONDITION_UNCERTAIN_BROKEN:
			// TODO ä”íËê¨î€îªíË
			if(true) {
				condition = CONDITION_NORMAL;
			} else {
				// TODO ëïîıâ¬î€îªíË
				if(false) {
					condition = CONDITION_UNCERTAIN_EQUIP_CURSE;
				} else {
					condition = CONDITION_UNCERTAIN_ADHESION_CURSE;
				}
			}
			break;
		default:
			BOOST_ASSERT(false);
			return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > Item::OnDispel(boost::shared_ptr<CharData> charcter) {
	switch(GetCondition()) {
		case CONDITION_UNCERTAIN:
		case CONDITION_UNCERTAIN_CURSE:
		case CONDITION_UNCERTAIN_BROKEN:
		case CONDITION_NORMAL:
		case CONDITION_CURSE:
		case CONDITION_BROKEN:
			return CREATE_ERROR(ERROR_CODE_ITEM_NONE_EQUIPED);
		case CONDITION_UNCERTAIN_EQUIP:
		case CONDITION_EQUIP:
			return CREATE_ERROR(ERROR_CODE_ITEM_NONE_CURSE);
		case CONDITION_UNCERTAIN_EQUIP_CURSE:
		case CONDITION_UNCERTAIN_ADHESION_CURSE:
		case CONDITION_EQUIP_CURSE:
			// TODO âéÙê¨î€îªíË
			if(true) {
				// ïÅí ÇÕîjâÛÇ≥ÇÍÇÈÇ™îOÇÃÇΩÇﬂéÙÇ¢ñ≥ÇµèÛë‘Ç…ñﬂÇµÇƒÇ®Ç≠
				if(CONDITION_EQUIP_CURSE) {
					condition = CONDITION_NORMAL;
				} else {
					condition = CONDITION_UNCERTAIN;
				}
			} else {
				return CREATE_ERROR(ERROR_CODE_ITEM_DISPEL_FAILURE);
			}
			break;
		default:
			BOOST_ASSERT(false);
			return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	return boost::none;
}

} // wten
