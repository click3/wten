#include "stdafx.h"

namespace wten {

using namespace utility;
using namespace boost::assign;

namespace {

boost::shared_ptr<JobList> instance;

boost::shared_ptr<const Job> CreateJob(unsigned int id, boost::shared_ptr<const std::string> name,
		unsigned int hp_base, unsigned int hp_count_bonus,
		unsigned int str, unsigned int iq, unsigned int pie,
		unsigned int vit, unsigned int agi, unsigned int luk, unsigned int thief_skill,
		unsigned int exp_base,
		const std::vector<boost::tuple<unsigned int, boost::shared_ptr<const actions::SpellBase> > >& spells)
{
	return boost::shared_ptr<const Job>(new Job(id,  name, hp_base, hp_count_bonus, str, iq, pie, vit, agi, luk, thief_skill, exp_base, spells));
}

#pragma pack(push, 4)
#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
template <typename Iterator>
struct JobListCSVParser : boost::spirit::qi::grammar<Iterator, std::vector<boost::shared_ptr<const Job> >()> {
	JobListCSVParser() :
		JobListCSVParser::base_type(root)
	{
		namespace qi = boost::spirit::qi;
		using qi::char_;
		using qi::lexeme;
		using qi::uint_;
		using qi::int_;

		quoted_string = lexeme['"' >> +(char_ - '"') >> '"'][qi::_val = boost::phoenix::bind(&StrV2Ptr, qi::_1)];
		unquoted_string = (+(char_ - ',' - '"'))[qi::_val = boost::phoenix::bind(&StrV2Ptr, qi::_1)];
		string = quoted_string | unquoted_string;
		comment_line = "//" >> *(char_ - '\n') >> -char_('\n');
		empty_line = '\n';
		data_line = (uint_ >> ',' >> string >> ','
			>> uint_ >> ',' >> uint_ >> ','
			>> uint_ >> ',' >> uint_ >> ',' >> uint_ >> ','
			>> uint_ >> ',' >> uint_ >> ',' >> uint_ >> ',' >> uint_ >> ','
			>> uint_ >> -char_('\n'))
			[qi::_val = boost::phoenix::bind(&CreateJob, qi::_1, qi::_2, qi::_3, qi::_4, qi::_5, qi::_6, qi::_7, qi::_8, qi::_9, qi::_10, qi::_11,
				qi::_12, std::vector<boost::tuple<unsigned int, boost::shared_ptr<const actions::SpellBase> > >())];
		line = *(comment_line | empty_line) >> data_line;
		root = +(line) >> *(comment_line | empty_line);
	}
	boost::spirit::qi::rule<Iterator, boost::shared_ptr<const std::string>()> quoted_string;
	boost::spirit::qi::rule<Iterator, boost::shared_ptr<const std::string>()> unquoted_string;
	boost::spirit::qi::rule<Iterator, boost::shared_ptr<const std::string>()> string;
	boost::spirit::qi::rule<Iterator> comment_line;
	boost::spirit::qi::rule<Iterator> empty_line;
	boost::spirit::qi::rule<Iterator, boost::shared_ptr<const Job>()> data_line;
	boost::spirit::qi::rule<Iterator, boost::shared_ptr<const Job>()> line;
	boost::spirit::qi::rule<Iterator, std::vector<boost::shared_ptr<const Job> >() > root;
};
#pragma warning(pop)
#pragma pack(pop)

std::vector<boost::shared_ptr<const Job> > ReadJob(const std::string &path) {
	typedef std::vector<char>::const_iterator Iterator;
	typedef JobListCSVParser<Iterator> Parser;

	std::vector<char> data;
	boost::optional<boost::shared_ptr<Error> > error = FileRead(path, &data);
	BOOST_ASSERT(!error);
	Iterator first = data.begin();
	const Iterator last = data.end();

	Parser rule;
	std::vector<boost::shared_ptr<const Job> > result;
	const bool parse_result = boost::spirit::qi::parse(first, last, rule, result);
	BOOST_ASSERT(parse_result);
	BOOST_ASSERT(first == last);
	return result;
}

} // anonymous

JobList::JobList(const std::vector<boost::shared_ptr<const Job> >& list) :
	list(list)
{
	BOOST_FOREACH(boost::shared_ptr<const Job> job, this->list) {
		BOOST_ASSERT(job);
	}
}

JobList::~JobList() {
}

//static
boost::shared_ptr<JobList> JobList::GetCurrentInstance(void) {
	if(!instance) {
		// TODO ‚¨‚¢‚¾‚µ
		const char *path = "data/job/job_list.csv";
		std::vector<boost::shared_ptr<const Job> > list = ReadJob(path);
		instance.reset(new JobList(list));
		BOOST_ASSERT(instance);
	}
	return instance;
}

std::vector<boost::shared_ptr<const Job> > JobList::GetList(void) const {
	return list;
}

std::vector<boost::shared_ptr<const Job> >::const_iterator JobList::Begin(void) const {
	return list.begin();
}

std::vector<boost::shared_ptr<const Job> >::const_iterator JobList::End(void) const {
	return list.end();
}

} // wten
