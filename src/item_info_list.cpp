#include "stdafx.h"

namespace wten {

using namespace utility;
using namespace boost::assign;

namespace {

boost::shared_ptr<ItemInfoList> instance;

struct item_types_ : boost::spirit::qi::symbols<char, ItemInfo::ITEM_TYPE> {
	item_types_() {
		add
			("WEAPON",	ItemInfo::ITEM_TYPE_WEAPON)
			("SHIELD",	ItemInfo::ITEM_TYPE_SHIELD)
			("ARMOR",	ItemInfo::ITEM_TYPE_ARMOR)
			("HELMET",	ItemInfo::ITEM_TYPE_HELMET)
			("GAUNTLET",	ItemInfo::ITEM_TYPE_GAUNTLET)
			("ADORNMENT",	ItemInfo::ITEM_TYPE_ADORNMENT)
			("TOOL",	ItemInfo::ITEM_TYPE_TOOL)
		;
	}
} item_types_impl;


boost::shared_ptr<const ItemInfo> CreateItemInfo(boost::shared_ptr<const std::wstring> uncertainty_name, boost::shared_ptr<const std::wstring> name,
		boost::shared_ptr<const std::wstring> description, unsigned int sale_price, unsigned int price,
		ItemInfo::ITEM_TYPE item_type, unsigned int atk_base, unsigned int atk_count, unsigned int atk_bonus,
		unsigned int hit, unsigned int hit_count, int ac, unsigned int broken_probability)
{
	unsigned int id = 0;
	std::vector<boost::shared_ptr<const Job> > equip_possible;
	std::vector<boost::tuple<Action::ACTION_TYPE, unsigned int> > element_resist;
	std::vector<boost::tuple<EnemyInfo::MONSTER_TYPE, unsigned int> > monster_resist;
	std::vector<boost::tuple<CharCondition::CONDITION, unsigned int> > condition_resist;
	return boost::shared_ptr<const ItemInfo>(
		new ItemInfo(
			id, uncertainty_name, name,
			description, sale_price, price,
			item_type, atk_base, atk_count, atk_bonus,
			hit, hit_count, ac, broken_probability, equip_possible, element_resist, monster_resist, condition_resist)
	);
}

#pragma pack(push, 4)
#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
template <typename Iterator>
struct ItemInfoListCSVParser : ListCSVParserBase<Iterator, boost::shared_ptr<const ItemInfo> > {
	ItemInfoListCSVParser() {
		namespace qi = boost::spirit::qi;
		using qi::char_;
		using qi::uint_;
		using qi::int_;

		quoted_item_types = '"' >> item_types_impl >> '"';
		item_types = quoted_item_types | item_types_impl;
		data_line = (string >> ',' >> string >> ','
			>> string >> ',' >> uint_ >> ',' >> uint_ >> ','
			>> item_types >> ',' >> uint_ >> ',' >> uint_ >> ',' >> uint_ >> ','
			>> uint_ >> ',' >> uint_ >> ',' >> int_ >> ',' >> uint_ >> -char_('\n'))
			[qi::_val = boost::phoenix::bind(&CreateItemInfo, qi::_1, qi::_2, qi::_3, qi::_4, qi::_5, qi::_6, qi::_7, qi::_8, qi::_9, qi::_10, qi::_11, qi::_12, qi::_13)];
		Initialize(data_line);
	}

	boost::spirit::qi::rule<Iterator, ItemInfo::ITEM_TYPE()> quoted_item_types;
	boost::spirit::qi::rule<Iterator, ItemInfo::ITEM_TYPE()> item_types;
	boost::spirit::qi::rule<Iterator, boost::shared_ptr<const ItemInfo>()> data_line;
};
#pragma warning(pop)
#pragma pack(pop)

std::vector<boost::shared_ptr<const ItemInfo> > ReadItemInfo(const std::string &path) {
	typedef std::vector<wchar_t>::const_iterator Iterator;
	typedef ItemInfoListCSVParser<Iterator> Parser;
	std::vector<boost::shared_ptr<const ItemInfo> > result;

	std::vector<wchar_t> data;
	boost::optional<boost::shared_ptr<Error> > error = UTF8FileRead(path, &data);
	if(error) {
		error.get()->Abort();
		BOOST_ASSERT(false);
		return result;
	}
	Iterator first = data.begin();
	const Iterator last = data.end();

	Parser rule;
	const bool parse_result = boost::spirit::qi::parse(first, last, rule, result);
	BOOST_ASSERT(parse_result);
	BOOST_ASSERT(first == last);
	return result;
}

} // anonymous

ItemInfoList::ItemInfoList(const std::vector<boost::shared_ptr<const ItemInfo> >& list) :
	list(list)
{
	BOOST_FOREACH(boost::shared_ptr<const ItemInfo> info, this->list) {
		BOOST_ASSERT(info);
	}
}

ItemInfoList::~ItemInfoList() {
}

//static
boost::shared_ptr<ItemInfoList> ItemInfoList::GetCurrentInstance(void) {
	if(!instance) {
		// TODO ‚¨‚¢‚¾‚µ
		const char *path = "data/item/item_info_list.csv";
		std::vector<boost::shared_ptr<const ItemInfo> > list = ReadItemInfo(path);
		instance.reset(new ItemInfoList(list));
		BOOST_ASSERT(instance);
	}
	return instance;
}

std::vector<boost::shared_ptr<const ItemInfo> > ItemInfoList::GetList(void) const {
	return list;
}

std::vector<boost::shared_ptr<const ItemInfo> >::const_iterator ItemInfoList::Begin(void) const {
	return list.begin();
}

std::vector<boost::shared_ptr<const ItemInfo> >::const_iterator ItemInfoList::End(void) const {
	return list.end();
}

} // wten
